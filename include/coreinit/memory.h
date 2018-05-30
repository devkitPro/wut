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

void *
OSBlockMove(void *dst,
            const void *src,
            uint32_t size,
            BOOL flush);

void *
OSBlockSet(void *dst,
           uint8_t val,
           uint32_t size);

void *
OSAllocFromSystem(uint32_t size,
                  int align);

void
OSFreeToSystem(void *ptr);

BOOL
OSGetForegroundBucket(uint32_t *outAddr,
                      uint32_t *outSize);

BOOL
OSGetForegroundBucketFreeArea(uint32_t *outAddr,
                              uint32_t *outSize);

int
OSGetMemBound(OSMemoryType type,
              uint32_t *outAddr,
              uint32_t *outSize);

#ifdef __cplusplus
}
#endif

/** @} */
