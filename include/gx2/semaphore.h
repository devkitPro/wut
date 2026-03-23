#pragma once
#include <wut.h>
#include "enum.h"

/**
 * \defgroup gx2_semaphore Semaphore
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t GX2Semaphore;

/**
 * Inserts a semaphore into the command stream.
 *
 * \param semaphore
 * Address of the semaphore. Must be aligned by \c 0x8.
 * 
 * \param action
 * Semaphore operation to perform.
 */
void
GX2SetSemaphore(GX2Semaphore *semaphore,
                GX2SemaphoreAction action);

#ifdef __cplusplus
}
#endif

/** @} */
