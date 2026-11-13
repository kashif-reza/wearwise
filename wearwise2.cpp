#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// ============================================================================
// DATA STRUCTURES
// ============================================================================

struct UserProfile {
    string name;
    int age;
    string targetGroup;       // Men, Women, Kids
    string categoryGroup;     // Adult, Child
    double heightCm;
    double weightKg;
    double chestCm;
    double waistCm;
    double hipCm;
    double shoulderCm;
    string preferredSize;      // XS, S, M, L, XL
    string preferredFit;       // Slim, Regular, Relaxed
    string favoriteColor1;
    string favoriteColor2;
    string avoidedColor;
    string primaryStyle;       // Casual, Smart Casual, Formal, Traditional, Sportswear
    string currentOccasion;    // University, Office, Interview, Wedding, Travel, Casual, Sports
    string currentSeason;      // Summer, Winter, Rainy season, Hot weather, Cold weather, All-Season
};

struct ClothingItem {
    string id;
    string name;
    string category;          // Upper, Lower, Footwear, Outerwear
    string targetGroup;       // Men, Women, Kids, Unisex
    string color;
    vector<string> sizes;
    string season;
    string occasion;
    string style;
    double price;
    bool isOwned;
    bool isAvailable;
};

struct ColorRule {
    string baseColor;
    vector<string> complementaryColors;
};

struct PlannerRecord {
    string date;
    string outfitDetails;
    string occasion;
};

// ============================================================================
// STRING UTILITIES
// ============================================================================

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    string item;
    stringstream ss(str);
    while (getline(ss, item, delim)) {
        string t = trim(item);
        if (!t.empty()) tokens.push_back(t);
    }
    return tokens;
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
    return s;
}

bool containsIgnoreCase(const string& haystack, const string& needle) {
    return toLower(haystack).find(toLower(needle)) != string::npos;
}

// ============================================================================
// SYSTEM ENGINE
// ============================================================================

class WearWiseSystem {
private:
    UserProfile user;
    vector<ClothingItem> clothingCatalogue;
    vector<ColorRule> colorRules;
    vector<PlannerRecord> historyRecords;
    vector<PlannerRecord> plannedOutfits;
    double monthlyBudget;
    double totalExpenditure;

    const string USERS_FILE    = "users.txt";
    const string CLOTHING_FILE = "clothing.txt";
    const string COLORS_FILE   = "colors.txt";
    const string BUDGET_FILE   = "budget.txt";
    const string HISTORY_FILE  = "history.txt";
    const string PLANNER_FILE  = "planner.txt";

public:
    WearWiseSystem() : monthlyBudget(300.00), totalExpenditure(75.00) {
        bootstrapFiles();
        loadColorRules();
        loadClothingCatalogue();
        loadBudget();
        loadHistory();
        loadPlanner();
    }

    void bootstrapFiles() {
        ifstream cf(COLORS_FILE);
        if (!cf.good()) {
            ofstream out(COLORS_FILE);
            out << "Navy|White,Beige,Grey,Brown,Khaki,Light Blue\n";
            out << "White|Navy,Black,Olive,Blue,Beige,Burgundy,Charcoal,Tan,Pink\n";
            out << "Black|White,Grey,Beige,Red,Olive,Camel,Silver,Gold\n";
            out << "Beige|Navy,White,Brown,Olive,Burgundy,Denim Blue,Cream\n";
            out << "Olive|Beige,White,Black,Navy,Tan,Cream\n";
            out << "Grey|Black,White,Navy,Burgundy,Olive,Dusty Pink\n";
            out << "Blue|White,Beige,Grey,Brown,Tan,Navy\n";
            out << "Brown|Navy,Beige,White,Olive,Cream,Mustard\n";
            out << "Burgundy|Grey,Navy,Black,White,Beige,Tan,Gold\n";
            out << "Charcoal|White,Light Blue,Burgundy,Pink,Olive\n";
            out << "Tan|Navy,White,Black,Burgundy,Denim Blue\n";
            out << "Cream|Brown,Navy,Olive,Burgundy,Forest Green,Gold\n";
            out << "Pink|White,Grey,Navy,Denim Blue,Beige\n";
            out << "Yellow|Navy,Charcoal,White,Blue\n";
            out << "Gold|Burgundy,Navy,Black,Cream,White\n";
            out.close();
        }

        ifstream clf(CLOTHING_FILE);
        if (!clf.good()) {
            ofstream out(CLOTHING_FILE);
            // MEN SECTION
            out << "M101|Oxford Button-Down Shirt|Upper|Men|White|S,M,L,XL|All-Season,Summer|Office,University,Formal,Smart Casual,Interview|Smart Casual|45.00|1|1\n";
            out << "M102|Slim-Fit Tailored Chinos|Lower|Men|Navy|M,L,XL|All-Season|Office,University,Casual,Smart Casual,Interview|Smart Casual|55.00|1|1\n";
            out << "M103|Classic Leather Penny Loafers|Footwear|Men|Brown|M,L|All-Season|Office,University,Formal,Smart Casual,Interview|Formal|85.00|1|1\n";
            out << "M104|Heavyweight Cotton T-Shirt|Upper|Men|Black|S,M,L,XL|Summer,Hot weather,All-Season|Casual,University,Travel|Casual|25.00|1|1\n";
            out << "M105|Straight-Leg Selvedge Denim|Lower|Men|Blue|S,M,L,XL|All-Season,Winter|Casual,University,Travel|Casual|65.00|1|1\n";
            out << "M106|Low-Top Leather Minimalist Sneakers|Footwear|Unisex|White|S,M,L,XL|Summer,All-Season|Casual,University,Smart Casual|Minimalist|75.00|1|1\n";
            out << "M107|Single-Breasted Wool Blazer|Outerwear|Men|Navy|M,L|Winter,Cold weather,All-Season|Formal,Office,Interview,Wedding|Formal|140.00|1|1\n";
            out << "M108|Flat-Front Dress Trousers|Lower|Men|Grey|S,M,L|All-Season|Formal,Office,Interview,Wedding|Formal|70.00|1|1\n";
            out << "M109|Embroidered Silk Kurta|Upper|Men|Cream|M,L,XL|All-Season|Wedding,Formal,Traditional|Traditional|65.00|0|1\n";
            out << "M110|Silk Pajama Trousers|Lower|Men|White|M,L,XL|All-Season|Wedding,Formal,Traditional|Traditional|40.00|0|1\n";
            out << "M111|Handcrafted Mojari Leather Shoes|Footwear|Men|Tan|M,L|All-Season|Wedding,Traditional|Traditional|55.00|0|1\n";
            out << "M112|Merino Wool Crewneck Sweater|Upper|Men|Charcoal|S,M,L,XL|Winter,Cold weather|Office,University,Smart Casual,Casual|Minimalist|70.00|0|1\n";
            out << "M113|Pace Breaker Athletic Shorts|Lower|Men|Black|S,M,L|Summer,Hot weather|Casual,Sports|Sportswear|38.00|1|1\n";
            out << "M114|Athletic Mesh Runner Shoes|Footwear|Unisex|Black|S,M,L,XL|All-Season|Sports,Casual,Travel|Sportswear|85.00|1|1\n";
            out << "M115|Water-Resistant Trench Shell|Outerwear|Men|Beige|M,L|Rainy season,All-Season|Office,University,Travel|Smart Casual|120.00|0|1\n";

            // WOMEN SECTION
            out << "W201|Chiffon Peplum Blouse|Upper|Women|Cream|S,M,L|Summer,All-Season|Office,University,Smart Casual,Formal|Smart Casual|42.00|1|1\n";
            out << "W202|High-Waisted Pleated Trousers|Lower|Women|Navy|S,M,L|All-Season|Office,University,Smart Casual,Interview|Smart Casual|58.00|1|1\n";
            out << "W203|Pointed Leather Block Heels|Footwear|Women|Tan|S,M,L|All-Season|Office,Formal,Interview,Wedding|Formal|75.00|1|1\n";
            out << "W204|Anarkali Handcrafted Long Kurti|Upper|Women|Burgundy|S,M,L,XL|All-Season|Wedding,Traditional,Formal|Traditional|72.00|0|1\n";
            out << "W205|Silk Churidar Bottoms|Lower|Women|Gold|S,M,L|All-Season|Wedding,Traditional,Formal|Traditional|38.00|0|1\n";
            out << "W206|Embroidered Velvet Juttis|Footwear|Women|Gold|S,M,L|All-Season|Wedding,Traditional|Traditional|48.00|0|1\n";
            out << "W207|A-Line Linen Midi Dress|Upper|Women|Beige|S,M,L|Summer,Hot weather|Casual,University,Travel|Minimalist|62.00|1|1\n";
            out << "W208|High-Rise Stretch Skinny Jeans|Lower|Women|Blue|S,M,L,XL|All-Season|Casual,University,Travel|Casual|55.00|1|1\n";
            out << "W209|Ribbed Knit Turtleneck Sweater|Upper|Women|White|S,M,L|Winter,Cold weather|Casual,University,Smart Casual|Minimalist|50.00|0|1\n";
            out << "W210|Tailored Wool Trench Coat|Outerwear|Women|Camel|M,L|Winter,Rainy season,Cold weather|Office,Smart Casual,Formal|Formal|155.00|0|1\n";
            out << "W211|Comfort Yoga Leggings|Lower|Women|Black|S,M,L|All-Season|Sports,Casual|Sportswear|35.00|1|1\n";

            // KIDS SECTION
            out << "K301|Graphic Dinosaur Print Cotton Tee|Upper|Kids|Blue|XS,S|Summer,Hot weather|Casual,Travel|Casual|18.00|1|1\n";
            out << "K302|Elastic Drawstring Denim Joggers|Lower|Kids|Navy|XS,S|All-Season|Casual,Travel|Casual|26.00|1|1\n";
            out << "K303|Hook-and-Loop Running Sneakers|Footwear|Kids|Navy|XS,S|All-Season|Casual,Sports|Sportswear|34.00|1|1\n";
            out << "K304|Pastel Floral Tiered Frock|Upper|Kids|Pink|XS,S|Summer,All-Season|Wedding,Casual|Traditional|32.00|0|1\n";
            out << "K305|Comfort Cotton Tights|Lower|Kids|White|XS,S|All-Season|Wedding,Casual|Casual|14.00|0|1\n";
            out << "K306|Sparkle Ballet Flats|Footwear|Kids|White|XS,S|All-Season|Wedding,Casual,Formal|Formal|28.00|0|1\n";
            out << "K307|Kids Miniature Blazer & Shirt Set|Upper|Kids|Navy|XS,S|All-Season|Wedding,Formal,Interview|Formal|48.00|0|1\n";
            out << "K308|Kids Elastic Dress Trousers|Lower|Kids|Grey|XS,S|All-Season|Wedding,Formal,Interview|Formal|25.00|0|1\n";
            out.close();
        }

        ifstream bf(BUDGET_FILE);
        if (!bf.good()) {
            ofstream out(BUDGET_FILE);
            out << "300.00 75.00\n";
            out.close();
        }

        ifstream hf(HISTORY_FILE);
        if (!hf.good()) {
            ofstream out(HISTORY_FILE);
            out << "2026-11-09|Oxford Button-Down Shirt + Slim-Fit Tailored Chinos + Classic Leather Penny Loafers|Office\n";
            out.close();
        }

        ifstream pf(PLANNER_FILE);
        if (!pf.good()) {
            ofstream out(PLANNER_FILE);
            out << "2026-11-15|Oxford Button-Down Shirt + Slim-Fit Tailored Chinos + Single-Breasted Wool Blazer|Interview\n";
            out.close();
        }
    }

    void loadColorRules() {
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

    void loadClothingCatalogue() {
        clothingCatalogue.clear();
        ifstream file(CLOTHING_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() >= 11) {
                ClothingItem item;
                item.id = p[0];
                item.name = p[1];
                item.category = p[2];
                item.targetGroup = p[3];
                item.color = p[4];
                item.sizes = split(p[5], ',');
                item.season = p[6];
                item.occasion = p[7];
                item.style = p[8];
                item.price = stod(p[9]);
                item.isOwned = (p[10] == "1");
                item.isAvailable = (p[11] == "1");
                clothingCatalogue.push_back(item);
            }
        }
    }

    void saveClothingCatalogue() {
        ofstream out(CLOTHING_FILE);
        for (const auto& itm : clothingCatalogue) {
            out << itm.id << "|" << itm.name << "|" << itm.category << "|" << itm.targetGroup << "|"
                << itm.color << "|";
            for (size_t i = 0; i < itm.sizes.size(); ++i) {
                out << itm.sizes[i] << (i + 1 < itm.sizes.size() ? "," : "");
            }
            out << "|" << itm.season << "|" << itm.occasion << "|" << itm.style << "|"
                << fixed << setprecision(2) << itm.price << "|"
                << (itm.isOwned ? "1" : "0") << "|" << (itm.isAvailable ? "1" : "0") << "\n";
        }
    }

    void loadBudget() {
        ifstream file(BUDGET_FILE);
        if (file.good()) {
            file >> monthlyBudget >> totalExpenditure;
        }
    }

    void saveBudget() {
        ofstream out(BUDGET_FILE);
        out << fixed << setprecision(2) << monthlyBudget << " " << totalExpenditure << "\n";
    }

    void loadHistory() {
        historyRecords.clear();
        ifstream file(HISTORY_FILE);
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() >= 3) {
                historyRecords.push_back({p[0], p[1], p[2]});
            }
        }
    }

    void saveHistory() {
        ofstream out(HISTORY_FILE);
        for (const auto& h : historyRecords) {
            out << h.date << "|" << h.outfitDetails << "|" << h.occasion << "\n";
        }
    }

    void loadPlanner() {
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

    void savePlanner() {
        ofstream out(PLANNER_FILE);
        for (const auto& p : plannedOutfits) {
            out << p.date << "|" << p.outfitDetails << "|" << p.occasion << "\n";
        }
    }

    bool loadUserProfile() {
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

    void saveUserProfile() {
        ofstream out(USERS_FILE);
        out << user.name << "|" << user.age << "|" << user.targetGroup << "|" << user.categoryGroup << "|"
            << fixed << setprecision(1) << user.heightCm << "|" << user.weightKg << "|"
            << user.chestCm << "|" << user.waistCm << "|" << user.hipCm << "|" << user.shoulderCm << "|"
            << user.preferredSize << "|" << user.preferredFit << "|"
            << user.favoriteColor1 << "|" << user.favoriteColor2 << "|" << user.avoidedColor << "|"
            << user.primaryStyle << "|" << user.currentOccasion << "|" << user.currentSeason << "\n";
    }

    void setupProfileWizard() {
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

    bool areColorsCompatible(const string& colorA, const string& colorB) {
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

    int calculateCompatibilityScore(const ClothingItem& upper, const ClothingItem& lower,
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

    // ========================================================================
    // PURPOSE 1: IDEAL STYLIST RECOMMENDATION (NO WARDROBE CONSTRAINT)
    // ========================================================================
    void getIdealStylistRecommendation() {
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

    // ========================================================================
    // PURPOSE 2: SMART WARDROBE MATCHER (STRICTLY FROM OWNED & READY CLOSET)
    // ========================================================================
    void getOwnedWardrobeRecommendation() {
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

    // Occasion and Situation Selector
    void configureOccasionAndWeather() {
        cout << "\n======================================================================\n";
        cout << "                  CONFIGURE OCCASION & WEATHER                        \n";
        cout << "======================================================================\n";
        cout << "Current: Occasion = " << user.currentOccasion << " | Weather/Season = " << user.currentSeason << "\n\n";

        cout << "Select Occasion / Situation:\n";
        cout << " [1] University / Campus / Classes\n";
        cout << " [2] Office / Professional Workplace\n";
        cout << " [3] Job Interview\n";
        cout << " [4] Wedding / Formal Celebration\n";
        cout << " [5] Casual Hangout / Outing\n";
        cout << " [6] Travel / Commute\n";
        cout << " [7] Sports / Fitness Training\n";
        cout << " [0] Go Back (Cancel)\n";
        cout << "Choice (0-7): ";
        int occ;
        if (cin >> occ && occ != 0) {
            if (occ == 1) user.currentOccasion = "University";
            else if (occ == 2) user.currentOccasion = "Office";
            else if (occ == 3) user.currentOccasion = "Interview";
            else if (occ == 4) user.currentOccasion = "Wedding";
            else if (occ == 5) user.currentOccasion = "Casual";
            else if (occ == 6) user.currentOccasion = "Travel";
            else if (occ == 7) user.currentOccasion = "Sports";
        } else if (occ == 0) {
            cin.ignore();
            return;
        }

        cout << "\nSelect Current Weather / Season:\n";
        cout << " [1] Summer / Hot Weather\n";
        cout << " [2] Winter / Cold Weather\n";
        cout << " [3] Rainy Season\n";
        cout << " [4] All-Season / Moderate Room Temperature\n";
        cout << " [0] Go Back (Cancel)\n";
        cout << "Choice (0-4): ";
        int seas;
        if (cin >> seas && seas != 0) {
            if (seas == 1) user.currentSeason = "Summer";
            else if (seas == 2) user.currentSeason = "Winter";
            else if (seas == 3) user.currentSeason = "Rainy season";
            else if (seas == 4) user.currentSeason = "All-Season";
        }
        cin.ignore();
        saveUserProfile();
        cout << "\n[SAVED] System now tuned for: " << user.currentOccasion << " (" << user.currentSeason << ").\n";
    }

    // Wardrobe Manager with Back Button
    void manageWardrobe() {
        while (true) {
            cout << "\n======================================================================\n";
            cout << "                 MY WARDROBE (" << user.targetGroup << " Section)                     \n";
            cout << "======================================================================\n";
            cout << left << setw(6) << "ID" << setw(34) << "Item Name" << setw(10) << "Group"
                 << setw(10) << "Category" << setw(9) << "Color" << setw(14) << "Status" << "\n";
            cout << "----------------------------------------------------------------------\n";

            for (const auto& itm : clothingCatalogue) {
                if (itm.isOwned) {
                    cout << left << setw(6) << itm.id << setw(34) << itm.name << setw(10) << itm.targetGroup
                         << setw(10) << itm.category << setw(9) << itm.color
                         << (itm.isAvailable ? "[Clean/Ready]" : "[In Laundry]") << "\n";
                }
            }
            cout << "----------------------------------------------------------------------\n";
            cout << "Actions: [1] Toggle Clean/Laundry Status  [2] Add New Item  [0] Go Back\nChoice: ";
            int opt;
            if (!(cin >> opt) || opt == 0) {
                cin.clear();
                cin.ignore(1000, '\n');
                return;
            }

            if (opt == 1) {
                cout << "Enter Item ID (e.g. M101, W201): ";
                string targetId;
                cin >> targetId;
                cin.ignore();
                bool found = false;
                for (auto& itm : clothingCatalogue) {
                    if (toLower(itm.id) == toLower(targetId)) {
                        itm.isAvailable = !itm.isAvailable;
                        cout << "[UPDATED] " << itm.name << " status is now "
                             << (itm.isAvailable ? "Clean/Ready" : "In Laundry") << "\n";
                        found = true;
                        break;
                    }
                }
                if (found) saveClothingCatalogue();
            } else if (opt == 2) {
                cin.ignore();
                ClothingItem newItem;
                cout << "Item ID: ";
                getline(cin, newItem.id);
                cout << "Garment Name: ";
                getline(cin, newItem.name);
                cout << "Target Group (Men/Women/Kids/Unisex): ";
                getline(cin, newItem.targetGroup);
                cout << "Category (Upper/Lower/Footwear/Outerwear): ";
                getline(cin, newItem.category);
                cout << "Color: ";
                getline(cin, newItem.color);
                cout << "Sizes (comma-separated): ";
                string sz;
                getline(cin, sz);
                newItem.sizes = split(sz, ',');
                cout << "Season: ";
                getline(cin, newItem.season);
                cout << "Occasions: ";
                getline(cin, newItem.occasion);
                cout << "Style: ";
                getline(cin, newItem.style);
                cout << "Price: $";
                cin >> newItem.price;
                newItem.isOwned = true;
                newItem.isAvailable = true;
                clothingCatalogue.push_back(newItem);
                saveClothingCatalogue();
                cout << "[SUCCESS] Saved new item to wardrobe.\n";
            }
        }
    }

    // Daily Outfit Planner with Back Button
    void dailyOutfitPlanner() {
        cout << "\n======================================================================\n";
        cout << "                     DAILY OUTFIT PLANNER                             \n";
        cout << "======================================================================\n";
        cout << "Scheduled Plans:\n";
        for (const auto& p : plannedOutfits) {
            cout << " Date: " << left << setw(12) << p.date << " | Event: " << setw(14)
                 << p.occasion << " | Outfit: " << p.outfitDetails << "\n";
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Options: [1] Schedule New Plan  [0] Go Back\nChoice: ";
        int ch;
        if (!(cin >> ch) || ch == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        cin.ignore();
        PlannerRecord rec;
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, rec.date);
        cout << "Occasion: ";
        getline(cin, rec.occasion);
        cout << "Outfit Description: ";
        getline(cin, rec.outfitDetails);
        plannedOutfits.push_back(rec);
        savePlanner();
        cout << "[SUCCESS] Scheduled and saved!\n";
    }

    // Profile Inspector with Back Button
    void displayProfile() {
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

    // Budget Advisor with Back Button
    void budgetAdvisor() {
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

    // AI Virtual Try-On Prompt Generator with Back Button
    void generateAIPrompt() {
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

    // Color Rules Viewer with Back Button
    void exploreColors() {
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

    // History Viewer with Back Button
    void showHistory() {
        cout << "\n======================================================================\n";
        cout << "                     OUTFIT USAGE HISTORY                             \n";
        cout << "======================================================================\n";
        for (const auto& rec : historyRecords) {
            cout << " Date: " << left << setw(12) << rec.date << " | Event: " << setw(14)
                 << rec.occasion << " | " << rec.outfitDetails << "\n";
        }
        cout << "----------------------------------------------------------------------\n";
        cout << "Options: [1] Log Today's Worn Outfit  [0] Go Back\nChoice: ";
        int ch;
        if (!(cin >> ch) || ch == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }

        cin.ignore();
        PlannerRecord entry;
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, entry.date);
        cout << "Occasion: ";
        getline(cin, entry.occasion);
        cout << "Outfit Worn: ";
        getline(cin, entry.outfitDetails);
        historyRecords.push_back(entry);
        saveHistory();
        cout << "[SUCCESS] Worn outfit logged!\n";
    }

    // ========================================================================
    // MAIN DASHBOARD LOOP
    // ========================================================================
    void runDashboard() {
        if (!loadUserProfile()) {
            setupProfileWizard();
        }

        while (true) {
            cout << "\n======================================================================\n";
            cout << "                              WEARWISE                                \n";
            cout << "       Offline Smart Fashion Assistant & Wardrobe System              \n";
            cout << "======================================================================\n";
            cout << " Active User: " << user.name << " [" << user.targetGroup << "]\n";
            cout << " Situation:   " << user.currentOccasion << " | Weather: " << user.currentSeason << "\n";
            cout << "======================================================================\n";
            cout << "  [1] Ideal Stylist Recommendation (Occasion & Weather Based, No Closet Needed)\n";
            cout << "  [2] Smart Wardrobe Recommendation (Strictly From What You Own & Clean)\n";
            cout << "  [3] Select Occasion, Situation & Weather\n";
            cout << "  [4] Explore Color Harmonies & Palettes\n";
            cout << "  [5] My Wardrobe (Inventory & Laundry Tracking)\n";
            cout << "  [6] Daily Outfit Planner\n";
            cout << "  [7] My Profile & Anthropometric Measurements\n";
            cout << "  [8] Budget & Purchase Advisor\n";
            cout << "  [9] Outfit Usage History\n";
            cout << " [10] AI Virtual Try-On Prompt Generator\n";
            cout << "  [0] Exit Application\n";
            cout << "======================================================================\n";
            cout << "Enter option (0-10): ";

            int selection;
            if (!(cin >> selection)) {
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (selection) {
                case 1:  getIdealStylistRecommendation(); break;
                case 2:  getOwnedWardrobeRecommendation(); break;
                case 3:  configureOccasionAndWeather(); break;
                case 4:  exploreColors(); break;
                case 5:  manageWardrobe(); break;
                case 6:  dailyOutfitPlanner(); break;
                case 7:  displayProfile(); break;
                case 8:  budgetAdvisor(); break;
                case 9:  showHistory(); break;
                case 10: generateAIPrompt(); break;
                case 0:
                    cout << "\nSaving all session data to text files. Exiting WearWise...\n";
                    return;
                default:
                    cout << "Invalid choice. Please enter a number between 0 and 10.\n";
            }
        }
    }
};

// ============================================================================
// MAIN ENTRY POINT
// ============================================================================

int main() {
    WearWiseSystem app;
    app.runDashboard();
    return 0;
}
