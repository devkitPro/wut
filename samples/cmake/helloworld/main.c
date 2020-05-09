/*
 * Copyright (C) 2015-2020 exjam <james.benton2@gmail.com>
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
