#pragma once
#include <wut.h>
#include "sync.h"

/**
 * \defgroup dmae_mem Memory Operations
 * \ingroup dmae
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! DMAE Memory endian swappng mode.
typedef enum
{
   //! No memory swapping.
   DMAE_SWAP_NONE = 0,
   //! 16 bit memory swapping.
   DMAE_SWAP_16   = 1,
   //! 32 bit memory swapping.
   DMAE_SWAP_32   = 2,
   //! 64 bit memory swapping.
   DMAE_SWAP_64   = 3,
} DMAESwapMode;

/**
 * Starts a DMAE copy operation.
 *
 * \param dst
 * Pointer to the destination buffer.
 *
 * \param src
 * Pointer to the source buffer.
 *
 * \param wordCount
 * Number of 32 bit words to copy.
 *
 * \param swap
 * Memory endian swapping mode.
 *
 * \return
 * DMAE operations queue timestamp.
 */
DMAETimeStamp
DMAECopyMem(void *dst,
            const void *src,
            uint32_t wordCount,
            DMAESwapMode swap);

/**
 * Starts a DMAE fill operation.
 *
 * \param dst
 * Pointer to the destination buffer.
 *
 * \param val
 * The value to fill the destination buffer.
 *
 * \param wordCount
 * Number of 32 bit words to fill.
 *
 * \return
 * DMAE operations queue timestamp.
 */
DMAETimeStamp
DMAEFillMem(void *dst,
            uint32_t val,
            uint32_t wordCount);

/**
 * Starts a DMAE fill operation for a physical address.
 *
 * \param dst
 * Pointer to the destination buffer (physical address).
 *
 * \param val
 * The value to fill the destination buffer.
 *
 * \param wordCount
 * Number of 32 bit words to fill.
 *
 * \return
 * DMAE operations queue timestamp.
 */
DMAETimeStamp
DMAEFillMemPhys(void *dst,
                uint32_t val,
                uint32_t wordCount);

#ifdef __cplusplus
}
#endif

/** @} */
