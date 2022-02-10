#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_scheduler Scheduler
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

extern void* __OSSchedulerLock;

void
__OSEnableScheduler();

void
__OSDisableScheduler();

void
__OSLockScheduler(void* lockId);

void
__OSUnlockScheduler(void* lockId);

BOOL
OSIsSchedulerLocked(void* lockId);

void
__OSTryLockScheduler(void* lockId);
 
void
__OSTouchSchedulerLock();

#ifdef __cplusplus
}
#endif

/** @} */
