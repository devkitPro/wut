#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_expheap Expanded Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMExpandedHeap MEMExpandedHeap;
typedef struct MEMExpandedHeapBlock MEMExpandedHeapBlock;
typedef struct MEMExpandedHeapBlockList MEMExpandedHeapBlockList;

typedef enum MEMExpandedHeapMode
{
   MEM_EXP_HEAP_MODE_FIRST_FREE     = 0,
   MEM_EXP_HEAP_MODE_NEAREST_SIZE   = 1,
} MEMExpandedHeapMode;

typedef enum MEMExpandedHeapDirection
{
   MEM_EXP_HEAP_DIR_FROM_TOP        = 0,
   MEM_EXP_HEAP_DIR_FROM_BOTTOM     = 1,
} MEMExpandedHeapDirection;

struct MEMExpandedHeapBlock
{
   uint32_t attribs;
   uint32_t blockSize;
   MEMExpandedHeapBlock *prev;
   MEMExpandedHeapBlock *next;
   uint16_t tag;
   UNKNOWN(0x02);
};
CHECK_OFFSET(MEMExpandedHeapBlock, 0x00, attribs);
CHECK_OFFSET(MEMExpandedHeapBlock, 0x04, blockSize);
CHECK_OFFSET(MEMExpandedHeapBlock, 0x08, prev);
CHECK_OFFSET(MEMExpandedHeapBlock, 0x0c, next);
CHECK_OFFSET(MEMExpandedHeapBlock, 0x10, tag);
CHECK_SIZE(MEMExpandedHeapBlock, 0x14);

struct MEMExpandedHeapBlockList
{
   MEMExpandedHeapBlock *head;
   MEMExpandedHeapBlock *tail;
};
CHECK_OFFSET(MEMExpandedHeapBlockList, 0x00, head);
CHECK_OFFSET(MEMExpandedHeapBlockList, 0x04, tail);
CHECK_SIZE(MEMExpandedHeapBlockList, 0x08);

struct MEMExpandedHeap
{
   MEMHeapHeader header;
   MEMExpandedHeapBlockList freeList;
   MEMExpandedHeapBlockList usedList;
   uint16_t groupId;
   uint16_t attribs;
};
CHECK_OFFSET(MEMExpandedHeap, 0x00, header);
CHECK_OFFSET(MEMExpandedHeap, 0x40, freeList);
CHECK_OFFSET(MEMExpandedHeap, 0x48, usedList);
CHECK_OFFSET(MEMExpandedHeap, 0x50, groupId);
CHECK_OFFSET(MEMExpandedHeap, 0x52, attribs);
CHECK_SIZE(MEMExpandedHeap, 0x54);

MEMExpandedHeap *
MEMCreateExpHeapEx(MEMExpandedHeap *heap,
                   uint32_t size,
                   uint16_t flags);

MEMExpandedHeap *
MEMDestroyExpHeap(MEMExpandedHeap *heap);

void *
MEMAllocFromExpHeapEx(MEMExpandedHeap *heap,
                      uint32_t size,
                      int alignment);

void
MEMFreeToExpHeap(MEMExpandedHeap *heap,
                 void *block);

MEMExpandedHeapMode
MEMSetAllocModeForExpHeap(MEMExpandedHeap *heap,
                          MEMExpandedHeapMode mode);

MEMExpandedHeapMode
MEMGetAllocModeForExpHeap(MEMExpandedHeap *heap);

uint32_t
MEMAdjustExpHeap(MEMExpandedHeap *heap);

uint32_t
MEMResizeForMBlockExpHeap(MEMExpandedHeap *heap,
                          void *block,
                          uint32_t size);

uint32_t
MEMGetTotalFreeSizeForExpHeap(MEMExpandedHeap *heap);

uint32_t
MEMGetAllocatableSizeForExpHeapEx(MEMExpandedHeap *heap,
                                  int alignment);

uint16_t
MEMSetGroupIDForExpHeap(MEMExpandedHeap *heap,
                        uint16_t id);

uint16_t
MEMGetGroupIDForExpHeap(MEMExpandedHeap *heap);

uint32_t
MEMGetSizeForMBlockExpHeap(void *block);

uint16_t
MEMGetGroupIDForMBlockExpHeap(void *block);

MEMExpandedHeapDirection
MEMGetAllocDirForMBlockExpHeap(void *block);

#ifdef __cplusplus
}
#endif

/** @} */
