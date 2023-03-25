#include "filter.h"
#pragma once

class Rainbow : public Filter {

public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~Rainbow() override = default;

private:
    void LayerColor(Color& color, const Color& shade) const;
    const double alpha_shade_ = 0.4;
    const std::vector<Color> rainbow_colors_ = {Color(1, 0, 0),
                                                Color(1, 110.0 / 255.0, 0),
                                                Color(1, 1, 0),
                                                Color(0, 1, 0),
                                                Color(0, 211.0 / 255.0, 1),
                                                Color(52.0 / 255.0, 52.0 / 255.0, 201.0 / 255.0),
                                                Color(211.0 / 255.0, 0, 1)};
    const int64_t seven_ = 7;
};