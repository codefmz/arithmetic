#ifndef _KIFIFO_H_
#define _KIFIFO_H_

#include <memory>
#include <stdexcept>
#include <sstream>

#define KFIFO_MAX_SIZE (100 * 1024 * 1024)

class KFIFO {
private:
    std::unique_ptr<char[]> buf;
    uint32_t size;
    volatile uint32_t in;
    volatile uint32_t out;
public:
    KFIFO(uint32_t size): in(0), out(0) {
        if (size == 0 || size > KFIFO_MAX_SIZE) {
            std::stringstream ss;
            ss << "size can't be 0 or more than " << KFIFO_MAX_SIZE << " cur is " << size;
            throw std::invalid_argument("size must be greater than 0" );
        }

        this->size = roundup_pow_of_two(size);
        buf = std::make_unique<char[]>(this->size);
    }

    uint32_t put(const char *data, uint32_t len);

    uint32_t get(char * rbuf, uint32_t len);
private:
    uint32_t roundup_pow_of_two(uint32_t x) {
        uint32_t b = 0;

        for (int i = 0; i < 32; i++) {
            b = 1UL << i;
            if (x <= b) {
                break;
            }
        }

        return b;
    }
};

#endif