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

    bool WearWiseSystem::loadUserProfile() {
        ifstream file(USERS_FILE);
        if (!file.good()) return false;
        string line;
        if (getline(file, line) && !line.empty()) {
            auto p = split(line, '|');
            if (p.size() >= 18) {
                user.name = p[0];
                user.age = stoi(p[1]);
                user.targetGroup = p[2];
                user.categoryGroup = p[3];
                user.heightCm = stod(p[4]);
                user.weightKg = stod(p[5]);
                user.chestCm = stod(p[6]);
                user.waistCm = stod(p[7]);
                user.hipCm = stod(p[8]);
                user.shoulderCm = stod(p[9]);
                user.preferredSize = p[10];
                user.preferredFit = p[11];
                user.favoriteColor1 = p[12];
                user.favoriteColor2 = p[13];
                user.avoidedColor = p[14];
                user.primaryStyle = p[15];
                user.currentOccasion = p[16];
                user.currentSeason = p[17];
                return true;
            }
        }
        return false;
    }

    void WearWiseSystem::saveUserProfile() {
        ofstream out(USERS_FILE);
        out << user.name << "|" << user.age << "|" << user.targetGroup << "|" << user.categoryGroup << "|"
            << fixed << setprecision(1) << user.heightCm << "|" << user.weightKg << "|"
            << user.chestCm << "|" << user.waistCm << "|" << user.hipCm << "|" << user.shoulderCm << "|"
            << user.preferredSize << "|" << user.preferredFit << "|"
            << user.favoriteColor1 << "|" << user.favoriteColor2 << "|" << user.avoidedColor << "|"
            << user.primaryStyle << "|" << user.currentOccasion << "|" << user.currentSeason << "\n";
    }

    void WearWiseSystem::setupProfileWizard() {
        cout << "\n======================================================================\n";
        cout << "                 WEARWISE : USER PROFILE SETUP WIZARD                 \n";
        cout << "======================================================================\n";
        cout << "Select Setup Option:\n";
        cout << " [1] Fast-Track Preset (1-Click Archetype)\n";
        cout << " [2] Custom Manual Setup (Detailed Body Measurements)\n";
        cout << " [0] Go Back\n";
        cout << "Choice: ";
        int choice;
        if (!(cin >> choice) || choice == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        if (choice == 1) {
            cout << "\nSelect Preset Archetype:\n";
            cout << " [1] Men   - Athletic Medium (Smart Casual / University / Office)\n";
            cout << " [2] Women - Slim Small      (Smart Casual / University / Office)\n";
            cout << " [3] Kids  - Active Child     (Casual / Playwear)\n";
            cout << " [0] Go Back\n";
            cout << "Select Preset (0-3): ";
            int p;
            cin >> p;
            cin.ignore();
            if (p == 0) return;

            if (p == 2) {
                user = {"Sophia Lee", 21, "Women", "Adult", 165.0, 53.0, 86.0, 68.0, 92.0, 39.0,
                        "S", "Regular", "Cream", "Burgundy", "Yellow", "Smart Casual", "University", "All-Season"};
            } else if (p == 3) {
                user = {"Leo Junior", 8, "Kids", "Child", 125.0, 25.0, 62.0, 56.0, 64.0, 28.0,
                        "S", "Relaxed", "Blue", "Navy", "Black", "Casual", "Casual", "Summer"};
            } else {
                user = {"Alex Mercer", 22, "Men", "Adult", 178.0, 72.0, 98.0, 82.0, 96.0, 46.0,
                        "M", "Regular", "Navy", "White", "Yellow", "Smart Casual", "University", "All-Season"};
            }
            saveUserProfile();
            cout << "\n[SUCCESS] Profile activated for: " << user.name << " (" << user.targetGroup << ")!\n";
            return;
        }

        cin.ignore();
        cout << "\nEnter Full Name: ";
        getline(cin, user.name);
        cout << "Age: ";
        cin >> user.age;
        cout << "Target Group (Men / Women / Kids): ";
        cin >> user.targetGroup;
        user.categoryGroup = (user.age < 13 || toLower(user.targetGroup) == "kids") ? "Child" : "Adult";
        if (user.categoryGroup == "Child") user.targetGroup = "Kids";

        cout << "Height (cm): ";
        cin >> user.heightCm;
        cout << "Weight (kg): ";
        cin >> user.weightKg;
        cout << "Chest / Bust circumference (cm): ";
        cin >> user.chestCm;
        cout << "Waist circumference (cm): ";
        cin >> user.waistCm;
        cout << "Hip circumference (cm): ";
        cin >> user.hipCm;
        cout << "Shoulder width (cm): ";
        cin >> user.shoulderCm;
        cin.ignore();

        cout << "Preferred Garment Size (XS, S, M, L, XL): ";
        getline(cin, user.preferredSize);
        cout << "Preferred Fit (Slim / Regular / Relaxed): ";
        getline(cin, user.preferredFit);
        cout << "Favorite Color 1: ";
        getline(cin, user.favoriteColor1);
        cout << "Favorite Color 2: ";
        getline(cin, user.favoriteColor2);
        cout << "Color to Avoid: ";
        getline(cin, user.avoidedColor);
        cout << "Fashion Style Goal (Casual, Smart Casual, Formal, Traditional, Sportswear): ";
        getline(cin, user.primaryStyle);

        user.currentOccasion = "University";
        user.currentSeason = "All-Season";

        saveUserProfile();
        cout << "\n[SUCCESS] Custom Profile saved to " << USERS_FILE << "!\n";
    }

    void WearWiseSystem::displayProfile() {
        cout << "\n======================================================================\n";
        cout << "                     MY PROFILE & MEASUREMENTS                        \n";
        cout << "======================================================================\n";
        cout << " Name:           " << user.name << " (" << user.age << " yrs, " << user.targetGroup << " / " << user.categoryGroup << ")\n";
        cout << " Height:         " << user.heightCm << " cm  | Weight: " << user.weightKg << " kg\n";
        cout << " Dimensions:     Chest " << user.chestCm << "cm | Waist " << user.waistCm
             << "cm | Hips " << user.hipCm << "cm | Shoulder " << user.shoulderCm << "cm\n";
        cout << " Preferred Size: " << user.preferredSize << " (" << user.preferredFit << " Fit)\n";
        cout << " Style Goal:     " << user.primaryStyle << "\n";
        cout << " Color Palettes: " << user.favoriteColor1 << ", " << user.favoriteColor2 << " (Avoid: " << user.avoidedColor << ")\n";
        cout << " Active State:   " << user.currentOccasion << " | " << user.currentSeason << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "Options: [1] Switch/Edit Profile  [0] Go Back\nChoice: ";
        int ch;
        if (cin >> ch && ch == 1) {
            cin.ignore();
            setupProfileWizard();
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
