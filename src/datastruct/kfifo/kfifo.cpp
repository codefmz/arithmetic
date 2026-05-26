#include "kfifo.h"
#include <string.h>

#define min(a, b)  (((a) < (b)) ? (a) : (b))

/**
  * @brief  Determine whether some value is a power of two.
  * @param  [in] x: The number to be confirmed.
  * @retval true:   Yes.
  * @retval false:  No.
  * @note   Where zero is not considered a power of two.
  */
static bool is_power_of_2(uint32_t x)
{
   return (x != 0) && ((x & (x - 1)) == 0);
}

/**
  * @brief  Round the given value up to nearest power of two.
  * @param  [in] x: The number to be converted.
  * @return The power of two.
  */
static uint32_t roundup_pow_of_two(uint32_t x)
{
    uint32_t b = 0;

    for(int i = 0; i < 32; i++) {
        b = 1UL << i;

        if(x <= b) {
            break;
        }
    }

    return b;
}

kfifo * kfifo_init(char * buffer, uint32_t size, pthread_mutex_t *lock)
{
    kfifo * pfifo = NULL;

    if (!is_power_of_2(size)) {
        return NULL;
    }

    pfifo = (kfifo *)malloc(sizeof(kfifo));
    if (pfifo == NULL) {
        return NULL;
    }

    pfifo->buffer = buffer;
    pfifo->size = size;
    pfifo->in = pfifo->out = 0;
    pfifo->lock = lock;

    return pfifo;
}

struct kfifo *kfifo_alloc(uint32_t size, pthread_mutex_t *lock)
{
    char *buffer;
    struct kfifo *pfifo = NULL;
    /*
    * round up to the next power of 2, since our 'let the indices
    * wrap' tachnique works only in this case.
    */
    if (size & (size - 1)) {  /* size must be a power of 2 */
        size = roundup_pow_of_two(size);
    }

    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    pfifo = kfifo_init(buffer, size, lock);
    if (pfifo == NULL) {
        free(buffer);
    }

    return pfifo;
}

void kfifo_free(struct kfifo *fifo)
{
    kfree(fifo->buffer);
    kfree(fifo);
}

/**
 * __kfifo_put - puts some data into the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
uint32_t __kfifo_put(struct kfifo *fifo, char *buffer, uint32_t len)
{
    uint32_t l;
    len = min(len, fifo->size - fifo->in + fifo->out);
    /*
    * Ensure that we sample the fifo->out index -before- we
    * start putting bytes into the kfifo.
    */
    SMP_MB();
    /* first put the data starting from fifo->in to buffer end */
    l = min(len, fifo->size - (fifo->in & (fifo->size - 1)));
    memcpy(fifo->buffer + (fifo->in & (fifo->size - 1)), buffer, l);
    /* then put the rest (if any) at the beginning of the buffer */
    memcpy(fifo->buffer, buffer + l, len - l);

    /*
    * Ensure that we add the bytes to the kfifo -before-
    * we update the fifo->in index.
    */
    SMP_WMB();
    fifo->in += len;

    return len;
}

/**
 * __kfifo_get - gets some data from the FIFO, no locking version
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 *
 * Note that with only one concurrent reader and one concurrent
 * writer, you don't need extra locking to use these functions.
 */
uint32_t __kfifo_get(struct kfifo *fifo, char *buffer, uint32_t len)
{
    uint32_t l;
    len = min(len, fifo->in - fifo->out);
    /*
    * Ensure that we sample the fifo->in index -before- we
    * start removing bytes from the kfifo.
    */
    SMP_RMB();
    /* first get the data from fifo->out until the end of the buffer */
    l = min(len, fifo->size - (fifo->out & (fifo->size - 1)));
    memcpy(buffer, fifo->buffer + (fifo->out & (fifo->size - 1)), l);
    /* then get the rest (if any) from the beginning of the buffer */
    memcpy(buffer + l, fifo->buffer, len - l);
    /*
    * Ensure that we remove the bytes from the kfifo -before-
    * we update the fifo->out index.
    */
    SMP_MB();
    fifo->out += len;
    return len;
}

/**
 * kfifo_put - puts some data into the FIFO
 * @fifo: the fifo to be used.
 * @buffer: the data to be added.
 * @len: the length of the data to be added.
 *
 * This function copies at most @len bytes from the @buffer into
 * the FIFO depending on the free space, and returns the number of
 * bytes copied.
 */
uint32_t kfifo_put(struct kfifo *fifo, char *buffer, uint32_t len)
{
    uint32_t ret;
    pthread_mutex_lock(&fifo->lock);
    ret = __kfifo_put(fifo, buffer, len);
    pthread_mutex_unlock(&fifo->lock);
    return ret;
}

/**
 * kfifo_get - gets some data from the FIFO
 * @fifo: the fifo to be used.
 * @buffer: where the data must be copied.
 * @len: the size of the destination buffer.
 *
 * This function copies at most @len bytes from the FIFO into the
 * @buffer and returns the number of copied bytes.
 */
uint32_t kfifo_get(struct kfifo *fifo, char *buffer, uint32_t len)
{
    uint32_t ret;
    pthread_mutex_lock(&fifo->lock);
    ret = __kfifo_get(fifo, buffer, len);
    /*
    * optimization: if the FIFO is empty, set the indices to 0
    * so we don't wrap the next time
    */
    if (fifo->in == fifo->out) {
        fifo->in = fifo->out = 0;
    }
    pthread_mutex_unlock(&fifo->lock);
    return ret;
}