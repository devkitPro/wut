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

typedef struct KernelInfo0 {
    struct CoreinitInfo {
        void *loaderHandle;
        void *textAddr;
        uint32_t textOffset;
        uint32_t textSize;
        void *dataAddr;
        uint32_t dataOffset;
        uint32_t dataSize;
        void *loadAddr;
        uint32_t loadOffset;
        uint32_t loadSize;
    };

    int32_t upid;
    int32_t rampid;
    uint32_t appFlags;
    void *dataAreaStart;
    void *dataAreaEnd;
    void *physDataAreaStart;
    void *physDataAreaEnd;
    void *physAvailStart;
    void *physAvailEnd;
    void *physCodeGenStart;
    void *physCodeGenEnd;
    void *sdaBase;
    void *sda2Base;
    uint32_t systemHeapSize;
    void *stackEnd0;
    void *stackEnd1;
    void *stackEnd2;
    void *stackBase0;
    void *stackBase1;
    void *stackBase2;
    void *exceptionStackEnd0;
    void *exceptionStackEnd1;
    void *exceptionStackEnd2;
    void *exceptionStackBase0;
    void *exceptionStackBase1;
    void *exceptionStackBase2;
    void *lockedCacheBase0;
    void *lockedCacheBase1;
    void *lockedCacheBase2;
    struct CoreinitInfo coreinit;
    uint32_t unk0x9C;
    uint64_t titleId;
} KernelInfo0;
WUT_CHECK_OFFSET(KernelInfo0, 0x00, upid);
WUT_CHECK_OFFSET(KernelInfo0, 0x04, rampid);
WUT_CHECK_OFFSET(KernelInfo0, 0x08, appFlags);
WUT_CHECK_OFFSET(KernelInfo0, 0x0C, dataAreaStart);
WUT_CHECK_OFFSET(KernelInfo0, 0x10, dataAreaEnd);
WUT_CHECK_OFFSET(KernelInfo0, 0x14, physDataAreaStart);
WUT_CHECK_OFFSET(KernelInfo0, 0x18, physDataAreaEnd);
WUT_CHECK_OFFSET(KernelInfo0, 0x1C, physAvailStart);
WUT_CHECK_OFFSET(KernelInfo0, 0x20, physAvailEnd);
WUT_CHECK_OFFSET(KernelInfo0, 0x24, physCodeGenStart);
WUT_CHECK_OFFSET(KernelInfo0, 0x28, physCodeGenEnd);
WUT_CHECK_OFFSET(KernelInfo0, 0x2C, sdaBase);
WUT_CHECK_OFFSET(KernelInfo0, 0x30, sda2Base);
WUT_CHECK_OFFSET(KernelInfo0, 0x34, systemHeapSize);
WUT_CHECK_OFFSET(KernelInfo0, 0x38, stackEnd0);
WUT_CHECK_OFFSET(KernelInfo0, 0x3C, stackEnd1);
WUT_CHECK_OFFSET(KernelInfo0, 0x40, stackEnd2);
WUT_CHECK_OFFSET(KernelInfo0, 0x44, stackBase0);
WUT_CHECK_OFFSET(KernelInfo0, 0x48, stackBase1);
WUT_CHECK_OFFSET(KernelInfo0, 0x4C, stackBase2);
WUT_CHECK_OFFSET(KernelInfo0, 0x50, exceptionStackEnd0);
WUT_CHECK_OFFSET(KernelInfo0, 0x54, exceptionStackEnd1);
WUT_CHECK_OFFSET(KernelInfo0, 0x58, exceptionStackEnd2);
WUT_CHECK_OFFSET(KernelInfo0, 0x5C, exceptionStackBase0);
WUT_CHECK_OFFSET(KernelInfo0, 0x60, exceptionStackBase1);
WUT_CHECK_OFFSET(KernelInfo0, 0x64, exceptionStackBase2);
WUT_CHECK_OFFSET(KernelInfo0, 0x68, lockedCacheBase0);
WUT_CHECK_OFFSET(KernelInfo0, 0x6C, lockedCacheBase1);
WUT_CHECK_OFFSET(KernelInfo0, 0x70, lockedCacheBase2);
WUT_CHECK_OFFSET(KernelInfo0, 0x74, coreinit);
WUT_CHECK_OFFSET(KernelInfo0, 0x9C, unk0x9C);
WUT_CHECK_OFFSET(KernelInfo0, 0xA0, titleId);
WUT_CHECK_SIZE(KernelInfo0, 0xA8);

typedef struct KernelInfo6 {
    uint64_t osTitleId;
    uint32_t unk0x08;
    WUT_PADDING_BYTES(0x108 - 0xC);
} KernelInfo6;
WUT_CHECK_OFFSET(KernelInfo6, 0x00, osTitleId);
WUT_CHECK_OFFSET(KernelInfo6, 0x08, unk0x08);
WUT_CHECK_SIZE(KernelInfo6, 0x108);

void __KernelSetUserModeExHandler(OSExceptionType exceptionType, OSExceptionChainInfo *chainInfo, OSExceptionChainInfo *prevChainInfo);

KernelTimerHandle __KernelAllocateTimer(KernelTimerCallbackFn, void *exceptionStack, OSContext *context);
uint32_t __KernelPrimeTimer(KernelTimerHandle handle, uint64_t startTimeInTicks, uint64_t intervalInTicks, uint32_t unknown);

void __KernelSendICI(OSICICommand cmd, void *arg1, uint32_t unknown1, uint32_t unknown2);

void __KernelGetInfo(uint32_t type, void *outBuffer, uint32_t outBufferSize, uint32_t core);

static inline void
__KernelGetInfo0(KernelInfo0 *outBuffer, uint32_t core)
{
   __KernelGetInfo(0, outBuffer, sizeof(KernelInfo0), core);
}

static inline void
__KernelGetInfo6(KernelInfo6 *outBuffer, uint32_t core)
{
   __KernelGetInfo(6, outBuffer, sizeof(KernelInfo6), core);
}

#ifdef __cplusplus
}
#endif

/** @} */
