#include "hash.h"
#include <cmath>

bool isPrime(size_t aNum) 
{
    for (size_t i = 2; i <= std::sqrt(aNum); ++i) {
        if (aNum % i == 0) {
            return false;
        }
    }

    return true;
}

size_t nextPrime(size_t num)
{
    for (size_t i = num; i > 1; --i) {
        if (isPrime(i)) {
            return i;
        }
    }

    return 1;
}