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

    void WearWiseSystem::generateAIPrompt() {
        cout << "\n======================================================================\n";
        cout << "           AI VIRTUAL TRY-ON PROMPT GENERATOR                         \n";
        cout << "======================================================================\n";
        cin.ignore();
        string topDesc, bottomDesc, shoeDesc, settingDesc;

        cout << "Describe Top Garment (or enter '0' to cancel): ";
        getline(cin, topDesc);
        if (topDesc == "0") return;
        cout << "Describe Bottom Garment: ";
        getline(cin, bottomDesc);
        cout << "Describe Footwear: ";
        getline(cin, shoeDesc);
        cout << "Setting / Environment (e.g. Modern university campus, Office lounge): ";
        getline(cin, settingDesc);

        cout << "\n------------------ GENERATED AI PROMPT (COPY BELOW) ------------------\n";
        cout << "Full-length editorial commercial fashion photograph of a "
             << user.targetGroup << " (" << user.categoryGroup << ") model, height approx "
             << user.heightCm << "cm, proportional build "
             << "with " << user.chestCm << "cm chest/bust and " << user.waistCm << "cm waist. "
             << "Setting: " << settingDesc << ". "
             << "Wearing " << topDesc << " in a " << user.preferredFit << " cut, styled with "
             << bottomDesc << " and " << shoeDesc << ". "
             << "Ultra-sharp 8k resolution, authentic fabric weave and drapery, "
             << "cinematic soft ambient lighting, realistic color balance, true anatomical fidelity.\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "\nPress Enter to return to menu...";
        cin.ignore(1000, '\n');
    }
