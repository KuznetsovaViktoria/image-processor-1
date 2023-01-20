#include "password.h"

#include <cctype>

bool ValidatePassword(const std::string& password) {
    const int ASCII_LOWER_BOUND = 33;
    const int ASCII_UPPER_BOUND = 126;
    const int MUST_NUMBER = 3;
    int upper_used = 0;
    int lower_used = 0;
    int digit_used = 0;
    int other_used = 0;
    for (size_t i = 0; i < password.size(); ++i) {
        if (!(ASCII_LOWER_BOUND <= static_cast<int>(password[i]) &&
              static_cast<int>(password[i]) <= ASCII_UPPER_BOUND)) {
            return false;
        }
        if (isupper(password[i]) && upper_used == 0) {
            ++upper_used;
        } else if (islower(password[i]) && lower_used == 0) {
            ++lower_used;
        } else if (isdigit(password[i]) && digit_used == 0) {
            ++digit_used;
        } else if (other_used == 0 && !(isupper(password[i]) || islower(password[i]) || isdigit(password[i]))) {
            ++other_used;
        }
    }
    if (upper_used + lower_used + digit_used + other_used < MUST_NUMBER) {
        return false;
    }
    const int LENGTH_LOWER_BOUND = 8;
    const int LENGTH_UPPER_BOUND = 14;
    if (!(LENGTH_LOWER_BOUND <= password.size() && password.size() <= LENGTH_UPPER_BOUND)) {
        return false;
    }
    return true;
}
