#include "WearWiseSystem.h"
#include "StringUtils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

void WearWiseSystem::clothingCareAssistant() {
    while (true) {
        cout << "\n======================================================================\n";
        cout << "                     CLOTHING CARE ASSISTANT                           \n";
        cout << "======================================================================\n";
        cout << "[1] Fabric care guide\n";
        cout << "[2] Stain removal guide\n";
        cout << "[3] Everyday clothing maintenance tips\n";
        cout << "[0] Back to main menu\n";
        cout << "Choice: ";

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
            ifstream file("fabric_care.txt");
            if (!file) {
                cout << "fabric_care.txt could not be opened. Keep it beside the WearWise executable/project.\n";
                continue;
            }
            vector<vector<string>> rows;
            string line;
            while (getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto fields = split(line, '|');
                if (fields.size() >= 6) rows.push_back(fields);
            }
            if (rows.empty()) {
                cout << "No fabric-care entries are available.\n";
                continue;
            }
            cout << "\nAvailable fabrics:\n";
            for (size_t i = 0; i < rows.size(); ++i)
                cout << " [" << i + 1 << "] " << rows[i][0] << "\n";
            cout << "Choose a fabric number (0 to go back): ";
            size_t index;
            if (!(cin >> index) || index > rows.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid fabric selection.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index == 0) continue;
            const auto& r = rows[index - 1];
            cout << "\n--- " << r[0] << " CARE GUIDE ---\n";
            cout << "Washing:  " << r[1] << "\n";
            cout << "Drying:   " << r[2] << "\n";
            cout << "Ironing:  " << r[3] << "\n";
            cout << "Storage:  " << r[4] << "\n";
            cout << "Extra:    " << r[5] << "\n";
        } else if (choice == 2) {
            ifstream file("stain_guide.txt");
            if (!file) {
                cout << "stain_guide.txt could not be opened. Keep it beside the WearWise executable/project.\n";
                continue;
            }
            vector<vector<string>> rows;
            string line;
            while (getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto fields = split(line, '|');
                if (fields.size() >= 4) rows.push_back(fields);
            }
            if (rows.empty()) {
                cout << "No stain-care entries are available.\n";
                continue;
            }
            cout << "\nCommon stains:\n";
            for (size_t i = 0; i < rows.size(); ++i)
                cout << " [" << i + 1 << "] " << rows[i][0] << "\n";
            cout << "Choose a stain number (0 to go back): ";
            size_t index;
            if (!(cin >> index) || index > rows.size()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid stain selection.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (index == 0) continue;
            const auto& r = rows[index - 1];
            cout << "\n--- " << r[0] << " STAIN GUIDE ---\n";
            cout << "First action: " << r[1] << "\n";
            cout << "Treatment:    " << r[2] << "\n";
            cout << "Avoid:        " << r[3] << "\n";
            cout << "Care reminder: test any treatment on a hidden area first and follow the garment label.\n";
        } else if (choice == 3) {
            ifstream file("maintenance_tips.txt");
            if (!file) {
                cout << "maintenance_tips.txt could not be opened. Keep it beside the WearWise executable/project.\n";
                continue;
            }
            string line;
            cout << "\n--- EVERYDAY MAINTENANCE ---\n";
            int count = 0;
            while (getline(file, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto fields = split(line, '|');
                if (fields.size() >= 2) {
                    cout << "\n" << ++count << ". " << fields[0] << "\n   " << fields[1] << "\n";
                }
            }
            if (count == 0) cout << "No maintenance tips are available.\n";
        } else {
            cout << "Please choose 0, 1, 2, or 3.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}
