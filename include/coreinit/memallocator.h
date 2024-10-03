#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_memallocator Allocator
 * \ingroup coreinit
 *
 * Functions for managing generic allocator objects.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMAllocatorFunctions MEMAllocatorFunctions;
typedef struct MEMAllocator MEMAllocator;

typedef void *(*MEMAllocatorAllocFn)(MEMAllocator *allocator, uint32_t size);
typedef void (*MEMAllocatorFreeFn)(MEMAllocator *allocator, void *ptr);

//! Holds context information that will be used to allocate and free memory.
struct MEMAllocator
{
   //! Points to the alloc/free functions.
   MEMAllocatorFunctions *funcs;
   //! The heap handle.
   MEMHeapHandle heap;
   //! The alignment the allocator will use.
   uint32_t align;
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(MEMAllocator, 0x0, funcs);
WUT_CHECK_OFFSET(MEMAllocator, 0x4, heap);
WUT_CHECK_OFFSET(MEMAllocator, 0x8, align);
WUT_CHECK_SIZE(MEMAllocator, 0x10);

//! The alloc/free functions.
struct MEMAllocatorFunctions
{
   MEMAllocatorAllocFn alloc;
   MEMAllocatorFreeFn free;
};
WUT_CHECK_OFFSET(MEMAllocatorFunctions, 0x0, alloc);
WUT_CHECK_OFFSET(MEMAllocatorFunctions, 0x4, free);
WUT_CHECK_SIZE(MEMAllocatorFunctions, 0x8);

/**
 * Allocates memory from the allocator.
 *
 * \return `allocator->funcs.alloc(allocator, size)`.
 */
void *
MEMAllocFromAllocator(MEMAllocator *allocator,
                      uint32_t size);

/**
 * Frees memory back to the allocator.
 *
 * It simply calls `allocator->funcs.free(allocator, ptr)`.
 */
void
MEMFreeToAllocator(MEMAllocator *allocator,
                   void *ptr);

/**
 * Initializes an allocator from an Expanded Heap.
 */
void
MEMInitAllocatorForExpHeap(MEMAllocator *allocator,
                           MEMHeapHandle heap,
                           uint32_t alignment);

/**
 * Initializes an allocator from a Frame Heap.
 */
void
MEMInitAllocatorForFrmHeap(MEMAllocator *allocator,
                           MEMHeapHandle heap,
                           uint32_t alignment);

/**
 * Initializes an allocator from a Unit Heap.
 */
void
MEMInitAllocatorForUnitHeap(MEMAllocator *allocator,
                            MEMHeapHandle heap);

/**
 * Initializes an allocator from the Default Heap.
 */
void
MEMInitAllocatorForDefaultHeap(MEMAllocator *allocator);

/**
 * Initializes an allocator from a Block Heap.
 */
void
MEMInitAllocatorForBlockHeap(MEMAllocator *allocator,
                             MEMHeapHandle heap,
                             uint32_t alignment);

#ifdef __cplusplus
}
#endif

/** @} */
