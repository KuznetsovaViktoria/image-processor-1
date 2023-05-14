#include "palindrome.h"

#include <algorithm>

bool IsPalindrome(const std::string& str) {
    std::string s1;
    std::string s2;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            s1 += str[i];
        }
    }
    s2 = s1;
    reverse(s1.begin(), s1.end());
    return (s1 == s2);
}
