#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/thread.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>
#include <sysapp/launch.h>

bool isAppRunning = true;

void
SaveCallback()
{
   OSSavesDone_ReadyToRelease(); // Required
}

bool
AppRunning()
{
   if(!OSIsMainCore())
   {
      ProcUISubProcessMessages(true);
   }
   else
   {
      ProcUIStatus status = ProcUIProcessMessages(true);
    
      if(status == PROCUI_STATUS_EXITING)
      {
          // Being closed, deinit, free, and prepare to exit
          isAppRunning = false;
          ProcUIShutdown();
      }
      else if(status == PROCUI_STATUS_RELEASE_FOREGROUND)
      {
          // Free up MEM1 to next foreground app, deinit screen, etc.
          ProcUIDrawDoneRelease();
      }
      else if(status == PROCUI_STATUS_IN_FOREGROUND)
      {
         // Executed while app is in foreground
      }
   }

   return isAppRunning;
}

int
CoreEntryPoint(int argc, const char **argv)
{
   OSReport("Hello world from %s", argv[0]);
   return argc;
}

int
main(int argc, char **argv)
{
   ProcUIInit(&SaveCallback);
   OSReport("Main thread running on core %d", OSGetCoreId());

   // Run thread on core 0
   OSThread *threadCore0 = OSGetDefaultThread(0);

   const char *core0Args[] = {
      "Core 0"
   };

   OSRunThread(threadCore0, CoreEntryPoint, 0, core0Args);

   // Run thread on core 2
   OSThread *threadCore2 = OSGetDefaultThread(2);

   const char *core2Args[] = {
      "Core 2"
   };

   OSRunThread(threadCore2, CoreEntryPoint, 2, core2Args);

   // Wait for threads to return
   int resultCore0 = -1, resultCore2 = -1;
   OSJoinThread(threadCore0, &resultCore0);
   OSJoinThread(threadCore2, &resultCore2);

   OSReport("Core 0 thread returned %d", resultCore0);
   OSReport("Core 2 thread returned %d", resultCore2);
   
   // Sends messages for ProcUI to release foreground, exit
   // and launch into the system menu immediately.
   SYSLaunchMenu();
   
   while(AppRunning());
   return 0;
}
