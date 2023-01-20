#include "password.h"

#include <cctype>

bool ValidatePassword(const std::string& password) {
    const int ascii_lower_bound = 33;
    const int ascii_upper_bound = 126;
    const int must_number = 3;
    int upper_used = 0;
    int lower_used = 0;
    int digit_used = 0;
    int other_used = 0;
    for (size_t i = 0; i < password.size(); ++i) {
        if (!(ascii_lower_bound <= static_cast<int>(password[i]) &&
              static_cast<int>(password[i]) <= ascii_upper_bound)) {
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
    if (upper_used + lower_used + digit_used + other_used < must_number) {
        return false;
    }
    const int length_lower_bound = 8;
    const int length_upper_bound = 14;
    if (!(length_lower_bound <= password.size() && password.size() <= length_upper_bound)) {
        return false;
    }
    return true;
}
