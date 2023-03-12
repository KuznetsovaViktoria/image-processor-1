#include "matrixFilter.h"
#include "filter.h"
#pragma once

class Sharpening : public MatrixFilter {

public:
    ~Sharpening() override = default;
    int GetCoef(int i) override;
private:
    std::vector<int> matrix_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};