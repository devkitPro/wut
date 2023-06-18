#include "wut_newlib.h"
#include "wut_thread_specific.h"
#include <stdlib.h>

#include <coreinit/thread.h>

#define __WUT_CONTEXT_THREAD_SPECIFIC_ID WUT_THREAD_SPECIFIC_1

struct __wut_thread_context {
    struct _reent reent;
    OSThreadCleanupCallbackFn savedCleanup;
};

static void
__wut_thread_cleanup(OSThread *thread,
                     void *stack) {
   struct __wut_thread_context *context;

   context = (struct __wut_thread_context *) wut_get_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID);
   if (!context || &context->reent == _GLOBAL_REENT) {
      abort();
   }

   if (context->savedCleanup) {
      context->savedCleanup(thread, stack);
   }

   _reclaim_reent(&context->reent);

   // Use global reent during free since the current reent is getting freed
   wut_set_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID, _GLOBAL_REENT);

   free(context);

   wut_set_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID, NULL);
}

struct _reent *
__wut_getreent(void) {
   struct __wut_thread_context *context;

   context = (struct __wut_thread_context *) wut_get_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID);
   if (!context) {
      // Temporarily use global reent during context allocation
      wut_set_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID, _GLOBAL_REENT);

      context = (struct __wut_thread_context *) malloc(sizeof(*context));
      if (!context) {
         wut_set_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID, NULL);
         return NULL;
      }

      _REENT_INIT_PTR(&context->reent);
      context->savedCleanup = OSSetThreadCleanupCallback(OSGetCurrentThread(), &__wut_thread_cleanup);

      wut_set_thread_specific(__WUT_CONTEXT_THREAD_SPECIFIC_ID, context);
   }

   return &context->reent;
}
