#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <coreinit/systeminfo.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <thread>

int
hello_thread()
{
   WHBLogPrintf("Hello World from a std::thread!");

   while(WHBProcIsRunning()) {
      OSCalendarTime tm;
      OSTicksToCalendarTime(OSGetTime(), &tm);
      WHBLogPrintf("%02d/%02d/%04d %02d:%02d:%02d I'm still here.",
                   tm.tm_mday, tm.tm_mon, tm.tm_year,
                   tm.tm_hour, tm.tm_min, tm.tm_sec);

      WHBLogConsoleDraw();
      OSSleepTicks(OSMillisecondsToTicks(1000));
   }

   WHBLogPrintf("Exiting... good bye.");
   WHBLogConsoleDraw();
   OSSleepTicks(OSMillisecondsToTicks(1000));
   return 0;
}

int
main(int argc, char **argv)
{
   WHBProcInit();
   WHBLogConsoleInit();

   std::thread t(hello_thread);
   t.join();

   WHBLogConsoleFree();
   WHBProcShutdown();
   return 0;
}
