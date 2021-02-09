#include "wut_newlib.h"
#include "wut_clock.h"

#include <coreinit/systeminfo.h>
#include <coreinit/time.h>

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
