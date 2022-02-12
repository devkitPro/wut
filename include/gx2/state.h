#pragma once
#include "enum.h"
#include <wut.h>

/**
 * \defgroup gx2_state State
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void GX2Init(uint32_t *attributes);

void GX2Shutdown();

void GX2Flush();

void GX2ResetGPU(uint32_t unknown);

#ifdef __cplusplus
}
#endif

/** @} */
