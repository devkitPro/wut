#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_unitheap Unit Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMUnitHeap MEMUnitHeap;

struct MEMUnitHeap
{
};
UNKNOWN_SIZE(MEMUnitHeap);

MEMUnitHeap *
MEMCreateUnitHeapEx(MEMUnitHeap *heap,
                    uint32_t size,
                    uint32_t blockSize,
                    int32_t alignment,
                    uint16_t flags);

void *
MEMDestroyUnitHeap(MEMUnitHeap *heap);

void *
MEMAllocFromUnitHeap(MEMUnitHeap *heap);

void
MEMFreeToUnitHeap(MEMUnitHeap *heap,
                  void *block);

void
MEMiDumpUnitHeap(MEMUnitHeap *heap);

uint32_t
MEMCountFreeBlockForUnitHeap(MEMUnitHeap *heap);

uint32_t
MEMCalcHeapSizeForUnitHeap(uint32_t blockSize,
                           uint32_t count,
                           int32_t alignment);

#ifdef __cplusplus
}
#endif

/** @} */
