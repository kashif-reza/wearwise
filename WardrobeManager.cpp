#include "WearWiseSystem.h"
#include "StringUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <cctype>
using namespace std;

    void WearWiseSystem::loadClothingCatalogue() {
        clothingCatalogue.clear();
        ifstream file(CLOTHING_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() >= 12) {
                ClothingItem item;
                item.id = p[0];
                item.name = p[1];
                item.category = p[2];
                item.targetGroup = p[3];
                item.color = p[4];
                item.sizes = split(p[5], ',');
                item.season = p[6];
                item.occasion = p[7];
                item.style = p[8];
                item.price = stod(p[9]);
                item.isOwned = (p[10] == "1");
                item.isAvailable = (p[11] == "1");
                clothingCatalogue.push_back(item);
            }
        }
    }

    void WearWiseSystem::saveClothingCatalogue() {
        ofstream out(CLOTHING_FILE);
        for (const auto& itm : clothingCatalogue) {
            out << itm.id << "|" << itm.name << "|" << itm.category << "|" << itm.targetGroup << "|"
                << itm.color << "|";
            for (size_t i = 0; i < itm.sizes.size(); ++i) {
                out << itm.sizes[i] << (i + 1 < itm.sizes.size() ? "," : "");
            }
            out << "|" << itm.season << "|" << itm.occasion << "|" << itm.style << "|"
                << fixed << setprecision(2) << itm.price << "|"
                << (itm.isOwned ? "1" : "0") << "|" << (itm.isAvailable ? "1" : "0") << "\n";
        }
    }

    void WearWiseSystem::manageWardrobe() {
        while (true) {
            cout << "\n======================================================================\n";
            cout << "                 MY WARDROBE (" << user.targetGroup << " Section)                     \n";
            cout << "======================================================================\n";
            cout << left << setw(6) << "ID" << setw(34) << "Item Name" << setw(10) << "Group"
                 << setw(10) << "Category" << setw(9) << "Color" << setw(14) << "Status" << "\n";
            cout << "----------------------------------------------------------------------\n";

            for (const auto& itm : clothingCatalogue) {
                if (itm.isOwned) {
                    cout << left << setw(6) << itm.id << setw(34) << itm.name << setw(10) << itm.targetGroup
                         << setw(10) << itm.category << setw(9) << itm.color
                         << (itm.isAvailable ? "[Clean/Ready]" : "[In Laundry]") << "\n";
                }
            }
            cout << "----------------------------------------------------------------------\n";
            cout << "Actions: [1] Toggle Clean/Laundry Status  [2] Add New Item  [0] Go Back\nChoice: ";
            int opt;
            if (!(cin >> opt) || opt == 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }

            if (opt == 1) {
                cout << "Enter Item ID (e.g. M101, W201): ";
                string targetId;
                cin >> targetId;
                cin.ignore();
                bool found = false;
                for (auto& itm : clothingCatalogue) {
                    if (toLower(itm.id) == toLower(targetId)) {
                        itm.isAvailable = !itm.isAvailable;
                        cout << "[UPDATED] " << itm.name << " status is now "
                             << (itm.isAvailable ? "Clean/Ready" : "In Laundry") << "\n";
                        found = true;
                        break;
                    }
                }
                if (found) saveClothingCatalogue();
            } else if (opt == 2) {
                cin.ignore();
                ClothingItem newItem;
                cout << "Item ID: ";
                getline(cin, newItem.id);
                cout << "Garment Name: ";
                getline(cin, newItem.name);
                cout << "Target Group (Men/Women/Kids/Unisex): ";
                getline(cin, newItem.targetGroup);
                cout << "Category (Upper/Lower/Footwear/Outerwear/Accessory; custom categories allowed): ";
                getline(cin, newItem.category);
                cout << "Color: ";
                getline(cin, newItem.color);
                cout << "Sizes (comma-separated): ";
                string sz;
                getline(cin, sz);
                newItem.sizes = split(sz, ',');
                cout << "Season: ";
                getline(cin, newItem.season);
                cout << "Occasions: ";
                getline(cin, newItem.occasion);
                cout << "Style: ";
                getline(cin, newItem.style);
                cout << "Price (purchase price; use 0 if unknown): $";
                cin >> newItem.price;
                newItem.isOwned = true;
                newItem.isAvailable = true;
                clothingCatalogue.push_back(newItem);
                saveClothingCatalogue();
                cout << "[SUCCESS] Saved new item to wardrobe.\n";
            }
        }
    }
