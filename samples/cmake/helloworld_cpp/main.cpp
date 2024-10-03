#include <coreinit/systeminfo.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <nn/ac.h>

#include <whb/log.h>
#include <whb/log_console.h>
#include <whb/proc.h>

#include <thread>

int
hello_thread()
{
   int last_tm_sec = -1;
   uint32_t ip     = 0;
   WHBLogPrintf("Hello World from a std::thread!");

   if (!nn::ac::GetAssignedAddress(&ip)) {
      WHBLogPrintf("GetAssignedAddress failed!");
   }

   WHBLogPrintf("My IP is: %u.%u.%u.%u",
                (ip >> 24) & 0xFF,
                (ip >> 16) & 0xFF,
                (ip >> 8) & 0xFF,
                (ip >> 0) & 0xFF);

   while (WHBProcIsRunning()) {
      OSCalendarTime tm;
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
   return 0;
}

int
main(int argc, char **argv)
{
   nn::ac::ConfigIdNum configId;

   nn::ac::Initialize();
   nn::ac::GetStartupId(&configId);
   nn::ac::Connect(configId);

   WHBProcInit();
   WHBLogConsoleInit();

   std::thread t(hello_thread);
   t.join();

   WHBLogConsoleFree();
   WHBProcShutdown();

   nn::ac::Finalize();
   return 0;
}
