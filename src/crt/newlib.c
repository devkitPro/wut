#include <wut.h>

#include <coreinit/atomic.h>
#include <coreinit/baseheap.h>
#include <coreinit/exit.h>
#include <coreinit/expandedheap.h>
#include <coreinit/mutex.h>
#include <coreinit/time.h>

#include <malloc.h>
#include <sys/errno.h>
#include <sys/iosupport.h>
#include <sys/reent.h>
#include <sys/time.h>

static OSMutex sMallocMutex;
static uint8_t *sHeapBase = NULL;
static uint32_t sHeapMaxSize = 0;
static volatile uint32_t sHeapSize = 0;

void
__init_wut_newlibc();

static void *__libwut_sbrk_r(struct _reent *r,
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

static int __libwut_lock_init(int *lock,
                              int recursive)
{
   OSMutex *mutex = NULL;
   if (!lock) {
      return -1;
   }

   mutex = (OSMutex *)malloc(sizeof(OSMutex));
   if (!mutex) {
      return -1;
   }

   OSInitMutex(mutex);
   *lock = (int)mutex;
   return 0;
}

static int __libwut_lock_close(int *lock)
{
   if (!lock || *lock == 0) {
      return -1;
   }

   free((void *)*lock);
   *lock = 0;
   return 0;
}

static int __libwut_lock_acquire(int *lock)
{
   OSMutex *mutex = (OSMutex *)*lock;
   if (!lock || *lock == 0) {
      return -1;
   }

   OSLockMutex(mutex);
   return 0;
}

static int __libwut_lock_release(int *lock)
{
   OSMutex *mutex = (OSMutex *)*lock;
   if (!lock || *lock == 0) {
      return -1;
   }

   OSUnlockMutex(mutex);
   return 0;
}

static void __libwut_malloc_lock(struct _reent *r)
{
   OSLockMutex(&sMallocMutex);
}

static void __libwut_malloc_unlock(struct _reent *r)
{
   OSUnlockMutex(&sMallocMutex);
}

static void __libwut_exit(int code)
{
   exit(code);
}

static int __libwut_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz)
{
   OSCalendarTime tm;
   OSTicksToCalendarTime(OSGetTime(), &tm);

   if (tp != NULL) {
      tp->tv_sec = tm.tm_sec;
      tp->tv_usec = tm.tm_usec + tm.tm_msec * 1000;
   }

   if (tz != NULL) {
      tz->tz_minuteswest = 0;
      tz->tz_dsttime = 0;
   }

   return 0;
}

static void
__init_malloc_lock()
{
   OSInitMutex(&sMallocMutex);
}

static void
__init_libc_heap()
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   uint32_t freeSize = MEMGetAllocatableSizeForExpHeapEx(heap, 0x1000);

   sHeapMaxSize = (uint32_t)(0.9f * (float)freeSize) & ~0xFFF;
   sHeapBase = (uint8_t *)MEMAllocFromExpHeapEx(heap, sHeapMaxSize, 0x1000);
   sHeapSize = 0;
}

static void
__free_libc_heap()
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   MEMFreeToExpHeap(heap, sHeapBase);
}

static void
__init_syscall_array()
{
   __syscalls.sbrk_r = __libwut_sbrk_r;
   __syscalls.lock_init = __libwut_lock_init;
   __syscalls.lock_close = __libwut_lock_close;
   __syscalls.lock_acquire = __libwut_lock_acquire;
   __syscalls.lock_release = __libwut_lock_release;
   __syscalls.malloc_lock = __libwut_malloc_lock;
   __syscalls.malloc_unlock = __libwut_malloc_unlock;
   __syscalls.exit = __libwut_exit;
   __syscalls.gettod_r = __libwut_gettod_r;
}

void
__init_wut_newlibc()
{
   __init_libc_heap();
   __init_malloc_lock();
   __init_syscall_array();
}
