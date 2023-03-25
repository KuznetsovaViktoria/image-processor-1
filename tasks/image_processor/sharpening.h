#include "matrixFilter.h"
#include "filter.h"
#pragma once

class Sharpening : public MatrixFilter {

public:
    ~Sharpening() override = default;
    const std::vector<int8_t>& GetMatrix() const override;

private:
    const std::vector<int8_t> matrix_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};