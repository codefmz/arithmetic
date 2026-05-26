#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread>

#ifndef KFIFO_H
#define KFIFO_H

#ifdef __cplusplus
extern "C" {
#endif

struct kfifo {
    char *buffer;  /* the buffer holding the data */
    uint32_t size;      /* the size of the allocated buffer */
    uint32_t in;        /* data is added at offset (in % size) */
    uint32_t out;       /* data is extracted from off. (out % size) */
    uint32_t reserved;
    pthread_mutex_t lock;
};

/* gcc 全屏障 */
#define SMP_MB() asm volatile("mfence" ::: "memory")
#define SMP_WMB() asm volatile("sfence" ::: "memory")
#define SMP_RMB() asm volatile("lfence" ::: "memory")

/**
 * kfifo_alloc - allocates a new FIFO and its internal buffer
 * @size: the size of the internal buffer to be allocated.
 * @gfp_mask: get_free_pages mask, passed to kmalloc()
 * @lock: the lock to be used to protect the fifo buffer
 *
 * The size will be rounded-up to a power of 2.
 */
struct kfifo *kfifo_alloc(uint32_t size, pthread_mutex_t *lock);

struct kfifo *kfifo_init(char *buffer, uint32_t size,  pthread_mutex_t *lock);

uint32_t kfifo_put(struct kfifo *fifo, char *buffer, uint32_t len);

uint32_t kfifo_get(struct kfifo *fifo, char *buffer, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* KFIFO_H */
