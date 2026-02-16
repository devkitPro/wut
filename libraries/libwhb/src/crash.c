#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/exception.h>
#include <coreinit/internal.h>
#include <coreinit/systeminfo.h>
#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <stdarg.h>
#include <stdio.h>
#include <whb/crash.h>
#include <whb/log.h>

#define LOG_DISASSEMBLY_SIZE (4096)
#define LOG_STACK_TRACE_SIZE (4096)
#define LOG_REGISTER_SIZE    (4096)

#define THREAD_STACK_SIZE    (4096)

static const char *
   sCrashType = NULL;

static char
   sDisassemblyBuffer[LOG_DISASSEMBLY_SIZE];

static uint32_t
   sDisassemblyLength = 0;

static char
   sStackTraceBuffer[LOG_STACK_TRACE_SIZE];

static uint32_t
   sStackTraceLength = 0;

static char
   sRegistersBuffer[LOG_REGISTER_SIZE];

static uint32_t
   sRegistersLength = 0;

static uint8_t
   sCrashThreadStack[THREAD_STACK_SIZE];

static OSThread __attribute__((aligned(8)))
sCrashThread;

static int
crashReportThread(int argc, void* argv)
{
   // Log crash dump
   WHBLogPrint(sRegistersBuffer);
   WHBLogPrint(sDisassemblyBuffer);
   WHBLogPrint(sStackTraceBuffer);

   // TODO: Save crash dump to SD card?
   return 0;
}

static WUT_FORMAT_PRINTF(1, 2) void
disassemblyPrintCallback(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   sDisassemblyLength += vsprintf(sDisassemblyBuffer + sDisassemblyLength,
                                  fmt, args);
   sDisassemblyBuffer[sDisassemblyLength] = 0;
   va_end(args);
}

static void
getDisassembly(OSContext *context)
{
   sDisassemblyLength    = 0;
   sDisassemblyBuffer[0] = 0;

   if (context->srr0 > 16) {
      DisassemblePPCRange((void *)(context->srr0 - 16),
                          (void *)(context->srr0 + 16),
                          disassemblyPrintCallback,
                          OSGetSymbolName,
                          DISASSEMBLE_PPC_FLAGS_NONE);
   }
}

static void
getStackTrace(OSContext *context)
{
   int i;
   uint32_t *stackPtr;
   char name[256];

   sStackTraceLength    = 0;
   sStackTraceBuffer[0] = 0;
   stackPtr             = (uint32_t *)context->gpr[1];

   sStackTraceLength += sprintf(sStackTraceBuffer + sStackTraceLength,
                                "Address:      Back Chain    LR Save\n");

   for (i = 0; i < 16; ++i) {
      uint32_t addr;

      if (!stackPtr ||
          (uintptr_t)stackPtr == 0x1 ||
          (uintptr_t)stackPtr == 0xFFFFFFFF) {
         break;
      }

      sStackTraceLength += sprintf(sStackTraceBuffer + sStackTraceLength,
                                   "0x%08x:   0x%08x    0x%08x",
                                   (uintptr_t)stackPtr,
                                   (uintptr_t)stackPtr[0],
                                   (uintptr_t)stackPtr[1]);

      addr = OSGetSymbolName(stackPtr[1], name, sizeof(name));
      if (addr) {
         sStackTraceLength += sprintf(sStackTraceBuffer + sStackTraceLength,
                                      " %s+0x%x", name,
                                      (uintptr_t)(stackPtr[1] - addr));
      }

      sStackTraceLength += sprintf(sStackTraceBuffer + sStackTraceLength, "\n");
      stackPtr = (uint32_t *)*stackPtr;
   }

   sStackTraceBuffer[sStackTraceLength] = 0;
}

static WUT_FORMAT_PRINTF(1, 2) void
writeRegister(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   sRegistersLength += vsprintf(sRegistersBuffer + sRegistersLength, fmt, args);
   sRegistersBuffer[sRegistersLength] = 0;
   va_end(args);
}

static void
getRegisters(OSContext *context)
{
   OSTime tbr = OSGetSystemTime();
   uint32_t addr;
   char name[256];
   int i;
   uint64_t *fpr, *psf;

   sRegistersLength                   = 0;
   sRegistersBuffer[sRegistersLength] = 0;

   writeRegister("--Proc%d-Core%u--------- OSContext 0x%p --------------------\n\n",
                 OSGetUPID(), OSGetCoreId(), context);
   writeRegister("tag1  = 0x%08X (expecting 0x%08X)\n",
                 (uint32_t)(context->tag >> 32),
                 (uint32_t)(OS_CONTEXT_TAG >> 32));
   writeRegister("tag2  = 0x%08X (expecting 0x%08X)\n",
                 (uint32_t)(context->tag & 0xFFFFFFFF),
                 (uint32_t)(OS_CONTEXT_TAG & 0xFFFFFFFF));
   writeRegister("TBR   = 0x%08X_%08X\n",
                 (uint32_t)(tbr >> 32), (uint32_t)(tbr & 0xFFFFFFFF));
   writeRegister("CR    = 0x%08X\n", context->cr);
   writeRegister("CTR   = 0x%08X\n", context->ctr);

   writeRegister("LR    = 0x%08X", context->lr);
   addr = OSGetSymbolName(context->lr, name, sizeof(name));
   if (addr) {
      writeRegister(" %s+0x%X", name, context->lr - addr);
   }
   writeRegister("\n");

   writeRegister("SRR0  = 0x%08X", context->srr0);
   addr = OSGetSymbolName(context->srr0, name, sizeof(name));
   if (addr) {
      writeRegister(" %s+0x%X", name, context->srr0 - addr);
   }
   writeRegister("\n");

   writeRegister("SRR1  = 0x%08X\n", context->srr1);
   writeRegister("state = 0x%04X\n", context->state);

   for (i = 0; i < 16; ++i) {
      writeRegister("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n",
                    i, context->gpr[i], context->gpr[i],
                    i + 16, context->gpr[i + 16], context->gpr[i + 16]);
   }

   writeRegister("\n--GQRs----------\n");
   for (i = 0; i < 4; ++i) {
      writeRegister("gqr%d = 0x%08x \t gqr%d = 0x%08x\n",
                    i, context->gqr[i],
                    i + 4, context->gqr[i + 4]);
   }

   writeRegister("\n--Per-core OSContext runtime ----\n");
   for (i = 0; i < 3; ++i) {
      writeRegister("coretime[%d] = 0x%016llX ticks, %lld second(s) elapsed\n",
                    i, context->coretime[i],
                    OSTicksToSeconds(context->coretime[i]));
   }

   writeRegister("\n--FPRs----------\n");
   fpr = (uint64_t *)context->fpr;
   for (i = 0; i < 16; ++i) {
      writeRegister("fr%d \t= 0x%16.16llx \t fr%d \t= 0x%16.16llx\n",
                    i, fpr[i],
                    i + 16, fpr[i + 16]);
   }

   writeRegister("\n\n--PSFs----------\n");
   psf = (uint64_t *)context->psf;
   for (i = 0; i < 16; ++i) {
      writeRegister("ps%d \t= 0x%16.16llx \t ps%d \t= 0x%16.16llx\n",
                    i, psf[i],
                    i + 16, psf[i + 16]);
   }
}

static BOOL
handleException(const char *type,
                OSContext *context)
{
   sCrashType = type;
   getDisassembly(context);
   getStackTrace(context);
   getRegisters(context);

   OSCreateThread(&sCrashThread,
                  crashReportThread,
                  0,
                  NULL,
                  sCrashThreadStack + THREAD_STACK_SIZE,
                  THREAD_STACK_SIZE,
                  16,
                  0);

   OSResumeThread(&sCrashThread);
   OSSuspendThread((OSThread *)context);
   return TRUE;
}

static BOOL
handleAlignment(OSContext *context)
{
   return handleException("ALIGNMENT", context);
}

static BOOL
handleDSI(OSContext *context)
{
   return handleException("DSI", context);
}

static BOOL
handleISI(OSContext *context)
{
   return handleException("ISI", context);
}

static BOOL
handleProgram(OSContext *context)
{
   return handleException("PROGRAM", context);
}

BOOL
WHBInitCrashHandler()
{
   OSSetExceptionCallbackEx(OS_EXCEPTION_MODE_GLOBAL,
                            OS_EXCEPTION_TYPE_ALIGNMENT, handleAlignment);
   OSSetExceptionCallbackEx(OS_EXCEPTION_MODE_GLOBAL,
                            OS_EXCEPTION_TYPE_DSI, handleDSI);
   OSSetExceptionCallbackEx(OS_EXCEPTION_MODE_GLOBAL,
                            OS_EXCEPTION_TYPE_ISI, handleISI);
   OSSetExceptionCallbackEx(OS_EXCEPTION_MODE_GLOBAL,
                            OS_EXCEPTION_TYPE_PROGRAM, handleProgram);
   return TRUE;
}
