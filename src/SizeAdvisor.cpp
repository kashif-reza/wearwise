#include "WearWiseSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

namespace {
string sizeFromMeasurement(double value, const vector<double>& limits) {
    const vector<string> labels = {"XS", "S", "M", "L", "XL", "XXL"};
    for (size_t i = 0; i < limits.size(); ++i) {
        if (value <= limits[i]) return labels[i];
    }
    return labels.back();
}

string upperText(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return value;
}

void showSizeResult(const string& garment, const string& size, const string& reason) {
    cout << "\n  " << left << setw(15) << garment << ": " << size << "\n";
    cout << "  Basis: " << reason << "\n";
}
}

void WearWiseSystem::recommendClothingSizes() {
    cout << "\n======================================================================\n";
    cout << "                 PERSONAL CLOTHING SIZE ADVISOR                       \n";
    cout << "======================================================================\n";
    cout << "Uses your saved body measurements to estimate garment sizes.\n";
    cout << "Sizes vary by brand, country, fabric and fit; always compare the\n";
    cout << "seller's own size chart before purchasing. These are starting estimates.\n";

    double chest = user.chestCm;
    double waist = user.waistCm;
    double hip = user.hipCm;
    double shoulder = user.shoulderCm;
    double footLength = 0.0;
    double inseam = 0.0;

    cout << "\nYour saved measurements (cm):\n";
    cout << "  Chest/Bust: " << chest << " | Waist: " << waist
         << " | Hips: " << hip << " | Shoulder: " << shoulder << "\n";
    cout << "\nEnter foot length in cm (heel to longest toe) for shoe sizing: ";
    while (!(cin >> footLength) || footLength < 15 || footLength > 35) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a realistic foot length (15-35 cm): ";
    }
    cout << "Enter preferred trouser inseam in cm (0 if unknown): ";
    while (!(cin >> inseam) || inseam < 0 || inseam > 120) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter 0-120 cm: ";
    }

    // Approximate generic body-circumference bands; not a brand-specific standard.
    const vector<double> upperLimits = {84, 92, 100, 108, 116};
    const vector<double> lowerLimits = {68, 76, 84, 92, 100};
    string upperSize = sizeFromMeasurement(chest, upperLimits);
    string lowerWaistSize = sizeFromMeasurement(waist, lowerLimits);
    string lowerHipSize = sizeFromMeasurement(hip, {88, 96, 104, 112, 120});
    string lowerSize = lowerWaistSize;
    if (lowerHipSize > lowerSize) lowerSize = lowerHipSize;

    // Foot-length ranges are approximate adult unisex EU starting points.
    int euShoe = static_cast<int>(round(footLength * 1.5 + 2.0));
    if (euShoe < 35) euShoe = 35;
    if (euShoe > 48) euShoe = 48;

    cout << "\n---------------- YOUR SIZE RECOMMENDATIONS ----------------\n";
    showSizeResult("Shirts / Tops", upperSize,
                   "chest/bust circumference " + to_string(static_cast<int>(chest)) +
                   " cm; shoulder width " + to_string(static_cast<int>(shoulder)) + " cm.");
    showSizeResult("Pants / Jeans", lowerSize,
                   "waist " + to_string(static_cast<int>(waist)) + " cm and hips " +
                   to_string(static_cast<int>(hip)) + " cm; choose the larger fit requirement.");
    showSizeResult("Shoes", "Approx. EU " + to_string(euShoe),
                   "foot length " + to_string(footLength) +
                   " cm. Confirm with the shoe brand's foot-length chart.");
    if (inseam > 0) showSizeResult("Trouser length", to_string(static_cast<int>(inseam)) + " cm inseam",
                                   "your preferred inside-leg measurement.");
    cout << "\nFit preference: " << user.preferredFit
         << " | Saved preferred size: " << user.preferredSize << "\n";

    cout << "\n---------------- CATALOGUE SIZE CHECK ----------------\n";
    bool found = false;
    for (const auto& item : clothingCatalogue) {
        if (item.category != "Upper" && item.category != "Lower" &&
            item.category != "Footwear" && item.category != "Outerwear") continue;
        if (item.targetGroup != user.targetGroup && item.targetGroup != "Unisex") continue;
        string wanted = item.category == "Upper" || item.category == "Outerwear"
                            ? upperSize : (item.category == "Lower" ? lowerSize : "");
        if (item.category == "Footwear") continue; // Catalogue shoe sizes are generic; foot length is the better guide.
        if (wanted.empty()) continue;
        bool available = find(item.sizes.begin(), item.sizes.end(), wanted) != item.sizes.end();
        cout << (available ? "[MATCH] " : "[CHECK] ") << item.name
             << " -> suggested " << wanted << " | listed sizes: ";
        for (size_t i = 0; i < item.sizes.size(); ++i)
            cout << (i ? ", " : "") << item.sizes[i];
        if (!available) cout << " (closest listed size needs checking)";
        cout << "\n";
        found = true;
    }
    if (!found) cout << "No matching catalogue garments found for your profile group.\n";

    cout << "\nNote: These are general fit estimates, not medical/body-shape advice.\n";
    cout << "For the best result, compare chest, waist, hip, shoulder and foot length\n";
    cout << "against the exact product's measurement chart.\n";
    cout << "\nPress Enter to return...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
