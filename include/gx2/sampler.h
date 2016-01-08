#pragma once
#include <wut.h>

/**
 * \defgroup gx2_sampler Sampler
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

struct GX2Sampler
{
   uint32_t regs[3];
};
CHECK_SIZE(GX2Sampler, 12);

typedef enum GX2TexBorderType
{
   GX2_TEX_BORDER_TYPE_TRANSPARENT_BLACK     = 0,
   GX2_TEX_BORDER_TYPE_BLACK                 = 1,
   GX2_TEX_BORDER_TYPE_WHITE                 = 2,
   GX2_TEX_BORDER_TYPE_VARIABLE              = 3,
} GX2TexBorderType;

typedef enum GX2TexClampMode
{
   GX2_TEX_CLAMP_MODE_WRAP                   = 0,
   GX2_TEX_CLAMP_MODE_MIRROR                 = 1,
   GX2_TEX_CLAMP_MODE_CLAMP                  = 2,
   GX2_TEX_CLAMP_MODE_MIRROR_ONCE            = 3,
   GX2_TEX_CLAMP_MODE_CLAMP_BORDER           = 6,
} GX2TexClampMode;

typedef enum GX2TexMipFilterMode
{
   GX2_TEX_MIP_FILTER_MODE_NONE              = 0,
   GX2_TEX_MIP_FILTER_MODE_POINT             = 1,
   GX2_TEX_MIP_FILTER_MODE_LINEAR            = 2,
} GX2TexMipFilterMode;

typedef enum GX2TexMipPerfMode
{
   GX2_TEX_MIP_PERF_MODE_DISABLE             = 0,
} GX2TexMipPerfMode;

typedef enum GX2TexXYFilterMode
{
   GX2_TEX_XY_FILLTER_MODE_POINT             = 0,
   GX2_TEX_XY_FILLTER_MODE_LINEAR            = 1,
} GX2TexXYFilterMode;

typedef enum GX2TexAnisoRatio
{
   GX2_TEX_ANISO_RATIO_NONE                  = 0,
} GX2TexAnisoRatio;

typedef enum GX2TexZFilterMode
{
   GX2_TEX_Z_FILTER_MODE_NONE                = 0,
   GX2_TEX_Z_FILTER_MODE_POINT               = 1,
   GX2_TEX_Z_FILTER_MODE_LINEAR              = 2,
} GX2TexZFilterMode;

typedef enum GX2TexZPerfMode
{
} GX2TexZPerfMode;

typedef enum GX2RoundingMode
{
   GX2_ROUNDING_MODE_ROUND_TO_EVEN           = 0,
   GX2_ROUNDING_MODE_TRUNCATE                = 1,
} GX2RoundingMode;

void
GX2InitSampler(GX2Sampler *sampler,
               GX2TexClampMode clampMode,
               GX2TexXYFilterMode minMagFilterMode);

void
GX2InitSamplerBorderType(GX2Sampler *sampler,
                         GX2TexBorderType borderType);

void
GX2InitSamplerClamping(GX2Sampler *sampler,
                       GX2TexClampMode clampX,
                       GX2TexClampMode clampY,
                       GX2TexClampMode clampZ);

void
GX2InitSamplerDepthCompare(GX2Sampler *sampler,
                           GX2CompareFunction depthCompare);

void
GX2InitSamplerFilterAdjust(GX2Sampler *sampler,
                           BOOL highPrecision,
                           GX2TexMipPerfMode perfMip,
                           GX2TexZPerfMode perfZ);

void
GX2InitSamplerLOD(GX2Sampler *sampler,
                  float lodMin,
                  float lodMax,
                  float lodBias);

void
GX2InitSamplerLODAdjust(GX2Sampler *sampler,
                        float unk1,
                        BOOL unk2);

void
GX2InitSamplerRoundingMode(GX2Sampler *sampler,
                           GX2RoundingMode roundingMode);

void
GX2InitSamplerXYFilter(GX2Sampler *sampler,
                       GX2TexXYFilterMode filterMag,
                       GX2TexXYFilterMode filterMin,
                       GX2TexAnisoRatio maxAniso);

void
GX2InitSamplerZMFilter(GX2Sampler *sampler,
                       GX2TexZFilterMode filterZ,
                       GX2TexMipFilterMode filterMip);

#ifdef __cplusplus
}
#endif

/** @} */
