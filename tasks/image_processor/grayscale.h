#include "filter.h"
#pragma once

class Grayscale : public Filter {

public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Grayscale() override = default;

private:
    const double r_coef_filter_ = 0.299;
    const double g_coef_filter_ = 0.587;
    const double b_coef_filter_ = 0.114;
};