#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv) {
    if (false) { // make false to run unit-tests
        // debug section
        Matrix matrix{{1, 0}, {0, 1}};
        Matrix inv = algebra::inverse(matrix);
        algebra::show(inv);
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