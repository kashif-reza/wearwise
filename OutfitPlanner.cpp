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

    void WearWiseSystem::loadPlanner() {
        plannedOutfits.clear();
        ifstream file(PLANNER_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() >= 3) {
                plannedOutfits.push_back({p[0], p[1], p[2]});
            }
        }
    }

    void WearWiseSystem::savePlanner() {
        ofstream out(PLANNER_FILE);
        for (const auto& p : plannedOutfits) {
            out << p.date << "|" << p.outfitDetails << "|" << p.occasion << "\n";
        }
    }

    void WearWiseSystem::dailyOutfitPlanner() {
        cout << "\n======================================================================\n";
        cout << "                     DAILY OUTFIT PLANNER                             \n";
        cout << "======================================================================\n";
        cout << "Scheduled Plans:\n";
        for (const auto& p : plannedOutfits) {
            cout << " Date: " << left << setw(12) << p.date << " | Event: " << setw(14)
                 << p.occasion << " | Outfit: " << p.outfitDetails << "\n";
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Options: [1] Schedule New Plan  [0] Go Back\nChoice: ";
        int ch;
        if (!(cin >> ch) || ch == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        cin.ignore();
        PlannerRecord rec;
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, rec.date);
        cout << "Occasion: ";
        getline(cin, rec.occasion);
        cout << "Outfit Description: ";
        getline(cin, rec.outfitDetails);
        plannedOutfits.push_back(rec);
        savePlanner();
        cout << "[SUCCESS] Scheduled and saved!\n";
    }
