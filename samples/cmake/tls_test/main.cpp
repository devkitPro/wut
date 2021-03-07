#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/proc.h>
#include <whb/log.h>
#include <whb/log_console.h>

#include <thread>

__thread
__attribute((tls_model("global-dynamic")))
const char* thread_name = "";

int
thread1_entry(void)
{
   thread_name = "Thread1";
   WHBLogPrintf("Hello from %-20s (thread_name@0x%08X)\n", thread_name, &thread_name);
   return 0;
}

int
main(int argc, char **argv)
{
   WHBProcInit();
   WHBLogConsoleInit();

   thread_name = "Main Thread";
   WHBLogPrintf("Hello from %-20s (thread_name@0x%08X)\n", thread_name, &thread_name);

   std::thread th1 = std::thread(thread1_entry);
   th1.join();

   WHBLogPrintf("Hello from %-20s (thread_name@0x%08X)\n", thread_name, &thread_name);
   WHBLogConsoleDraw();

   while(WHBProcIsRunning()) {
      OSSleepTicks(OSMillisecondsToTicks(1000));
   }

   WHBLogPrintf("Exiting... good bye.");
   WHBLogConsoleDraw();
   OSSleepTicks(OSMillisecondsToTicks(1000));

   WHBLogConsoleFree();
   WHBProcShutdown();
   return 0;
}
