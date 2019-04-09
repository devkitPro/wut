#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

int
main(int argc, char **argv)
{
   int last_tm_sec = -1;
   OSCalendarTime tm;

   WHBProcInit();
   WHBLogConsoleInit();
   WHBLogPrintf("Hello World!");

   while(WHBProcIsRunning()) {
      OSTicksToCalendarTime(OSGetTime(), &tm);

      if (tm.tm_sec != last_tm_sec) {
         WHBLogPrintf("%02d/%02d/%04d %02d:%02d:%02d I'm still here.",
                      tm.tm_mday, tm.tm_mon, tm.tm_year,
                      tm.tm_hour, tm.tm_min, tm.tm_sec);
         last_tm_sec = tm.tm_sec;
       }

      WHBLogConsoleDraw();
      OSSleepTicks(OSMillisecondsToTicks(100));
   }

   WHBLogPrintf("Exiting... good bye.");
   WHBLogConsoleDraw();
   OSSleepTicks(OSMillisecondsToTicks(1000));

   WHBLogConsoleFree();
   WHBProcShutdown();
   return 0;
}
