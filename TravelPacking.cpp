#include "WearWiseSystem.h"
#include "StringUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <limits>
using namespace std;

namespace {
string travelField(string value) {
    replace(value.begin(), value.end(), '|', '/');
    return trim(value);
}
}

void WearWiseSystem::travelPackingPlanner() {
    const string fileName = "travel_packing.txt";
    while (true) {
        cout << "\n======================================================================\n";
        cout << "                    SMART TRAVEL PACKING PLANNER                      \n";
        cout << "======================================================================\n";
        cout << "[1] Create a travel packing plan\n";
        cout << "[2] View and update packing checklists\n";
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
            string destination, travelDate, tripType;
            int days = 0;
            cout << "Destination: ";
            getline(cin, destination);
            cout << "Departure date (YYYY-MM-DD): ";
            getline(cin, travelDate);
            cout << "Number of days: ";
            if (!(cin >> days) || days < 1 || days > 90) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a trip length between 1 and 90 days.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Trip type (Vacation / Business / Adventure / Family visit): ";
            getline(cin, tripType);
            destination = travelField(destination);
            travelDate = travelField(travelDate);
            tripType = travelField(tripType);
            if (destination.empty() || travelDate.empty() || tripType.empty()) {
                cout << "Destination, date, and trip type are required. Nothing was saved.\n";
                continue;
            }

            const string tripId = to_string(static_cast<long long>(time(nullptr)));
            ofstream out(fileName, ios::app);
            if (!out) {
                cout << "Could not open " << fileName << " for writing.\n";
                continue;
            }
            out << "T|" << tripId << "|" << destination << "|" << travelDate << "|"
                << days << "|" << tripType << "\n";

            int tops = min(days, 5);
            int bottoms = min((days + 1) / 2, 4);
            int footwear = 1;
            int outerwear = (containsIgnoreCase(tripType, "adventure") ||
                             containsIgnoreCase(tripType, "business")) ? 1 : 0;
            bool hasTop = false, hasBottom = false, hasFootwear = false, hasOuterwear = false;
            for (const auto& item : clothingCatalogue) {
                if (!item.isOwned) continue;
                if (toLower(item.targetGroup) != toLower(user.targetGroup) &&
                    toLower(item.targetGroup) != "unisex") continue;
                if (item.category == "Upper" && !hasTop) {
                    out << "P|" << tripId << "|" << travelField(item.name) << "|Clothing|" << tops << "|0\n";
                    hasTop = true;
                } else if (item.category == "Lower" && !hasBottom) {
                    out << "P|" << tripId << "|" << travelField(item.name) << "|Clothing|" << bottoms << "|0\n";
                    hasBottom = true;
                } else if (item.category == "Footwear" && !hasFootwear) {
                    out << "P|" << tripId << "|" << travelField(item.name) << "|Footwear|" << footwear << "|0\n";
                    hasFootwear = true;
                } else if (item.category == "Outerwear" && outerwear > 0 && !hasOuterwear) {
                    out << "P|" << tripId << "|" << travelField(item.name) << "|Outerwear|" << outerwear << "|0\n";
                    hasOuterwear = true;
                }
            }
            if (!hasTop) out << "P|" << tripId << "|Suitable tops (not in wardrobe)|Buy / borrow|" << tops << "|0\n";
            if (!hasBottom) out << "P|" << tripId << "|Suitable bottoms (not in wardrobe)|Buy / borrow|" << bottoms << "|0\n";
            if (!hasFootwear) out << "P|" << tripId << "|Comfortable footwear (not in wardrobe)|Buy / borrow|1|0\n";
            if (outerwear > 0 && !hasOuterwear)
                out << "P|" << tripId << "|Weather-appropriate outer layer|Buy / borrow|1|0\n";
            out << "P|" << tripId << "|Underwear|Essentials|" << days << "|0\n";
            out << "P|" << tripId << "|Socks|Essentials|" << days << "|0\n";
            out << "P|" << tripId << "|Toiletries|Essentials|1|0\n";
            out << "P|" << tripId << "|Phone charger|Essentials|1|0\n";
            out << "P|" << tripId << "|ID and travel documents|Essentials|1|0\n";
            out.close();
            cout << "\n[SAVED] Packing plan created for " << destination << ".\n";
            cout << "The checklist uses your owned wardrobe where possible. Quantities are starter estimates; adjust them for your activities and laundry access.\n";
        } else if (choice == 2) {
            ifstream in(fileName);
            vector<string> lines;
            string line;
            vector<vector<string>> trips;
            while (getline(in, line)) {
                lines.push_back(line);
                auto fields = split(line, '|');
                if (fields.size() >= 6 && fields[0] == "T") trips.push_back(fields);
            }
            if (trips.empty()) {
                cout << "No travel plans yet. Create one first.\n";
                continue;
            }
            cout << "\nYOUR TRIPS\n";
            for (size_t i = 0; i < trips.size(); ++i)
                cout << "[" << i + 1 << "] " << trips[i][2] << " | " << trips[i][3]
                     << " | " << trips[i][4] << " day(s) | " << trips[i][5] << "\n";
            cout << "Select a trip number (0 to cancel): ";
            size_t selected;
            if (!(cin >> selected) || selected > trips.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid trip selection.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (selected == 0) continue;
            const string tripId = trips[selected - 1][1];
            vector<size_t> itemLineIndexes;
            cout << "\nPACKING CHECKLIST — " << trips[selected - 1][2] << "\n";
            for (size_t i = 0; i < lines.size(); ++i) {
                auto fields = split(lines[i], '|');
                if (fields.size() >= 6 && fields[0] == "P" && fields[1] == tripId) {
                    itemLineIndexes.push_back(i);
                    cout << "[" << itemLineIndexes.size() << "] "
                         << (fields[5] == "1" ? "[PACKED] " : "[ ] ")
                         << fields[2] << " — " << fields[3] << " — Qty: " << fields[4] << "\n";
                }
            }
            if (itemLineIndexes.empty()) {
                cout << "No checklist items found for this trip.\n";
                continue;
            }
            cout << "Enter item number to toggle packed status (0 to return): ";
            size_t itemChoice;
            if (!(cin >> itemChoice) || itemChoice > itemLineIndexes.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid item number.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (itemChoice == 0) continue;
            size_t lineIndex = itemLineIndexes[itemChoice - 1];
            auto fields = split(lines[lineIndex], '|');
            fields[5] = fields[5] == "1" ? "0" : "1";
            lines[lineIndex] = "P|" + fields[1] + "|" + fields[2] + "|" + fields[3] + "|" + fields[4] + "|" + fields[5];
            ofstream out(fileName);
            for (const auto& savedLine : lines) out << savedLine << "\n";
            cout << "[UPDATED] Packing status saved.\n";
        } else {
            cout << "Invalid choice. Please choose 0, 1, or 2.\n";
        }
    }
}
