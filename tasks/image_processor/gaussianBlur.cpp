#include "gaussianBlur.h"
#include <cmath>

long double Blur::CountCoefficient(int64_t x0, int64_t x) const {
    return exp(-(x0 - x) * (x0 - x) / (2 * sigma_ * sigma_));
}

void Blur::NormilizeColor(Color& i) {
    if (i.r < 0) {
        i.r = 0;
    } else if (i.r > 1) {
        i.r = 1;
    }
    if (i.g < 0) {
        i.g = 0;
    } else if (i.g > 1) {
        i.g = 1;
    }
    if (i.b < 0) {
        i.b = 0;
    } else if (i.b > 1) {
        i.b = 1;
    }
}

void Blur::ApplyFilter(Bmp& image, std::vector<double> args) {
    sigma_ = args[0];
    int64_t s = ceil(3 * sigma_);
    std::vector<Color> new_colors(image.GetWidth() * image.GetHeight(), Color(0, 0, 0));

    long double coef = 1 / pow(2 * M_PI * sigma_ * sigma_, 0.5);

    for (int64_t y0 = 0; y0 < image.GetHeight(); ++y0) {
        for (int64_t x0 = 0; x0 < image.GetWidth(); ++x0) {
            for (int64_t i = x0 - s; i <= x0 + s; ++i) {
                int64_t x = std::min(static_cast<int>(image.GetWidth()) - 1, std::max(0, static_cast<int>(i)));
                long double c = CountCoefficient(x0, i) * coef;
                new_colors[y0 * image.GetWidth() + x0].r += image.GetColor(x, y0).r * c;
                new_colors[y0 * image.GetWidth() + x0].g += image.GetColor(x, y0).g * c;
                new_colors[y0 * image.GetWidth() + x0].b += image.GetColor(x, y0).b * c;
            }
        }
    }
    image.ChangePrivateVectorOfColors(new_colors);
    new_colors.clear();
    new_colors.resize(image.GetWidth() * image.GetHeight(), Color(0, 0, 0));

    for (int64_t y0 = 0; y0 < image.GetHeight(); ++y0) {
        for (int64_t x0 = 0; x0 < image.GetWidth(); ++x0) {
            for (int64_t i = y0 - s; i <= y0 + s; ++i) {
                int64_t y = std::min(static_cast<int>(image.GetHeight()) - 1, std::max(0, static_cast<int>(i)));
                long double c = CountCoefficient(y0, i) * coef;
                new_colors[y0 * image.GetWidth() + x0].r += image.GetColor(x0, y).r * c;
                new_colors[y0 * image.GetWidth() + x0].g += image.GetColor(x0, y).g * c;
                new_colors[y0 * image.GetWidth() + x0].b += image.GetColor(x0, y).b * c;
            }
        }
    }
    for (Color& i : new_colors) {
        NormilizeColor(i);
    }
    image.ChangePrivateVectorOfColors(new_colors);
}