#include <atomic>
#include <algorithm>
#include "kfifo.h"

uint32_t KFIFO::put(const char * data, uint32_t len)
{
    uint32_t l;
    len = std::min(len, size - in + out);
    /*
    * Ensure that we sample the fifo->out index -before- we
    * start putting bytes into the kfifo.
    */
    std::atomic_thread_fence(std::memory_order_seq_cst);
    /* first put the data starting from fifo->in to buffer end */
    l = std::min(len, size - (in & (size - 1)));
    memcpy(buf.get() + (in & (size - 1)), data, l);
    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(buf.get(), data + l, len - l);

    /*
    * Ensure that we add the bytes to the kfifo -before-
    * we update the fifo->in index.
    */
    std::atomic_thread_fence(std::memory_order_release);
    in += len;

    return len;
}

uint32_t KFIFO::get(char * rbuf, uint32_t len)
{
    uint32_t l;
    len = std::min(len, in - out);
    /*
    * Ensure that we sample the in index -before- we
    * start removing bytes from the kfifo.
    */
    std::atomic_thread_fence(std::memory_order_acquire);
    /* first get the data from fifo->out until the end of the buffer */
    l = std::min(len, size - (out & (size - 1)));
    memcpy(rbuf, buf.get() + (out & (size - 1)), l);
    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(rbuf + l, buf.get(), len - l);
    /*
    * Ensure that we remove the bytes from the kfifo -before-
    * we update the fifo->out index.
    */
    std::atomic_thread_fence(std::memory_order_seq_cst);
    out += len;
    if (out == in) {
        out = in = 0;
    }

    return len;
}
