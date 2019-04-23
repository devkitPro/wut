#include "wut_gthread.h"

int
__wut_recursive_mutex_init_function(OSMutex *mutex)
{
   OSInitMutex(mutex);
   return 0;
}

int
__wut_recursive_mutex_lock(OSMutex *mutex)
{
   OSLockMutex(mutex);
   return 0;
}

int
__wut_recursive_mutex_trylock(OSMutex *mutex)
{
   if (!OSTryLockMutex(mutex)) {
      return -1;
   }

   return 0;
}

int
__wut_recursive_mutex_unlock(OSMutex *mutex)
{
   OSUnlockMutex(mutex);
   return 0;
}

int
__wut_recursive_mutex_destroy(OSMutex *mutex)
{
   return 0;
}
