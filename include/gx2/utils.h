#pragma once
#include <wut.h>

/**
 * \defgroup gx2_utils Utils
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GX2_SQ_SEL
{
   GX2_SQ_SEL_X       = 0,
   GX2_SQ_SEL_Y       = 1,
   GX2_SQ_SEL_Z       = 2,
   GX2_SQ_SEL_W       = 3,

   GX2_SQ_SEL_R       = 0,
   GX2_SQ_SEL_G       = 1,
   GX2_SQ_SEL_B       = 2,
   GX2_SQ_SEL_A       = 3,

   GX2_SQ_SEL_0       = 4,
   GX2_SQ_SEL_1       = 5,
   GX2_SQ_SEL_MASK    = 7,
} GX2_SQ_SEL;

#define GX2_SEL_MASK(x, y, z, w) (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))
#define GX2_COMP_MAP(x, y, z, w) (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))

#ifdef __cplusplus
}
#endif

/** @} */
