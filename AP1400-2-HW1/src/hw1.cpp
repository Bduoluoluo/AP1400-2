#include "hw1.h"

size_t algebra::getRowNum (const Matrix& matrix) {
    return matrix.size();
}

size_t algebra::getColNum (const Matrix& matrix) {
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

Matrix algebra::transpose (const Matrix& matrix) {
    int row = algebra::getRowNum(matrix), col = algebra::getColNum(matrix);
    Matrix trans_matrix = algebra::zeros(col, row);
    for (int i = 0; i < row; i ++)
        for (int j = 0; j < col; j ++)
            trans_matrix[j][i] = matrix[i][j];
    return trans_matrix;
}

Matrix algebra::minor (const Matrix& matrix, size_t n, size_t m) {
    int row = algebra::getRowNum(matrix), col = algebra::getColNum(matrix);
    if (n >= row || m >= col || n < 0 || m < 0)
        throw std::logic_error("(n, m) must be within the shape of the matrix!");

    Matrix minor_matrix = algebra::zeros(row - 1, col - 1);
    for (int i = 0, ni = 0; i < row; i ++) {
        if (i == n) continue;
        for (int j = 0, nj = 0; j < col; j ++) {
            if (j == m) continue;
            minor_matrix[ni][nj] = matrix[i][j];
            nj ++;
        }
        ni ++;
    }
    return minor_matrix;
}

double algebra::determinant (const Matrix& matrix) {
    if (algebra::getRowNum(matrix) != algebra::getColNum(matrix))
        throw std::logic_error("The number of rows must equal to the number of columns!");

    if (matrix.empty())
        return 1;

    int row = algebra::getRowNum(matrix);
    double det = 0, coe = 1;
    for (int i = 0; i < row; i ++) {
        det += matrix[i][0] * coe * algebra::determinant(algebra::minor(matrix, i, 0));
        coe *= -1;
    }
    return det;
}

Matrix algebra::inverse (const Matrix& matrix) {
    if (algebra::getRowNum(matrix) != algebra::getColNum(matrix))
        throw std::logic_error("The number of rows must equal to the number of columns!");
    
    if (matrix.empty())
        return matrix;

    double det = algebra::determinant(matrix);
    if (fabs(det) < eps)
        throw std::logic_error("This matrix can't be inversed!");

    int n = algebra::getRowNum(matrix);
    Matrix adj_matrix = algebra::zeros(n, n);
    for (int i = 0; i < n; i ++) {
        double coe = (i & 1) ? -1 : 1;
        for (int j = 0; j < n; j ++) {
            adj_matrix[j][i] = coe * algebra::determinant(algebra::minor(matrix, i, j));
            coe *= -1;
        }        
    }

    return algebra::multiply(adj_matrix, 1 / det);
}