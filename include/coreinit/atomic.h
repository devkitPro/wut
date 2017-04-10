#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_atomic Atomic Operations
 * \ingroup coreinit
 *
 * These functions are used for atomically operating on 32 bit values in memory.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

BOOL
OSCompareAndSwapAtomic(volatile uint32_t *ptr,
                       uint32_t compare,
                       uint32_t value);

BOOL
OSCompareAndSwapAtomicEx(volatile uint32_t *ptr,
                         uint32_t compare,
                         uint32_t value,
                         uint32_t *old);

uint32_t
OSSwapAtomic(volatile uint32_t *ptr,
             uint32_t value);

int32_t
OSAddAtomic(volatile int32_t *ptr,
            int32_t value);

uint32_t
OSAndAtomic(volatile uint32_t *ptr,
            uint32_t value);

uint32_t
OSOrAtomic(volatile uint32_t *ptr,
           uint32_t value);

uint32_t
OSXorAtomic(volatile uint32_t *ptr,
            uint32_t value);

BOOL
OSTestAndClearAtomic(volatile uint32_t *ptr,
                     uint32_t bit);

BOOL
OSTestAndSetAtomic(volatile uint32_t *ptr,
                   uint32_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
