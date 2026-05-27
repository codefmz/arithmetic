#ifndef _HASH_H
#define _HASH_H

#include <string>

bool isPrime(size_t aNum);

size_t nextPrime(size_t num);

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
class cd<int> {
public:
    size_t operator()(const int& key) const {
        return key;
    }
};

#endif