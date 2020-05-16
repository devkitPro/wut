#include "wut_gthread.h"
#include <bits/gthr-default.h>
#include <bit>

static constexpr __wut_key_t gthread_key_to_wut(__gthread_key_t key)
{
    __wut_key_t dst={};
    static_assert(sizeof(__wut_key_t) == sizeof(__gthread_key_t), "Incompatible definition of thread local key type");
    __builtin_memcpy(&dst, &key, sizeof(dst));
    return dst;
}

extern "C" {

int __gthr_impl_active (void) {
   return 1;
}

int __gthr_impl_create (__gthread_t *__threadid, void *(*__func) (void*), void *__args) {
   return __wut_thread_create((OSThread**)__threadid, __func, __args);
}

int __gthr_impl_join (__gthread_t __threadid, void **__value_ptr) {
   return __wut_thread_join((OSThread*)__threadid, __value_ptr);
}

int __gthr_impl_detach (__gthread_t __threadid) {
   return __wut_thread_detach((OSThread*)__threadid);
}

int __gthr_impl_equal (__gthread_t __t1, __gthread_t __t2) {
   return __wut_thread_equal( (OSThread*)__t1, (OSThread*)__t2);
}

__gthread_t __gthr_impl_self (void) {
   return __wut_thread_self();
}

int __gthr_impl_yield (void) {
   return __wut_thread_yield();
}

int __gthr_impl_once (__gthread_once_t *__once, void (*__func) (void)) {
   return __wut_once((__wut_once_t*)__once, __func);
}

int __gth_impl_key_create (__gthread_key_t *__key, void (*__dtor) (void *)) {
   return __wut_key_create((__wut_key_t*)__key, __dtor);
}

int __gthr_impl_key_delete (__gthread_key_t __key) {
   return __wut_key_delete( gthread_key_to_wut(__key) );
}
void *__gthr_impl_getspecific (__gthread_key_t __key) {
   return __wut_getspecific( gthread_key_to_wut(__key) );
}
int __gthr_impl_setspecific (__gthread_key_t __key, const void *__ptr) {
   return __wut_setspecific(gthread_key_to_wut(__key), __ptr);
}

void __gthr_impl_mutex_init_function (__gthread_mutex_t *__mutex) {
   return __wut_mutex_init_function((OSMutex*)__mutex);
}

int __gthr_impl_mutex_destroy (__gthread_mutex_t *__mutex) {
   return __wut_mutex_destroy((OSMutex*)__mutex);
}
int __gthr_impl_mutex_lock (__gthread_mutex_t *__mutex) {
   return __wut_mutex_lock((OSMutex*)__mutex);
}

int __gthr_impl_mutex_trylock (__gthread_mutex_t *__mutex) {
   return __wut_mutex_trylock((OSMutex*)__mutex);
}

int __gthr_impl_mutex_unlock (__gthread_mutex_t *__mutex) {
   return __wut_mutex_unlock((OSMutex*)__mutex);
}

int __gthr_impl_recursive_mutex_init_function (__gthread_recursive_mutex_t *__mutex) {
   return __wut_recursive_mutex_init_function((OSMutex*)__mutex);
}

int __gthr_impl_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex) {
   return __wut_recursive_mutex_lock((OSMutex*)__mutex);
}

int __gthr_impl_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex) {
   return __wut_recursive_mutex_trylock((OSMutex*)__mutex);
}

int __gthr_impl_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex) {
   return __wut_recursive_mutex_unlock((OSMutex*)__mutex);
}

int __gthr_impl_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex) {
   return __wut_recursive_mutex_destroy((OSMutex*)__mutex);
}

void __gthr_impl_cond_init_function (__gthread_cond_t *__cond) {
   return __wut_cond_init_function((OSCondition*)__cond);
}

int __gthr_impl_cond_broadcast (__gthread_cond_t *__cond) {
   return __wut_cond_broadcast((OSCondition*)__cond);
}

int __gthr_impl_cond_signal (__gthread_cond_t *__cond) {
   return __wut_cond_signal((OSCondition*)__cond);
}

int __gthr_impl_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex) {
   return __wut_cond_wait((OSCondition*)__cond, (OSMutex*)__mutex);
}

int __gthr_impl_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex, const __gthread_time_t *__abs_timeout) {
   return __wut_cond_timedwait((OSCondition*)__cond, (OSMutex*)__mutex, __abs_timeout);
}

int __gthr_impl_cond_wait_recursive (__gthread_cond_t *__cond, __gthread_recursive_mutex_t *__mutex) {
   return __wut_cond_wait_recursive((OSCondition*)__cond, (OSMutex*)__mutex);
}

int __gthr_impl_cond_destroy (__gthread_cond_t* __cond) {
   return __wut_cond_destroy((OSCondition*)__cond);
}


void __init_wut_stdcpp()
{
}

void __fini_wut_stdcpp()
{
}

}

