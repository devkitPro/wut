#include "wut_newlib.h"

#include <coreinit/systeminfo.h>
#include <coreinit/time.h>

// The Wii U epoch is at 2000, so we must map it to 1970 for gettime
#define WIIU_EPOCH_YEAR (2000)

#define EPOCH_YEAR (1970)
#define EPOCH_YEARS_SINCE_LEAP 2
#define EPOCH_YEARS_SINCE_CENTURY 70
#define EPOCH_YEARS_SINCE_LEAP_CENTURY 370

#define EPOCH_DIFF_YEARS (2000 - EPOCH_YEAR)
#define EPOCH_DIFF_DAYS \
   ((EPOCH_DIFF_YEARS * 365) + \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_LEAP) / 4 - \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_CENTURY) / 100 + \
    (EPOCH_DIFF_YEARS - 1 + EPOCH_YEARS_SINCE_LEAP_CENTURY) / 400)
#define EPOCH_DIFF_SECS (60ull * 60ull * 24ull * (uint64_t)EPOCH_DIFF_DAYS)

int
__wut_clock_gettime(clockid_t clock_id,
                    struct timespec *tp)
{
   if (clock_id == CLOCK_MONOTONIC) {
      OSTime time = OSGetSystemTime();
      tp->tv_sec = (time_t)OSTicksToSeconds(time);

      time -= OSSecondsToTicks(tp->tv_sec);
      tp->tv_nsec = (long)OSTicksToNanoseconds(time);
   } else if (clock_id == CLOCK_REALTIME) {
      OSTime time = OSGetTime();
      tp->tv_sec = (time_t)OSTicksToSeconds(time);

      time -= OSSecondsToTicks(tp->tv_sec);
      tp->tv_nsec = (long)OSTicksToNanoseconds(time);

      tp->tv_sec += EPOCH_DIFF_SECS;
   } else {
      return EINVAL;
   }

   return 0;
}

int
__wut_clock_settime(clockid_t clock_id,
                    const struct timespec *tp)
{
   return EPERM;
}

int
__wut_clock_getres(clockid_t clock_id,
                   struct timespec *res)
{
   if (clock_id != CLOCK_MONOTONIC &&
       clock_id != CLOCK_REALTIME) {
      return EINVAL;
   }

   res->tv_sec = 0;
   res->tv_nsec = (long)((1000000000ull + (uint64_t)OSTimerClockSpeed) / (uint64_t)OSTimerClockSpeed);
   return 0;
}
