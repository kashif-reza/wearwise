#include "StringUtils.h"
#include <sstream>
#include <algorithm>
#include <cctype>

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
