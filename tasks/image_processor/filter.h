#pragma once
#include "bmp.h"

class Filter {
public:
    virtual void ApplyFilter(Bmp& image, std::vector<double> args){};
    virtual ~Filter() = default;
    void NormalizeColor(Color& color);
};