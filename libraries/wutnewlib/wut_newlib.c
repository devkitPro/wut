#include "wut_newlib.h"
#include <coreinit/exit.h>

void(*__wut_exit)(int rc);
extern void __fini_wut(void);

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr) {
	return __wut_sbrk_r(ptr, incr);
}

void __syscall_lock_init(int *lock) {
  __wut_lock_init(lock, 0);
}

void __syscall_lock_acquire(int *lock) {
  __wut_lock_acquire(lock);
}

void __syscall_lock_release(int *lock) {
  __wut_lock_release(lock);
}

void __syscall_lock_close(int *lock) {
  __wut_lock_close(lock);
}
void __syscall_lock_init_recursive(_LOCK_T *lock) {
  __wut_lock_init(lock, 1);
}

void __syscall_lock_acquire_recursive(int *lock) {
  __wut_lock_acquire(lock);
}

void __syscall_lock_release_recursive(int *lock) {
  __wut_lock_release(lock);
}

void __syscall_lock_close_recursive(int *lock) {
  __wut_lock_close(lock);
}

void __syscall_malloc_lock(struct _reent *ptr) {
	return __wut_malloc_lock(ptr);
}

void __syscall_malloc_unlock(struct _reent *ptr) {
	return __wut_malloc_unlock(ptr);
}

void __syscall_exit(int rc) { 
  __fini_wut();
  __wut_exit(rc);
}

int  __syscall_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz) {
  return __wut_gettod_r(ptr, tp, tz);
}

int __syscall_nanosleep(const struct timespec *req, struct timespec *rem) {
  return __wut_nanosleep(req, rem);
}

int __syscall_clock_gettime(clockid_t clock_id, struct timespec *tp) {
  return __wut_clock_gettime(clock_id, tp);
}

int __syscall_clock_settime(clockid_t clock_id, const struct timespec *tp) {
   return __wut_clock_settime(clock_id, tp);
}

int __syscall_clock_getres(clockid_t clock_id, struct timespec *res) {
   return __wut_clock_getres(clock_id, res);
}

void
__init_wut_newlib()
{
   __wut_exit = RPLWRAP(exit);
}

void
__fini_wut_newlib()
{
  __fini_wut_sbrk_heap();
}
