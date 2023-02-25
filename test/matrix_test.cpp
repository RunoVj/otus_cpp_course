#include "matrix.h"

#include <gtest/gtest.h>

TEST(TestMatrix, test_matrix)
{
    Matrix<int, -1> matrix;
    GTEST_ASSERT_EQ(matrix.size(), 0);
    auto a = matrix[0][0];
    GTEST_ASSERT_EQ(a, -1);
    GTEST_ASSERT_EQ(matrix.size(), 0);
    matrix[100][100] = 314;
    GTEST_ASSERT_EQ(matrix[100][100], 314);
    GTEST_ASSERT_EQ(matrix.size(), 1);

    std::stringstream out;
    for (const auto &c : matrix) {
        int x, y, v;
        std::tie(x, y, v) = c;
        out << x << y << v;
    }
    GTEST_ASSERT_EQ(out.str(), "100100314");
}

TEST(TestMatrix, test_canonical_form)
{
    Matrix<int, 0> matrix;
    ((matrix[100][100] = 314) = 0) = 217;
    GTEST_ASSERT_EQ(matrix[100][100], 217);
}
