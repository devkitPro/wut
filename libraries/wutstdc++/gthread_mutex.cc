#include "include/bits/gthr-default.h"

void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
   OSInitMutex(__mutex);
}

int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
   OSLockMutex(__mutex);
   return 0;
}

int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
   if (!OSTryLockMutex(__mutex)) {
      return -1;
   }

   return 0;
}

int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
   OSUnlockMutex(__mutex);
   return 0;
}

int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
   return 0;
}
