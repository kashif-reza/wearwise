#pragma once
#include <string>
#include <vector>
using namespace std;

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
