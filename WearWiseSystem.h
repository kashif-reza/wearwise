#pragma once
#include <string>
#include <vector>
#include "UserProfile.h"
#include "ClothingItem.h"
using namespace std;

class WearWiseSystem {
private:
    UserProfile user{};
    vector<ClothingItem> clothingCatalogue;
    vector<ColorRule> colorRules;
    vector<PlannerRecord> historyRecords;
    vector<PlannerRecord> plannedOutfits;
    double monthlyBudget;
    double totalExpenditure;
    const string USERS_FILE = "users.txt";
    const string CLOTHING_FILE = "clothing.txt";
    const string COLORS_FILE = "colors.txt";
    const string BUDGET_FILE = "budget.txt";
    const string HISTORY_FILE = "history.txt";
    const string PLANNER_FILE = "planner.txt";
public:
    WearWiseSystem();
    void bootstrapFiles();
    void loadColorRules();
    void loadClothingCatalogue();
    void saveClothingCatalogue();
    void loadBudget();
    void saveBudget();
    void loadHistory();
    void saveHistory();
    void loadPlanner();
    void savePlanner();
    bool loadUserProfile();
    void saveUserProfile();
    void setupProfileWizard();
    bool areColorsCompatible(const string& colorA, const string& colorB);
    int calculateCompatibilityScore(const ClothingItem& upper, const ClothingItem& lower,
                                    const ClothingItem& foot, vector<string>& breakdown);
    void whatShouldIWearToday();
    void getRandomStyleInspiration();
    void clothingCareAssistant();
    void getOwnedWardrobeRecommendation();
    bool configureOccasionAndWeather();
    void manageWardrobe();
    void dailyOutfitPlanner();
    void displayProfile();
    void budgetAdvisor();
    void generateAIPrompt();
    void exploreColors();
    void showHistory();
    void wardrobeInsights();
    void runDashboard();
};
