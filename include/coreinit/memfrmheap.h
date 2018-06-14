#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_memfrmheap Frame Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum MEMFrmHeapFreeMode
{
   MEM_FRM_HEAP_FREE_HEAD   = 1 << 0,
   MEM_FRM_HEAP_FREE_TAIL   = 1 << 1,
   MEM_FRM_HEAP_FREE_ALL    = MEM_FRM_HEAP_FREE_HEAD | MEM_FRM_HEAP_FREE_TAIL,
} MEMFrmHeapFreeMode;

typedef struct MEMFrmHeap MEMFrmHeap;
typedef struct MEMFrmHeapState MEMFrmHeapState;

struct MEMFrmHeapState
{
   uint32_t tag;
   void *head;
   void *tail;
   MEMFrmHeapState *previous;
};
CHECK_OFFSET(MEMFrmHeapState, 0x00, tag);
CHECK_OFFSET(MEMFrmHeapState, 0x04, head);
CHECK_OFFSET(MEMFrmHeapState, 0x08, tail);
CHECK_OFFSET(MEMFrmHeapState, 0x0C, previous);
CHECK_SIZE(MEMFrmHeapState, 0x10);

struct MEMFrmHeap
{
   MEMHeapHeader header;
   void *head;
   void *tail;
   MEMFrmHeapState *previousState;
};
CHECK_OFFSET(MEMFrmHeap, 0x00, header);
CHECK_OFFSET(MEMFrmHeap, 0x40, head);
CHECK_OFFSET(MEMFrmHeap, 0x44, tail);
CHECK_OFFSET(MEMFrmHeap, 0x48, previousState);
CHECK_SIZE(MEMFrmHeap, 0x4C);

MEMHeapHandle
MEMCreateFrmHeapEx(void *heap,
                   uint32_t size,
                   uint32_t flags);

void *
MEMDestroyFrmHeap(MEMHeapHandle heap);

void *
MEMAllocFromFrmHeapEx(MEMHeapHandle heap,
                      uint32_t size,
                      int alignment);

void
MEMFreeToFrmHeap(MEMHeapHandle heap,
                 MEMFrmHeapFreeMode mode);

BOOL
MEMRecordStateForFrmHeap(MEMHeapHandle heap,
                         uint32_t tag);

BOOL
MEMFreeByStateToFrmHeap(MEMHeapHandle heap,
                        uint32_t tag);

uint32_t
MEMAdjustFrmHeap(MEMHeapHandle heap);

uint32_t
MEMResizeForMBlockFrmHeap(MEMHeapHandle heap,
                          uint32_t addr,
                          uint32_t size);

uint32_t
MEMGetAllocatableSizeForFrmHeapEx(MEMHeapHandle heap,
                                  int alignment);

#ifdef __cplusplus
}
#endif

/** @} */
