#pragma once

#include <vector>

struct Color {
    long double r;
    long double g;
    long double b;

    Color() = default;
    Color(long double r, long double g, long double b);

//    void operator*=(const size_t x);
//    void operator+=(const Color& x);
//    void operator-=(const Color& x);
};

class Bmp {
public:
    void Read(const char* path);
    void Export(const char* path);
    void Crop(int new_width, int new_height);
    Color GetColor(int x, int y) const;
    int GetHeight() const;
    int GetWidth() const;
    Color& operator[](size_t);
    void ChangePrivateVectorOfColors(std::vector<Color> new_colors);

private:
    int width_;
    int height_;
    int file_size_;
    int padding_amount_;
    std::vector<Color> colors_;
    const int bmp_header_size_ = 14;
    const int dib_header_size_ = 40;
    const long double rgb_ = 255.0;
};