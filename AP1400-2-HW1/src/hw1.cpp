#include "hw1.h"

int algebra::getRowNum (const Matrix& matrix) {
    return matrix.size();
}

int algebra::getColNum (const Matrix& matrix) {
    if (matrix.empty())
        return 0;
    return matrix[0].size();
}

Matrix algebra::zeros (size_t n, size_t m) {
    Matrix matrix(n);
    for (int i = 0; i < n; i ++)
        matrix[i].resize(m, 0);
    return matrix;
}

Matrix algebra::ones (size_t n, size_t m) {
    Matrix matrix(n);
    for (int i = 0; i < n; i ++)
        matrix[i].resize(m, 1);
    return matrix;
}

Matrix algebra::random (size_t n, size_t m, double min, double max) {
    if (min > max)
        throw std::logic_error("Min must be less than or equal to max!");

    Matrix matrix(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);

    for (int i = 0; i < n; i ++) {
        matrix[i].resize(m);
        for (int j = 0; j < m; j ++)
            matrix[i][j] = distrib(gen);
    }
    return matrix;
}

void algebra::show (const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (auto elem : row)
            cout << std::fixed << std::setw(10) << std::setprecision(3) << elem;
        cout << endl;
    }
}

Matrix algebra::multiply (const Matrix& matrix, double c) {
    Matrix mul_matrix = matrix;
    for (auto& row : mul_matrix)
        for (auto& elem : row)
            elem *= c;
    return mul_matrix;
}

Matrix algebra::multiply (const Matrix& matrix1, const Matrix& matrix2) {
    if (algebra::getColNum(matrix1) != algebra::getRowNum(matrix2))
        throw std::logic_error("The number of columns in matrix1 must equal to the number of rows in matrix2!");

    int row = getRowNum(matrix1), col = getColNum(matrix2), tmp = getColNum(matrix1);
    Matrix mul_matrix = algebra::zeros(row, col);
    for (int i = 0; i < row; i ++)
        for (int k = 0; k < tmp; k ++)
            for (int j = 0; j < col; j ++)
                mul_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
    return mul_matrix;
}

Matrix algebra::sum (const Matrix& matrix, double c) {
    Matrix sum_matrix = matrix;
    for (auto& row : sum_matrix)
        for (auto& elem : row)
            elem += c;
    return sum_matrix;
}

Matrix algebra::sum (const Matrix& matrix1, const Matrix& matrix2) {
    if (algebra::getRowNum(matrix1) != algebra::getRowNum(matrix2) || algebra::getColNum(matrix1) != algebra::getColNum(matrix2))
        throw std::logic_error("The shapes of matrix1 and matrix2 must be the same!");
    
    Matrix sum_matrix = matrix1;
    for (int i = 0; i < algebra::getRowNum(sum_matrix); i ++)
        for (int j = 0; j < algebra::getColNum(sum_matrix); j ++)
            sum_matrix[i][j] += matrix2[i][j];
    return sum_matrix;
}