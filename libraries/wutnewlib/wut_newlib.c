#include "wut_newlib.h"
#include <coreinit/exit.h>
#include <coreinit/debug.h>
#include <coreinit/internal.h>
#include <stdio.h>
#include <string.h>

void(*__wut_exit)(int rc);
extern void __fini_wut(void);

void __attribute__((weak))
abort(void) {
   const char *error_text = "Abort called.\n";
   if (OSIsDebuggerPresent()) {
      __asm__ __volatile__("mr 3, %0\n"      // load 'tmp' into r3
                           "tw 0x1f, 31, 31" // DBGSTR_INSTRUCTION
              :
              : "r"(error_text)
              : "r3");
   }
   OSFatal(error_text);
   /* NOTREACHED */
   while (1);
}

void __attribute__((weak))
__assert_func(const char *file,
              int line,
              const char *func,
              const char *failedexpr)
{
   char tmp[512] = {};
   char buffer[512] = {};

   snprintf(tmp, sizeof(tmp), "assertion \"%s\" failed:\n file \"%s\", line %d%s%s",
            failedexpr, file, line,
            func ? ", function: " : "", func ? func : "");

   // make sure to add a \n every 64 characters to fit on the DRC screen.
   char *target_ptr = buffer;
   int i = 0, j = 0, lineLength = 0;
   while (tmp[i] != '\0' && j < sizeof(buffer) - 2) {
      if (tmp[i] == '\n') {
         lineLength = 0;
      } else if (lineLength >= 64) {
         target_ptr[j++] = '\n';
         lineLength = 0;
      }
      target_ptr[j++] = tmp[i++];
      lineLength++;
   }

   if (OSIsDebuggerPresent()) {
      __asm__ __volatile__("mr 3, %0\n"      // load 'tmp' into r3
                           "tw 0x1f, 31, 31" // DBGSTR_INSTRUCTION
              :
              : "r"(tmp)
              : "r3");
   }

   OSFatal(buffer);
   /* NOTREACHED */
   while (1);
}

void __attribute__((weak))
__assert(const char *file,
         int line,
         const char *failedexpr)
{
   __assert_func(file, line, NULL, failedexpr);
   /* NOTREACHED */
}

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

struct _reent *__syscall_getreent(void) {
  return __wut_getreent();
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
