#include "WearWiseSystem.h"
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

void WearWiseSystem::showWardrobeInsights() {
    map<string, int> categoryCounts;
    map<string, int> colorCounts;
    int owned = 0;
    int ready = 0;
    int laundry = 0;

    for (const auto& item : clothingCatalogue) {
        if (!item.isOwned) continue;
        ++owned;
        ++categoryCounts[item.category.empty() ? "Other" : item.category];
        ++colorCounts[item.color.empty() ? "Unspecified" : item.color];
        if (item.isAvailable) ++ready;
        else ++laundry;
    }

    cout << "\n======================================================================\n";
    cout << "                       MY WARDROBE INSIGHTS                            \n";
    cout << "======================================================================\n";
    cout << "Owned clothing items       : " << owned << "\n";
    cout << "Ready to wear              : " << ready << "\n";
    cout << "In laundry / unavailable   : " << laundry << "\n";

    if (owned == 0) {
        cout << "\nYour wardrobe is empty. Add owned items to start seeing insights.\n";
        cout << "Press Enter to return...";
        cin.ignore(10000, '\n');
        cin.get();
        return;
    }

    cout << "\nCATEGORY BREAKDOWN\n";
    for (const auto& entry : categoryCounts)
        cout << "  " << left << setw(16) << entry.first << entry.second << "\n";

    cout << "\nCOLOUR BREAKDOWN\n";
    for (const auto& entry : colorCounts)
        cout << "  " << left << setw(16) << entry.first << entry.second << "\n";

    cout << "\nQUICK SUGGESTIONS\n";
    if (ready == 0)
        cout << "  All owned items are unavailable. Update laundry status in My Wardrobe.\n";
    else if (laundry > ready)
        cout << "  More than half your wardrobe is unavailable. Consider doing laundry.\n";
    else
        cout << "  You have ready-to-wear items. Try mixing colours and categories.\n";

    if (categoryCounts["Footwear"] == 0)
        cout << "  No owned footwear is recorded. Add shoes to improve outfit matching.\n";
    if (categoryCounts["Upper"] == 0 || categoryCounts["Lower"] == 0)
        cout << "  Add both upper- and lower-body items for more complete outfit combinations.\n";

    cout << "\nInsights use your owned clothing records; no history-name guessing is involved.\n";
    cout << "Press Enter to return...";
    cin.ignore(10000, '\n');
    cin.get();
}
