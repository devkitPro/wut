#include "wut_newlib.h"

#include <coreinit/atomic.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memexpheap.h>
#include <coreinit/memheap.h>

static MEMHeapHandle sHeapHandle   = NULL;
static void *sHeapBase             = NULL;
static uint32_t sHeapMaxSize       = 0;
static volatile uint32_t sHeapSize = 0;

void *
__wut_sbrk_r(struct _reent *r,
             ptrdiff_t incr)
{
   uint32_t newSize;
   uint32_t oldSize = sHeapSize;

   do {
      newSize = oldSize + incr;

      if (newSize > sHeapMaxSize) {
         r->_errno = ENOMEM;
         return (void *)-1;
      }
   } while (!OSCompareAndSwapAtomicEx(&sHeapSize, oldSize, newSize, &oldSize));

   return ((uint8_t *)sHeapBase) + oldSize;
}

void
__init_wut_sbrk_heap(MEMHeapHandle heapHandle)
{
   if (sHeapBase) {
      // Already initialised
      return;
   }

   sHeapHandle  = heapHandle;

   // Use all of the available memory for the custom heap
   sHeapMaxSize = MEMGetAllocatableSizeForExpHeapEx(sHeapHandle, 4);
   sHeapBase    = MEMAllocFromExpHeapEx(sHeapHandle, sHeapMaxSize, 4);

   sHeapSize    = 0;
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
   }

   sHeapBase    = NULL;
   sHeapSize    = 0;
   sHeapMaxSize = 0;
}
