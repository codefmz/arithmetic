#ifndef __RADIXTREE_H__
#define __RADIXTREE_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define INVALID_VALUE (uintptr_t) - 1

typedef void* RD_HANDLE; /* 定义 */

void* RadixTreeCreate32(int preallocate);

uint32_t RadixTreeDestory32(void* rTree);

uint32_t RadixTreeInsert32(void* rTree, uint32_t key, uintptr_t value);

uint32_t RadixTreeDelete32(void* rTree, uint32_t key);

uintptr_t RadixTreeFind32(void* rTree, uint32_t key);

#ifdef __cplusplus
}
#endif

#endif //__RADIXTREE_H__