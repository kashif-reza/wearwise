#pragma once
#include <string>
using namespace std;

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
