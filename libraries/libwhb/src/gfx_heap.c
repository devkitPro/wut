#include "gfx_heap.h"
#include <coreinit/memdefaultheap.h>
#include <coreinit/memexpheap.h>
#include <coreinit/memfrmheap.h>
#include <coreinit/memheap.h>
#include <whb/log.h>

static void *
        sGfxHeapMEM1 = NULL;

static void *
        sGfxHeapForeground = NULL;

#define GFX_FRAME_HEAP_TAG (0x123DECAF)

BOOL GfxHeapInitMEM1()
{
   MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
   uint32_t size;
   void *base;

   if (!MEMRecordStateForFrmHeap(heap, GFX_FRAME_HEAP_TAG)) {
      WHBLogPrintf("%s: MEMRecordStateForFrmHeap failed", __FUNCTION__);
      return FALSE;
   }

   size = MEMGetAllocatableSizeForFrmHeapEx(heap, 4);
   if (!size) {
      WHBLogPrintf("%s: MEMGetAllocatableSizeForFrmHeapEx == 0", __FUNCTION__);
      return FALSE;
   }

   base = MEMAllocFromFrmHeapEx(heap, size, 4);
   if (!base) {
      WHBLogPrintf("%s: MEMAllocFromFrmHeapEx(heap, 0x%X, 4) failed", __FUNCTION__, size);
      return FALSE;
   }

   sGfxHeapMEM1 = MEMCreateExpHeapEx(base, size, 0);
   if (!sGfxHeapMEM1) {
      WHBLogPrintf("%s: MEMCreateExpHeapEx(0x%08X, 0x%X, 0) failed", __FUNCTION__, base, size);
      return FALSE;
   }

   return TRUE;
}

BOOL GfxHeapDestroyMEM1()
{
   MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);

   if (sGfxHeapMEM1) {
      MEMDestroyExpHeap(sGfxHeapMEM1);
      sGfxHeapMEM1 = NULL;
   }

   MEMFreeByStateToFrmHeap(heap, GFX_FRAME_HEAP_TAG);
   return TRUE;
}

BOOL GfxHeapInitForeground()
{
   MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);
   uint32_t size;
   void *base;

   size = MEMGetAllocatableSizeForFrmHeapEx(heap, 4);
   if (!size) {
      WHBLogPrintf("%s: MEMAllocFromFrmHeapEx(heap, 0x%X, 4)", __FUNCTION__, size);
      return FALSE;
   }

   base = MEMAllocFromFrmHeapEx(heap, size, 4);
   if (!base) {
      WHBLogPrintf("%s: MEMGetAllocatableSizeForFrmHeapEx == 0", __FUNCTION__);
      return FALSE;
   }

   sGfxHeapForeground = MEMCreateExpHeapEx(base, size, 0);
   if (!sGfxHeapForeground) {
      WHBLogPrintf("%s: MEMCreateExpHeapEx(0x%08X, 0x%X, 0)", __FUNCTION__, base, size);
      return FALSE;
   }

   return TRUE;
}

BOOL GfxHeapDestroyForeground()
{
   MEMHeapHandle foreground = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);

   if (sGfxHeapForeground) {
      MEMDestroyExpHeap(sGfxHeapForeground);
      sGfxHeapForeground = NULL;
   }

   MEMFreeToFrmHeap(foreground, MEM_FRM_HEAP_FREE_ALL);
   return TRUE;
}

void *
GfxHeapAllocMEM1(uint32_t size,
                 uint32_t alignment)
{
   void *block;

   if (!sGfxHeapMEM1) {
      return NULL;
   }

   if (alignment < 4) {
      alignment = 4;
   }

   block = MEMAllocFromExpHeapEx(sGfxHeapMEM1, size, alignment);
   return block;
}

void GfxHeapFreeMEM1(void *block)
{
   if (!sGfxHeapMEM1) {
      return;
   }

   MEMFreeToExpHeap(sGfxHeapMEM1, block);
}

void *
GfxHeapAllocForeground(uint32_t size,
                       uint32_t alignment)
{
   void *block;

   if (!sGfxHeapForeground) {
      return NULL;
   }

   if (alignment < 4) {
      alignment = 4;
   }

   block = MEMAllocFromExpHeapEx(sGfxHeapForeground, size, alignment);
   return block;
}

void GfxHeapFreeForeground(void *block)
{
   if (!sGfxHeapForeground) {
      return;
   }

   MEMFreeToExpHeap(sGfxHeapForeground, block);
}

void *
GfxHeapAllocMEM2(uint32_t size,
                 uint32_t alignment)
{
   if (alignment < 4) {
      alignment = 4;
   }

   return MEMAllocFromDefaultHeapEx(size, alignment);
}

void GfxHeapFreeMEM2(void *block)
{
   MEMFreeToDefaultHeap(block);
}
