#pragma once
#include "filter.h"

class Blur : public Filter {
public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Blur() override = default;
    long double CountCoefficient(int x0, int x) const;

private:
    double sigma_ = 1;
    void NormilizeColor(Color& c);
};