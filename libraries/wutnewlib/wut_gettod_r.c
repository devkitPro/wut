#include "wut_clock.h"
#include "wut_newlib.h"

#include <coreinit/time.h>

int __wut_gettod_r(struct _reent *ptr,
                   struct timeval *tp,
                   struct timezone *tz)
{
   OSTime time = OSGetTime();

   if (tp != NULL) {
      tp->tv_sec = (time_t) OSTicksToSeconds(time);

      time -= OSSecondsToTicks(tp->tv_sec);
      tp->tv_usec = (long) OSTicksToMicroseconds(time);

      tp->tv_sec += EPOCH_DIFF_SECS;
   }

   if (tz != NULL) {
      tz->tz_minuteswest = 0;
      tz->tz_dsttime     = 0;
   }

   return 0;
}
