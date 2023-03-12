#include "filter.h"
#pragma once
#include <iostream>
void Filter::ApplyFilter(Bmp& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            std::cout << image.GetColor(x, y).r *255<< ' ' << image.GetColor(x, y).g *255 << ' ' << image.GetColor(x, y).b *255
                      << '\t';
        }
        std::cout<<'\n';
    }
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            image[y * image.GetWidth() + x] = CountColor(image.GetColor(x, y));
            std::cout << image.GetColor(x, y).r * 255 << '\t';
        }
        std::cout<<'\n';

    }
}

Color Filter::CountColor(Color c) {
    return Color();
}