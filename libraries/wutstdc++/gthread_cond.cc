#include "include/bits/gthr-default.h"

void
__gthread_cond_init_function (__gthread_cond_t *__cond)
{
   OSInitCond(__cond);
}

int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
                               __gthread_recursive_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
   return 0;
}
