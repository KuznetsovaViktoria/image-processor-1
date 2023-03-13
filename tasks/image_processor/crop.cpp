#include "crop.h"

void Crop::ApplyFilter(Bmp &image, std::vector<double> args) {
    size_t new_width = static_cast<size_t>(args[0]);
    size_t new_height = static_cast<size_t>(args[1]);
    new_width = std::min(static_cast<int>(new_width), static_cast<int>(image.GetWidth()));
    new_height = std::min(static_cast<int>(new_height), static_cast<int>(image.GetHeight()));

    std::vector<Color> new_colors;
    new_colors.resize(new_width * new_height);

    image.SetPaddingAmount((4 - (new_width * 3) % 4) % 4);

    for (size_t y = 0; y < new_height; ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            new_colors[(new_height - 1 - y) * new_width + x] = image.GetColor(x, (image.GetHeight() - 1 - y));
        }
    }
    image.SetWidth(new_width);
    image.SetHeight(new_height);
    image.SetWidth(new_width);
    image.ChangePrivateVectorOfColors(new_colors);
    image.SetFileSize(image.GetBmpHeaderSize() + image.GetDibHeaderSize() + new_width * new_height * 3 +
                      ((4 - (new_width * 3) % 4) % 4) * new_height);
}