#include "my_first_rpl.h"

#include <coreinit/thread.h>
#include <coreinit/time.h>

#include <whb/log.h>
#include <whb/log_console.h>
#include <whb/proc.h>

int main(int argc, char **argv)
{
   WHBProcInit();
   WHBLogConsoleInit();
   WHBLogPrintf(my_first_export());

   while (WHBProcIsRunning()) {
      WHBLogConsoleDraw();
      OSSleepTicks(OSMillisecondsToTicks(30));
   }

   WHBLogConsoleFree();
   WHBProcShutdown();
   return 0;
}
