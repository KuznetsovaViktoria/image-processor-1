#include "poly.h"

#include <cmath>
#include <string>

Poly::Poly(std::initializer_list<int64_t> coefs) {
    int64_t i = 0;
    for (int64_t x : coefs) {
        if (x != 0) {
            coefs_[i] = x;
        }
        ++i;
    }
}

Poly::Poly(std::initializer_list<std::pair<int64_t, int64_t>> coefs) {
    for (std::pair<int64_t, int64_t> x : coefs) {
        if (x.second != 0) {
            coefs_[x.first] = x.second;
        }
    }
}

int64_t Poly::operator()(int64_t k) const {
    int64_t ans = 0;
    for (std::pair<int64_t, int64_t> a : coefs_) {
        ans += a.second * static_cast<int64_t>(pow(static_cast<double>(k), static_cast<double>(a.first)));
    }
    return ans;
}

bool Poly::operator==(const Poly &other) const {
    return coefs_ == other.coefs_;
}

bool Poly::operator!=(const Poly &other) const {
    return coefs_ != other.coefs_;
}

Poly operator+(const Poly &left, const Poly &right) {
    Poly ans;
    for (std::pair<int64_t, int64_t> a : left.coefs_) {
        ans.coefs_[a.first] = a.second;
    }
    for (std::pair<int64_t, int64_t> a : right.coefs_) {
        if (ans.coefs_[a.first] + a.second != 0) {
            ans.coefs_[a.first] += a.second;
        } else {
            ans.coefs_.erase(a.first);
        }
    }
    return ans;
}

Poly Poly::operator-() const {
    Poly ans;
    for (std::pair<int64_t, int64_t> a : coefs_) {
        ans.coefs_[a.first] = -a.second;
    }
    return ans;
}

Poly operator-(const Poly &left, const Poly &right) {
    return left + (-right);
}

void Poly::operator+=(const Poly &other) {
    for (std::pair<int64_t, int64_t> a : other.coefs_) {
        if (coefs_[a.first] + a.second != 0) {
            coefs_[a.first] += a.second;
        } else {
            coefs_.erase(a.first);
        }
    }
}

void Poly::operator-=(const Poly &other) {
    for (std::pair<int64_t, int64_t> a : other.coefs_) {
        if (coefs_[a.first] - a.second != 0) {
            coefs_[a.first] -= a.second;
        } else {
            coefs_.erase(a.first);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Poly &poly) {
    if (poly.coefs_.empty()) {
        return os << "y = 0";
    }
    std::string ans;
    for (auto it = poly.coefs_.rbegin(); it != poly.coefs_.rend(); ++it) {
        std::pair<int64_t, int64_t> x = *(it);

        if (ans.empty()) {
            if (x.second < 0) {
                ans += "-";
            }
            ans += std::to_string(std::abs(x.second)) + "x^" + std::to_string(x.first);
            continue;
        }
        if (x.second > 0) {
            ans += " + ";
        } else {
            ans += " - ";
        }
        if (x.first == 0) {
            ans += std::to_string(std::abs(x.second));
            continue;
        }
        ans += std::to_string(std::abs(x.second)) + "x^" + std::to_string(x.first);
    }
    return os << "y = " << ans;
}

Poly operator*(const Poly &left, const Poly &right) {
    Poly ans;
    for (std::pair<int64_t, int64_t> a : left.coefs_) {
        for (std::pair<int64_t, int64_t> b : right.coefs_) {
            ans.coefs_[a.first + b.first] += a.second * b.second;
            if (ans.coefs_[a.first + b.first] == 0) {
                ans.coefs_.erase(a.first + b.first);
            }
        }
    }
    return ans;
}

void Poly::operator*=(const Poly &other) {
    std::map<int64_t, int64_t> ans;
    for (std::pair<int64_t, int64_t> a : other.coefs_) {
        for (std::pair<int64_t, int64_t> b : coefs_) {
            ans[a.first + b.first] += a.second * b.second;
            if (ans[a.first + b.first] == 0) {
                ans.erase(a.first + b.first);
            }
        }
    }
    coefs_ = ans;
}