#include <iostream>
#include <limits>

#include "solution.hpp"

int main() {
    std::pair<unsigned int, int> result_overflow_1 = ExponentToOverflow(1048, 2);
    std::cout << result_overflow_1.first << '\t' << result_overflow_1.second << std::endl;

    std::pair<unsigned int, int> result_overflow_2 = ExponentToOverflow(-20000, 4);
    std::cout << result_overflow_2.first << '\t' << result_overflow_2.second << std::endl;
}
