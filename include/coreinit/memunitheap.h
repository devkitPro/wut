#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_unitheap Unit Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMUnitHeap MEMUnitHeap;
typedef struct MEMUnitHeapFreeBlock MEMUnitHeapFreeBlock;

struct MEMUnitHeapFreeBlock
{
   MEMUnitHeapFreeBlock *next;
};
WUT_CHECK_OFFSET(MEMUnitHeapFreeBlock, 0x00, next);
WUT_CHECK_SIZE(MEMUnitHeapFreeBlock, 0x04);

struct WUT_PACKED MEMUnitHeap
{
   MEMHeapHeader header;
   MEMUnitHeapFreeBlock *freeBlocks;
   uint32_t blockSize;
};
WUT_CHECK_OFFSET(MEMUnitHeap, 0x00, header);
WUT_CHECK_OFFSET(MEMUnitHeap, 0x40, freeBlocks);
WUT_CHECK_OFFSET(MEMUnitHeap, 0x44, blockSize);
WUT_CHECK_SIZE(MEMUnitHeap, 0x48);

MEMHeapHandle
MEMCreateUnitHeapEx(void *heap,
                    uint32_t size,
                    uint32_t blockSize,
                    int32_t alignment,
                    uint16_t flags);

void *
MEMDestroyUnitHeap(MEMHeapHandle heap);

void *
MEMAllocFromUnitHeap(MEMHeapHandle heap);

void
MEMFreeToUnitHeap(MEMHeapHandle heap,
                  void *block);

void
MEMiDumpUnitHeap(MEMHeapHandle heap);

uint32_t
MEMCountFreeBlockForUnitHeap(MEMHeapHandle heap);

uint32_t
MEMCalcHeapSizeForUnitHeap(uint32_t blockSize,
                           uint32_t count,
                           int32_t alignment);

#ifdef __cplusplus
}
#endif

/** @} */
