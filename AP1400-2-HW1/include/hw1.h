#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <iostream>
#include <random>
#include <iomanip>

using std::vector;
using std::cout;
using std::endl;
using Matrix = vector<vector<double>>;

const double eps = 1e-9;

namespace algebra {
    size_t getRowNum (const Matrix& matrix);
    size_t getColNum (const Matrix& matrix);
    Matrix zeros (size_t n, size_t m);
    Matrix ones (size_t n, size_t m);
    Matrix random (size_t n, size_t m, double min, double max);
    void show (const Matrix& matrix);
    Matrix multiply (const Matrix& matrix, double c);
    Matrix multiply (const Matrix& matrix1, const Matrix& matrix2);
    Matrix sum (const Matrix& matrix, double c);
    Matrix sum (const Matrix& matrix1, const Matrix& matrix2);
    Matrix transpose (const Matrix& matrix);
    Matrix minor (const Matrix& matrix, size_t n, size_t m);
    double determinant (const Matrix& matrix);
    Matrix inverse (const Matrix& matrix);
}

#endif //AP_HW1_H
