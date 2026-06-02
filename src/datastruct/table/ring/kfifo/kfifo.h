#ifndef _KIFIFO_H_
#define _KIFIFO_H_

#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <mutex>
#include <algorithm>

#define KFIFO_MAX_SIZE (128 * 1024 * 1024)

template <typename Node>
class KFIFO {
public:
    enum class MODE{
        SPSC,
        SPMC,
        MPSC,
        MPMC
    };

    KFIFO(MODE mode, uint32_t size): mMode(mode), mIn(0), mOut(0) {
        if (size == 0 || size > KFIFO_MAX_SIZE) {
            std::stringstream ss;
            ss << "size can't be 0 or more than " << KFIFO_MAX_SIZE << " cur is " << size;
            throw std::invalid_argument("size must be greater than 0" );
        }

        this->size = roundup_pow_of_two(size);
        mBuf.resize(this->size);
    }

    uint32_t put(const Node *data, uint32_t len) {
        if (len > mBuf.size()) {
            return 0;
        }

        if (mMode == MODE::MPSC || mMode == MODE::MPMC) {
            mMutex.lock();
        }
        int l = putImpl(data, len);
        if (mMode == MODE::MPSC || mMode == MODE::MPMC) {
            mMutex.unlock();
        }

        return l;
    }

    uint32_t get(const Node *data, uint32_t len) {
        if (len > mBuf.size()) {
            return 0;
        }

        if (mMode == MODE::SPMC || mMode == MODE::MPMC) {
            mMutex.lock();
        }
        int l = getImpl(data, len);
        if (mMode == MODE::SPMC || mMode == MODE::MPMC) {
            mMutex.unlock();
        }

        return l;
    }

private:
    uint32_t putImpl(const Node *data, uint32_t len) {
        uint32_t l;
        uint32_t size = mBuf.size();
        len = std::min(len, size - mIn + mOut);
        /*
        * Ensure that we sample the fifo->out index -before- we
        * start putting bytes into the kfifo.
        */
        std::atomic_thread_fence(std::memory_order_seq_cst);
        /* first put the data starting from fifo->in to buffer end */
        l = std::min(len, size - (mIn & (size - 1)));
        memcpy(mBuf.data() + (mIn & (size - 1)), data, l);
        /* then put the rest (if any) at the beginning of the buffer */
        memcpy(mBuf.data(), data + l, len - l);

        /*
        * Ensure that we add the bytes to the kfifo -before-
        * we update the fifo->in index.
        */
        std::atomic_thread_fence(std::memory_order_release);
        mIn += len;

        return len;
    }

    uint32_t getImpl(const Node *data, uint32_t len) { 
        uint32_t l;
        uint32_t size = mBuf.size();
        len = std::min(len, mIn - mOut);
        /*
        * Ensure that we sample the in index -before- we
        * start removing bytes from the kfifo.
        */
        std::atomic_thread_fence(std::memory_order_acquire);
        /* first get the data from fifo->out until the end of the buffer */
        l = std::min(len, size - (mOut & (size - 1)));
        memcpy(data, mBuf.data() + (mOut & (size - 1)), l);
        /* then get the rest (if any) from the beginning of the buffer */
        memcpy(data + l, mBuf.data(), len - l);
        /*
        * Ensure that we remove the bytes from the kfifo -before-
        * we update the fifo->out index.
        */
        std::atomic_thread_fence(std::memory_order_seq_cst);
        mOut += len;

        return len;
    }

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

private:
    MODE mMode;
    std::mutex mMutex;
    std::vector<Node> mBuf;
    volatile uint32_t mIn;
    volatile uint32_t mOut;
};

#endif