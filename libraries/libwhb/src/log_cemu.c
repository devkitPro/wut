#include <coreinit/debug.h>
#include <whb/log.h>

#include <string.h>

static void
cemuLogHandler(const char * msg)
{
   uint32_t size = strlen(msg);
   if (size > 0 && msg[size-1] == '\n') {
      // OSConsoleWrite on Cemu already adds a new line
      size--;
   }

   OSConsoleWrite(msg, size);
}

BOOL
WHBLogCemuInit()
{
   return WHBAddLogHandler(cemuLogHandler);
}

BOOL
WHBLogCemuDeinit()
{
   return WHBRemoveLogHandler(cemuLogHandler);
}
