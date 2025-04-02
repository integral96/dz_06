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
    Matrix<int, 0, 2> matrix1(cols, rows);
    for (size_t i = 0; i < cols; ++i) {
        matrix1[i][i] = i;
        matrix1[i][(rows - 1) - i] = (rows - 1) - i;
    }
    std::cout << "\nmatrix2D = \n" << matrix1 << std::endl;
    std::cout << "подматрица matrix2D = \n" << std::endl;
    matrix1.print_sub_mtrx({1, 9}, {1, 9});
    std::cout << "\n выведем количество занятых ячеек matrix2D = " << matrix1.size_no_empty() << std::endl;
    std::cout << "все занятые ячейки вместе со своими позициями matrix2D = \n" << std::endl;
    matrix1.print_no_empty();
    size_t N1 = 3;
    size_t N2 = 3;
    size_t N3 = 3;
    size_t N4 = 3;
    size_t N5 = 3;
    Matrix<int, 0, 5> matrix5(N1, N2, N3, N4, N5);
    for (size_t k = 0; k < N1; ++k)
    for (size_t i = 0; i < N2; ++i)
    for (size_t j = 0; j < N3; ++j) {
        for (size_t l = 0; l < N4; ++l) {
            matrix5[k][i][j][l][l] = l + 1;
            matrix5[k][i][j][l][(N4 - 1) - l] = (N4 - 1) - l + 1;
        }
    }
    std::cout << "\nmatrix5D =\n" << matrix5 << std::endl;
    std::cout << "print sub matrix5D =\n" << std::endl;
    auto dd = {0, 2};
    matrix5.print_sub_mtrx(dd, dd, dd, dd, dd);
    std::cout << "\n выведем количество занятых ячеек matrix5D = " << matrix5.size_no_empty() << std::endl;
    std::cout << "все занятые ячейки вместе со своими позициями matrix5D = \n" << std::endl;
    matrix5.print_no_empty();

    return 0;
}
