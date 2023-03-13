#include "negative.h"

void Negative::ApplyFilter(Bmp& image, std::vector<double> args) {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color color = image.GetColor(x, y);
            image[y * image.GetWidth() + x] = Color(1 - color.r, 1 - color.g, 1 - color.b);
        }
    }
}