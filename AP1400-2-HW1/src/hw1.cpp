#include "hw1.h"


Matrix algebra::zeros (size_t n, size_t m) {
    Matrix mat(n);
    for (int i = 0; i < n; i ++)
        mat[i].resize(m, 0);
    return mat;
}