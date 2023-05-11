#include "solution.hpp"

#include <cmath>
#include <iostream>
#include <limits>

std::pair<unsigned int, int> ExponentToOverflow(int init_value, unsigned int base) {
    std::pair<unsigned int, int> result;
        int exponent=1;
        while (true){
            long long result = static_cast<long long>((int)pow((double)base,(double)exponent)) * static_cast<long long>(init_value);
            if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min()) {
                return std::make_pair(exponent,(int)result);
            }
            exponent++;
        }
}
