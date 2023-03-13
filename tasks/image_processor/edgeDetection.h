#include "matrixFilter.h"
#pragma once

class EdgeDetection : public MatrixFilter {

public:
    ~EdgeDetection() override = default;
    int GetCoef(int i) override;
    void CorrectColors(Bmp& image) const;
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
private:
    double threshold_ = 0.1;
    std::vector<int> matrix_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
};