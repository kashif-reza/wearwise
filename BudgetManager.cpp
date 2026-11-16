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
        cout << "\n======================================================================\n";
        cout << "                  BUDGET & PURCHASE ADVISOR                           \n";
        cout << "======================================================================\n";
        cout << " Monthly Budget:   $" << fixed << setprecision(2) << monthlyBudget << "\n";
        cout << " Spent to Date:    $" << totalExpenditure << "\n";
        cout << " Remaining Funds:  $" << (monthlyBudget - totalExpenditure) << "\n";
        cout << "----------------------------------------------------------------------\n";

        double remaining = monthlyBudget - totalExpenditure;
        cout << "Catalogue Purchases fitting within your remaining budget:\n";
        for (const auto& itm : clothingCatalogue) {
            bool matches = (toLower(itm.targetGroup) == toLower(user.targetGroup) || toLower(itm.targetGroup) == "unisex");
            if (!itm.isOwned && matches && itm.price <= remaining) {
                cout << " * " << left << setw(30) << itm.name << " [" << itm.category
                     << "] - $" << fixed << setprecision(2) << itm.price << "\n";
            }
        }
        cout << "\nOptions: [1] Adjust Budget  [2] Record Purchase  [0] Go Back\nChoice: ";
        int ch;
        if (!(cin >> ch) || ch == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (ch == 1) {
            cout << "Enter new monthly budget: $";
            cin >> monthlyBudget;
            saveBudget();
        } else if (ch == 2) {
            double spent;
            cout << "Enter purchase amount: $";
            cin >> spent;
            totalExpenditure += spent;
            saveBudget();
        }
        cin.ignore();
    }
