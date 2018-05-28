#include "wut_newlib.h"

#include <coreinit/atomic.h>
#include <coreinit/baseheap.h>
#include <coreinit/expandedheap.h>

static uint8_t *sHeapBase = NULL;
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

   return sHeapBase + oldSize;
}

void
__init_wut_sbrk_heap()
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   uint32_t freeSize = MEMGetAllocatableSizeForExpHeapEx(heap, 0x1000);

   sHeapMaxSize = (uint32_t)(0.9f * (float)freeSize) & ~0xFFF;
   sHeapBase = (uint8_t *)MEMAllocFromExpHeapEx(heap, sHeapMaxSize, 0x1000);
   sHeapSize = 0;
}

void
__fini_wut_sbrk_heap()
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   MEMFreeToExpHeap(heap, sHeapBase);
}
