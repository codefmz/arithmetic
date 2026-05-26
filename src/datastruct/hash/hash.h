#ifndef _HASH_H
#define _HASH_H

#include <string>

using namespace std;
bool isPrime(size_t aNum) {
    for (size_t i = 2; i <= sqrt(aNum); ++i) {
        if (aNum % i == 0) {
            return false;
        }
    }
    return true;
}

size_t nextPrime(size_t num) {
    for (size_t i = num; i > 1; --i) {
        if (isPrime(i)) {
            return i;
        }
    }
    return 1;
}

template<typename Key>
class mhash {
public:
    size_t operator()(const Key& k) const {
        return 1;
    }
};

template<>
class mhash<string> {
public:
    size_t operator()(const string& key) const {
        size_t hash_val = 0;
        for (char c : key) {
            hash_val = 37 * hash_val + c;
        }
        return hash_val;
    }
};

template<>
class mhash<int> {
public:
    size_t operator()(const int& key) const {
        return key;
    }
};

#endif