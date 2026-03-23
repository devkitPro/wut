#pragma once
#include <wut.h>
#include <gx2/semaphore.h>

/**
 * \defgroup dmae_sync Synchronization
 * \ingroup dmae
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! Timestamp for a DMAE operation.
typedef uint64_t DMAETimeStamp;

DMAETimeStamp
DMAEGetLastSubmittedTimeStamp(void);

DMAETimeStamp
DMAEGetRetiredTimeStamp(void);

/**
 * Waits for a DMAE operation to complete.
 *
 * \param timestamp
 * Timestamp of the operation to wait for.
 *
 * \return
 * TRUE when successful.
 */
BOOL
DMAEWaitDone(DMAETimeStamp timestamp);

uint32_t
DMAEGetTimeout(void);

void
DMAESetTimeout(uint32_t timeout);

void
DMAESemaphore(GX2Semaphore *semaphore,
              GX2SemaphoreAction action);

#ifdef __cplusplus
}
#endif

/** @} */
