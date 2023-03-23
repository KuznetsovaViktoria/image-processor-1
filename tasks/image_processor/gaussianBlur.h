#pragma once
#include "filter.h"

class Blur : public Filter {
public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Blur() override = default;
    long double CountCoefficient(int64_t x0, int64_t x) const;

private:
    double sigma_ = 1;
};