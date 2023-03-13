#include "filter.h"
#pragma once
#include <vector>

class MatrixFilter : public Filter {

public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~MatrixFilter() override = default;
    virtual int8_t GetCoef(size_t i);

private:
    std::vector<int8_t> matrix_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
};