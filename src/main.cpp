#include "matrix.h"

#include <fmt/format.h>
#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{

    Matrix<int, 0> matrix;

    for (uint8_t i = 0; i < 10; ++i) {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    for (uint8_t i = 1; i < 9; ++i) {
        for (uint8_t j = 1; j < 9; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    fmt::print("Filled cells amount: {}\n", matrix.size());

    for (const auto &c : matrix) {
        int x, y, v;
        std::tie(x, y, v) = c;
        fmt::print("[{}][{}] = {}\n", x, y, v);
    }
    return 0;
}
