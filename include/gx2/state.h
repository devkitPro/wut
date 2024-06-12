#pragma once

#include <wut.h>
#include "enum.h"

/**
 * \defgroup gx2_state State
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
GX2Init(uint32_t *attributes);

void
GX2Shutdown();

void
GX2Flush();

void
GX2ResetGPU(uint32_t unknown);

/**
 * @return -1 if GX2 is not running, on success the core where GX2Init has been called is returned.
 */
int
GX2GetMainCoreId();

#ifdef __cplusplus
}
#endif

/** @} */
