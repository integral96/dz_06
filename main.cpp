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
    // for(auto c: matrix) {
    //     int x;
    //     int y;
    //     int v;
    //     std::tie(x, y, v) = c;
    //     std::cout << x << y << v << std::endl;
    // }
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
    size_t N3 = 4;
    size_t N4 = 5;
    Matrix<int, -1, 4> matrix4(N1, N2, N3, N4);
    std::cout << "\nmatrix4D =\n" << matrix4 << std::endl;

    std::cout << "HELLO" << std::endl;
    return 0;
}
