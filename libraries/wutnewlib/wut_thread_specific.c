#include "wut_thread_specific.h"
#include <coreinit/thread.h>
#include <wut.h>

void wut_set_thread_specific(__wut_thread_specific_id id, void *value) {
   OSThread *thread = OSGetCurrentThread();
   if (thread != NULL && id >= WUT_THREAD_SPECIFIC_0 && id <= WUT_THREAD_SPECIFIC_4) {
      thread->wut_specifics[id] = value;
   } else {
      WUT_DEBUG_REPORT("wut_set_thread_specific: invalid thread or id\n");
   }
}

void *wut_get_thread_specific(__wut_thread_specific_id id) {
   OSThread *thread = OSGetCurrentThread();
   if (thread != NULL && id >= WUT_THREAD_SPECIFIC_0 && id <= WUT_THREAD_SPECIFIC_4) {
      return thread->wut_specifics[id];
   } else {
      WUT_DEBUG_REPORT("wut_get_thread_specific: invalid thread or id\n");
   }
   return NULL;
}