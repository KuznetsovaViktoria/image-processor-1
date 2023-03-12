#pragma once
#include "bmp.h"

class Filter {
public:
    virtual void ApplyFilter(Bmp& image);
    virtual Color CountColor(Color c);
    virtual ~Filter() = default;
};