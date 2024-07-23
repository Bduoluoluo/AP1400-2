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

namespace algebra {
    Matrix zeros (size_t n, size_t m);
    Matrix ones (size_t n, size_t m);
    Matrix random (size_t n, size_t m, double min, double max);
    void show (const Matrix& matrix);
}

#endif //AP_HW1_H
