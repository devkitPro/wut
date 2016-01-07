#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_baseheap Base Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t MEMBaseHeapType;
typedef void *MEMHeapHandle;

enum MEMBaseHeapType
{
   MEM_BASE_HEAP_MEM1   = 0,
   MEM_BASE_HEAP_MEM2   = 1,
   MEM_BASE_HEAP_FG     = 8,
};

MEMBaseHeapType
MEMGetArena(MEMHeapHandle handle);

MEMHeapHandle
MEMGetBaseHeapHandle(MEMBaseHeapType type);

MEMHeapHandle
MEMSetBaseHeapHandle(MEMBaseHeapType type,
                     MEMHeapHandle handle);

#ifdef __cplusplus
}
#endif

/** @} */
