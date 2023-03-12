#include "edgeDetection.h"
#pragma once
int EdgeDetection::GetCoef(int i) {
    return matrix_[i];
};

void EdgeDetection::CorrectColors(Bmp& image) const {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color c = image.GetColor(x, y);
            if (c.r > threshold || c.g > threshold || c.b > threshold){
                image[y * image.GetWidth() + x] = Color(1, 1, 1);
            }else{
                image[y * image.GetWidth() + x] = Color(0, 0, 0);
            }
        }
    }
}