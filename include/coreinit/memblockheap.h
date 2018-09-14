#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_memblockheap Block Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMBlockHeapBlock MEMBlockHeapBlock;
typedef struct MEMBlockHeapTracking MEMBlockHeapTracking;
typedef struct MEMBlockHeap MEMBlockHeap;

struct MEMBlockHeapTracking
{
   WUT_UNKNOWN_BYTES(0x8);

   //! Pointer to first memory block
   MEMBlockHeapBlock *blocks;

   //! Number of blocks in this tracking heap
   uint32_t blockCount;
};
WUT_CHECK_OFFSET(MEMBlockHeapTracking, 0x08, blocks);
WUT_CHECK_OFFSET(MEMBlockHeapTracking, 0x0C, blockCount);
WUT_CHECK_SIZE(MEMBlockHeapTracking, 0x10);

struct MEMBlockHeapBlock
{
   //! First address of the data region this block has allocated
   void *start;

   //! End address of the data region this block has allocated
   void *end;

   //! TRUE if the block is free, FALSE if allocated
   BOOL isFree;

   //! Link to previous block, note that this is only set for allocated blocks
   MEMBlockHeapBlock *prev;

   //! Link to next block, always set
   MEMBlockHeapBlock *next;
};
WUT_CHECK_OFFSET(MEMBlockHeapBlock, 0x00, start);
WUT_CHECK_OFFSET(MEMBlockHeapBlock, 0x04, end);
WUT_CHECK_OFFSET(MEMBlockHeapBlock, 0x08, isFree);
WUT_CHECK_OFFSET(MEMBlockHeapBlock, 0x0c, prev);
WUT_CHECK_OFFSET(MEMBlockHeapBlock, 0x10, next);
WUT_CHECK_SIZE(MEMBlockHeapBlock, 0x14);

struct WUT_PACKED MEMBlockHeap
{
   MEMHeapHeader header;

   //! Default tracking heap, tracks only defaultBlock
   MEMBlockHeapTracking defaultTrack;

   //! Default block, used so we don't have an empty block list
   MEMBlockHeapBlock defaultBlock;

   //! First block in this heap
   MEMBlockHeapBlock *firstBlock;

   //! Last block in this heap
   MEMBlockHeapBlock *lastBlock;

   //! First free block
   MEMBlockHeapBlock *firstFreeBlock;

   //! Free block count
   uint32_t numFreeBlocks;
};
WUT_CHECK_OFFSET(MEMBlockHeap, 0x00, header);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x40, defaultTrack);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x50, defaultBlock);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x64, firstBlock);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x68, lastBlock);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x6C, firstFreeBlock);
WUT_CHECK_OFFSET(MEMBlockHeap, 0x70, numFreeBlocks);
WUT_CHECK_SIZE(MEMBlockHeap, 0x74);

MEMHeapHandle
MEMInitBlockHeap(MEMBlockHeap *heap,
                 void *start,
                 void *end,
                 MEMBlockHeapTracking *blocks,
                 uint32_t size,
                 uint32_t flags);

void *
MEMDestroyBlockHeap(MEMHeapHandle heap);

int
MEMAddBlockHeapTracking(MEMHeapHandle heap,
                        MEMBlockHeapTracking *tracking,
                        uint32_t size);

void *
MEMAllocFromBlockHeapAt(MEMHeapHandle heap,
                        void *addr,
                        uint32_t size);

void *
MEMAllocFromBlockHeapEx(MEMHeapHandle heap,
                        uint32_t size,
                        int32_t align);

void
MEMFreeToBlockHeap(MEMHeapHandle heap,
                   void *data);

uint32_t
MEMGetAllocatableSizeForBlockHeapEx(MEMHeapHandle heap,
                                    int32_t align);

uint32_t
MEMGetTrackingLeftInBlockHeap(MEMHeapHandle heap);

uint32_t
MEMGetTotalFreeSizeForBlockHeap(MEMHeapHandle heap);

#ifdef __cplusplus
}
#endif

/** @} */
