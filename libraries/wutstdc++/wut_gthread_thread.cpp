#include "wut_gthread.h"

#include <malloc.h>
#include <string.h>
#include <sys/errno.h>

static void
__wut_thread_deallocator(OSThread *thread,
                         void *stack)
{
   free(thread);
   free(stack);
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
   OSThread *thread = (OSThread *)memalign(16, sizeof(OSThread));
   if (!thread) {
      return ENOMEM;
   }   
   memset(thread, 0, sizeof(OSThread));

   char *stack = (char *)memalign(16, __WUT_STACK_SIZE);
   if (!stack) {
      free(thread);
      return ENOMEM;
   }

   if (!OSCreateThread(thread,
                       (OSThreadEntryPointFn)entryPoint,
                       (int)entryArgs,
                       NULL,
                       stack + __WUT_STACK_SIZE,
                       __WUT_STACK_SIZE,
                       16,
                       OS_THREAD_ATTRIB_AFFINITY_ANY)) {
      free(thread);
      free(stack);
      return EINVAL;
   }

   *outThread = thread;
   OSSetThreadDeallocator(thread, &__wut_thread_deallocator);
   OSSetThreadCleanupCallback(thread, &__wut_thread_cleanup);

   // Set a thread run quantum to 1 millisecond, to force the threads to
   // behave more like pre-emptive scheduling rather than co-operative.
   OSSetThreadRunQuantum(thread, 1000);

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
