#include "gfx_heap.h"
#include <coreinit/baseheap.h>
#include <coreinit/expandedheap.h>
#include <coreinit/frameheap.h>
#include <defaultheap.h>

static void *
sGfxHeapMEM1 = NULL;

static void *
sGfxHeapForeground = NULL;

BOOL
GfxHeapInitMEM1()
{
   MEMHeapHandle mem1 = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
   uint32_t size = MEMGetAllocatableSizeForFrmHeapEx(mem1, 4);
   if (!size) {
      return FALSE;
   }

   void *base = MEMAllocFromFrmHeapEx(mem1, size, 4);
   if (!base) {
      return FALSE;
   }

   sGfxHeapMEM1 = MEMCreateExpHeapEx(base, size, 0);
   if (!sGfxHeapMEM1) {
      return FALSE;
   }

   return TRUE;
}

BOOL
GfxHeapDestroyMEM1()
{
   MEMHeapHandle mem1 = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);

   if (sGfxHeapMEM1) {
      MEMDestroyExpHeap(sGfxHeapMEM1);
      sGfxHeapMEM1 = NULL;
   }

   MEMFreeToFrmHeap(mem1, MEM_FRAME_HEAP_FREE_ALL);
   return TRUE;
}

BOOL
GfxHeapInitForeground()
{
   MEMHeapHandle mem1 = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);
   uint32_t size = MEMGetAllocatableSizeForFrmHeapEx(mem1, 4);
   if (!size) {
      return FALSE;
   }

   void *base = MEMAllocFromFrmHeapEx(mem1, size, 4);
   if (!base) {
      return FALSE;
   }

   sGfxHeapForeground = MEMCreateExpHeapEx(base, size, 0);
   if (!sGfxHeapForeground) {
      return FALSE;
   }

   return TRUE;
}

BOOL
GfxHeapDestroyForeground()
{
   MEMHeapHandle foreground = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);

   if (sGfxHeapForeground) {
      MEMDestroyExpHeap(sGfxHeapForeground);
      sGfxHeapForeground = NULL;
   }

   MEMFreeToFrmHeap(foreground, MEM_FRAME_HEAP_FREE_ALL);
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

void
GfxHeapFreeMEM1(void *block)
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

void
GfxHeapFreeForeground(void *block)
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

void
GfxHeapFreeMEM2(void *block)
{
   MEMFreeToDefaultHeap(block);
}
