#include "WearWiseSystem.h"
#include "StringUtils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <limits>
using namespace std;

namespace {
string wishlistField(string value) {
    replace(value.begin(), value.end(), '|', '/');
    return trim(value);
}
}

void WearWiseSystem::manageFavoritesAndWishlist() {
    const string favoritesFile = "favorites.txt";
    const string wishlistFile = "wishlist.txt";
    while (true) {
        cout << "\n======================================================================\n";
        cout << "                  MY FAVORITES & PURCHASE WISHLIST                    \n";
        cout << "======================================================================\n";
        cout << "[1] View / add / remove favorite clothes\n";
        cout << "[2] View purchase wishlist\n";
        cout << "[3] Add an item I want to buy\n";
        cout << "[4] Mark a wishlist item as purchased\n";
        cout << "[5] Remove a wishlist item\n";
        cout << "[0] Go Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid menu number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 0) return;

        if (choice == 1) {
            vector<string> favoriteIds;
            ifstream in(favoritesFile);
            string id;
            while (getline(in, id)) if (!trim(id).empty()) favoriteIds.push_back(trim(id));
            cout << "\nMY FAVORITE CLOTHES\n";
            if (favoriteIds.empty()) cout << "No favorites saved yet.\n";
            for (const auto& favoriteId : favoriteIds) {
                auto it = find_if(clothingCatalogue.begin(), clothingCatalogue.end(),
                    [&](const ClothingItem& item) { return item.id == favoriteId; });
                if (it != clothingCatalogue.end())
                    cout << " - " << it->id << " | " << it->name << " (" << it->color << ")\n";
            }
            cout << "[1] Add a favorite by wardrobe item ID  [2] Remove a favorite  [0] Back\nChoice: ";
            int action;
            if (!(cin >> action)) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (action == 1) {
                cout << "\nOWNED WARDROBE ITEMS\n";
                for (const auto& item : clothingCatalogue)
                    if (item.isOwned) cout << item.id << " | " << item.name << "\n";
                cout << "Enter item ID: ";
                getline(cin, id);
                auto it = find_if(clothingCatalogue.begin(), clothingCatalogue.end(),
                    [&](const ClothingItem& item) { return item.id == trim(id) && item.isOwned; });
                if (it == clothingCatalogue.end()) {
                    cout << "That ID is not an owned wardrobe item.\n";
                } else if (find(favoriteIds.begin(), favoriteIds.end(), it->id) != favoriteIds.end()) {
                    cout << "This item is already in your favorites.\n";
                } else {
                    ofstream out(favoritesFile, ios::app);
                    out << it->id << "\n";
                    cout << "[SAVED] " << it->name << " added to favorites.\n";
                }
            } else if (action == 2) {
                cout << "Enter favorite item ID to remove: ";
                getline(cin, id);
                favoriteIds.erase(remove(favoriteIds.begin(), favoriteIds.end(), trim(id)), favoriteIds.end());
                ofstream out(favoritesFile);
                for (const auto& favoriteId : favoriteIds) out << favoriteId << "\n";
                cout << "[UPDATED] Favorites saved.\n";
            }
        } else if (choice == 2) {
            ifstream in(wishlistFile);
            string line;
            double total = 0.0;
            bool any = false;
            cout << "\nTHINGS I WANT TO BUY\n";
            while (getline(in, line)) {
                auto fields = split(line, '|');
                if (fields.size() < 7 || fields[0] != "W") continue;
                any = true;
                double price = 0.0;
                try { price = stod(fields[4]); } catch (...) {}
                if (fields[6] == "Pending") total += price;
                cout << fields[1] << " | " << fields[2] << " | " << fields[3]
                     << " | " << fields[4] << " | Priority: " << fields[5]
                     << " | " << fields[6] << "\n";
            }
            if (!any) cout << "Your purchase wishlist is empty.\n";
            else cout << "Total pending estimated cost: " << fixed << setprecision(2) << total << "\n";
        } else if (choice == 3) {
            string name, category, color, priceText, priority;
            cout << "Item name: "; getline(cin, name);
            cout << "Category (Upper / Lower / Footwear / Outerwear / Accessory): "; getline(cin, category);
            cout << "Preferred color: "; getline(cin, color);
            cout << "Expected price (number): "; getline(cin, priceText);
            cout << "Priority (High / Medium / Low): "; getline(cin, priority);
            double price;
            try { price = stod(priceText); if (price < 0) throw 1; }
            catch (...) { cout << "Invalid price. Item was not saved.\n"; continue; }
            name = wishlistField(name); category = wishlistField(category);
            color = wishlistField(color); priority = wishlistField(priority);
            if (name.empty() || category.empty() || color.empty() || priority.empty()) {
                cout << "All fields are required. Item was not saved.\n";
                continue;
            }
            const string itemId = "WL" + to_string(static_cast<long long>(time(nullptr)));
            ofstream out(wishlistFile, ios::app);
            out << "W|" << itemId << "|" << name << "|" << category << "|"
                << fixed << setprecision(2) << price << "|" << priority << "|Pending\n";
            cout << "[SAVED] Added " << name << " to your purchase wishlist.\n";
        } else if (choice == 4 || choice == 5) {
            vector<string> lines;
            vector<size_t> pendingIndexes;
            ifstream in(wishlistFile);
            string line;
            while (getline(in, line)) {
                auto fields = split(line, '|');
                if (fields.size() >= 7 && fields[0] == "W" &&
                    (choice == 5 || fields[6] == "Pending")) pendingIndexes.push_back(lines.size());
                lines.push_back(line);
            }
            if (pendingIndexes.empty()) {
                cout << (choice == 4 ? "No pending wishlist items to purchase.\n" : "Wishlist is already empty.\n");
                continue;
            }
            cout << "\n";
            for (size_t i = 0; i < pendingIndexes.size(); ++i) {
                auto fields = split(lines[pendingIndexes[i]], '|');
                cout << "[" << i + 1 << "] " << fields[2] << " | " << fields[3]
                     << " | " << fields[4] << " | " << fields[5] << "\n";
            }
            cout << "Select item number (0 to cancel): ";
            size_t selected;
            if (!(cin >> selected) || selected > pendingIndexes.size()) {
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid selection.\n"; continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (selected == 0) continue;
            size_t lineIndex = pendingIndexes[selected - 1];
            auto fields = split(lines[lineIndex], '|');
            if (choice == 4) {
                ClothingItem item{};
                item.id = "OWN" + to_string(static_cast<long long>(time(nullptr)));
                item.name = fields[2];
                item.category = fields[3];
                item.targetGroup = user.targetGroup;
                item.color = fields[3] == "Footwear" ? fields[2] : fields[3];
                item.sizes = {user.preferredSize.empty() ? "One Size" : user.preferredSize};
                item.season = "All-Season";
                item.occasion = "Casual,University";
                item.style = user.primaryStyle;
                try { item.price = stod(fields[4]); } catch (...) { item.price = 0.0; }
                item.isOwned = true;
                item.isAvailable = true;
                cout << "Enter actual color for your new " << item.name << ": ";
                getline(cin, item.color);
                item.color = wishlistField(item.color);
                if (item.color.empty()) item.color = "Unknown";
                clothingCatalogue.push_back(item);
                saveClothingCatalogue();
                fields[6] = "Purchased";
                lines[lineIndex] = "W|" + fields[1] + "|" + fields[2] + "|" + fields[3] + "|" +
                    fields[4] + "|" + fields[5] + "|" + fields[6];
                cout << "[SUCCESS] Added to My Wardrobe and marked as purchased.\n";
            } else {
                lines.erase(lines.begin() + static_cast<long>(lineIndex));
                cout << "[REMOVED] Wishlist item deleted.\n";
            }
            ofstream out(wishlistFile);
            for (const auto& savedLine : lines) out << savedLine << "\n";
        } else {
            cout << "Invalid choice. Please choose 0-5.\n";
        }
    }
}
