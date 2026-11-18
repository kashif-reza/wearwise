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

    void WearWiseSystem::loadHistory() {
        historyRecords.clear();
        ifstream file(HISTORY_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() >= 3) {
                historyRecords.push_back({p[0], p[1], p[2]});
            }
        }
    }

    void WearWiseSystem::saveHistory() {
        ofstream out(HISTORY_FILE);
        for (const auto& h : historyRecords) {
            out << h.date << "|" << h.outfitDetails << "|" << h.occasion << "\n";
        }
    }

    void WearWiseSystem::showHistory() {
        cout << "\n======================================================================\n";
        cout << "                     OUTFIT USAGE HISTORY                             \n";
        cout << "======================================================================\n";
        for (const auto& rec : historyRecords) {
            cout << " Date: " << left << setw(12) << rec.date << " | Event: " << setw(14)
                 << rec.occasion << " | " << rec.outfitDetails << "\n";
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Options: [1] Log a Worn Outfit  [0] Go Back\nChoice: ";
        int ch;
        if (!(cin >> ch) || ch == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        cin.ignore();
        PlannerRecord entry;
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, entry.date);
        cout << "Occasion: ";
        getline(cin, entry.occasion);
        cout << "Outfit Worn: ";
        getline(cin, entry.outfitDetails);
        if (entry.date.empty() || entry.occasion.empty() || entry.outfitDetails.empty()) {
            cout << "All fields are required. Nothing was saved.\n";
            return;
        }
        historyRecords.push_back(entry);
        saveHistory();
        cout << "[SUCCESS] Worn outfit logged!\n";
    }

    void WearWiseSystem::wardrobeInsights() {
        cout << "\n======================================================================\n";
        cout << "                         WARDROBE INSIGHTS                            \n";
        cout << "======================================================================\n";
        if (historyRecords.empty()) {
            cout << "No outfit history yet. Log outfits from My Wardrobe & Outfit History first.\n";
            cout << "Press Enter to return...";
            cin.ignore(10000, '\n');
            cin.get();
            return;
        }

        struct ItemUsage { const ClothingItem* item; int wears; string lastWorn; };
        vector<ItemUsage> usage;
        for (const auto& item : clothingCatalogue) {
            if (!item.isOwned) continue;
            int count = 0;
            string latest;
            for (const auto& record : historyRecords) {
                if (containsIgnoreCase(record.outfitDetails, item.name)) {
                    ++count;
                    if (record.date > latest) latest = record.date;
                }
            }
            usage.push_back({&item, count, latest});
        }
        sort(usage.begin(), usage.end(), [](const ItemUsage& a, const ItemUsage& b) {
            return a.wears > b.wears;
        });

        cout << "\nMOST-WORN ITEMS\n";
        int shown = 0;
        for (const auto& entry : usage) {
            if (entry.wears == 0) continue;
            cout << " - " << entry.item->name << ": " << entry.wears
                 << " time(s), last logged " << entry.lastWorn << "\n";
            if (++shown == 5) break;
        }
        if (shown == 0) cout << " - No owned items matched the names in your history yet.\n";

        cout << "\nNEVER-WORN OWNED ITEMS\n";
        shown = 0;
        for (auto it = usage.rbegin(); it != usage.rend() && shown < 5; ++it) {
            if (it->wears == 0) {
                cout << " - " << it->item->name << "\n";
                ++shown;
            }
        }
        if (shown == 0) cout << " - Every owned item appears in your logged outfits.\n";

        cout << "\nCOST PER WEAR\n";
        for (const auto& entry : usage) {
            if (entry.wears > 0 && entry.item->price > 0)
                cout << " - " << entry.item->name << ": $" << fixed << setprecision(2)
                     << entry.item->price / entry.wears << " per logged wear\n";
        }

        cout << "\nMOST-REPEATED OUTFITS\n";
        vector<pair<string, int>> combinations;
        for (const auto& record : historyRecords) {
            auto it = find_if(combinations.begin(), combinations.end(), [&](const auto& p) {
                return p.first == record.outfitDetails;
            });
            if (it == combinations.end()) combinations.push_back({record.outfitDetails, 1});
            else ++it->second;
        }
        sort(combinations.begin(), combinations.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
        for (size_t i = 0; i < min<size_t>(3, combinations.size()); ++i)
            cout << " - " << combinations[i].first << " (" << combinations[i].second << " time(s))\n";

        cout << "\nInsights depend on accurately logging garment names in each outfit.\n";
        cout << "Press Enter to return...";
        cin.ignore(10000, '\n');
        cin.get();
    }
