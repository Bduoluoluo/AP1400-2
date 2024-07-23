#include "hw1.h"

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
    if (min > max) {
        throw std::logic_error("Min must be less than or equal to max!");
    }

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