#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_atomic64 Atomic Operations 64 bit
 * \ingroup coreinit
 *
 * These functions are used for atomically operating on 64 bit values in memory.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

uint64_t
OSGetAtomic64(volatile uint64_t *ptr);

uint64_t
OSSetAtomic64(volatile uint64_t *ptr,
              uint64_t value);

BOOL
OSCompareAndSwapAtomic64(volatile uint64_t *ptr,
                         uint64_t compare,
                         uint64_t value);

BOOL
OSCompareAndSwapAtomicEx64(volatile uint64_t *ptr,
                           uint64_t compare,
                           uint64_t value,
                           uint64_t *old);

uint64_t
OSSwapAtomic64(volatile uint64_t *ptr,
               uint64_t value);

int64_t
OSAddAtomic64(volatile int64_t *ptr,
              int64_t value);

uint64_t
OSAndAtomic64(volatile uint64_t *ptr,
              uint64_t value);

uint64_t
OSOrAtomic64(volatile uint64_t *ptr,
             uint64_t value);

uint64_t
OSXorAtomic64(volatile uint64_t *ptr,
              uint64_t value);

BOOL
OSTestAndClearAtomic64(volatile uint64_t *ptr,
                       uint32_t bit);

BOOL
OSTestAndSetAtomic64(volatile uint64_t *ptr,
                     uint32_t bit);

#ifdef __cplusplus
}
#endif

/** @} */
