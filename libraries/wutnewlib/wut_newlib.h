#ifndef __WUT_NEWLIB_H
#define __WUT_NEWLIB_H

#include <sys/errno.h>
#include <sys/iosupport.h>
#include <sys/reent.h>
#include <sys/time.h>

#define __WUT_MAX_KEYS               (128)
#define __WUT_STACK_SIZE             (128 * 1024)

#define __WUT_KEY_THREAD_SPECIFIC_ID WUT_THREAD_SPECIFIC_0

void *
__wut_sbrk_r(struct _reent *r, ptrdiff_t incr);
int
__wut_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz);
int
__wut_clock_gettime(clockid_t clock_id, struct timespec *tp);
int
__wut_clock_settime(clockid_t clock_id, const struct timespec *tp);
int
__wut_clock_getres(clockid_t clock_id, struct timespec *res);
int
__wut_nanosleep(const struct timespec *req, struct timespec *rem);
struct _reent *
__wut_getreent(void);

void
__fini_wut_sbrk_heap();

#endif // ifndef __WUT_NEWLIB_H
