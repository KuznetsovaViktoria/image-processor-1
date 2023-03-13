#include "filter.h"

#pragma once

class Grayscale : public Filter {

public:
    Color CountColor(Color c) override;
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Grayscale() override = default;
};