#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_cache Cache
 * \ingroup coreinit
 *
 * Interface to the low-level caching system of the PowerPC processor.
 *
 * The cache acts as a middleman between main
 * memory and the processor, speeding up access to frequently-used data.
 * However, the Wii U is not cache-coherent - written data may be cached
 * without updating main memory, and data read from the cache may be out of date
 * with respect to memory. While this isn't a problem for most code, certain
 * hardware accesses may require manual synchronisation of the cache. This is
 * achieved with coreinit's Cache group of functions.
 *
 * Since the PowerPC has a seperate cache for data and instructions, any data
 * written with the intent of executing it as instructions requires manual
 * flushing and invalidation of the data and instruction caches.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Invalidates a range of cached data, in blocks. Equivalent to a loop of
 * PowerPC \c dcbi instructions.
 *
 * This function forces the next reads from the given address to bypass the
 * the cache and go straight to memory, resulting in slower reads that are
 * guaranteed to reflect main memory.
 *
 * \param addr
 * The effective address of the data to invalidate.
 *
 * \param size
 * The size of the range to invalidate. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
DCInvalidateRange(void *addr,
                  uint32_t size);

/**
 * Flushes a range of cached data, in blocks. Equivalent to a loop of PowerPC
 * \c dcbf instructions, followed by a \c sync and \c eieio.
 *
 * This function flushes any recently cached data into main memory.
 * This allows other hardware in the console to read the data without worry
 * of main memory being outdated. It will also invalidate cached data.
 *
 * \param addr
 * The effective address of the data to flush.
 *
 * \param size
 * The size of the range to flush. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
DCFlushRange(void *addr,
             uint32_t size);

/**
 * Stores a range of cached data, in blocks. Equivalent to a loop of PowerPC
 * \c dcbst instructions, followed by a \c sync and \c eieio.
 *
 * This function writes any recently cached data into main memory.
 * This allows other hardware in the console to read the data without worry
 * of main memory being outdated. This function does <em>not</em> invalidate
 * the cached data.
 *
 * \param addr
 * The effective address of the data to store.
 *
 * \param size
 * The size of the range to store. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
DCStoreRange(void *addr,
             uint32_t size);

/**
 * Similar to \link DCFlushRange \endlink, though this function will
 * <em>not</em> run PowerPC \c sync and \c eieio instructions after flushing.
 *
 * \param addr
 * The effective address of the data to flush.
 *
 * \param size
 * The size of the range to flush. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
DCFlushRangeNoSync(void *addr,
                   uint32_t size);

/**
 * Similar to \link DCStoreRange \endlink, though this function will
 * <em>not</em> run PowerPC \c sync and \c eieio instructions after storing.
 *
 * \param addr
 * The effective address of the data to store.
 *
 * \param size
 * The size of the range to store. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
DCStoreRangeNoSync(void *addr,
                   uint32_t size);


/**
 * Zeroes the given area of the data cache (to the nearest block) with a loop of
 * PowerPC \c dcbz instructions.
 * This will not affect main memory immediately, though it will eventually
 * trickle down. Can be combined with \link DCFlushRange \endlink or
 * \link DCStoreRange \endlink to efficiently set memory to 0.
 *
 * \warning
 * The size of the range passed into this function will be internally rounded up
 * to the next multiple of 0x20. Failing to account for this could result in
 * delayed, hard-to-diagnose memory corruption.
 *
 * \param addr
 * The effective address of the data to zero.
 *
 * \param size
 * The size of the range to zero. Will be rounded up to the next 0x20.
 */
void
DCZeroRange(void *addr,
            uint32_t size);


/**
 * Gives the processor a hint that the given range of memory is likely to be
 * accessed soon, and that performance would be improved if it were cached.
 * The processor does not have to cache the requested area, but it may do so in
 * response to this function. This function is equvalent to a loop of PowerPC
 * \c dcbt instructions.
 *
 * \param addr
 * The effective address of the data to cache.
 *
 * \param size
 * The size of the range to cache. Will be rounded up to the next 0x20.
 */
void
DCTouchRange(void *addr,
             uint32_t size);


/**
 * Invalidates a range of cached instructions, in blocks. Equivalent to a loop
 * of PowerPC \c icbi instructions.
 *
 * This function forces the next instruction fetches from the given address to
 * bypass the the cache and go straight to memory, resulting in slower fetches
 * that are guaranteed to reflect main memory.
 *
 * \param addr
 * The effective address of the instructions to invalidate.
 *
 * \param size
 * The size of the range to invalidate. Will be rounded up to the next 0x20.
 *
 * \note
 * Unnecessary use of caching functions can have an adverse performance impact.
 * They should only be used when needed while interfacing with hardware.
 */
void
ICInvalidateRange(void *addr,
                  uint32_t size);
				  
void
OSMemoryBarrier();

#ifdef __cplusplus
}
#endif

/** @} */
