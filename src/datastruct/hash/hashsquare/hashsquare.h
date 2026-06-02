#ifndef HASH_SQUARE_H
#define HASH_SQUARE_H

#include "hash.h"
#include <iostream>
#include <utility>
#include <vector>


// 开放寻址法解决hash 冲突
template <typename HashObj>
class HashTable
{
public:
    explicit HashTable(int size = 31) {
        array.resize(size);
        currentSize = 0;
        makeEmpty();
    }

    bool contains(const HashObj& x) {
        int pos = findPos(x);
        return isActive(pos);
    }

    void makeEmpty() {
        for (auto& entry : array) {
            entry.type = EMPTY;
        }
    }

    bool insert(const HashObj& x) {
        int pos = findPos(x);
        if (isActive(pos)) {
            return false;
        }
        array[pos].element = x;
        array[pos].type = ACTIVE;
        if (++currentSize > array.size() / 2) {
            rehash();
        }
        return true;
    }

    bool insert(HashObj&& x) {
        int pos = findPos(x);
        if (isActive(pos)) {
            return false;
        }
        swap(array[pos].element, x);
        array[pos].type = ACTIVE;
        if (++currentSize > array.size() / 2) {
            rehash();
        }
        return true;
    }

    bool remove(const HashObj& x) {
        int pos = findPos(x);
        if (isActive(pos)) {
            array[pos].type = DELETED;
            return true;
        }
        return false;
    }

    void printHashTable() {
        for (auto& obj : array) {
            if (obj.type == ACTIVE) {
                std::cout << obj.element << " ";
            }
        }
        std::cout << std::endl;
    }

private:
    enum EntryType {
        ACTIVE = 0,
        EMPTY,
        DELETED
    };
    struct HashEntry {
        HashObj element;
        EntryType type;
        HashEntry(const HashObj& e = HashObj{}, EntryType _type = EMPTY) :element(e), type(_type) {};
        HashEntry(HashObj&& e, EntryType _type = EMPTY) :element(std::move(e)), type(_type) {};
    };

    void rehash() {
        std::vector<HashEntry> oldArray = array;
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto& entry : array) {
            entry.type = EMPTY;
        }

        currentSize = 0;
        for (auto& entry : oldArray) {
            if (entry.type == ACTIVE) {
                insert(std::move(entry.element));
            }
        }
    }

    bool isActive(int currentPos) const {
        return array[currentPos].type == ACTIVE;
    }

    int findPos(const HashObj& obj) {
        int offset = 1;
        int currentPos = myhash(obj);
        while (array[currentPos].type != EMPTY && array[currentPos].element != obj) {
            currentPos += offset;
            offset += 2;
            if (currentPos >= array.size()) {
                currentPos -= array.size();
            }
        }
        return currentPos;
    }

    size_t myhash(const HashObj& x) const {
        static mhash<HashObj> hh;
        return hh(x) % array.size();
    }

private:
    std::vector<HashEntry> array;
    int currentSize;
};

#endif
