#include "edgeDetection.h"
#include "grayscale.h"

int8_t EdgeDetection::GetCoef(size_t i) {
    return matrix_[i];
}

void EdgeDetection::CorrectColors(Bmp& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color c = image.GetColor(x, y);
            if (c.r > threshold_) {
                image[y * image.GetWidth() + x] = Color(1, 1, 1);
            } else {
                image[y * image.GetWidth() + x] = Color(0, 0, 0);
            }
        }
    }
}

void EdgeDetection::ApplyFilter(Bmp& image, std::vector<double> args) {
    Grayscale gr;
    gr.ApplyFilter(image, {});
    threshold_ = args[0];
    MatrixFilter::ApplyFilter(image, {});
    CorrectColors(image);
}