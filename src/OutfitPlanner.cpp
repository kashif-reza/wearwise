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
    while (true) {
        cout << "\n======================================================================\n";
        cout << "                     STYLE & OUTFIT PLANNER                           \n";
        cout << "======================================================================\n";
        if (plannedOutfits.empty()) {
            cout << "No plans yet. Create a date-based outfit plan to get started.\n";
        } else {
            cout << "Scheduled Plans:\n";
            for (size_t i = 0; i < plannedOutfits.size(); ++i) {
                const auto& plan = plannedOutfits[i];
                cout << " [" << (i + 1) << "] " << left << setw(12) << plan.date
                     << " | " << setw(14) << plan.occasion
                     << " | " << plan.outfitDetails << "\n";
            }
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "[1] Schedule outfit  [2] Remove plan  [0] Back\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a menu number.\n";
            continue;
        }
        cin.ignore(10000, '\n');
        if (choice == 0) return;

        if (choice == 1) {
            PlannerRecord record;
            cout << "Date (YYYY-MM-DD): ";
            getline(cin, record.date);
            cout << "Occasion (e.g. University, Office, Wedding, Casual, Travel): ";
            getline(cin, record.occasion);
            cout << "Outfit description (items from your wardrobe): ";
            getline(cin, record.outfitDetails);
            if (record.date.empty() || record.occasion.empty() || record.outfitDetails.empty()) {
                cout << "Date, occasion, and outfit description are required. Plan not saved.\n";
                continue;
            }
            const bool duplicate = any_of(plannedOutfits.begin(), plannedOutfits.end(),
                [&](const PlannerRecord& existing) {
                    return existing.date == record.date && existing.occasion == record.occasion;
                });
            if (duplicate) {
                cout << "A plan already exists for this date and occasion. Remove it first to replace it.\n";
                continue;
            }
            plannedOutfits.push_back(record);
            savePlanner();
            cout << "Outfit plan saved.\n";
        } else if (choice == 2) {
            if (plannedOutfits.empty()) {
                cout << "There are no plans to remove.\n";
                continue;
            }
            cout << "Enter plan number to remove (1-" << plannedOutfits.size() << "): ";
            size_t index;
            if (!(cin >> index) || index == 0 || index > plannedOutfits.size()) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "Invalid plan number. Nothing removed.\n";
                continue;
            }
            cin.ignore(10000, '\n');
            plannedOutfits.erase(plannedOutfits.begin() + static_cast<long>(index - 1));
            savePlanner();
            cout << "Plan removed and saved.\n";
        } else {
            cout << "Invalid choice. Please choose 0, 1, or 2.\n";
        }
    }
}
