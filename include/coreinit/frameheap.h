#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_frameheap Frame Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t MEMFrameHeapFreeMode;

enum MEMFrameHeapFreeMode
{
   MEM_FRAME_HEAP_FREE_FROM_BOTTOM  = 1 << 0,
   MEM_FRAME_HEAP_FREE_FROM_TOP     = 1 << 1,
};

MEMFrameHeap *
MEMCreateFrmHeap(MEMFrameHeap *heap,
                 uint32_t size);

MEMFrameHeap *
MEMCreateFrmHeapEx(MEMFrameHeap *heap,
                   uint32_t size,
                   uint16_t flags);

void *
MEMDestroyFrmHeap(MEMFrameHeap *heap);

void *
MEMAllocFromFrmHeap(MEMFrameHeap *heap,
                    uint32_t size);

void *
MEMAllocFromFrmHeapEx(MEMFrameHeap *heap,
                      uint32_t size,
                      int alignment);

void
MEMFreeToFrmHeap(MEMFrameHeap *heap,
                 MEMFrameHeapFreeMode mode);

BOOL
MEMRecordStateForFrmHeap(MEMFrameHeap *heap,
                         uint32_t tag);

BOOL
MEMFreeByStateToFrmHeap(MEMFrameHeap *heap,
                        uint32_t tag);

uint32_t
MEMAdjustFrmHeap(MEMFrameHeap *heap);

uint32_t
MEMResizeForMBlockFrmHeap(MEMFrameHeap *heap,
                          uint32_t addr,
                          uint32_t size);

uint32_t
MEMGetAllocatableSizeForFrmHeap(MEMFrameHeap *heap);

uint32_t
MEMGetAllocatableSizeForFrmHeapEx(MEMFrameHeap *heap,
                                  int alignment);

#ifdef __cplusplus
}
#endif

/** @} */
