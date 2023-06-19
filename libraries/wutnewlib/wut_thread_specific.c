#include "wut_thread_specific.h"
#include <coreinit/thread.h>
#include <wut.h>

void __attribute__((weak))
wut_set_thread_specific(__wut_thread_specific_id id, void *value) {
   OSSetThreadSpecific(OS_THREAD_SPECIFIC_WUT_RESERVED_0 + id - WUT_THREAD_SPECIFIC_0, value);
}

void *__attribute__((weak))
wut_get_thread_specific(__wut_thread_specific_id id) {
   return OSGetThreadSpecific(OS_THREAD_SPECIFIC_WUT_RESERVED_0 + id - WUT_THREAD_SPECIFIC_0);;
}