#include "wut_newlib.h"

#include <coreinit/atomic.h>
#include <coreinit/memdefaultheap.h>

static uint8_t *sHeapBase = NULL;
static uint32_t sHeapMaxSize = 128 * 1024;
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
   sHeapMaxSize = 128 * 1024;
   sHeapBase = (uint8_t *)MEMAllocFromDefaultHeap(sHeapMaxSize);
   sHeapSize = 0;
}

void
__fini_wut_sbrk_heap()
{
   MEMFreeToDefaultHeap(sHeapBase);
   sHeapBase = NULL;
   sHeapSize = 0;
   sHeapMaxSize = 0;
}
