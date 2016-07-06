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

void *
OSBlockMove(void *dst,
            const void *src,
            uint32_t size,
            BOOL flush);

void *
OSBlockSet(void *dst,
           uint8_t val,
           uint32_t size);

#ifdef __cplusplus
}
#endif

/** @} */
