#include "wut_newlib.h"

#include <coreinit/mutex.h>
#include <malloc.h>

#define MAX_LOCKS 16

static OSMutex sLibcLocks[MAX_LOCKS];
static uint32_t sLibcLockUsedMask = 0;

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
   uint32_t cur_mask = __atomic_load_n(&sLibcLockUsedMask, __ATOMIC_SEQ_CST);
   do {
      slot = __builtin_ffs(~cur_mask)-1;
      if (slot < 0 || slot >= MAX_LOCKS) break;
      new_mask = cur_mask | (1U << slot);
   } while (!__atomic_compare_exchange_n(&sLibcLockUsedMask, &cur_mask, new_mask, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));

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
   uint32_t cur_mask = __atomic_load_n(&sLibcLockUsedMask, __ATOMIC_SEQ_CST);
   do {
      new_mask = cur_mask &~ (1U << *lock);
   } while (!__atomic_compare_exchange_n(&sLibcLockUsedMask, &cur_mask, new_mask, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));

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
