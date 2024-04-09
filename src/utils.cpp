#include "utils.h"
#include <algorithm>
#include <cctype>

std::string trim(const std::string& str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    return result;
}

std::string removeBOM(const std::string& str) {
    if (str.size() >= 3 && str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF') {
        return str.substr(3);
    }
    return str;
}