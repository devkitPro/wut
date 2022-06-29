#pragma once
#include <wut.h>

/**
 * \defgroup proc_ui_memory ProcUI Memory Operations
 * \ingroup proc_ui
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Calculate the required size for the memory pool.
 *
 * \sa
 * - ProcUISetMemoryPool()
 * 
 * \param numCallbacks
 * The amount of callbacks which can be registered for each type.
 * 
 * \returns
 * The amount of memory required for the memory pool.
 */
uint32_t
ProcUICalcMemorySize(uint32_t numCallbacks);

/**
 * Set a custom memory pool.
 * By default all allocations are done from the default heap.
 *
 * \sa
 * - ProcUICalcMemorySize()
 * 
 * \param pool
 * The allocated memory pool.
 * 
 * \param size
 * The size of the pool.
 * 
 * \returns
 * \c 0 on success, negative value on error.
 */
int32_t
ProcUISetMemoryPool(void *pool,
                    uint32_t size);

/**
 * Set the stack size for the callback threads.
 * Default: \c 0x2000
 *
 * \param size
 * The stack size.
 */
void
ProcUISetCallbackStackSize(uint32_t size);

/**
 * Set a buffer to store the foreground bucket data after losing foreground.
 * Will be automatically restored after re-entering foreground.
 * 
 * \param buf
 * Allocated buffer in MEM2 to store the data.
 * 
 * \param size
 * The size of the buffer.
 * Use \link OSGetForegroundBucketFreeArea \endlink to determine the size.
 */
void
ProcUISetBucketStorage(void *buf,
                       uint32_t size);

/**
 * Set a buffer to store the MEM1 data after losing foreground.
 * Will be automatically restored after re-entering foreground.
 * 
 * \param buf
 * Allocated buffer in MEM2 to store the data.
 * 
 * \param size
 * The size of the buffer.
 * Use \link OSGetMemBound \endlink for \link OS_MEM1 \endlink to determine the size.
 */
void
ProcUISetMEM1Storage(void *buf,
                     uint32_t size);

#ifdef __cplusplus
}
#endif

/** @} */
