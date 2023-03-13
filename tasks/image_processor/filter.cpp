#include "filter.h"

void Filter::ApplyFilter(Bmp& image, std::vector<double> args) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            image[y * image.GetWidth() + x] = CountColor(image.GetColor(x, y));
        }
    }
}

Color Filter::CountColor(Color c) {
    return Color();
}