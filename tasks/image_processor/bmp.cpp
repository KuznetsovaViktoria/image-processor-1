#include "bmp.h"

#include<iostream>
#include<fstream>

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {};


// https://www.youtube.com/watch?v=NcEE5xmpgQ0
// https://www.youtube.com/watch?v=vqT5j38bWGg
void Bmp::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "This file couldn't be read\n";
        return;
    }
    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "The file is not a .bmp file\n";
        f.close();
        return;
    }

    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);

    int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
    width_ = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) +
             (information_header[7] << 24);
    height_ = information_header[8] + (information_header[10] << 8) + (information_header[11] << 16) +
              (information_header[12] << 24);
    colors_.resize(width_ * height_);

    const int padding_amount = ((4 - (width_ * 3) % 4) % 4);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);

            colors_[y * width_ + x].r = static_cast<float>(color[2] / 255.0f);
            colors_[y * width_ + x].g = static_cast<float>(color[1] / 255.0f);
            colors_[y * width_ + x].b = static_cast<float>(color[0] / 255.0f);
        }
        f.ignore(padding_amount);
    }
    f.close();


};