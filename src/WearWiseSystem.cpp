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
            ifstream seedItems("resources/clothing_seed.txt");
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

    bool WearWiseSystem::configureOccasionAndWeather() {
        cout << "\n======================================================================\n";
        cout << "                 TODAY'S OCCASION & WEATHER                           \n";
        cout << "======================================================================\n";
        cout << "Current: " << user.currentOccasion << " | " << user.currentSeason << "\n";

        const vector<string> occasions = {
            "University", "Office", "Interview", "Wedding", "Casual", "Travel", "Sports"
        };
        const vector<string> seasons = {
            "Summer", "Winter", "Rainy season", "All-Season"
        };
        int choice = 0;
        while (true) {
            cout << "\nSelect today's situation:\n";
            for (size_t i = 0; i < occasions.size(); ++i)
                cout << " [" << i + 1 << "] " << occasions[i] << "\n";
            cout << " [0] Cancel\nChoice: ";
            if (cin >> choice && choice >= 0 && choice <= static_cast<int>(occasions.size())) break;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid selection. Please try again.\n";
        }
        cin.ignore(10000, '\n');
        if (choice == 0) return false;
        user.currentOccasion = occasions[choice - 1];

        while (true) {
            cout << "\nSelect today's weather / season:\n";
            for (size_t i = 0; i < seasons.size(); ++i)
                cout << " [" << i + 1 << "] " << seasons[i] << "\n";
            cout << " [0] Cancel\nChoice: ";
            if (cin >> choice && choice >= 0 && choice <= static_cast<int>(seasons.size())) break;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid selection. Please try again.\n";
        }
        cin.ignore(10000, '\n');
        if (choice == 0) return false;
        user.currentSeason = seasons[choice - 1];
        saveUserProfile();
        cout << "\n[SAVED] Today's context: " << user.currentOccasion
             << " | " << user.currentSeason << "\n";
        return true;
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
            cout << "  [1] What Should I Wear Today? (Ideas, Closet Match & Outfit Planner)\n";
            cout << "  [2] My Wardrobe & Outfit History\n";
            cout << "  [3] Smart Travel Packing Planner\n";
            cout << "  [4] My Favorites & Purchase Wishlist\n";
            cout << "  [5] Clothing Care Assistant\n";
            cout << "  [6] Explore Color Harmonies\n";
            cout << "  [7] My Profile & Preferences\n";
            cout << "  [0] Exit Application\n";
            cout << "======================================================================\n";
            cout << "Enter option (0-9): ";

            int selection;
            if (!(cin >> selection)) {
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            switch (selection) {
                case 1:  whatShouldIWearToday(); break;
                case 2:  manageWardrobe(); break;
                case 3:  travelPackingPlanner(); break;
                case 4:  manageFavoritesAndWishlist(); break;
                case 5:  clothingCareAssistant(); break;
                case 6:  exploreColors(); break;
                case 7:  displayProfile(); break;
                case 8:  generateAIPrompt(); break;
                case 9:  showWardrobeInsights(); break;
                case 0:
                    cout << "\nSaving all session data to text files. Exiting WearWise...\n";
                    return;
                default:
                    cout << "Invalid choice. Please enter a number between 0 and 9.\n";
            }
        }
    }

    WearWiseSystem::WearWiseSystem() {
        bootstrapFiles();
        loadColorRules();
        loadClothingCatalogue();
        loadHistory();
        loadPlanner();
    }
