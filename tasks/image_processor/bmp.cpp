#include "bmp.h"
#include <iostream>
#include <fstream>

Color::Color(long double r, long double g, long double b) : r(r), g(g), b(b) {
}

const int EIGHT = 8;
const double RGB = 255;

void ReadNBytes(unsigned char *arr, size_t start, size_t n, size_t &value) {
    value = arr[start];
    for (size_t i = 1; i < n; i++) {
        value += arr[i + start] << (i * EIGHT);
    }
}

void Bmp::Read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("This file couldn't be read\n");
    }

    unsigned char file_header[bmp_header_size_];
    f.read(reinterpret_cast<char *>(file_header), static_cast<int64_t>(bmp_header_size_));

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        f.close();
        throw std::runtime_error("The file is not a .bmp file\n");
    }

    unsigned char information_header[dib_header_size_];
    f.read(reinterpret_cast<char *>(information_header), static_cast<int64_t>(dib_header_size_));
    ReadNBytes(file_header, 2, 4, file_size_);
    ReadNBytes(information_header, 4, 4, width_);
    ReadNBytes(information_header, EIGHT, 4, height_);

    colors_.resize(width_ * height_);
    SetPaddingAmount();

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);

            colors_[y * width_ + x].r = static_cast<long double>(color[2]) / RGB;
            colors_[y * width_ + x].g = static_cast<long double>(color[1]) / RGB;
            colors_[y * width_ + x].b = static_cast<long double>(color[0]) / RGB;
        }
        f.ignore(static_cast<int64_t>(padding_amount_));
    }
    f.close();
}

void WriteNBytes(unsigned char arr[], size_t start, size_t n, size_t value) {
    for (size_t i = 0; i < n; i++) {
        arr[i + start] = value >> (i * EIGHT);
    }
}

const size_t BMP_HEADER_SIZE = 14;
const size_t DIB_HEADER_SIZE = 40;
const size_t INDEX_HEADER_SIZE = 10;
const size_t INDEX_NUMBER_OF_COLOR_PLANES = 12;
const size_t INDEX_NUMBER_OF_BITS_PER_PIXEL = 14;
const size_t NUMBER_OF_BITS_PER_PIXEL = 24;

void Bmp::Export(const char *path) const {
    std::ofstream f(static_cast<std::string>(path), std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("This file couldn't be opened\n");
    }
    unsigned char bmp_pad[3] = {0, 0, 0};
    unsigned char bmp_header[BMP_HEADER_SIZE] = {0};
    bmp_header[0] = 'B';
    bmp_header[1] = 'M';
    WriteNBytes(bmp_header, 2, 4, file_size_);
    bmp_header[INDEX_HEADER_SIZE] = bmp_header_size_ + dib_header_size_;

    unsigned char dib_header[DIB_HEADER_SIZE] = {0};
    dib_header[0] = dib_header_size_;
    WriteNBytes(dib_header, 4, 4, width_);
    WriteNBytes(dib_header, EIGHT, 4, height_);
    dib_header[INDEX_NUMBER_OF_COLOR_PLANES] = 1;
    dib_header[INDEX_NUMBER_OF_BITS_PER_PIXEL] = NUMBER_OF_BITS_PER_PIXEL;

    f.write(reinterpret_cast<char *>(bmp_header), static_cast<int64_t>(bmp_header_size_));
    f.write(reinterpret_cast<char *>(dib_header), static_cast<int64_t>(dib_header_size_));

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            unsigned char color[3];
            color[2] = static_cast<unsigned char>(GetColor(x, y).r * RGB);
            color[1] = static_cast<unsigned char>(GetColor(x, y).g * RGB);
            color[0] = static_cast<unsigned char>(GetColor(x, y).b * RGB);

            f.write(reinterpret_cast<char *>(color), 3);
        }
        f.write(reinterpret_cast<char *>(bmp_pad), static_cast<int64_t>(padding_amount_));
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
const size_t Bmp::GetBmpHeaderSize() const {
    return BMP_HEADER_SIZE;
}
const size_t Bmp::GetDibHeaderSize() const {
    return DIB_HEADER_SIZE;
}

Color &Bmp::operator[](size_t i) {
    return colors_[i];
}

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

void Bmp::SetPaddingAmount() {
    padding_amount_ = ((4 - (width_ * 3) % 4) % 4);
}
size_t Bmp::GetPadding() const {
    return padding_amount_;
}
