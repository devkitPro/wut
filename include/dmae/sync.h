#pragma once
#include <wut.h>

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

#ifdef __cplusplus
}
#endif

/** @} */
