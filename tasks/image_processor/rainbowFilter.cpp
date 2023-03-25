#include "rainbowFilter.h"
#include "cmath"

void Rainbow::LayerColor(Color& color, const Color& shade) const {
    color.r += (shade.r - color.r) * alpha_shade_;
    color.g += (shade.g - color.g) * alpha_shade_;
    color.b += (shade.b - color.b) * alpha_shade_;
}

void Rainbow::ApplyFilter(Bmp& image, std::vector<double> args) {
    std::vector<Color> new_colors(image.GetWidth() * image.GetHeight());

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color color = image.GetColor(x, y);
            LayerColor(
                color,
                rainbow_colors_[(x / (image.GetWidth() / seven_) + y / (image.GetHeight() / seven_) + 1) % seven_]);
            NormalizeColor(color);
            new_colors[y * image.GetWidth() + x] = color;
        }
    }
    image.ChangePrivateVectorOfColors(new_colors);
}