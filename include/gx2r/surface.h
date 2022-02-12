#pragma once
#include "resource.h"
#include <wut.h>

/**
 * \defgroup gx2r_surface Surface
 * \ingroup gx2r
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Surface GX2Surface;

BOOL GX2RCreateSurface(GX2Surface *surface,
                       GX2RResourceFlags flags);

BOOL GX2RCreateSurfaceUserMemory(GX2Surface *surface,
                                 uint8_t *image,
                                 uint8_t *mipmap,
                                 GX2RResourceFlags flags);

BOOL GX2RDestroySurfaceEx(GX2Surface *surface,
                          GX2RResourceFlags flags);

BOOL GX2RInvalidateSurface(GX2Surface *surface,
                           int32_t level,
                           GX2RResourceFlags flags);

void *
GX2RLockSurfaceEx(GX2Surface *surface,
                  int32_t level,
                  GX2RResourceFlags flags);

void GX2RUnlockSurfaceEx(GX2Surface *surface,
                         int32_t level,
                         GX2RResourceFlags flags);

#ifdef __cplusplus
}
#endif

/** @} */
