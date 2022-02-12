#include <coreinit/debug.h>
#include <whb/log.h>

#include <string.h>

static void
cafeLogHandler(const char *msg)
{
   int length = strlen(msg);

   if (msg[length - 1] != '\n') {
      OSReport("%s\n", msg);
   } else {
      OSReport(msg);
   }
}

BOOL WHBLogCafeInit()
{
   return WHBAddLogHandler(cafeLogHandler);
}

BOOL WHBLogCafeDeinit()
{
   return WHBRemoveLogHandler(cafeLogHandler);
}
