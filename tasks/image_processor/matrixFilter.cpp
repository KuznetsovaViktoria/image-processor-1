#include "matrixFilter.h"

void MatrixFilter::ApplyFilter(Bmp& image, std::vector<double> args) {
    std::vector<Color> new_colors(image.GetWidth() * image.GetHeight());
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            long double r = 0;
            long double g = 0;
            long double b = 0;
            std::vector<std::pair<int, int>> d = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0},
                                                  {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
            for (int i = 0; i < 9; ++i) {
                if (0 <= x + d[i].first && x + d[i].first < image.GetWidth() && 0 <= y + d[i].second &&
                    y + d[i].second < image.GetHeight()) {
                    r += GetCoef(i) * image.GetColor(x + d[i].first, y + d[i].second).r;
                    g += GetCoef(i) * image.GetColor(x + d[i].first, y + d[i].second).g;
                    b += GetCoef(i) * image.GetColor(x + d[i].first, y + d[i].second).b;
                } else {
                    r += GetCoef(i) * image.GetColor(x, y).r;
                    g += GetCoef(i) * image.GetColor(x, y).g;
                    b += GetCoef(i) * image.GetColor(x, y).b;
                }
            }
            if (r < 0) {
                r = 0;
            } else if (r > 1) {
                r = 1;
            }
            if (g < 0) {
                g = 0;
            } else if (g > 1) {
                g = 1;
            }
            if (b < 0) {
                b = 0;
            } else if (b > 1) {
                b = 1;
            }
            new_colors[y * image.GetWidth() + x] = Color(r, g, b);
        }
    }
    image.ChangePrivateVectorOfColors(new_colors);
}

int MatrixFilter::GetCoef(int i) {
    return 0;
};