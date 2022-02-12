#pragma once
#include "enum.h"
#include <wut.h>

/**
 * \defgroup gx2_mem Memory
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void GX2Invalidate(GX2InvalidateMode mode,
                   void *buffer,
                   uint32_t size);

#ifdef __cplusplus
}
#endif

/** @} */
