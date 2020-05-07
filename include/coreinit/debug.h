#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_debug Debug
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*DisassemblyPrintFn)(const char *fmt, ...);
typedef uint32_t (*DisassemblyFindSymbolFn)(uint32_t addr, char *symbolNameBuf, uint32_t symbolNameBufSize);

typedef enum DisassemblePPCFlags
{
   DISASSEMBLE_PPC_FLAGS_NONE = 0,
} DisassemblePPCFlags;


void
OSConsoleWrite(const char *msg,
               uint32_t size);


void
OSReport(const char *fmt, ...);


void
OSReportVerbose(const char *fmt, ...);


void
OSReportInfo(const char *fmt, ...);


void
OSReportWarn(const char *fmt, ...);


void
OSPanic(const char *file,
        uint32_t line,
        const char *fmt, ...);


void
OSFatal(const char *msg);


uint32_t
OSGetSymbolName(uint32_t addr,
                char *symbolNameBuf,
                uint32_t symbolNameBufSize);


uint32_t
OSGetUPID();

BOOL
OSIsDebuggerInitialized();

BOOL
OSIsDebuggerPresent();

BOOL
OSIsECOBoot();

BOOL
OSIsECOMode();

BOOL
DisassemblePPCOpcode(uint32_t *opcode,
                     char *buffer,
                     uint32_t bufferSize,
                     DisassemblyFindSymbolFn findSymbolFn,
                     DisassemblePPCFlags flags);

void
DisassemblePPCRange(void *start,
                    void *end,
                    DisassemblyPrintFn printFn,
                    DisassemblyFindSymbolFn findSymbolFn,
                    DisassemblePPCFlags flags);

#ifdef __cplusplus
}
#endif

/** @} */
