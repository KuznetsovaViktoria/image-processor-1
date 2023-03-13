#include "bmp.h"
#include <iostream>
#include <fstream>
#include <array>

Color::Color(long double r, long double g, long double b) : r(r), g(g), b(b) {
}

void Bmp::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "This file couldn't be read\n";
        return;
    }

    unsigned char file_header[bmp_header_size_];
    f.read(reinterpret_cast<char *>(file_header), bmp_header_size_);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "The file is not a .bmp file\n";
        f.close();
        return;
    }

    unsigned char information_header[dib_header_size_];
    f.read(reinterpret_cast<char *>(information_header), dib_header_size_);

    file_size_ = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);

    width_ = information_header[4] + (information_header[5] << 8) + (information_header[6] << 16) +
             (information_header[7] << 24);
    height_ = information_header[8] + (information_header[9] << 8) + (information_header[10] << 16) +
              (information_header[11] << 24);
    colors_.resize(width_ * height_);

    padding_amount_ = ((4 - (width_ * 3) % 4) % 4);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);

            colors_[y * width_ + x].r = static_cast<long double>(color[2]) / 255;
            colors_[y * width_ + x].g = static_cast<long double>(color[1]) / 255;
            colors_[y * width_ + x].b = static_cast<long double>(color[0]) / 255;
        }
        f.ignore(padding_amount_);
    }
    f.close();
};

void WriteNBytes(unsigned char arr[], size_t start, size_t n, size_t value) {
    for (size_t i = 0; i < n; i++) {
        arr[i + start] = value >> (i * 8);
    }
}

void Bmp::Export(const char *path) const {
    std::ofstream f(static_cast<std::string>(path), std::ios::binary);
    if (!f.is_open()) {
        std::cout << "This file couldn't be opened\n";
        return;
    }
    unsigned char bmp_pad[3] = {0, 0, 0};
    unsigned char bmp_header[14] = {0};
    bmp_header[0] = 'B';
    bmp_header[1] = 'M';
    WriteNBytes(bmp_header, 2, 4, file_size_);
    //    bmp_header[2] = file_size_;
    //    bmp_header[3] = file_size_ >> 8;
    //    bmp_header[4] = file_size_ >> 16;
    //    bmp_header[5] = file_size_ >> 24;
    bmp_header[10] = bmp_header_size_ + dib_header_size_;

    unsigned char dib_header[40] = {0};
    dib_header[0] = dib_header_size_;
    WriteNBytes(dib_header, 4, 4, width_);
    //    dib_header[4] = width_;
    //    dib_header[5] = width_ >> 8;
    //    dib_header[6] = width_ >> 16;
    //    dib_header[7] = width_ >> 24;
    WriteNBytes(dib_header, 8, 4, height_);
    //    dib_header[8] = height_;
    //    dib_header[9] = height_ >> 8;
    //    dib_header[10] = height_ >> 16;
    //    dib_header[11] = height_ >> 24;
    dib_header[12] = 1;
    dib_header[14] = 24;

    f.write(reinterpret_cast<char *>(bmp_header), bmp_header_size_);
    f.write(reinterpret_cast<char *>(dib_header), dib_header_size_);

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            unsigned char color[3];
            color[2] = static_cast<unsigned char>(GetColor(x, y).r * 255);
            color[1] = static_cast<unsigned char>(GetColor(x, y).g * 255);
            color[0] = static_cast<unsigned char>(GetColor(x, y).b * 255);

            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), padding_amount_);
    }
    f.close();
}

Color Bmp::GetColor(size_t x, size_t y) const {
    return colors_[y * width_ + x];
}

size_t Bmp::GetHeight() const {
    return height_;
}

size_t Bmp::GetWidth() const {
    return width_;
}
size_t Bmp::GetBmpHeaderSize() const {
    return bmp_header_size_;
}
size_t Bmp::GetDibHeaderSize() const {
    return dib_header_size_;
}

Color &Bmp::operator[](size_t i) {
    return colors_[i];
};

void Bmp::ChangePrivateVectorOfColors(std::vector<Color> new_colors) {
    colors_ = new_colors;
}

void Bmp::SetFileSize(size_t new_size) {
    file_size_ = new_size;
}

void Bmp::SetHeight(size_t new_height) {
    height_ = new_height;
}

void Bmp::SetWidth(size_t new_width) {
    width_ = new_width;
}

void Bmp::SetPaddingAmount(size_t new_padding) {
    padding_amount_ = new_padding;
}