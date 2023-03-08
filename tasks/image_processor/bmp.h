#pragma once

#include<vector>

struct Color{
    float r;
    float g;
    float b;

    Color() = default;
    Color(float r, float g, float b);
};

class Bmp{
public:
    void Read (const char* path);

private:
    int width_;
    int height_;
    std::vector<Color> colors_;
};