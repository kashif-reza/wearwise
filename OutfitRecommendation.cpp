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

    int WearWiseSystem::calculateCompatibilityScore(const ClothingItem& upper, const ClothingItem& lower,
                                    const ClothingItem& foot, vector<string>& breakdown) {
        int score = 0;
        breakdown.clear();

        // 1. Color Harmony (25 pts)
        bool c1 = areColorsCompatible(upper.color, lower.color);
        bool c2 = areColorsCompatible(lower.color, foot.color);
        if (c1 && c2) {
            score += 25;
            breakdown.push_back("Full Color Harmony across all pieces (+25)");
        } else if (c1 || c2) {
            score += 15;
            breakdown.push_back("Partial complementary tone balance (+15)");
        } else {
            score += 5;
            breakdown.push_back("Neutral base pairing (+5)");
        }

        if (toLower(upper.color) == toLower(user.avoidedColor) ||
            toLower(lower.color) == toLower(user.avoidedColor) ||
            toLower(foot.color) == toLower(user.avoidedColor)) {
            score -= 10;
            breakdown.push_back("Penalty: Contains your avoided tone (" + user.avoidedColor + ") (-10)");
        }

        // 2. Fit and Size (20 pts)
        bool uSize = find(upper.sizes.begin(), upper.sizes.end(), user.preferredSize) != upper.sizes.end();
        bool lSize = find(lower.sizes.begin(), lower.sizes.end(), user.preferredSize) != lower.sizes.end();
        if (uSize && lSize) {
            score += 20;
            breakdown.push_back("Exact anatomical size match: " + user.preferredSize + " with " + user.preferredFit + " cut (+20)");
        } else if (uSize || lSize) {
            score += 10;
            breakdown.push_back("Partial size alignment (+10)");
        }

        // 3. Style Goal (20 pts)
        int styleHits = (upper.style == user.primaryStyle) + (lower.style == user.primaryStyle) + (foot.style == user.primaryStyle);
        int stylePoints = (styleHits * 20) / 3;
        score += stylePoints;
        if (styleHits > 0) breakdown.push_back("Style Alignment: Matches " + user.primaryStyle + " (+" + to_string(stylePoints) + ")");

        // 4. Occasion Alignment (15 pts)
        if (containsIgnoreCase(upper.occasion, user.currentOccasion) && containsIgnoreCase(lower.occasion, user.currentOccasion)) {
            score += 15;
            breakdown.push_back("Tailored for " + user.currentOccasion + " (+15)");
        } else if (containsIgnoreCase(upper.occasion, user.currentOccasion) || containsIgnoreCase(lower.occasion, user.currentOccasion)) {
            score += 8;
            breakdown.push_back("Flexible event match (+8)");
        }

        // 5. Personal Color Palette (10 pts)
        if (toLower(upper.color) == toLower(user.favoriteColor1) || toLower(lower.color) == toLower(user.favoriteColor1) ||
            toLower(upper.color) == toLower(user.favoriteColor2) || toLower(lower.color) == toLower(user.favoriteColor2)) {
            score += 10;
            breakdown.push_back("Includes your favorite colors (+10)");
        }

        // 6. Season / Weather Match (10 pts)
        if (containsIgnoreCase(upper.season, user.currentSeason) || containsIgnoreCase(upper.season, "All-Season")) {
            score += 10;
            breakdown.push_back("Appropriate fabric for " + user.currentSeason + " (+10)");
        }

        return max(0, min(100, score));
    }

    void WearWiseSystem::getIdealStylistRecommendation() {
        cout << "\n======================================================================\n";
        cout << "          PURPOSE 1: IDEAL STYLIST & OCCASION RECOMMENDATION          \n";
        cout << "  (Fashion Designer Mode: Generates ideal combinations without        \n";
        cout << "   requiring you to own or store the items in your closet first)      \n";
        cout << "======================================================================\n";
        cout << " Active Situation Filter:\n";
        cout << " - Demographic Section: " << user.targetGroup << "\n";
        cout << " - Occasion/Event:      " << user.currentOccasion << "\n";
        cout << " - Weather/Season:      " << user.currentSeason << "\n";
        cout << " - Preferred Cut:       " << user.preferredFit << "\n";
        cout << "----------------------------------------------------------------------\n";

        struct RankedCombo {
            ClothingItem upper;
            ClothingItem lower;
            ClothingItem foot;
            int score;
            vector<string> breakdown;
        };

        vector<ClothingItem> uppers, lowers, feet;
        // Queries ENTIRE fashion catalogue regardless of isOwned / isAvailable
        for (const auto& item : clothingCatalogue) {
            bool matchesGroup = (toLower(item.targetGroup) == toLower(user.targetGroup) || toLower(item.targetGroup) == "unisex");
            if (matchesGroup) {
                if (item.category == "Upper") uppers.push_back(item);
                if (item.category == "Lower") lowers.push_back(item);
                if (item.category == "Footwear") feet.push_back(item);
            }
        }

        if (uppers.empty() || lowers.empty() || feet.empty()) {
            cout << "Catalogue does not have sufficient items for " << user.targetGroup << ".\n";
            return;
        }

        vector<RankedCombo> validCombos;
        for (const auto& u : uppers) {
            for (const auto& l : lowers) {
                for (const auto& f : feet) {
                    vector<string> reasons;
                    int sc = calculateCompatibilityScore(u, l, f, reasons);
                    validCombos.push_back({u, l, f, sc, reasons});
                }
            }
        }

        sort(validCombos.begin(), validCombos.end(), [](const RankedCombo& a, const RankedCombo& b) {
            return a.score > b.score;
        });

        int limit = min(3, (int)validCombos.size());
        for (int i = 0; i < limit; ++i) {
            cout << "\n[IDEAL OUTFIT " << (i + 1) << "] (Compatibility Score: " << validCombos[i].score << " / 100)\n";
            cout << "  - Top:      " << validCombos[i].upper.name << " [" << validCombos[i].upper.color << ", " << validCombos[i].upper.style << "]\n";
            cout << "  - Bottom:   " << validCombos[i].lower.name << " [" << validCombos[i].lower.color << ", " << validCombos[i].lower.style << "]\n";
            cout << "  - Footwear: " << validCombos[i].foot.name << " [" << validCombos[i].foot.color << "]\n";
            cout << "  Stylist Rationale:\n";
            for (const auto& r : validCombos[i].breakdown) {
                cout << "    * " << r << "\n";
            }
        }
        cout << "\nPress Enter to return to menu...";
        cin.ignore(1000, '\n');
    }

    void WearWiseSystem::getOwnedWardrobeRecommendation() {
        cout << "\n======================================================================\n";
        cout << "           PURPOSE 2: SMART WARDROBE RECOMMENDATION                   \n";
        cout << "  (Closet Mode: Generates outfits strictly from items you OWN         \n";
        cout << "   and marked as CLEAN/READY in your local wardrobe)                  \n";
        cout << "======================================================================\n";

        struct RankedCombo {
            ClothingItem upper;
            ClothingItem lower;
            ClothingItem foot;
            int score;
            vector<string> breakdown;
        };

        vector<ClothingItem> uppers, lowers, feet;
        // Strictly checks isOwned == true and isAvailable == true
        for (const auto& item : clothingCatalogue) {
            if (item.isOwned && item.isAvailable) {
                bool matchesGroup = (toLower(item.targetGroup) == toLower(user.targetGroup) || toLower(item.targetGroup) == "unisex");
                if (matchesGroup) {
                    if (item.category == "Upper") uppers.push_back(item);
                    if (item.category == "Lower") lowers.push_back(item);
                    if (item.category == "Footwear") feet.push_back(item);
                }
            }
        }

        if (uppers.empty() || lowers.empty() || feet.empty()) {
            cout << "Notice: Your wardrobe does not have all necessary pieces clean & ready.\n";
            cout << "Currently ready in your closet:\n";
            cout << " - Clean Tops:     " << uppers.size() << "\n";
            cout << " - Clean Bottoms:  " << lowers.size() << "\n";
            cout << " - Clean Footwear: " << feet.size() << "\n";
            cout << "\nTip: Open Option 5 (My Wardrobe) to mark laundry items as clean,\n";
            cout << "or use Option 1 (Ideal Stylist Recommendation) to get outfit ideas first.\n";
            cout << "\nPress Enter to return...";
            cin.ignore(1000, '\n');
            return;
        }

        vector<RankedCombo> validCombos;
        for (const auto& u : uppers) {
            for (const auto& l : lowers) {
                for (const auto& f : feet) {
                    vector<string> reasons;
                    int sc = calculateCompatibilityScore(u, l, f, reasons);
                    validCombos.push_back({u, l, f, sc, reasons});
                }
            }
        }

        sort(validCombos.begin(), validCombos.end(), [](const RankedCombo& a, const RankedCombo& b) {
            return a.score > b.score;
        });

        int limit = min(3, (int)validCombos.size());
        for (int i = 0; i < limit; ++i) {
            cout << "\n[WARDROBE OUTFIT " << (i + 1) << "] (Score: " << validCombos[i].score << " / 100)\n";
            cout << "  - Top:      " << validCombos[i].upper.name << " (" << validCombos[i].upper.color << ")\n";
            cout << "  - Bottom:   " << validCombos[i].lower.name << " (" << validCombos[i].lower.color << ")\n";
            cout << "  - Footwear: " << validCombos[i].foot.name << " (" << validCombos[i].foot.color << ")\n";
            cout << "  Why this works from your closet:\n";
            for (const auto& r : validCombos[i].breakdown) {
                cout << "    * " << r << "\n";
            }
        }
        cout << "\nPress Enter to return to menu...";
        cin.ignore(1000, '\n');
    }
