#pragma once
#include <array>
#include <mdspan>

namespace janum{
    struct row_operations{
        std::mdspan<double, std::dextents<size_t, 2>> matrix;
        int cols;
        int rowA;
        int rowB = 0;
        double scale = 1;
        char flag = 'p';
    };

    void row_op(row_operations op);
    std::array<int, 2> find_pivot(row_operations op, int row, bool augumented, char flag, int col = 0);
    void gauss_jordan(row_operations op, bool augumented);
} // namespace janum