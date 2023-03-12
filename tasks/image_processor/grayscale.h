#include "filter.h"

#pragma once

class Grayscale : public Filter {

public:
    Color CountColor(Color c) override;
    ~Grayscale() override = default;
};