#pragma once
#include <wut.h>
#include "enum.h"
#include "surface.h"

/**
 * \defgroup gx2_aperture Aperture
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t GX2ApertureHandle;

/**
 * Allocates a tiling aperture.
 * This function creates a linear and untiled buffer to read from and write to the surface.
 * The total size of the buffer will be width * height * bpp.
 * 
 * \param surface
 * A pointer to the surface to create the tiling aperture for.
 * 
 * \param level
 * The level of the surface to create the tiling aperture for.
 *
 * \param depth
 * The depth of the surface to create the tiling aperture for.
 * 
 * \param endian
 * The endian swap mode.
 * 
 * \param outHandle
 * A pointer to store the handle for the aperture.
 * 
 * \param outAddress
 * A pointer to store the address for the aperture.
 */
void
GX2AllocateTilingApertureEx(GX2Surface *surface,
                            uint32_t level,
                            uint32_t depth,
                            GX2EndianSwapMode endian,
                            GX2ApertureHandle *outHandle,
                            void **outAddress);

/**
 * Frees an allocated tiling aperture.
 *
 * \param handle
 * The handle of the tiling aperture which should be freed.
 */
void
GX2FreeTilingAperture(GX2ApertureHandle handle);

#ifdef __cplusplus
}
#endif

/** @} */
