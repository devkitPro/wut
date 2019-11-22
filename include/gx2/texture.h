#pragma once
#include <wut.h>
#include "surface.h"

/**
 * \defgroup gx2_texture Texture
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Texture GX2Texture;

struct GX2Texture
{
   GX2Surface surface;
   uint32_t viewFirstMip;
   uint32_t viewNumMips;
   uint32_t viewFirstSlice;
   uint32_t viewNumSlices;
   uint32_t compMap;

   uint32_t regs[5];
};
WUT_CHECK_OFFSET(GX2Texture, 0x0, surface);
WUT_CHECK_OFFSET(GX2Texture, 0x74, viewFirstMip);
WUT_CHECK_OFFSET(GX2Texture, 0x78, viewNumMips);
WUT_CHECK_OFFSET(GX2Texture, 0x7c, viewFirstSlice);
WUT_CHECK_OFFSET(GX2Texture, 0x80, viewNumSlices);
WUT_CHECK_OFFSET(GX2Texture, 0x84, compMap);
WUT_CHECK_OFFSET(GX2Texture, 0x88, regs);
WUT_CHECK_SIZE(GX2Texture, 0x9c);

void
GX2InitTextureRegs(GX2Texture *texture);

void
GX2SetPixelTexture(const GX2Texture *texture,
                   uint32_t unit);

void
GX2SetVertexTexture(const GX2Texture *texture,
                    uint32_t unit);

void
GX2SetGeometryTexture(const GX2Texture *texture,
                      uint32_t unit);

#ifdef __cplusplus
}
#endif

/** @} */
