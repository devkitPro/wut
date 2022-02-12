#include <coreinit/memdefaultheap.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <whb/log.h>

#define MAX_HANDLERS         16
#define PRINTF_BUFFER_LENGTH 2048

static LogHandlerFn
        sHandlers[MAX_HANDLERS] = {0};

static inline void
dispatchMessage(const char *str)
{
   int i;
   for (i = 0; i < MAX_HANDLERS; ++i) {
      if (sHandlers[i]) {
         sHandlers[i](str);
      }
   }
}

BOOL WHBAddLogHandler(LogHandlerFn fn)
{
   int i;

   for (i = 0; i < MAX_HANDLERS; ++i) {
      if (sHandlers[i] == fn) {
         return TRUE;
      }
      if (!sHandlers[i]) {
         sHandlers[i] = fn;
         return TRUE;
      }
   }

   return FALSE;
}

BOOL WHBRemoveLogHandler(LogHandlerFn fn)
{
   int i;

   for (i = 0; i < MAX_HANDLERS; ++i) {
      if (sHandlers[i] == fn) {
         sHandlers[i] = NULL;
         return TRUE;
      }
   }

   return FALSE;
}

BOOL WHBLogWrite(const char *str)
{
   dispatchMessage(str);
   return TRUE;
}

BOOL WHBLogPrint(const char *str)
{
   char *buf = MEMAllocFromDefaultHeapEx(PRINTF_BUFFER_LENGTH, 4);
   if (!buf) {
      return FALSE;
   }

   snprintf(buf, PRINTF_BUFFER_LENGTH, "%s\n", str);
   dispatchMessage(buf);

   MEMFreeToDefaultHeap(buf);
   return TRUE;
}

BOOL WHBLogWritef(const char *fmt, ...)
{
   char *buf = MEMAllocFromDefaultHeapEx(PRINTF_BUFFER_LENGTH, 4);
   va_list va;

   if (!buf) {
      return FALSE;
   }

   va_start(va, fmt);
   vsnprintf(buf, PRINTF_BUFFER_LENGTH, fmt, va);
   dispatchMessage(buf);

   MEMFreeToDefaultHeap(buf);
   va_end(va);
   return TRUE;
}

BOOL WHBLogPrintf(const char *fmt, ...)
{
   char *buf1 = MEMAllocFromDefaultHeapEx(PRINTF_BUFFER_LENGTH, 4);
   char *buf2 = MEMAllocFromDefaultHeapEx(PRINTF_BUFFER_LENGTH, 4);
   va_list va;

   if (!buf1) {
      return FALSE;
   }

   if (!buf2) {
      MEMFreeToDefaultHeap(buf1);
      return FALSE;
   }

   va_start(va, fmt);

   vsnprintf(buf1, PRINTF_BUFFER_LENGTH, fmt, va);
   snprintf(buf2, PRINTF_BUFFER_LENGTH, "%s\n", buf1);
   dispatchMessage(buf2);

   MEMFreeToDefaultHeap(buf1);
   MEMFreeToDefaultHeap(buf2);
   va_end(va);
   return TRUE;
}
