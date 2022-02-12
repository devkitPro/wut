#include "wut_newlib.h"

#include <coreinit/mutex.h>
#include <malloc.h>

int __wut_lock_init(int *lock,
                    int recursive)
{
   OSMutex *mutex = NULL;
   if (!lock) {
      return -1;
   }

   mutex = (OSMutex *) malloc(sizeof(OSMutex));
   if (!mutex) {
      return -1;
   }

   OSInitMutex(mutex);
   *lock = (int) mutex;
   return 0;
}

int __wut_lock_close(int *lock)
{
   if (!lock || *lock == 0) {
      return -1;
   }

   free((void *) *lock);
   *lock = 0;
   return 0;
}

int __wut_lock_acquire(int *lock)
{
   OSMutex *mutex = (OSMutex *) *lock;
   if (!lock || *lock == 0) {
      return -1;
   }

   OSLockMutex(mutex);
   return 0;
}

int __wut_lock_release(int *lock)
{
   OSMutex *mutex = (OSMutex *) *lock;
   if (!lock || *lock == 0) {
      return -1;
   }

   OSUnlockMutex(mutex);
   return 0;
}
