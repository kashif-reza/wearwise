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
        cout << "Options: [1] Log Today's Worn Outfit  [0] Go Back\nChoice: ";
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
        historyRecords.push_back(entry);
        saveHistory();
        cout << "[SUCCESS] Worn outfit logged!\n";
    }
