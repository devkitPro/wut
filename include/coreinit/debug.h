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

typedef struct OSFatalError OSFatalError;

typedef void (*DisassemblyPrintFn)(const char *fmt, ...);

typedef uint32_t (*DisassemblyFindSymbolFn)(uint32_t addr, char *symbolNameBuf, uint32_t symbolNameBufSize);

typedef enum DisassemblePPCFlags
{
   DISASSEMBLE_PPC_FLAGS_NONE = 0,
} DisassemblePPCFlags;

typedef enum OSFatalErrorMessageType
{
   OS_FATAL_ERROR_UNKOWN              = 0,
   OS_FATAL_ERROR_GENERAL             = 1,

   //! These are only valid for errorCode 1600200 - 1609999
   OS_FATAL_ERROR_CORRUPTION          = 2,
   OS_FATAL_ERROR_FATAL_SYSTEM_OR_USB = 3,
   OS_FATAL_ERROR_CORRUPTION_SLC      = 4,
   OS_FATAL_ERROR_CORRUPTION_USB      = 5,
   OS_FATAL_ERROR_STORAGE_REMOVED     = 6,
   OS_FATAL_ERROR_DISC_REMOVED        = 7,
   OS_FATAL_ERROR_CORRUPTION_DISC     = 8,
   OS_FATAL_ERROR_WRITE_PROTECT       = 9,
} OSFatalErrorMessageType;

struct OSFatalError
{
   OSFatalErrorMessageType messageType;
   //! Error code, displayed on screen as unsigned, and printed in log as signed
   uint32_t errorCode;
   //! See \link OSGetUPID \endlink
   uint32_t processId;
   //! Internal error code printed in log
   uint32_t internalErrorCode;
   uint32_t line;
   char functionName[64];
   WUT_UNKNOWN_BYTES(0x80);
};
WUT_CHECK_OFFSET(OSFatalError, 0x00, messageType);
WUT_CHECK_OFFSET(OSFatalError, 0x04, errorCode);
WUT_CHECK_OFFSET(OSFatalError, 0x08, processId);
WUT_CHECK_OFFSET(OSFatalError, 0x0C, internalErrorCode);
WUT_CHECK_OFFSET(OSFatalError, 0x10, line);
WUT_CHECK_OFFSET(OSFatalError, 0x14, functionName);
WUT_CHECK_SIZE(OSFatalError, 0xD4);

void
OSConsoleWrite(const char *msg,
               uint32_t size);

void
__OSConsoleWrite(const char *msg,
                 uint32_t size);

void
OSReport(const char *fmt, ...)
   WUT_FORMAT_PRINTF(1, 2);


void
OSReportVerbose(const char *fmt, ...)
   WUT_FORMAT_PRINTF(1, 2);


void
OSReportInfo(const char *fmt, ...)
   WUT_FORMAT_PRINTF(1, 2);


void
OSReportWarn(const char *fmt, ...)
   WUT_FORMAT_PRINTF(1, 2);

/**
 * Halts the system and logs the cause, traps if debugger is present
 * \param file name of the file where the panic occurred
 * \param line position in the file where the panic occurred
 * \param fmt printf-style format string for logging
 */
void
OSPanic(const char *file,
        uint32_t line,
        const char *fmt,
        ...)
   WUT_FORMAT_PRINTF(3, 4) WUT_NORETURN;

/**
 * Displays a message on TV and gamepad screens via OSScreen, and halts the system via \link OSPanic \endlink
 * \param msg message to be displayed and logged
 * \sa coreinit_screen
 */
void
OSFatal(const char *msg) WUT_NORETURN;

/**
 * Switch to the fatal error process ("An error has occured." screen)
 * \param error structure describing the error
 * \param functionName function name printed in log
 * \param line line number printed in log
 *
 * The fatal error process displays the error code, firmware version, Wii U model, serial number and status code
 */
void
OSSendFatalError(OSFatalError *error,
                 const char *functionName,
                 uint32_t line) WUT_NORETURN;

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

void
__OSSetCrashRecovery(uint32_t crashRecovery);

uint32_t
__OSGetCrashRecovery();

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
