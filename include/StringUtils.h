#pragma once
#include <string>
#include <vector>
using namespace std;

string trim(const string& s);
vector<string> split(const string& str, char delim);
string toLower(string s);
bool containsIgnoreCase(const string& haystack, const string& needle);
