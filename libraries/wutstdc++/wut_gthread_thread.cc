#include "wut_gthread.h"

#include <string.h>
#include <sys/errno.h>

static void
__wut_thread_deallocator(OSThread *thread,
                         void *stack)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   MEMFreeToExpHeap(heap, thread);
   MEMFreeToExpHeap(heap, stack);
}

static void
__wut_thread_cleanup(OSThread *thread, void *stack)
{
   __wut_key_cleanup(thread);
}

int
__wut_thread_create(OSThread **outThread,
                    void *(*entryPoint) (void*),
                    void *entryArgs)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   OSThread *thread = (OSThread *)MEMAllocFromExpHeapEx(heap, sizeof(OSThread), 8);
   char *stack = (char *)MEMAllocFromExpHeapEx(heap, __WUT_STACK_SIZE, 8);
   memset(thread, 0, sizeof(OSThread));

   if (!OSCreateThread(thread,
                       (OSThreadEntryPointFn)entryPoint,
                       (int)entryArgs,
                       NULL,
                       stack + __WUT_STACK_SIZE,
                       __WUT_STACK_SIZE,
                       16,
                       OS_THREAD_ATTRIB_AFFINITY_ANY)) {
      MEMFreeToExpHeap((MEMExpandedHeap*)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), thread);
      return EINVAL;
   }

   *outThread = thread;
   OSSetThreadDeallocator(thread, &__wut_thread_deallocator);
   OSSetThreadCleanupCallback(thread, &__wut_thread_cleanup);
   OSResumeThread(thread);
   return 0;
}

int
__wut_thread_join(OSThread *thread,
                  void **outValue)
{
   if (!OSJoinThread(thread, (int *)outValue)) {
      return EINVAL;
   }

   return 0;
}

int
__wut_thread_detach(OSThread * thread)
{
   OSDetachThread(thread);
   return 0;
}

int
__wut_thread_equal(OSThread *thread1,
                   OSThread *thread2)
{
   return thread1 == thread2;
}

OSThread *
__wut_thread_self()
{
   return OSGetCurrentThread();
}

int
__wut_thread_yield()
{
   OSYieldThread();
   return 0;
}
