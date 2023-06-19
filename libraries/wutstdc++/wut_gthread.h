#pragma once
#include <bits/gthr-default.h>

#include <coreinit/atomic.h>
#include <coreinit/condition.h>
#include <coreinit/thread.h>
#include <coreinit/mutex.h>

#include "../wutnewlib/wut_thread_specific.h"

#define __WUT_MAX_KEYS (128)
#define __WUT_STACK_SIZE (128*1024)

#define __WUT_ONCE_VALUE_INIT (0)
#define __WUT_ONCE_VALUE_STARTED (1)
#define __WUT_ONCE_VALUE_DONE (2)

#define __WUT_KEY_THREAD_SPECIFIC_ID WUT_THREAD_SPECIFIC_0

typedef volatile uint32_t __wut_once_t;
typedef struct {
   uint32_t index;
} __wut_key_t;

void
__init_wut_gthread();

int
__wut_active_p();

int
__wut_thread_create(OSThread **outThread,
                    void *(*func) (void*),
                    void *args);

int
__wut_thread_join(OSThread * thread,
                  void **outValue);

int
__wut_thread_detach(OSThread * thread);

int
__wut_thread_equal(OSThread *thread1,
                   OSThread *thread2);

OSThread *
__wut_thread_self();

int
__wut_thread_yield();

int
__wut_once(__wut_once_t *once,
           void (*func) (void));

void
__wut_key_cleanup(OSThread *thread);

int
__wut_key_create(__wut_key_t *key,
                 void (*dtor) (void *));

int
__wut_key_delete(__wut_key_t key);

void *
__wut_getspecific(__wut_key_t key);

int
__wut_setspecific(__wut_key_t key,
                  const void *ptr);

void
__wut_mutex_init_function(OSMutex *mutex);

int
__wut_mutex_destroy(OSMutex *mutex);

int
__wut_mutex_lock(OSMutex *mutex);

int
__wut_mutex_trylock(OSMutex *mutex);

int
__wut_mutex_unlock(OSMutex *mutex);

int
__wut_recursive_mutex_init_function(OSMutex *mutex);

int
__wut_recursive_mutex_lock(OSMutex *mutex);

int
__wut_recursive_mutex_trylock(OSMutex *mutex);

int
__wut_recursive_mutex_unlock(OSMutex *mutex);

int
__wut_recursive_mutex_destroy(OSMutex *mutex);

void
__wut_cond_init_function(OSCondition *cond);

int
__wut_cond_broadcast(OSCondition *cond);

int
__wut_cond_signal(OSCondition *cond);

int
__wut_cond_wait(OSCondition *cond,
                OSMutex *mutex);

int
__wut_cond_timedwait(OSCondition *cond,
                     OSMutex *mutex,
                     const __gthread_time_t *abs_timeout);

int
__wut_cond_wait_recursive(OSCondition *cond,
                          OSMutex *mutex);

int
__wut_cond_destroy(OSCondition* cond);
