#pragma once
#include <wut.h>
#include "time.h"

/**
 * \defgroup coreinit_spinlock Spinlock
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSpinLock OSSpinLock;

struct WUT_ALIGNAS(16) OSSpinLock
{
   uint32_t owner;
   WUT_UNKNOWN_BYTES(0x4);
   uint32_t recursion;
   WUT_UNKNOWN_BYTES(0x4);
};
WUT_CHECK_OFFSET(OSSpinLock, 0x0, owner);
WUT_CHECK_OFFSET(OSSpinLock, 0x8, recursion);
WUT_CHECK_SIZE(OSSpinLock, 0x10);

void
OSInitSpinLock(OSSpinLock *spinlock);

BOOL
OSAcquireSpinLock(OSSpinLock *spinlock);

BOOL
OSTryAcquireSpinLock(OSSpinLock *spinlock);

BOOL
OSTryAcquireSpinLockWithTimeout(OSSpinLock *spinlock,
                                OSTime timeout);

BOOL
OSReleaseSpinLock(OSSpinLock *spinlock);

BOOL
OSUninterruptibleSpinLock_Acquire(OSSpinLock *spinlock);

BOOL
OSUninterruptibleSpinLock_TryAcquire(OSSpinLock *spinlock);

BOOL
OSUninterruptibleSpinLock_TryAcquireWithTimeout(OSSpinLock *spinlock,
                                                OSTime timeout);

BOOL
OSUninterruptibleSpinLock_Release(OSSpinLock *spinlock);

#ifdef __cplusplus
}
#endif

/** @} */
