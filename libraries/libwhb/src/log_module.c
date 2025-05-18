#include <coreinit/debug.h>
#include <coreinit/dynload.h>
#include <string.h>
#include <whb/log.h>

static OSDynLoad_Module sModuleHandle              = NULL;
static void (*sWUMSLogWrite)(const char *, size_t) = NULL;

static void
moduleLogHandler(const char *msg)
{
   if (sWUMSLogWrite != NULL) {
      sWUMSLogWrite(msg, strlen(msg));
   }
}

BOOL
WHBLogModuleInit()
{
   if (OSDynLoad_Acquire("homebrew_logging", &sModuleHandle) != OS_DYNLOAD_OK) {
      OSReport("WHBLogModuleInit: OSDynLoad_Acquire failed.\n");
      return false;
   }

   if (OSDynLoad_FindExport(sModuleHandle, FALSE, "WUMSLogWrite", (void **)&sWUMSLogWrite) != OS_DYNLOAD_OK) {
      OSReport("WHBLogModuleInit: OSDynLoad_FindExport failed.\n");
      return false;
   }

   return WHBAddLogHandler(moduleLogHandler);
}

BOOL
WHBLogModuleDeinit()
{
   return WHBRemoveLogHandler(moduleLogHandler);
}