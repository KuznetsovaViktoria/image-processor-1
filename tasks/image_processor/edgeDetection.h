#include "matrixFilter.h"
#pragma once

class EdgeDetection : public MatrixFilter {

public:
    ~EdgeDetection() override = default;
    int GetCoef(int i) override;
    void CorrectColors(Bmp& image) const;
    double threshold = 0.1;
private:
    std::vector<int> matrix_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
};