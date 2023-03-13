#include "filter.h"
#pragma once

class Crop : public Filter {
public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Crop() override = default;
};