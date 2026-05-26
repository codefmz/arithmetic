#ifndef MY_HASH_H
#define MY_HASH_H

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include <

using namespace std;

//散列： 分离链接法
template <typename HashObj>
class HashTable {
public:
    explicit HashTable(int size = 31) {
        theList.resize(size);
        currentSize = 0;
    }

    bool contains(const HashObj& x) {
        auto whiList = theList[myhash(x)];
        return find(whiList.begin(), whiList.end(), x) != whiList.end();
    }

    void makeEmpty() {
        for (auto& alist : theList) {
            alist.clear();
        }
    }

    bool insert(const HashObj& x) {
        auto& whichList = theList[myhash(x)];
        if (find(whichList.begin(), whichList.end(), x) != whichList.end()) {
            return false;
        }
        whichList.push_back(x);
        if (++currentSize == theList.size()) {
            rehash();
        }
        return true;
    }

    bool insert(HashObj&& x) {
        auto& whichList = theList[myhash(x)];
        if (find(whichList.begin(), whichList.end(), x) != whichList.end()) {
            return false;
        }
        whichList.push_back(move(x));
        if (++currentSize == theList.size()) {
            rehash();
        }
        return true;
    }

    bool remove(const HashObj& x) {
        auto& whichList = theList[myhash(x)];
        auto iter = find(whichList.begin(), whichList.end(), x);
        if (iter == whichList.end()) {
            return false;
        }
        whichList.erase(iter);
        --currentSize;
        return true;
    }

    void printHashTable() {
        for (auto & list : theList) {
            for (auto & obj : list) {
                cout << obj << " ";
            }
            cout << endl;
        }
    }

private:
    vector<list<HashObj>> theList;
    int currentSize;
    void rehash() {
        auto oldList = theList;
        theList.resize(nextPrime(2 * theList.size()));
        currentSize = 0;
        for (auto& aList : oldList) {
            for (auto& e : aList) {
                insert(move(e));
            }
        }
    }

    size_t myhash(const HashObj& x) const {
        static mhash<HashObj> hh;
        return hh(x) % theList.size();
    }
};

#endif