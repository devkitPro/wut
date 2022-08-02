#include "wut_newlib.h"

#include <coreinit/mutex.h>
#include <coreinit/atomic.h>

#define MAX_LOCKS 16

static OSMutex sLibcLocks[MAX_LOCKS];
static volatile uint32_t sLibcLockUsedMask = 0;

static inline bool
__wut_is_lock_valid(int *lock)
{
   return lock && *lock >= 0 && *lock < MAX_LOCKS;
}

int
__wut_lock_init(int *lock,
                int recursive)
{
   if (!lock) {
      return -1;
   }

   int slot;
   uint32_t new_mask;
   uint32_t cur_mask = sLibcLockUsedMask;
   do {
      slot = __builtin_ffs(~cur_mask)-1;
      if (slot < 0 || slot >= MAX_LOCKS) break;
      new_mask = cur_mask | (1U << slot);
   } while (!OSCompareAndSwapAtomicEx(&sLibcLockUsedMask, cur_mask, new_mask, &cur_mask));

   if (slot < 0 || slot >= MAX_LOCKS) {
      return -1;
   }

   *lock = slot;
   OSInitMutex(&sLibcLocks[*lock]);
   return 0;
}

int
__wut_lock_close(int *lock)
{
   if (!__wut_is_lock_valid(lock)) {
      return -1;
   }

   uint32_t new_mask;
   uint32_t cur_mask = sLibcLockUsedMask;
   do {
      new_mask = cur_mask &~ (1U << *lock);
   } while (!OSCompareAndSwapAtomicEx(&sLibcLockUsedMask, cur_mask, new_mask, &cur_mask));

   *lock = -1;
   return 0;
}

int
__wut_lock_acquire(int *lock)
{
   if (!__wut_is_lock_valid(lock)) {
      return -1;
   }

   OSLockMutex(&sLibcLocks[*lock]);
   return 0;
}

int
__wut_lock_release(int *lock)
{
   if (!__wut_is_lock_valid(lock)) {
      return -1;
   }

   OSUnlockMutex(&sLibcLocks[*lock]);
   return 0;
}
