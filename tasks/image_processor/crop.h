#include "filter.h"
#pragma once

class Crop: public Filter{
public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    Color CountColor(Color c) override;
    ~Crop() override = default;
};