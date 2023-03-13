#include "matrixFilter.h"
#include "filter.h"
#pragma once

class Sharpening : public MatrixFilter {

public:
    ~Sharpening() override = default;
    int8_t GetCoef(size_t i) override;
private:
    std::vector<int8_t> matrix_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};