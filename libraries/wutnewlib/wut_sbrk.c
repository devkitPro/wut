#include "wut_newlib.h"

#include <coreinit/atomic.h>
#include <coreinit/memheap.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memexpheap.h>

extern uint32_t __attribute__((weak)) __wut_heap_max_size;

static MEMHeapHandle sHeapHandle = NULL;
static void *sHeapBase = NULL;
static uint32_t sHeapMaxSize = 0;
static volatile uint32_t sHeapSize = 0;

void *
__wut_sbrk_r(struct _reent *r,
             ptrdiff_t incr)
{
   uint32_t oldSize, newSize;

   do {
      oldSize = sHeapSize;
      newSize = oldSize + incr;

      if (newSize > sHeapMaxSize) {
         r->_errno = ENOMEM;
         return (void *)-1;
      }
   } while (!OSCompareAndSwapAtomic(&sHeapSize, oldSize, newSize));

   return ((uint8_t *)sHeapBase) + oldSize;
}

void
__init_wut_sbrk_heap()
{
   if (sHeapBase) {
      // Already initialised
      return;
   }

   if (&__wut_heap_max_size) {
      // Use default heap
      sHeapBase = MEMAllocFromDefaultHeap(__wut_heap_max_size);
      sHeapMaxSize = __wut_heap_max_size;
   } else {
      // No max size specified, use 90% of base MEM2 heap
      sHeapHandle = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);

      uint32_t freeSize = MEMGetAllocatableSizeForExpHeapEx(sHeapHandle, 4);
      sHeapMaxSize = (uint32_t)(0.9f * (float)freeSize) & ~0xFFF;

      sHeapBase = MEMAllocFromExpHeapEx(sHeapHandle, sHeapMaxSize, 4);
   }

   sHeapSize = 0;
}

void
__fini_wut_sbrk_heap()
{
   if (!sHeapBase) {
      // Already finalised
      return;
   }

   if (sHeapHandle) {
      MEMFreeToExpHeap(sHeapHandle, sHeapBase);
   } else {
      MEMFreeToDefaultHeap(sHeapBase);
   }

   sHeapBase = NULL;
   sHeapSize = 0;
   sHeapMaxSize = 0;
}
