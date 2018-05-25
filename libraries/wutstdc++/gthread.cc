#include "include/bits/gthr-default.h"

static void
__gthread_thread_deallocator(OSThread *thread, void *stack)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   MEMFreeToExpHeap(heap, thread);
   MEMFreeToExpHeap(heap, stack);
}

static void
__gthread_thread_cleanup(OSThread *thread, void *stack)
{
   __gthread_key_cleanup(thread);
}

int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*), void *__args)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   OSThread *thread = (OSThread *)MEMAllocFromExpHeapEx(heap, sizeof(OSThread), 8);
   char *stack = (char *)MEMAllocFromExpHeapEx(heap, __GTHREAD_STACK_SIZE, 8);
   memset(thread, 0, sizeof(OSThread));

   if (!OSCreateThread(thread,
                       (OSThreadEntryPointFn)__func,
                       (int)__args,
                       NULL,
                       stack + __GTHREAD_STACK_SIZE,
                       __GTHREAD_STACK_SIZE,
                       16,
                       OS_THREAD_ATTRIB_AFFINITY_ANY)) {
      MEMFreeToExpHeap((MEMExpandedHeap*)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), thread);
      return EINVAL;
   }

   *__threadid = thread;
   OSSetThreadDeallocator(thread, &__gthread_thread_deallocator);
   OSSetThreadCleanupCallback(thread, &__gthread_thread_cleanup);
   OSResumeThread(thread);
   return 0;
}

int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
   if (!OSJoinThread(__threadid, (int *)__value_ptr)) {
      return EINVAL;
   }

   return 0;
}

int
__gthread_detach (__gthread_t __threadid)
{
   OSDetachThread(__threadid);
   return 0;
}

int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
   return __t1 == __t2;
}

__gthread_t
__gthread_self (void)
{
   return OSGetCurrentThread();
}

int
__gthread_yield (void)
{
   OSYieldThread();
   return 0;
}
