#pragma once
#include <wut.h>
#include "memheap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMAllocatorFunctions MEMAllocatorFunctions;
typedef struct MEMAllocator MEMAllocator;

typedef void * (*MEMAllocatorAllocFn)(MEMAllocator *allocator,
                                      uint32_t size);
typedef void   (*MEMAllocatorFreeFn) (MEMAllocator *allocator,
                                      void *ptr);

struct MEMAllocator {
   MEMAllocatorFunctions *funcs;
   MEMHeapHandle          heap;
   uint32_t               align;
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(MEMAllocator, 0x0, funcs);
WUT_CHECK_OFFSET(MEMAllocator, 0x4, heap);
WUT_CHECK_OFFSET(MEMAllocator, 0x8, align);
WUT_CHECK_SIZE(MEMAllocator, 0x10);

struct MEMAllocatorFunctions {
   MEMAllocatorAllocFn alloc;
   MEMAllocatorFreeFn  free;
};
WUT_CHECK_OFFSET(MEMAllocatorFunctions, 0x0, alloc);
WUT_CHECK_OFFSET(MEMAllocatorFunctions, 0x4, free);
WUT_CHECK_SIZE(MEMAllocatorFunctions, 0x8);

void *
MEMAllocFromAllocator(MEMAllocator *allocator,
                      uint32_t size);

void
MEMFreeToAllocator(MEMAllocator *allocator,
                   void *ptr);

void
MEMInitAllocatorForExpHeap(MEMAllocator *allocator,
                           MEMHeapHandle heap,
                           uint32_t alignment);

void
MEMInitAllocatorForFrmHeap(MEMAllocator *allocator,
                           MEMHeapHandle heap,
                           uint32_t alignment);

void
MEMInitAllocatorForUnitHeap(MEMAllocator *allocator,
                            MEMHeapHandle heap);

void
MEMInitAllocatorForDefaultHeap(MEMAllocator *allocator);

void
MEMInitAllocatorForBlockHeap(MEMAllocator *allocator,
                             MEMHeapHandle heap,
                             uint32_t alignment);

#ifdef __cplusplus
}
#endif
