#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

void *
MEMAllocFromDefaultHeap(uint32_t size);

void *
MEMAllocFromDefaultHeapEx(uint32_t size,
                          int32_t alignment);

void
MEMFreeToDefaultHeap(void *block);

#ifdef __cplusplus
}
#endif
