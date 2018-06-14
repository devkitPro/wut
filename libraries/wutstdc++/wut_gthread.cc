#include "wut_gthread.h"
#include <bits/gthr-default.h>

typedef int (* __gthread_fn_active) (void);
typedef int (* __gthread_fn_create) (__gthread_t *__threadid, void *(*__func) (void*), void *__args);
typedef int (* __gthread_fn_join) (__gthread_t __threadid, void **__value_ptr);
typedef int (* __gthread_fn_detach) (__gthread_t __threadid);
typedef int (* __gthread_fn_equal) (__gthread_t __t1, __gthread_t __t2);
typedef __gthread_t (* __gthread_fn_self) (void);
typedef int (* __gthread_fn_yield) (void);
typedef int (* __gthread_fn_once) (__gthread_once_t *__once, void (*__func) (void));
typedef int (* __gthread_fn_key_create) (__gthread_key_t *__key, void (*__dtor) (void *));
typedef int (* __gthread_fn_key_delete) (__gthread_key_t __key);
typedef void *(* __gthread_fn_getspecific) (__gthread_key_t __key);
typedef int (* __gthread_fn_setspecific) (__gthread_key_t __key, const void *__ptr);
typedef void (* __gthread_fn_mutex_init_function) (__gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_mutex_destroy) (__gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_mutex_lock) (__gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_mutex_trylock) (__gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_mutex_unlock) (__gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_recursive_mutex_init_function) (__gthread_recursive_mutex_t *__mutex);
typedef int (* __gthread_fn_recursive_mutex_lock) (__gthread_recursive_mutex_t *__mutex);
typedef int (* __gthread_fn_recursive_mutex_trylock) (__gthread_recursive_mutex_t *__mutex);
typedef int (* __gthread_fn_recursive_mutex_unlock) (__gthread_recursive_mutex_t *__mutex);
typedef int (* __gthread_fn_recursive_mutex_destroy) (__gthread_recursive_mutex_t *__mutex);
typedef void (* __gthread_fn_cond_init_function) (__gthread_cond_t *__cond);
typedef int (* __gthread_fn_cond_broadcast) (__gthread_cond_t *__cond);
typedef int (* __gthread_fn_cond_signal) (__gthread_cond_t *__cond);
typedef int (* __gthread_fn_cond_wait) (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex);
typedef int (* __gthread_fn_cond_timedwait) (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex, const __gthread_time_t *__abs_timeout);
typedef int (* __gthread_fn_cond_wait_recursive) (__gthread_cond_t *__cond, __gthread_recursive_mutex_t *__mutex);
typedef int (* __gthread_fn_cond_destroy) (__gthread_cond_t* __cond);

int
__wut_active_p()
{
   return 1;
}

void
__init_wut_gthread()
{
   __gthread_impl.active = &__wut_active_p;
   __gthread_impl.active = (__gthread_fn_active)__wut_active_p;
   __gthread_impl.create = (__gthread_fn_create)__wut_thread_create;
   __gthread_impl.join = (__gthread_fn_join)__wut_thread_join;
   __gthread_impl.detach = (__gthread_fn_detach)__wut_thread_detach;
   __gthread_impl.equal = (__gthread_fn_equal)__wut_thread_equal;
   __gthread_impl.self = (__gthread_fn_self)__wut_thread_self;
   __gthread_impl.yield = (__gthread_fn_yield)__wut_thread_yield;
   __gthread_impl.once = (__gthread_fn_once)__wut_once;
   __gthread_impl.key_create = (__gthread_fn_key_create)__wut_key_create;
   __gthread_impl.key_delete = (__gthread_fn_key_delete)__wut_key_delete;
   __gthread_impl.getspecific = (__gthread_fn_getspecific)__wut_getspecific;
   __gthread_impl.setspecific = (__gthread_fn_setspecific)__wut_setspecific;
   __gthread_impl.mutex_init_function = (__gthread_fn_mutex_init_function)__wut_mutex_init_function;
   __gthread_impl.mutex_destroy = (__gthread_fn_mutex_destroy)__wut_mutex_destroy;
   __gthread_impl.mutex_lock = (__gthread_fn_mutex_lock)__wut_mutex_lock;
   __gthread_impl.mutex_trylock = (__gthread_fn_mutex_trylock)__wut_mutex_trylock;
   __gthread_impl.mutex_unlock = (__gthread_fn_mutex_unlock)__wut_mutex_unlock;
   __gthread_impl.recursive_mutex_init_function = (__gthread_fn_recursive_mutex_init_function)__wut_recursive_mutex_init_function;
   __gthread_impl.recursive_mutex_lock = (__gthread_fn_recursive_mutex_lock)__wut_recursive_mutex_lock;
   __gthread_impl.recursive_mutex_trylock = (__gthread_fn_recursive_mutex_trylock)__wut_recursive_mutex_trylock;
   __gthread_impl.recursive_mutex_unlock = (__gthread_fn_recursive_mutex_unlock)__wut_recursive_mutex_unlock;
   __gthread_impl.recursive_mutex_destroy = (__gthread_fn_recursive_mutex_destroy)__wut_recursive_mutex_destroy;
   __gthread_impl.cond_init_function = (__gthread_fn_cond_init_function)__wut_cond_init_function;
   __gthread_impl.cond_broadcast = (__gthread_fn_cond_broadcast)__wut_cond_broadcast;
   __gthread_impl.cond_signal = (__gthread_fn_cond_signal)__wut_cond_signal;
   __gthread_impl.cond_wait = (__gthread_fn_cond_wait)__wut_cond_wait;
   __gthread_impl.cond_timedwait = (__gthread_fn_cond_timedwait)__wut_cond_timedwait;
   __gthread_impl.cond_wait_recursive = (__gthread_fn_cond_wait_recursive)__wut_cond_wait_recursive;
   __gthread_impl.cond_destroy = (__gthread_fn_cond_destroy)__wut_cond_destroy;
}
