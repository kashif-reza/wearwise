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

    void WearWiseSystem::loadColorRules() {
        colorRules.clear();
        ifstream file(COLORS_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto parts = split(line, '|');
            if (parts.size() >= 2) {
                ColorRule r;
                r.baseColor = parts[0];
                r.complementaryColors = split(parts[1], ',');
                colorRules.push_back(r);
            }
        }
    }

    bool WearWiseSystem::areColorsCompatible(const string& colorA, const string& colorB) {
        if (toLower(colorA) == toLower(colorB)) return true;
        for (const auto& rule : colorRules) {
            if (toLower(rule.baseColor) == toLower(colorA)) {
                for (const auto& match : rule.complementaryColors) {
                    if (toLower(match) == toLower(colorB)) return true;
                }
            }
        }
        return false;
    }

    void WearWiseSystem::exploreColors() {
        cout << "\n======================================================================\n";
        cout << "                     COLOR HARMONY MATRIX                             \n";
        cout << "======================================================================\n";
        for (const auto& rule : colorRules) {
            cout << " " << left << setw(14) << rule.baseColor << " -> ";
            for (size_t i = 0; i < rule.complementaryColors.size(); ++i) {
                cout << rule.complementaryColors[i] << (i + 1 < rule.complementaryColors.size() ? ", " : "");
            }
            cout << "\n";
        }
        cout << "\nYour Favorites: " << user.favoriteColor1 << ", " << user.favoriteColor2 << "\n";
        cout << "Your Avoided:   " << user.avoidedColor << "\n";
        cout << "\nPress Enter to return to menu...";
        cin.ignore();
        cin.get();
    }
