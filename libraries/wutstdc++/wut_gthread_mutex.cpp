#include "wut_gthread.h"

void __wut_mutex_init_function(OSMutex *mutex)
{
   OSInitMutex(mutex);
}

int __wut_mutex_lock(OSMutex *mutex)
{
   OSLockMutex(mutex);
   return 0;
}

int __wut_mutex_trylock(OSMutex *mutex)
{
   if (!OSTryLockMutex(mutex)) {
      return -1;
   }

   return 0;
}

int __wut_mutex_unlock(OSMutex *mutex)
{
   OSUnlockMutex(mutex);
   return 0;
}

int __wut_mutex_destroy(OSMutex *mutex)
{
   return 0;
}
