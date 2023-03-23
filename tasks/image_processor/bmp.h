#pragma once
#include <vector>

struct Color {
    long double r;
    long double g;
    long double b;

    Color() = default;
    Color(long double r, long double g, long double b);
};

class Bmp {
public:
    void Read(const char* path);
    void Export(const char* path) const;
    Color GetColor(size_t x, size_t y) const;
    size_t GetHeight() const;
    size_t GetWidth() const;
    size_t GetPadding() const;
    const size_t GetBmpHeaderSize() const;
    const size_t GetDibHeaderSize() const;
    Color& operator[](size_t);
    void ChangePrivateVectorOfColors(std::vector<Color> new_colors);
    void SetHeight(size_t new_height);
    void SetWidth(size_t new_width);
    void SetFileSize(size_t new_size);
    void SetPaddingAmount();

private:
    size_t width_;
    size_t height_;
    size_t file_size_;
    size_t padding_amount_;
    std::vector<Color> colors_;
    const size_t bmp_header_size_ = 14;
    const size_t dib_header_size_ = 40;
};