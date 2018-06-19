#pragma once
#include <wut.h>
#include "spinlock.h"
#include "memlist.h"

/**
 * \defgroup coreinit_memheap Common Memory Heap
 * \ingroup coreinit
 *
 * Common memory heap fucntions.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMHeapHeader MEMHeapHeader;
typedef MEMHeapHeader *MEMHeapHandle;

typedef enum MEMBaseHeapType
{
   MEM_BASE_HEAP_MEM1   = 0,
   MEM_BASE_HEAP_MEM2   = 1,
   MEM_BASE_HEAP_FG     = 8,
} MEMBaseHeapType;

typedef enum MEMHeapFillType
{
   MEM_HEAP_FILL_TYPE_UNUSED    = 0,
   MEM_HEAP_FILL_TYPE_ALLOCATED = 1,
   MEM_HEAP_FILL_TYPE_FREED     = 2,
} MEMHeapFillType;

typedef enum MEMHeapTag
{
  MEM_BLOCK_HEAP_TAG      = 0x424C4B48u,
  MEM_EXPANDED_HEAP_TAG   = 0x45585048u,
  MEM_FRAME_HEAP_TAG      = 0x46524D48u,
  MEM_UNIT_HEAP_TAG       = 0x554E5448u,
  MEM_USER_HEAP_TAG       = 0x55535248u,
} MEMHeapTag;

typedef enum MEMHeapFlags
{
  MEM_HEAP_FLAG_ZERO_ALLOCATED  = 1 << 0,
  MEM_HEAP_FLAG_DEBUG_MODE      = 1 << 1,
  MEM_HEAP_FLAG_USE_LOCK        = 1 << 2,
} MEMHeapFlags;

struct MEMHeapHeader
{
   //! Tag indicating which type of heap this is
   MEMHeapTag tag;

   //! Link for list this heap is in
   MEMMemoryLink link;

   //! List of all child heaps in this heap
   MEMMemoryList list;

   //! Pointer to start of allocatable memory
   void *dataStart;

   //! Pointer to end of allocatable memory
   void *dataEnd;

   //! Lock used when MEM_HEAP_FLAG_USE_LOCK is set.
   OSSpinLock lock;

   //! Flags set during heap creation.
   uint32_t flags;

   WUT_UNKNOWN_BYTES(0x0C);
};
WUT_CHECK_OFFSET(MEMHeapHeader, 0x00, tag);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x04, link);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x0C, list);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x18, dataStart);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x1C, dataEnd);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x20, lock);
WUT_CHECK_OFFSET(MEMHeapHeader, 0x30, flags);
WUT_CHECK_SIZE(MEMHeapHeader, 0x40);


/**
 * Get which memory area a heap belongs to.
 */
MEMBaseHeapType
MEMGetArena(MEMHeapHandle handle);


/**
 * Get base heap for memory area.
 */
MEMHeapHandle
MEMGetBaseHeapHandle(MEMBaseHeapType type);


/**
 * Set base heap for memory area.
 */
MEMHeapHandle
MEMSetBaseHeapHandle(MEMBaseHeapType type,
                     MEMHeapHandle handle);

/**
 * Create a heap handle for a user defined heap.
 */
MEMHeapHandle
MEMCreateUserHeapHandle(void *heap,
                        uint32_t size);

/**
 * Print details about heap to COSWarn
 */
void
MEMDumpHeap(MEMHeapHandle heap);


/**
 * Find heap which contains a memory block.
 */
MEMHeapHeader *
MEMFindContainHeap(void *block);

/**
 * Find the parent heap of a given heap. Return NULL if no parent was found.
 */
MEMHeapHandle
MEMFindParentHeap(MEMHeapHandle handle);

/**
 * Get the data fill value used when MEM_HEAP_FLAG_DEBUG_MODE is set.
 */
uint32_t
MEMGetFillValForHeap(MEMHeapFillType type);


/**
 * Set the data fill value used when MEM_HEAP_FLAG_DEBUG_MODE is set.
 */
void
MEMSetFillValForHeap(MEMHeapFillType type,
                     uint32_t value);

#ifdef __cplusplus
}
#endif

/** @} */
