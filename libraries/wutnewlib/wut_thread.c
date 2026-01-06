#include "wut_newlib.h"

#include <string.h>

#include <coreinit/spinlock.h>
#include <coreinit/atomic.h>
#include <coreinit/fastmutex.h>
#include <coreinit/fastcondition.h>
#include <coreinit/thread.h>
#include <coreinit/core.h>
#include <coreinit/memdefaultheap.h>

static OSSpinLock sSyncSpinLock;
static OSSpinLock sMallocSpinLock;

void
__init_wut_thread()
{
   OSInitSpinLock(&sSyncSpinLock);
   OSInitSpinLock(&sMallocSpinLock);
}

static OSFastMutex*
__wut_get_mutex(_LOCK_T *lock)
{
   if (*lock) {
      return (OSFastMutex*)*lock;
   }

   OSUninterruptibleSpinLock_Acquire(&sSyncSpinLock);

   OSFastMutex* m = (OSFastMutex*)*lock;
   if (!m) {
      m = MEMAllocFromDefaultHeap(sizeof(OSFastMutex));
      OSFastMutex_Init(m, NULL);
      *lock = (uint32_t)m;
   }

   OSUninterruptibleSpinLock_Release(&sSyncSpinLock);

   return m;
}

static OSFastCondition*
__wut_get_cond(_COND_T *cond)
{
   if (*cond) {
      return (OSFastCondition*)*cond;
   }

   OSUninterruptibleSpinLock_Acquire(&sSyncSpinLock);

   OSFastCondition* c = (OSFastCondition*)*cond;
   if (!c) {
      c = MEMAllocFromDefaultHeap(sizeof(OSFastCondition));
      OSFastCond_Init(c, NULL);
      *cond = (uint32_t)c;
   }

   OSUninterruptibleSpinLock_Release(&sSyncSpinLock);

   return c;
}

void
__SYSCALL(malloc_lock)(struct _reent *ptr)
{
   OSUninterruptibleSpinLock_Acquire(&sMallocSpinLock);
}

void
__SYSCALL(malloc_unlock)(struct _reent *ptr)
{
   OSUninterruptibleSpinLock_Release(&sMallocSpinLock);
}

void
__SYSCALL(lock_close)(_LOCK_T *lock)
{
   if (*lock) {
      MEMFreeToDefaultHeap((void*)*lock);
      *lock = 0;
   }
}

void
__SYSCALL(lock_acquire)(_LOCK_T *lock)
{
   OSFastMutex_Lock(__wut_get_mutex(lock));
}

int
__SYSCALL(lock_try_acquire)(_LOCK_T *lock)
{
   return OSFastMutex_TryLock(__wut_get_mutex(lock));
}

void
__SYSCALL(lock_release)(_LOCK_T *lock)
{
   OSFastMutex_Unlock(__wut_get_mutex(lock));
}

void
__SYSCALL(lock_close_recursive)(_LOCK_RECURSIVE_T *lock)
{
   __SYSCALL(lock_close)(&lock->lock);
}

void
__SYSCALL(lock_acquire_recursive)(_LOCK_RECURSIVE_T *lock)
{
   __SYSCALL(lock_acquire)(&lock->lock);
}

int32_t
__SYSCALL(lock_try_acquire_recursive)(_LOCK_RECURSIVE_T *lock)
{
   return __SYSCALL(lock_try_acquire)(&lock->lock);
}

void
__SYSCALL(lock_release_recursive)(_LOCK_RECURSIVE_T *lock)
{
   __SYSCALL(lock_release)(&lock->lock);
}

void
__SYSCALL(cond_close)(_COND_T *cond)
{
   if (*cond) {
      MEMFreeToDefaultHeap((void*)*cond);
      *cond = 0;
   }
}

int
__SYSCALL(cond_signal)(_COND_T *cond)
{
   OSFastCond_Signal(__wut_get_cond(cond)); // XX: this is broadcast
   return 0;
}

int
__SYSCALL(cond_broadcast)(_COND_T *cond)
{
   OSFastCond_Signal(__wut_get_cond(cond));
   return 0;
}

typedef struct {
   OSFastCondition *cond;
   bool timed_out;
} __wut_condwait_t;

static void
__wut_cond_alarmcb(OSAlarm *alarm, OSContext *context)
{
   __wut_condwait_t *data = OSGetAlarmUserData(alarm);
   data->timed_out        = true;
   OSFastCond_Signal(data->cond);
}

int
__SYSCALL(cond_wait)(_COND_T *cond, _LOCK_T *lock, uint64_t timeout_ns)
{
   if (timeout_ns == UINT64_MAX) {
      OSFastCond_Wait(__wut_get_cond(cond), __wut_get_mutex(lock));
      return 0;
   }

   __wut_condwait_t data;
   data.cond      = __wut_get_cond(cond);
   data.timed_out = false;

   OSAlarm alarm;
   OSCreateAlarm(&alarm);
   OSSetAlarmUserData(&alarm, &data);
   OSSetAlarm(&alarm, OSNanosecondsToTicks(timeout_ns), __wut_cond_alarmcb);
   OSFastCond_Wait(data.cond, __wut_get_mutex(lock));
   OSCancelAlarm(&alarm);

   return data.timed_out ? ETIMEDOUT : 0;
}

int
__SYSCALL(cond_wait_recursive)(_COND_T *cond, _LOCK_RECURSIVE_T *lock, uint64_t timeout_ns)
{
   return __SYSCALL(cond_wait)(cond, &lock->lock, timeout_ns);
}

struct __pthread_t {
	OSThread base;
};

int
__SYSCALL(thread_create)(struct __pthread_t **thread, void* (*func)(void*), void *arg, void *stack_addr, size_t stack_size)
{
   if (!stack_size) {
      stack_size = __WUT_STACK_SIZE;
   }

   uint32_t alloc_size = sizeof(struct __pthread_t);
   alloc_size = (alloc_size + 15) &~ 15;
   stack_size = stack_size &~ 15;

   if (!stack_addr) {
      alloc_size += stack_size;
   }

   struct __pthread_t *t = MEMAllocFromDefaultHeapEx(alloc_size, 0x10);
   if (!t) {
      return ENOMEM;
   }

   memset(t, 0, sizeof(*t));

   if (!stack_addr) {
      stack_addr = (char*)t + alloc_size;
   } else {
      stack_addr = (char*)stack_addr + stack_size;
   }

   BOOL ok = OSCreateThread(
      &t->base,
      (OSThreadEntryPointFn)func,
      (int32_t)arg,
      NULL,
      stack_addr,
      stack_size,
      16,
      OS_THREAD_ATTRIB_AFFINITY_ANY
   );

   if (!ok) {
      MEMFreeToDefaultHeap(t);
      return EINVAL;
   }

   *thread = t;
   OSSetThreadDeallocator(&t->base, (OSThreadDeallocatorFn)MEMFreeToDefaultHeap);
   //XX: OSSetThreadCleanupCallback: use to free TLS slots

   // Enable timeslicing, using 1ms as the thread run quantum
   OSSetThreadRunQuantum(&t->base, 1000);

   OSResumeThread(&t->base);
   return 0;
}

void*
__SYSCALL(thread_join)(struct __pthread_t *thread)
{
   int res = 0;
   OSJoinThread(&thread->base, &res); // XX: assert?
   return (void*)res;
}

int
__SYSCALL(thread_detach)(struct __pthread_t *thread)
{
   OSDetachThread(&thread->base);
   return 0;
}

void
__SYSCALL(thread_exit)(void *value)
{
   OSExitThread((int)value);
}

struct __pthread_t *
__SYSCALL(thread_self)(void)
{
   return (struct __pthread_t*)OSGetCurrentThread();
}

int sched_yield(void)
{
   OSYieldThread();
   return 0;
}

int sched_getcpu(void)
{
   return OSGetCoreId();
}
