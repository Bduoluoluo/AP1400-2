#ifndef Q1_H
#define Q1_H

#include <cmath>
#include <functional>

const double eps = 1e-6;

namespace q1 {
    double derivative (double x, std::function<double(double)> func);

    double gradient_descent (double init, double step, std::function<double(double)> func);

    template <typename T, typename F>
    double gradient_descent (T init, T step);
}

inline double q1::derivative (double x, std::function<double(double)> func) {
    return (func(x + eps) - func(x)) / eps;
}

inline double q1::gradient_descent (double init, double step, std::function<double(double)> func) {
    double x = init;
    double d = derivative(x, func);
    while (fabs(d) >= eps) {
        x -= step * d;
        d = derivative(x, func);
    }
    return x;
}

template <typename T, typename F>
inline double q1::gradient_descent (T init, T step) {
    return gradient_descent(init, step, F());
}

#endif //Q1_H