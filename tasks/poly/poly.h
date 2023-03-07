#pragma once

#include <initializer_list>
#include <tuple>
#include <map>
#include <iostream>

class Poly {
public:
    Poly() = default;
    Poly(std::initializer_list<int64_t> coefs);
    Poly(std::initializer_list<std::pair<int64_t, int64_t>> coefs);

    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    friend Poly operator+(const Poly& left, const Poly& right);
    friend Poly operator-(const Poly& left, const Poly& right);
    Poly operator-() const;
    friend Poly operator*(const Poly& left, const Poly& right);
    void operator+=(const Poly& other);
    void operator-=(const Poly& other);
    friend std::ostream& operator<<(std::ostream& os, const Poly& poly);
    int64_t operator()(int64_t k) const;

private:
    std::map<int64_t, int64_t> coefs_;
};
