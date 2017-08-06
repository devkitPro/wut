#include <coreinit/debug.h>
#include <whb/log.h>

static void
cafeLogHandler(const char * msg)
{
   OSReport("%s\n", msg);
}

BOOL
WHBLogCafeInit()
{
   WHBAddLogHandler(cafeLogHandler);
   return TRUE;
}
