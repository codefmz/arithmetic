#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <exception>
#include <stdexcept>

template <typename Object>
class BinaryHeap {
public:
    explicit BinaryHeap(int capacity = 100) :array(capacity), currentSize(0) {}
    explicit BinaryHeap(const std::vector<Object>& items) :array(items) {
        currentSize = items.size() - 1;
        buildHeap();
    };

    bool isEmpty() const {
        return currentSize == 0;
    }

    const Object& findMin() const {
        return array[1];
    }

    void insert(const Object& o) {
        if (currentSize == array.size() - 1) {
            array.resize(2 * array.size());
        }
        int hole = ++currentSize;
        for (; o < array[hole / 2]; hole /= 2) {
            array[hole] = std::move(array[hole / 2]);
        }
        array[hole] = o;
    }

    void insert(Object&& o) {
        if (currentSize == array.size() - 1) {
            array.resize(2 * array.size());
        }
        int hole = ++currentSize;
        for (; hole > 0 && o < array[hole / 2]; hole /= 2) {
            array[hole] = std::move(array[hole / 2]);
        }
        array[hole] = std::move(o);
    }

    void deleteMin() {
        if (isEmpty()) {
            throw std::runtime_error("this object is empty!");
        }
        array[1] = std::move(array[currentSize--]);
        percolateDown(1);
    }

    void deleteMin(Object& minO) {
        if (isEmpty()) {
            throw std::runtime_error("this object is empty!");
        }
        minO = std::move(array[1]);
        array[1] = std::move(array[currentSize--]);
        percolateDown(1);
    }

    void makeEmpey() {
        array.clear();
        currentSize = 0;
    }
private:
    void buildHeap() {
        for (int hole = currentSize / 2; hole > 0; --hole) {
            percolateDown(hole);
        }
    }

    void percolateDown(int hole) {
        auto temp = std::move(array[hole]);
        while (2 * hole <= currentSize) {
            int child = 2 * hole;
            if (child + 1 <= currentSize && array[child] > array[child + 1]) {
                ++child;
            }
            if (temp > array[child]) {
                array[hole] = array[child];
                hole = child;
            } else {
                break;
            }
        }
        array[hole] = std::move(temp);
    }

private:
    int currentSize;
    std::vector<Object> array;
};

#endif