#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t ind = str.size() - 1;
    while (ind >= 0 && str[ind] == ' ') {
        --ind;
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            continue;
        }
        if (str[i] != str[ind]) {
            return false;
        }
        --ind;
        while (ind >= 0 && str[ind] == ' ') {
            --ind;
        }
    }
    return true;
}
