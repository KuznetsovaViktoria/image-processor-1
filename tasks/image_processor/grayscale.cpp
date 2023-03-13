#include "grayscale.h"

void Grayscale::ApplyFilter(Bmp& image, std::vector<double> args) {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            long double c =
                0.299 * image.GetColor(x, y).r + 0.587 * image.GetColor(x, y).g + 0.114 * image.GetColor(x, y).b;
            if (c < 0) {
                c = 0;
            } else if (c > 1) {
                c = 1;
            }
            image[y * image.GetWidth() + x] = Color(c, c, c);
        }
    }
}