#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv) {
    if (false) { // make false to run unit-tests
        // debug section
        Matrix matrix{{7, 2.5, 3.1}, {4.2, 5, 10.4}, {70.7, 8, 0}};
        Matrix minor = algebra::minor(matrix, 1, 1);
        algebra::show(matrix);
        algebra::show(minor);
    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}