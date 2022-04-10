#include "wut_newlib.h"
#include <coreinit/exit.h>

void(*__wut_exit)(int rc);
extern void __fini_wut(void);

int __syscall_lock_init(int *lock, int recursive) {
  return __wut_lock_init(lock, recursive);
}

int __syscall_lock_close(int *lock) {
  return __wut_lock_close(lock);
}

int __syscall_lock_release(int *lock) {
  return __wut_lock_release(lock);
}

int __syscall_lock_acquire(int *lock) {
  return __wut_lock_acquire(lock);
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
}
