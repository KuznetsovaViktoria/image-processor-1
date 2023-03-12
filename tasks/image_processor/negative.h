#include "filter.h"
#pragma once

class Negative : public Filter {

public:
    Color CountColor(Color c) override;
    ~Negative() override = default;
};