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

    void WearWiseSystem::loadBudget() {
        ifstream file(BUDGET_FILE);
        if (file.good()) {
            file >> monthlyBudget >> totalExpenditure;
        }
    }

    void WearWiseSystem::saveBudget() {
        ofstream out(BUDGET_FILE);
        out << fixed << setprecision(2) << monthlyBudget << " " << totalExpenditure << "\n";
    }

    void WearWiseSystem::budgetAdvisor() {
    cout << "\n------------------------------------------------------------------\n";
    cout << " OPTIONAL PURCHASE AWARENESS (STYLE PLANNER)\n";
    cout << "------------------------------------------------------------------\n";
    cout << "This is an optional helper. Wardrobe and outfit planning remain the main focus.\n";
    cout << "Currency display retains the existing $ notation used by the catalogue.\n\n";

    const double remaining = monthlyBudget - totalExpenditure;
    cout << fixed << setprecision(2);
    cout << "Optional spending limit: $" << monthlyBudget << "\n";
    cout << "Recorded purchases:      $" << totalExpenditure << "\n";
    cout << "Remaining limit:         $" << remaining << "\n\n";

    cout << "Owned, ready items that may suit " << user.currentOccasion << ":\n";
    bool foundOwned = false;
    for (const auto& item : clothingCatalogue) {
        const bool groupMatches = toLower(item.targetGroup) == toLower(user.targetGroup)
            || toLower(item.targetGroup) == "unisex";
        const bool occasionMatches = item.occasion.empty()
            || toLower(item.occasion).find(toLower(user.currentOccasion)) != string::npos;
        if (item.isOwned && item.isAvailable && groupMatches && occasionMatches) {
            cout << "  - " << item.name << " (" << item.category << ", " << item.color << ")\n";
            foundOwned = true;
        }
    }
    if (!foundOwned) cout << "  No matching ready owned items found.\n";

    cout << "\n[1] Change optional limit  [2] Record purchase  [0] Back\nChoice: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Returning to planner.\n";
        return;
    }
    cin.ignore(10000, '\n');
    if (choice == 0) return;
    if (choice == 1) {
        double newLimit;
        cout << "Enter optional limit in the displayed currency (>= 0): $";
        if (!(cin >> newLimit) || newLimit < 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid limit. No changes saved.\n";
            return;
        }
        cin.ignore(10000, '\n');
        monthlyBudget = newLimit;
        saveBudget();
        cout << "Optional limit saved.\n";
    } else if (choice == 2) {
        double amount;
        cout << "Purchase amount in the displayed currency (> 0): $";
        if (!(cin >> amount) || amount <= 0) {
            cin.clear(); cin.ignore(10000, '\n');
            cout << "Invalid amount. No purchase recorded.\n";
            return;
        }
        cin.ignore(10000, '\n');
        totalExpenditure += amount;
        saveBudget();
        cout << "Purchase recorded. Remaining optional limit: $"
             << (monthlyBudget - totalExpenditure) << "\n";
        if (totalExpenditure > monthlyBudget)
            cout << "Gentle reminder: recorded purchases exceed your optional limit.\n";
    } else cout << "Unknown option. No changes made.\n";
}
