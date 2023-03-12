#include "filter.h"
#pragma once
#include<vector>

class MatrixFilter : public Filter {

public:
    void ApplyFilter(Bmp& image) override;
    ~MatrixFilter() override = default;
    virtual int GetCoef(int i);
private:
    std::vector<int> matrix_ = {0, 0, 0, 0, 0, 0, 0, 0, 0};
};