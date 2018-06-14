#include "wut_newlib.h"

#include <coreinit/time.h>

int
__wut_gettod_r(struct _reent *ptr,
               struct timeval *tp,
               struct timezone *tz)
{
   OSCalendarTime tm;
   OSTicksToCalendarTime(OSGetTime(), &tm);

   if (tp != NULL) {
      tp->tv_sec = tm.tm_sec;
      tp->tv_usec = tm.tm_usec + tm.tm_msec * 1000;
   }

   if (tz != NULL) {
      tz->tz_minuteswest = 0;
      tz->tz_dsttime = 0;
   }

   return 0;
}
