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
#include <set>
using namespace std;

    void WearWiseSystem::bootstrapFiles() {
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
            out << "M116|Classic Analog Wristwatch|Accessory|Men|Silver|One Size|All-Season|Office,Formal,University|Classic|60.00|1|1\n";
            out << "M117|Leather Belt|Accessory|Men|Brown|S,M,L,XL|All-Season|Office,Formal,Casual|Classic|25.00|1|1\n";
            out << "W212|Minimalist Wristwatch|Accessory|Women|Gold|One Size|All-Season|Office,Formal,Casual|Minimalist|55.00|1|1\n";
            out << "W213|Everyday Shoulder Bag|Accessory|Women|Black|One Size|All-Season|University,Office,Casual,Travel|Casual|48.00|1|1\n";
            out << "K309|Kids School Backpack|Accessory|Kids|Navy|One Size|All-Season|University,Travel|Casual|22.00|1|1\n";
            out << "U401|Unisex Sunglasses|Accessory|Unisex|Black|One Size|Summer,All-Season|Casual,Travel|Casual|30.00|0|1\n";
            out.close();
        }

        // Add new catalogue examples without overwriting a user's existing wardrobe.
        // This safely upgrades existing installations while preserving ownership/status.
        set<string> existingIds;
        {
            ifstream currentItems(CLOTHING_FILE);
            string existingLine;
            while (getline(currentItems, existingLine)) {
                auto fields = split(existingLine, '|');
                if (!fields.empty()) existingIds.insert(fields[0]);
            }
        }
        {
            ifstream seedItems("clothing_seed.txt");
            ofstream currentItems(CLOTHING_FILE, ios::app);
            string seedLine;
            while (getline(seedItems, seedLine)) {
                if (seedLine.empty() || seedLine[0] == '#') continue;
                auto fields = split(seedLine, '|');
                if (fields.size() >= 12 && existingIds.insert(fields[0]).second) {
                    currentItems << seedLine << "\n";
                }
            }
        }

        ifstream bf(BUDGET_FILE);
        if (!bf.good()) {
            ofstream out(BUDGET_FILE);
            out << "300.00 0.00\n";
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

    void WearWiseSystem::configureOccasionAndWeather() {
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

    void WearWiseSystem::runDashboard() {
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
            cout << "  [1] What Should I Wear Today? (Style Ideas + My Wardrobe)\n";
            cout << "  [2] Explore Color Harmonies & Palettes\n";
            cout << "  [3] My Wardrobe (Inventory & Laundry Tracking)\n";
            cout << "  [4] Style & Outfit Planner\n";
            cout << "  [5] My Profile & Anthropometric Measurements\n";
            cout << "  [6] Outfit Usage History\n";
            cout << "  [7] AI Virtual Try-On Prompt Generator\n";
            cout << "  [8] Clothing Care Assistant\n";
            cout << "  [0] Exit Application\n";
            cout << "======================================================================\n";
            cout << "Enter option (0-8): ";

            int selection;
            if (!(cin >> selection)) {
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (selection) {
                case 1:  whatShouldIWearToday(); break;
                case 2:  exploreColors(); break;
                case 3:  manageWardrobe(); break;
                case 4:  dailyOutfitPlanner(); break;
                case 5:  displayProfile(); break;
                case 6:  showHistory(); break;
                case 7:  generateAIPrompt(); break;
                case 8:  clothingCareAssistant(); break;
                case 0:
                    cout << "\nSaving all session data to text files. Exiting WearWise...\n";
                    return;
                default:
                    cout << "Invalid choice. Please enter a number between 0 and 8.\n";
            }
        }
    }

    WearWiseSystem::WearWiseSystem() : monthlyBudget(300.00), totalExpenditure(75.00) {
        bootstrapFiles();
        loadColorRules();
        loadClothingCatalogue();
        loadBudget();
        loadHistory();
        loadPlanner();
    }
