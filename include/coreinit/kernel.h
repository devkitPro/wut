#pragma once
#include <wut.h>
#include <coreinit/exception.h>

/**
 * \defgroup coreinit_kernel
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSICICommand {
    OS_ICI_COMMAND_INVALID_IC_RANGE     = 1,
    OS_ICI_COMMAND_RESCHEDULE_CORE      = 2,
    OS_ICI_COMMAND_HALT_CORE            = 3,
    OS_ICI_COMMAND_PROC_EXIT            = 4,
    OS_ICI_COMMAND_SET_DABR             = 5,
    OS_ICI_COMMAND_PROC_SCHED           = 6,
    OS_ICI_COMMAND_FAST_BG_EXIT         = 7,
    OS_ICI_COMMAND_IOP_SHELL_CORE_TRACE = 8,
    OS_ICI_COMMAND_SYSTEM_FATAL         = 9,
    OS_ICI_COMMAND_SET_IABR             = 10,
    OS_ICI_COMMAND_PANIC_0X15           = 0xB,
    OS_ICI_COMMAND_PROC_KILL            = 0xC,
    OS_ICI_COMMAND_PROC_CRASH           = 0xD,
    OS_ICI_COMMAND_UNKNOWN              = 0xE, // Waits for rendezvous, then updates heartbeat
    OS_ICI_COMMAND_OVERLAY_ARENA        = 0xF,
} OSICICommand;
WUT_CHECK_SIZE(OSICICommand, 4);

typedef void (*OSExceptionCallbackExFn)(OSExceptionType exceptionType, OSContext * interruptedContext, OSContext *cbContext);

typedef void (*KernelTimerCallbackFn)(OSExceptionType exception, OSContext *interruptedContext, OSContext *currentContext);

typedef uint32_t KernelTimerHandle;

typedef struct OSExceptionChainInfo {
    OSExceptionCallbackExFn callback;
    void *stack;
    OSContext *context;
} OSExceptionChainInfo;
WUT_CHECK_OFFSET(OSExceptionChainInfo, 0, callback);
WUT_CHECK_OFFSET(OSExceptionChainInfo, 4, stack);
WUT_CHECK_OFFSET(OSExceptionChainInfo, 8, context);
WUT_CHECK_SIZE(OSExceptionChainInfo, 12);

void __KernelSetUserModeExHandler(OSExceptionType exceptionType, OSExceptionChainInfo *chainInfo, OSExceptionChainInfo *prevChainInfo);

KernelTimerHandle __KernelAllocateTimer(KernelTimerCallbackFn, void *exceptionStack, OSContext *context);
uint32_t __KernelPrimeTimer(KernelTimerHandle handle, uint64_t startTimeInTicks, uint64_t intervalInTicks, uint32_t unknown);

void __KernelSendICI(OSICICommand cmd, void *arg1, uint32_t unknown1, uint32_t unknown2);

void __KernelGetInfo(uint32_t type, void *outBuffer, uint32_t outBufferSize, uint32_t core);

#ifdef __cplusplus
}
#endif

/** @} */
