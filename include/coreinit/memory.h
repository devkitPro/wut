#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_memory Memory
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSMemoryType
{
   OS_MEM1 = 1,
   OS_MEM2 = 2,
} OSMemoryType;

typedef enum OSSharedDataType
{
   OS_SHAREDDATATYPE_FONT_CHINESE      = 0,
   OS_SHAREDDATATYPE_FONT_KOREAN       = 1,
   OS_SHAREDDATATYPE_FONT_STANDARD     = 2,
   OS_SHAREDDATATYPE_FONT_TAIWANESE    = 3,
   OS_SHAREDDATATYPE_FONT_MAX          = 4,
} OSSharedDataType;

BOOL
OSGetSharedData(OSSharedDataType type,
                uint32_t unk_r4,
                void **outPtr,
                uint32_t *outSize);

/**
 * Moves chunks of memory around, similarly to memmove. Overlapping source and
 * destination regions are supported.
 *
 * \param dst
 * The destination address for the move.
 *
 * \param src
 * The source address for the move.
 *
 * \param size
 * The size of the data to be moved, in bytes.
 *
 * \param flush
 * Whether to flush the data caches for the source and destination.
 *
 * \return
 * dst is returned.
 *
 * \note
 * This function makes use of the cache to speed up the copy, so a flush is
 * recommended.
 */
void *
OSBlockMove(void *dst,
            const void *src,
            uint32_t size,
            BOOL flush);

/**
 * Fills a chunk of memory with the given value, like memset.
 *
 * \param dst
 * Pointer to the memory to fill.
 *
 * \param val
 * Byte value to be set.
 *
 * \param size
 * Number of bytes to be set to val.
 *
 * \return
 * dst is returned.
 */
void *
OSBlockSet(void *dst,
           uint8_t val,
           uint32_t size);

void *
OSAllocFromSystem(uint32_t size,
                  int align);

void
OSFreeToSystem(void *ptr);

/**
 * Gets the location and size of the foreground bucket memory area.
 *
 * \note
 * This function may not account for the system reserved portion of the
 * foreground bucket. Consider using OSGetForegroundBucketFreeArea() instead.
 *
 * \param outAddr
 * Pointer to write the foreground bucket's address to.
 *
 * \param outSize
 * Pointer to write the foreground bucket's size to.
 *
 * \return
 * \c true on success.
 */
BOOL
OSGetForegroundBucket(uint32_t *outAddr,
                      uint32_t *outSize);

/**
 * Gets the location and size of the application-usable portion of the
 * foreground bucket area.
 *
 * \param outAddr
 * Pointer to write the bucket area's address to.
 *
 * \param outSize
 * Pointer to write the bucket area's size to.
 *
 * \return
 * \c true on success.
 */
BOOL
OSGetForegroundBucketFreeArea(uint32_t *outAddr,
                              uint32_t *outSize);

/**
 * Gets the location and size of available memory areas.
 *
 * \param type
 * Type of memory to get information about. See #OSMemoryType.
 *
 * \param outAddr
 * Pointer to write the area's address to.
 *
 * \param outSize
 * Pointer to write the area's size to.
 *
 * \return
 * 0 on success, -1 otherwise.
 */
int
OSGetMemBound(OSMemoryType type,
              uint32_t *outAddr,
              uint32_t *outSize);

/**
 * Zeros the memory for a given proccessID. 
 * Works only inside the ROOT process.
 **/
void
__OSZeroProcessMemory(uint32_t proccesID);

#ifdef __cplusplus
}
#endif

/** @} */
