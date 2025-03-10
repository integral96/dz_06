#include <iostream>

#include "my_spatial.hpp"



int main()
{
    Matrix<int, -1, 2> matrix;
    assert(matrix.size() == 0); // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    // выведется одна строка
    // 100100314
    for(auto c: matrix) {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    size_t cols = 10;
    size_t rows = 10;
    Matrix<int, -1, 2> matrix1(cols, rows);
    for (size_t i = 0; i < cols; ++i) {
        matrix1[i][i] = i;
        matrix1[i][(rows - 1) - i] = (rows - 1) - i;
    }
    std::cout << "\nmatrix2D = \n" << matrix1 << std::endl;
    size_t N1 = 3;
    size_t N2 = 3;
    size_t N3 = 3;
    size_t N4 = 3;
    Matrix<int, 0, 4> matrix4(N1, N2, N3, N4);
    for (size_t k = 0; k < N1; ++k)
    for (size_t i = 0; i < N1; ++i)
    for (size_t j = 0; j < N1; ++j) {
       matrix4[k][i][j][j] = j + 1;
       matrix4[k][i][j][(N1 - 1) - j] = (N1 - 1) - j + 1;
    }
    std::cout << "\nmatrix4D =\n" << matrix4 << std::endl;

    size_t N5 = 3;
    size_t N6 = 3;
    size_t N7 = 3;

    Matrix<int, -1, 7> matrix7(N1, N2, N3, N4, N5, N6, N7);
    std::cout << "\nmatrix7D =\n" << matrix7 << std::endl;

    return 0;
}
