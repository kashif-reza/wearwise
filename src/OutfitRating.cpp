#include "WearWiseSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
using namespace std;

namespace {
int askRating(const string& question) {
    int value = 0;
    while (true) {
        cout << question << " (1 = very poor, 5 = excellent): ";
        if (cin >> value && value >= 1 && value <= 5) return value;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number from 1 to 5.\n";
    }
}
}

void WearWiseSystem::rateOutfit() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n======================================================================\n";
    cout << "                    OUTFIT RATING & STYLE REVIEW                      \n";
    cout << "======================================================================\n";
    cout << "Describe the clothes you want to rate. Your answers help WearWise\n";
    cout << "evaluate the outfit and give you a score from 1 to 10.\n\n";

    string top, bottom, shoes, occasion, weather;
    cout << "What shirt/top are you wearing? ";
    getline(cin, top);
    cout << "What pants/skirt/bottom are you wearing? ";
    getline(cin, bottom);
    cout << "What shoes are you wearing? ";
    getline(cin, shoes);

    const vector<string> occasions = {"University / Classes", "Office / Work", "Interview",
        "Wedding / Celebration", "Casual outing", "Travel", "Sports / Fitness", "At home"};
    cout << "\nWhere are you planning to wear this outfit?\n";
    for (size_t i = 0; i < occasions.size(); ++i)
        cout << " [" << i + 1 << "] " << occasions[i] << "\n";
    int occasionChoice = 0;
    while (!(cin >> occasionChoice) || occasionChoice < 1 ||
           occasionChoice > static_cast<int>(occasions.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose a valid option (1-" << occasions.size() << "): ";
    }
    occasion = occasions[occasionChoice - 1];

    const vector<string> weathers = {"Hot / Summer", "Rainy / Humid", "Cold / Winter", "Mild"};
    cout << "\nWhat is the weather like?\n";
    for (size_t i = 0; i < weathers.size(); ++i)
        cout << " [" << i + 1 << "] " << weathers[i] << "\n";
    int weatherChoice = 0;
    while (!(cin >> weatherChoice) || weatherChoice < 1 ||
           weatherChoice > static_cast<int>(weathers.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose a valid option (1-" << weathers.size() << "): ";
    }
    weather = weathers[weatherChoice - 1];

    cout << "\nRate each part of your outfit. Be honest; this helps make the result useful.\n";
    int fit = askRating("1. How well do the clothes fit your body");
    int comfort = askRating("2. How comfortable do you feel");
    int occasionFit = askRating("3. How suitable is the outfit for " + occasion);
    int weatherFit = askRating("4. How suitable are the fabrics/layers for " + weather);
    int colorMatch = askRating("5. How well do the colours work together");
    int shoesMatch = askRating("6. How well do the shoes match the outfit");

    // Weighted score: fit 25%, comfort 20%, occasion 20%, weather 15%, colours 15%, shoes 5%.
    double weighted = fit * 0.25 + comfort * 0.20 + occasionFit * 0.20 +
                      weatherFit * 0.15 + colorMatch * 0.15 + shoesMatch * 0.05;
    double score = weighted * 2.0;

    cout << fixed << setprecision(1);
    cout << "\n======================================================================\n";
    cout << "                         YOUR OUTFIT SCORE                            \n";
    cout << "======================================================================\n";
    cout << " Outfit: " << top << " + " << bottom << " + " << shoes << "\n";
    cout << " Occasion: " << occasion << " | Weather: " << weather << "\n\n";
    cout << "                         " << score << " / 10\n";

    if (score >= 9.0) cout << "Excellent! Your outfit looks well balanced based on your answers.\n";
    else if (score >= 7.5) cout << "Great choice! A few small improvements could make it even better.\n";
    else if (score >= 6.0) cout << "Good start. Consider improving the lower-rated areas below.\n";
    else if (score >= 4.0) cout << "There is room to improve this outfit. Try adjusting a few pieces.\n";
    else cout << "This combination may need some changes for better comfort and coordination.\n";

    cout << "\nSUGGESTIONS\n";
    if (fit <= 2) cout << "- Reconsider the size or cut; choose clothes that fit comfortably.\n";
    if (comfort <= 2) cout << "- Prioritize breathable fabric and comfortable movement.\n";
    if (occasionFit <= 2) cout << "- Choose pieces that better match the formality of " << occasion << ".\n";
    if (weatherFit <= 2) cout << "- Adjust fabric and layers for " << weather << " conditions.\n";
    if (colorMatch <= 2) cout << "- Try a neutral base and one complementary or accent colour.\n";
    if (shoesMatch <= 2) cout << "- Try shoes with a style and formality closer to the rest of the outfit.\n";
    if (fit > 2 && comfort > 2 && occasionFit > 2 && weatherFit > 2 &&
        colorMatch > 2 && shoesMatch > 2)
        cout << "- Keep this combination. It scored well across all rating areas.\n";

    cout << "\nRating is based on your answers and is a style guide, not an objective\n";
    cout << "fashion rule. Personal taste and confidence matter too.\n";
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
