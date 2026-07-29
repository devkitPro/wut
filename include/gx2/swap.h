#pragma once
#include <wut.h>
#include "enum.h"

/**
 * \defgroup gx2_swap Swap
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2ColorBuffer GX2ColorBuffer;
typedef struct GX2Texture GX2Texture;

void
GX2CopyColorBufferToScanBuffer(const GX2ColorBuffer *buffer,
                               GX2ScanTarget scanTarget);

void
GX2SwapScanBuffers();

/**
 * Gets the last frame displayed before exiting foreground.
 * This can be used for transition effects with the splash.
 * 
 * \param scanTarget
 * The scan-target to source from.
 * 
 * \param texture 
 * A pointer to the texture to store the frame. The resulting surface format is #GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8.
 *
 * \sa
 * - GX2GetLastFrameGamma()
 */
BOOL
GX2GetLastFrame(GX2ScanTarget scanTarget,
                GX2Texture *texture);

/**
 * Gets the gamma of the last frame displayed before exiting foreground.
 * \param scanTarget
 * The scan-target to source from.
 * 
 * \param gammaOut 
 * A pointer to store the gamma.
 *
 * \sa
 * - GX2GetLastFrame()
 */
BOOL
GX2GetLastFrameGamma(GX2ScanTarget scanTarget,
                     float *gammaOut);

uint32_t
GX2GetSwapInterval();

void
GX2SetSwapInterval(uint32_t interval);

#ifdef __cplusplus
}
#endif

/** @} */
