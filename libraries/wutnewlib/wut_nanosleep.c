#include "wut_newlib.h"

#include <coreinit/systeminfo.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>

int
__wut_nanosleep(const struct timespec *req,
                struct timespec *rem)
{
   OSSleepTicks(OSSecondsToTicks(req->tv_sec) +
                OSNanosecondsToTicks(req->tv_nsec));
   rem->tv_sec  = 0;
   rem->tv_nsec = 0;
   return 0;
}
