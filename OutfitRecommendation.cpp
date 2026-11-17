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

    void WearWiseSystem::whatShouldIWearToday() {
        while (true) {
            cout << "\n======================================================================\n";
            cout << "                    WHAT SHOULD I WEAR TODAY?                          \n";
            cout << "======================================================================\n";
            cout << "[1] Random Style Inspiration (does not check your wardrobe)\n";
            cout << "[2] My Wardrobe Recommendation (only my own clean clothes)\n";
            cout << "[0] Back to main menu\n";
            cout << "Choice: ";

            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a valid number.\n";
                continue;
            }
            cin.ignore(10000, '\n');

            if (choice == 0) return;
            if (choice == 1) {
                getRandomStyleInspiration();
            } else if (choice == 2) {
                cout << "\nLet's update today's situation before checking your own wardrobe.\n";
                if (configureOccasionAndWeather()) getOwnedWardrobeRecommendation();
            } else {
                cout << "Please choose 0, 1, or 2.\n";
            }
        }
    }

    void WearWiseSystem::getRandomStyleInspiration() {
        cout << "\n======================================================================\n";
        cout << "                      RANDOM STYLE INSPIRATION                         \n";
        cout << "     Answer a few quick questions. Your closet is not required.        \n";
        cout << "======================================================================\n";

        vector<string> questions = {"occasion", "weather", "location", "mood", "style", "activity"};
        unsigned seed = static_cast<unsigned>(
            chrono::steady_clock::now().time_since_epoch().count());
        mt19937 rng(seed);
        shuffle(questions.begin(), questions.end(), rng);

        string occasion, weather, location, mood, style, activity;
        for (const string& question : questions) {
            vector<string> options;
            string label;
            if (question == "occasion") {
                label = "Today's situation";
                options = {"University / Classes", "Office / Work", "Casual outing / Cafe",
                           "Wedding / Celebration", "Travel / Commute", "Sports / Fitness", "At home"};
            } else if (question == "weather") {
                label = "Weather";
                options = {"Hot and sunny", "Rainy or humid", "Cool / Winter", "Mild / Comfortable"};
            } else if (question == "location") {
                label = "Where will you spend most of your time?";
                options = {"Mostly indoors", "Mostly outdoors", "A mix of indoor and outdoor"};
            } else if (question == "mood") {
                label = "Today's mood";
                options = {"Confident", "Relaxed", "Creative", "Energetic", "Low-key"};
            } else if (question == "style") {
                label = "Style direction";
                options = {"Minimalist", "Smart Casual", "Casual", "Streetwear", "Traditional", "Sporty"};
            } else {
                label = "How active will your day be?";
                options = {"Mostly sitting", "A lot of walking", "A short event", "Physically active"};
            }

            cout << "\n" << label << ":\n";
            for (size_t i = 0; i < options.size(); ++i)
                cout << " [" << i + 1 << "] " << options[i] << "\n";
            int answer = 0;
            while (true) {
                cout << "Choose (1-" << options.size() << "): ";
                if (cin >> answer && answer >= 1 && answer <= static_cast<int>(options.size())) {
                    cin.ignore(10000, '\n');
                    break;
                }
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "That selection is not valid. Try again.\n";
            }
            const string selected = options[answer - 1];
            if (question == "occasion") occasion = selected;
            else if (question == "weather") weather = selected;
            else if (question == "location") location = selected;
            else if (question == "mood") mood = selected;
            else if (question == "style") style = selected;
            else activity = selected;
        }

        vector<string> tops;
        vector<string> bottoms;
        vector<string> shoes;
        vector<string> finishing;
        if (weather == "Hot and sunny") {
            tops = {"breathable cotton or linen shirt", "lightweight polo shirt", "relaxed cotton T-shirt", "airy kurta"};
            bottoms = {"lightweight chinos", "linen trousers", "straight-leg cotton pants", "clean denim"};
            finishing = {"keep the layers minimal and choose breathable fabrics", "use a light neutral palette and avoid heavy layering"};
        } else if (weather == "Rainy or humid") {
            tops = {"quick-dry polo or T-shirt", "lightweight shirt with a breathable inner layer", "simple kurta in a quick-drying fabric"};
            bottoms = {"quick-dry straight trousers", "comfortable chinos", "dark denim"};
            finishing = {"add a light water-resistant outer layer", "choose darker colours and keep a compact umbrella with you"};
        } else if (weather == "Cool / Winter") {
            tops = {"long-sleeve shirt with a knit sweater", "crewneck sweatshirt", "turtleneck or warm kurta"};
            bottoms = {"tailored trousers", "dark straight-leg denim", "comfortable chinos"};
            finishing = {"add a light jacket or structured overshirt", "use one warm layer instead of several bulky layers"};
        } else {
            tops = {"Oxford shirt", "polo shirt", "clean crewneck T-shirt", "lightweight blouse or kurta"};
            bottoms = {"straight-leg trousers", "dark denim", "chinos", "a simple midi skirt"};
            finishing = {"carry a light overshirt in case the temperature changes", "keep the outfit balanced with one relaxed and one structured piece"};
        }

        if (style == "Minimalist") {
            tops = {"plain cotton T-shirt", "clean Oxford shirt", "simple knit top"};
            bottoms = {"straight-leg neutral trousers", "dark clean denim", "tailored chinos"};
        } else if (style == "Smart Casual") {
            tops = {"Oxford button-down shirt", "fine-knit polo shirt", "structured blouse"};
            bottoms = {"tailored chinos", "straight-leg trousers", "dark clean denim"};
        } else if (style == "Casual") {
            tops = {"cotton T-shirt", "relaxed polo shirt", "casual overshirt"};
            bottoms = {"straight denim", "cotton chinos", "relaxed trousers"};
        } else if (style == "Streetwear") {
            tops = {"oversized graphic T-shirt", "boxy sweatshirt", "layered long-sleeve tee"};
            bottoms = {"relaxed cargo trousers", "wide-leg denim", "straight-leg relaxed jeans"};
        } else if (style == "Traditional") {
            tops = {"kurta", "traditional tunic", "embroidered long shirt"};
            bottoms = {"straight-cut trousers", "churidar bottoms", "tailored traditional pants"};
        } else if (style == "Sporty") {
            tops = {"moisture-wicking training T-shirt", "athletic polo", "lightweight sports top"};
            bottoms = {"joggers", "track pants", "athletic shorts"};
        }

        if (activity == "A lot of walking" || activity == "Physically active" || style == "Sporty") {
            shoes = {"supportive clean sneakers", "lightweight walking shoes"};
        } else if (style == "Streetwear") {
            shoes = {"high-top sneakers", "chunky low-top sneakers"};
        } else if (occasion == "Office / Work" || occasion == "Wedding / Celebration") {
            shoes = {"clean loafers or formal shoes", "simple low-profile dress shoes"};
        } else {
            shoes = {"minimal sneakers", "comfortable loafers or flats", "clean casual shoes"};
        }

        uniform_int_distribution<int> topPick(0, static_cast<int>(tops.size()) - 1);
        uniform_int_distribution<int> bottomPick(0, static_cast<int>(bottoms.size()) - 1);
        uniform_int_distribution<int> shoePick(0, static_cast<int>(shoes.size()) - 1);
        uniform_int_distribution<int> finishPick(0, static_cast<int>(finishing.size()) - 1);
        const string top = tops[topPick(rng)];
        const string bottom = bottoms[bottomPick(rng)];
        const string shoe = shoes[shoePick(rng)];
        const string finish = finishing[finishPick(rng)];
        string styleTip;
        if (style == "Minimalist") styleTip = "keep the silhouette clean, use simple shapes, and limit the palette to two or three colours";
        else if (style == "Smart Casual") styleTip = "combine one polished piece, such as a structured shirt, with a relaxed but neat item";
        else if (style == "Streetwear") styleTip = "try a relaxed fit, one statement piece, and balanced proportions";
        else if (style == "Traditional") styleTip = "choose a traditional silhouette and keep accessories coordinated rather than crowded";
        else if (style == "Sporty") styleTip = "prioritise movement, breathable materials, and supportive footwear";
        else styleTip = "keep the outfit relaxed, comfortable, and coordinated";
        string contextTip = location == "Mostly outdoors"
            ? "For outdoor time, consider sun protection or a compact umbrella depending on the forecast"
            : (location == "Mostly indoors" ? "For indoor settings, avoid unnecessary heavy layers" : "Choose a layer that is easy to remove when moving between places");
        string moodTip = mood == "Energetic" ? "Use one brighter accent colour to give the look energy"
            : (mood == "Low-key" ? "Choose calm neutrals and keep accessories subtle"
            : (mood == "Confident" ? "Add one structured piece to make the outfit feel intentional"
            : "Let comfort lead and add one small detail that expresses your personality"));


        cout << "\n======================================================================\n";
        cout << "                       YOUR RANDOM STYLE PLAN                          \n";
        cout << "======================================================================\n";
        cout << "Situation: " << occasion << " | Weather: " << weather << "\n";
        cout << "Location:  " << location << " | Mood: " << mood << "\n";
        cout << "Style:     " << style << " | Activity: " << activity << "\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "TOP:      " << top << "\n";
        cout << "BOTTOM:   " << bottom << "\n";
        cout << "FOOTWEAR: " << shoe << "\n";
        cout << "STYLE TIP: " << finish << ".\n";
        cout << "FIT TIP:   " << styleTip << ".\n";
        cout << "DAY TIP:   " << contextTip << ".\n";
        cout << "MOOD TIP:  " << moodTip << ".\n";
        cout << "COLOUR TIP: try a neutral base such as navy, white, beige, grey, or black,\n";
        cout << "            then add one accent colour that suits your mood.\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "This is style inspiration, not an inventory check. Use similar garment\n";
        cout << "types from your own closet; you do not need to own these exact items.\n";
        cout << "\nPress Enter to return...";
        cin.get();
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
            cout << "\nTip: Open Option 3 (My Wardrobe) to mark laundry items as clean,\n";
            cout << "or use Option 1 (Random Style Inspiration) to get outfit ideas first.\n";
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
