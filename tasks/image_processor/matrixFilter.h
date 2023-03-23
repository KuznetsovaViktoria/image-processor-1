#include "filter.h"
#pragma once
#include <vector>

class MatrixFilter : public Filter {

public:
    void ApplyFilter(Bmp& image, std::vector<double> args) override;
    ~MatrixFilter() override = default;
    virtual int8_t GetCoef(size_t i);

private:
    const std::vector<std::pair<int8_t, int8_t>> delta_ = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0},
                                                           {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
    std::vector<int8_t> matrix_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
};