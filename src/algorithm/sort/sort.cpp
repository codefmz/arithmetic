#include "sort.h"

void bubble(int arr[], size_t len) {
    if (len == 0) {
        return;
    }

    for (int i = 0; i < len - 1; i++) {
        for (int j = 1; j < len - i; j++) {
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void select(int* arr, size_t len) {
    if (len == 0) {
        return;
    }

    size_t maxIndex;
    for (size_t i = 0; i < len - 1; ++i) {
        maxIndex = 0;
        for (size_t j = 1; j < len - i; ++j) {
            if (arr[maxIndex] < arr[j]) {
                maxIndex = j;
            }
        }
        std::swap(arr[maxIndex], arr[len - i - 1]);
    }
}

void insert(int* arr, size_t len) {
    for (size_t p = 1; p < len; ++p) {
        auto temp = arr[p];
        int j = p;
        for (; j >= 1 && temp > arr[j - 1]; --j) {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}

void shell(int* arr, size_t len) {
    for (int gap = len / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; ++i) {
            int index = i;
            int val = arr[i];
            while (index >= gap && val < arr[index - gap]) {
                arr[index] = arr[index - gap];
                index -= gap;
            }
            arr[index] = val;
        }
    }
}

void quick(int* arr, size_t len) {
    quickHelp(arr, 0, len - 1);
}

void quickHelp(int* arr, int left, int right) {
    if (left < right) {
        int pivot = left;
        int index = left + 1;
        for (int i = index; i <= right; i++) {
            if (arr[i] < arr[pivot])
            {
                std::swap(arr[index], arr[i]);
                ++index;
            }
        }
        std::swap(arr[--index], arr[pivot]);
        quickHelp(arr, left, index - 1);
        quickHelp(arr, index + 1, right);
    }
}

void quick2(int* arr, size_t len) {
    quickHelp2(arr, 0, len - 1);
}

void quickHelp2(int* arr, size_t left, size_t right) {
    size_t l = left, r = right;
    int pivot = arr[(l + r) / 2];

    while (l < r) {
        while (arr[l] > pivot) {
            ++l;
        }

        while (arr[r] < pivot) {
            --r;
        }

        std::swap(arr[l], arr[r]);
        if (arr[r] == pivot) {
            ++l;
        }

        if (arr[l] == pivot) {
            --r;
        }
    }

    if (l == r) {
        ++l;
        --r;
    }

    if (r > left) {
        quickHelp2(arr, left, r);
    }

    if (l < right) {
        quickHelp2(arr, l, right);
    }
}

void quick3(int* arr, size_t len) {
    quickHelp3(arr, 0, len - 1);
}

void quickHelp3(int* arr, size_t left, size_t right) {
    if (left + 10 < right) {
        const int pivot = median3(arr, left, right);
        int l = left, r = right - 1;
        while (true) {
            while (arr[++l] < pivot) {};
            while (arr[--r] > pivot) {};
            if (l < r) {
                swap(arr[l], arr[r]);
            } else {
                break;
            }
        }
        swap(arr[l], arr[right - 1]);
        if (l > 0) {
            quickHelp3(arr, left, l - 1);
        }
        quickHelp3(arr, l + 1, right);
    } else if (left < right) {
        for (int i = left; i < right; ++i) {
            for (int j = left + 1; j <= right - left; ++j) {
                if (arr[j - 1] > arr[j]) {
                    std::swap(arr[j - 1], arr[j]);
                }
            }
        }
    }
}

int median3(int* arr, size_t left, size_t right) {
    int centor = (left + right) / 2;
    if (arr[centor] < arr[left]) {
        swap(arr[left], arr[centor]);
    }

    if (arr[right] < arr[left]) {
        swap(arr[right], arr[left]);
    }

    if (arr[right] < arr[centor]) {
        swap(arr[right], arr[centor]);
    }

    swap(arr[centor], arr[right - 1]);
    return arr[right - 1];
}

void merge(int* arr, size_t len) {
    int* temp = new int[len];
    mergeHelp(arr, 0, len - 1, temp);
    delete[] temp;
}

void mergeHelp(int* arr, size_t left, size_t right, int* temp) {
    if (left < right) {
        size_t mid = (left + right) / 2;
        mergeHelp(arr, left, mid, temp);
        mergeHelp(arr, mid + 1, right, temp);
        size_t i = left;
        size_t j = mid + 1;
        size_t t = 0;
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[t++] = arr[i++];
            } else {
                temp[t++] = arr[j++];
            }
        }

        while (j <= right) {
            temp[t++] = arr[j++];
        }

        while (i <= mid) {
            temp[t++] = arr[i++];
        }

        t = 0;
        size_t tLeft = left;
        while (tLeft <= right) {
            arr[tLeft++] = temp[t++];
        }
    }
}

void radix(int* arr, size_t len) {
    int** bucket = new int* [10]{};
    for (size_t i = 0; i < 10; i++) {
        bucket[i] = new int[len] {};
    }

    int* bucketCount = new int[10]{};
    int max_value = arr[0];
    for (size_t i = 1; i < len; i++) {
        max_value < arr[i] ? max_value = arr[i] : 1;
    }

    size_t max_bit = 1;
    while (max_value >= 10) {
        max_value /= 10;
        ++max_bit;
    }

    int n = 1;
    for (size_t i = 0; i < max_bit; i++) {
        for (size_t j = 0; j < len; j++) {
            int count = arr[j] / n % 10;
            bucket[count][bucketCount[count]++] = arr[j];
        }
        n *= 10;
        //从桶中取出
        size_t t = 0;
        for (size_t h = 0; h < 10; h++) {
            for (size_t k = 0; k < bucketCount[h]; k++) {
                arr[t++] = bucket[h][k];
            }
            bucketCount[h] = 0;
        }
    }

    for (size_t i = 0; i < 10; i++) {
        delete[] bucket[i];
    }
    delete[] bucketCount;
}

void heap(int* arr, size_t len) {
    for (size_t i = len / 2; i > 0; --i) {
        heapHelp(arr, i - 1, len);
    }

    for (size_t i = 0; i < len - 1; ++i) {
        std::swap(arr[0], arr[len - i - 1]);
        heapHelp(arr, 0, len - i - 1);
    }
}

void heapHelp(int* arr, size_t n, size_t len)
{
    int temp = arr[n];
    for (size_t i = 2 * n + 1; i < len; i = 2 * i + 1) {
        if (i + 1 < len && arr[i] < arr[i + 1]) {
            i += 1;
        }

        if (arr[i] > temp) {
            arr[n] = arr[i];
            n = i;
        } else {
            break;
        }
    }
    arr[n] = temp;
}

void sort(int arr[], size_t len, Fun f)
{
    clock_t before = clock();
    f(arr, len);
    clock_t after = clock();
    std::cout << __FILE__ << "(" << __LINE__ << "): " << __func__ << "  "
        << after - before << " s " << std::endl;
}