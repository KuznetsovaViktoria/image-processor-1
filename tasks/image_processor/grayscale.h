#include "filter.h"
#pragma once

class Grayscale : public Filter {

public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Grayscale() override = default;
};