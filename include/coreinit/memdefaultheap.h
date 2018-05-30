#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_memdefaultheap Default Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*MEMAllocFromDefaultHeapFn)(uint32_t size);
typedef void *(*MEMAllocFromDefaultHeapExFn)(uint32_t size, int32_t alignment);
typedef void (*MEMFreeToDefaultHeapFn)(void *ptr);

extern MEMAllocFromDefaultHeapFn MEMAllocFromDefaultHeap;
extern MEMAllocFromDefaultHeapExFn MEMAllocFromDefaultHeapEx;
extern MEMFreeToDefaultHeapFn MEMFreeToDefaultHeap;

/**
 * Default implementation of __preinit_user.
 */
void
CoreInitDefaultHeap(MEMHeapHandle *outMem1,
                    MEMHeapHandle *outFG,
                    MEMHeapHandle *outMem2);

/**
 * Allows the user to completely customise the default heaps, this runs after
 * the rpx code section has loaded but before the data section as the data
 * sections are allocated from the default heap.
 *
 * This is for a user to export from their .rpx file, it is not exported from
 * coreinit.rpl
 */
void
__preinit_user(MEMHeapHandle *outMem1,
               MEMHeapHandle *outFG,
               MEMHeapHandle *outMem2);

#ifdef __cplusplus
}
#endif

/** @} */
