#pragma once
#include <wut.h>

/**
 * \defgroup gx2_surface Surface
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2Surface GX2Surface;
typedef struct GX2DepthBuffer GX2DepthBuffer;
typedef struct GX2ColorBuffer GX2ColorBuffer;

typedef enum
{
   GX2_SURFACE_DIM_TEXTURE_1D                   = 0,
   GX2_SURFACE_DIM_TEXTURE_2D                   = 1,
   GX2_SURFACE_DIM_TEXTURE_3D                   = 2,
   GX2_SURFACE_DIM_TEXTURE_CUBE                 = 3,
   GX2_SURFACE_DIM_TEXTURE_1D_ARRAY             = 4,
   GX2_SURFACE_DIM_TEXTURE_2D_ARRAY             = 5,
   GX2_SURFACE_DIM_TEXTURE_2D_MSAA              = 6,
   GX2_SURFACE_DIM_TEXTURE_2D_MSAA_ARRAY        = 7,
} GX2SurfaceDim;

typedef enum
{
   GX2_SURFACE_FORMAT_INVALID                   = 0x00,
   GX2_SURFACE_FORMAT_UNORM_R4_G4               = 0x02,
   GX2_SURFACE_FORMAT_UNORM_R4_G4_B4_A4         = 0x0b,
   GX2_SURFACE_FORMAT_UNORM_R8                  = 0x01,
   GX2_SURFACE_FORMAT_UNORM_R8_G8               = 0x07,
   GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8         = 0x01a,
   GX2_SURFACE_FORMAT_UNORM_R16                 = 0x05,
   GX2_SURFACE_FORMAT_UNORM_R16_G16             = 0x0f,
   GX2_SURFACE_FORMAT_UNORM_R16_G16_B16_A16     = 0x01f,
   GX2_SURFACE_FORMAT_UNORM_R5_G6_B5            = 0x08,
   GX2_SURFACE_FORMAT_UNORM_R5_G5_B5_A1         = 0x0a,
   GX2_SURFACE_FORMAT_UNORM_A1_B5_G5_R5         = 0x0c,
   GX2_SURFACE_FORMAT_UNORM_R24_X8              = 0x011,
   GX2_SURFACE_FORMAT_UNORM_A2_B10_G10_R10      = 0x01b,
   GX2_SURFACE_FORMAT_UNORM_R10_G10_B10_A2      = 0x019,
   GX2_SURFACE_FORMAT_UNORM_BC1                 = 0x031,
   GX2_SURFACE_FORMAT_UNORM_BC2                 = 0x032,
   GX2_SURFACE_FORMAT_UNORM_BC3                 = 0x033,
   GX2_SURFACE_FORMAT_UNORM_BC4                 = 0x034,
   GX2_SURFACE_FORMAT_UNORM_BC5                 = 0x035,
   GX2_SURFACE_FORMAT_UNORM_NV12                = 0x081,

   GX2_SURFACE_FORMAT_UINT_R8                   = 0x101,
   GX2_SURFACE_FORMAT_UINT_R8_G8                = 0x107,
   GX2_SURFACE_FORMAT_UINT_R8_G8_B8_A8          = 0x11a,
   GX2_SURFACE_FORMAT_UINT_R16                  = 0x105,
   GX2_SURFACE_FORMAT_UINT_R16_G16              = 0x10f,
   GX2_SURFACE_FORMAT_UINT_R16_G16_B16_A16      = 0x11f,
   GX2_SURFACE_FORMAT_UINT_R32                  = 0x10d,
   GX2_SURFACE_FORMAT_UINT_R32_G32              = 0x11d,
   GX2_SURFACE_FORMAT_UINT_R32_G32_B32_A32      = 0x122,
   GX2_SURFACE_FORMAT_UINT_A2_B10_G10_R10       = 0x11b,
   GX2_SURFACE_FORMAT_UINT_R10_G10_B10_A2       = 0x119,
   GX2_SURFACE_FORMAT_UINT_X24_G8               = 0x111,
   GX2_SURFACE_FORMAT_UINT_G8_X24               = 0x11c,

   GX2_SURFACE_FORMAT_SNORM_R8                  = 0x201,
   GX2_SURFACE_FORMAT_SNORM_R8_G8               = 0x207,
   GX2_SURFACE_FORMAT_SNORM_R8_G8_B8_A8         = 0x21a,
   GX2_SURFACE_FORMAT_SNORM_R16                 = 0x205,
   GX2_SURFACE_FORMAT_SNORM_R16_G16             = 0x20f,
   GX2_SURFACE_FORMAT_SNORM_R16_G16_B16_A16     = 0x21f,
   GX2_SURFACE_FORMAT_SNORM_R10_G10_B10_A2      = 0x219,
   GX2_SURFACE_FORMAT_SNORM_BC4                 = 0x234,
   GX2_SURFACE_FORMAT_SNORM_BC5                 = 0x235,

   GX2_SURFACE_FORMAT_SINT_R8                   = 0x301,
   GX2_SURFACE_FORMAT_SINT_R8_G8                = 0x307,
   GX2_SURFACE_FORMAT_SINT_R8_G8_B8_A8          = 0x31a,
   GX2_SURFACE_FORMAT_SINT_R16                  = 0x305,
   GX2_SURFACE_FORMAT_SINT_R16_G16              = 0x30f,
   GX2_SURFACE_FORMAT_SINT_R16_G16_B16_A16      = 0x31f,
   GX2_SURFACE_FORMAT_SINT_R32                  = 0x30d,
   GX2_SURFACE_FORMAT_SINT_R32_G32              = 0x31d,
   GX2_SURFACE_FORMAT_SINT_R32_G32_B32_A32      = 0x322,
   GX2_SURFACE_FORMAT_SINT_R10_G10_B10_A2       = 0x319,

   GX2_SURFACE_FORMAT_SRGB_R8_G8_B8_A8          = 0x41a,
   GX2_SURFACE_FORMAT_SRGB_BC1                  = 0x431,
   GX2_SURFACE_FORMAT_SRGB_BC2                  = 0x432,
   GX2_SURFACE_FORMAT_SRGB_BC3                  = 0x433,

   GX2_SURFACE_FORMAT_FLOAT_R32                 = 0x80e,
   GX2_SURFACE_FORMAT_FLOAT_R32_G32             = 0x81e,
   GX2_SURFACE_FORMAT_FLOAT_R32_G32_B32_A32     = 0x823,
   GX2_SURFACE_FORMAT_FLOAT_R16                 = 0x806,
   GX2_SURFACE_FORMAT_FLOAT_R16_G16             = 0x810,
   GX2_SURFACE_FORMAT_FLOAT_R16_G16_B16_A16     = 0x820,
   GX2_SURFACE_FORMAT_FLOAT_R11_G11_B10         = 0x816,
   GX2_SURFACE_FORMAT_FLOAT_D24_S8              = 0x811,
   GX2_SURFACE_FORMAT_FLOAT_X8_X24              = 0x81c,
} GX2SurfaceFormat;

typedef enum GX2AAMode
{
   GX2_AA_MODE1X                                = 0,
} GX2AAMode;

typedef enum GX2SurfaceUse
{
   GX2_SURFACE_USE_TEXTURE                      = 1 << 0,
   GX2_SURFACE_USE_COLOR_BUFFER                 = 1 << 1,
   GX2_SURFACE_USE_DEPTH_BUFFER                 = 1 << 2,
   GX2_SURFACE_USE_SCAN_BUFFER                  = 1 << 3,
} GX2SurfaceUse;

typedef enum GX2RResourceFlags
{
   GX2R_RESOURCE_FLAGS_BIND_TEXTURE             = 1 << 0,
   GX2R_RESOURCE_FLAGS_BIND_COLOR_BUFFER        = 1 << 1,
   GX2R_RESOURCE_FLAGS_BIND_DEPTH_BUFFER        = 1 << 2,
   GX2R_RESOURCE_FLAGS_BIND_SCAN_BUFFER         = 1 << 3,
   GX2R_RESOURCE_FLAGS_BIND_VERTEX_BUFFER       = 1 << 4,
   GX2R_RESOURCE_FLAGS_BIND_INDEX_BUFFER        = 1 << 5,
   GX2R_RESOURCE_FLAGS_BIND_UNIFORM_BLOCK       = 1 << 6,
   GX2R_RESOURCE_FLAGS_BIND_SHADER_PROGRAM      = 1 << 7,
   GX2R_RESOURCE_FLAGS_BIND_STREAM_OUTPUT       = 1 << 8,
   GX2R_RESOURCE_FLAGS_BIND_DISPLAY_LIST        = 1 << 9,
   GX2R_RESOURCE_FLAGS_BIND_GS_RING             = 1 << 10,
   GX2R_RESOURCE_FLAGS_USAGE_CPU_READ           = 1 << 11,
   GX2R_RESOURCE_FLAGS_USAGE_CPU_WRITE          = 1 << 12,
   GX2R_RESOURCE_FLAGS_USAGE_GPU_READ           = 1 << 13,
   GX2R_RESOURCE_FLAGS_USAGE_GPU_WRITE          = 1 << 14,
   GX2R_RESOURCE_FLAGS_USAGE_DMA_READ           = 1 << 15,
   GX2R_RESOURCE_FLAGS_USAGE_DMA_WRITE          = 1 << 16,
   GX2R_RESOURCE_FLAGS_USAGE_FORCE_MEM1         = 1 << 17,
   GX2R_RESOURCE_FLAGS_USAGE_FORCE_MEM2         = 1 << 18,
   GX2R_RESOURCE_FLAGS_USER_MEMORY              = 1 << 29,
   GX2R_RESOURCE_FLAGS_LOCKED                   = 1 << 30,
} GX2RResourceFlags;

typedef enum GX2TileMode
{
   GX2_TILE_MODE_DEFAULT                        = 0,
   GX2_TILE_MODE_LINEAR_ALIGNED                 = 1,
   GX2_TILE_MODE_TILED_1D_THIN1                 = 2,
   GX2_TILE_MODE_TILED_1D_THICK                 = 3,
   GX2_TILE_MODE_TILED_2D_THIN1                 = 4,
   GX2_TILE_MODE_TILED_2D_THIN2                 = 5,
   GX2_TILE_MODE_TILED_2D_THIN4                 = 6,
   GX2_TILE_MODE_TILED_2D_THICK                 = 7,
   GX2_TILE_MODE_TILED_2B_THIN1                 = 8,
   GX2_TILE_MODE_TILED_2B_THIN2                 = 9,
   GX2_TILE_MODE_TILED_2B_THIN4                 = 10,
   GX2_TILE_MODE_TILED_2B_THICK                 = 11,
   GX2_TILE_MODE_TILED_3D_THIN1                 = 12,
   GX2_TILE_MODE_TILED_3D_THICK                 = 13,
   GX2_TILE_MODE_TILED_3B_THIN1                 = 14,
   GX2_TILE_MODE_TILED_3B_THICK                 = 15,
   GX2_TILE_MODE_LINEAR_SPECIAL                 = 16,
} GX2TileMode;

typedef enum GX2RenderTarget
{
   GX2_RENDER_TARGET_0                          = 0,
   GX2_RENDER_TARGET_1                          = 1,
   GX2_RENDER_TARGET_2                          = 2,
   GX2_RENDER_TARGET_3                          = 3,
   GX2_RENDER_TARGET_4                          = 4,
   GX2_RENDER_TARGET_5                          = 5,
   GX2_RENDER_TARGET_6                          = 6,
} GX2RenderTarget;

struct GX2Surface
{
   GX2SurfaceDim dim;
   uint32_t width;
   uint32_t height;
   uint32_t depth;
   uint32_t mipLevels;
   GX2SurfaceFormat format;
   GX2AAMode aa;
   union
   {
      GX2SurfaceUse use;
      GX2RResourceFlags resourceFlags;
   };
   uint32_t imageSize;
   void *image;
   uint32_t mipmapSize;
   void *mipmaps;
   GX2TileMode tileMode;
   uint32_t swizzle;
   uint32_t alignment;
   uint32_t pitch;
   uint32_t mipLevelOffset[13];
};
CHECK_OFFSET(GX2Surface, 0x0, dim);
CHECK_OFFSET(GX2Surface, 0x4, width);
CHECK_OFFSET(GX2Surface, 0x8, height);
CHECK_OFFSET(GX2Surface, 0xc, depth);
CHECK_OFFSET(GX2Surface, 0x10, mipLevels);
CHECK_OFFSET(GX2Surface, 0x14, format);
CHECK_OFFSET(GX2Surface, 0x18, aa);
CHECK_OFFSET(GX2Surface, 0x1c, use);
CHECK_OFFSET(GX2Surface, 0x1c, resourceFlags);
CHECK_OFFSET(GX2Surface, 0x20, imageSize);
CHECK_OFFSET(GX2Surface, 0x24, image);
CHECK_OFFSET(GX2Surface, 0x28, mipmapSize);
CHECK_OFFSET(GX2Surface, 0x2c, mipmaps);
CHECK_OFFSET(GX2Surface, 0x30, tileMode);
CHECK_OFFSET(GX2Surface, 0x34, swizzle);
CHECK_OFFSET(GX2Surface, 0x38, alignment);
CHECK_OFFSET(GX2Surface, 0x3C, pitch);
CHECK_OFFSET(GX2Surface, 0x40, mipLevelOffset);
CHECK_SIZE(GX2Surface, 0x74);

struct GX2DepthBuffer
{
   GX2Surface surface;

   uint32_t viewMip;
   uint32_t viewFirstSlice;
   uint32_t viewNumSlices;
   void *hiZPtr;
   uint32_t hiZSize;
   float depthClear;
   uint32_t stencilClear;

   uint32_t regs[7];
};
CHECK_OFFSET(GX2DepthBuffer, 0x74, viewMip);
CHECK_OFFSET(GX2DepthBuffer, 0x78, viewFirstSlice);
CHECK_OFFSET(GX2DepthBuffer, 0x7C, viewNumSlices);
CHECK_OFFSET(GX2DepthBuffer, 0x80, hiZPtr);
CHECK_OFFSET(GX2DepthBuffer, 0x84, hiZSize);
CHECK_OFFSET(GX2DepthBuffer, 0x88, depthClear);
CHECK_OFFSET(GX2DepthBuffer, 0x8C, stencilClear);
CHECK_OFFSET(GX2DepthBuffer, 0x90, regs);
CHECK_SIZE(GX2DepthBuffer, 0xAC);

struct GX2ColorBuffer
{
   GX2Surface surface;

   uint32_t viewMip;
   uint32_t viewFirstSlice;
   uint32_t viewNumSlices;
   void *aaBuffer;
   uint32_t aaSize;

   uint32_t regs[5];
};
CHECK_OFFSET(GX2ColorBuffer, 0x74, viewMip);
CHECK_OFFSET(GX2ColorBuffer, 0x78, viewFirstSlice);
CHECK_OFFSET(GX2ColorBuffer, 0x7C, viewNumSlices);
CHECK_OFFSET(GX2ColorBuffer, 0x80, aaBuffer);
CHECK_OFFSET(GX2ColorBuffer, 0x84, aaSize);
CHECK_OFFSET(GX2ColorBuffer, 0x88, regs);
CHECK_SIZE(GX2ColorBuffer, 0x9C);

void
GX2CalcSurfaceSizeAndAlignment(GX2Surface *surface);

void
GX2CalcDepthBufferHiZInfo(GX2DepthBuffer *depthBuffer,
                          uint32_t *outSize,
                          uint32_t *outAlignment);

void
GX2SetColorBuffer(GX2ColorBuffer *colorBuffer,
                  GX2RenderTarget target);

void
GX2SetDepthBuffer(GX2DepthBuffer *depthBuffer);

void
GX2InitColorBufferRegs(GX2ColorBuffer *colorBuffer);

void
GX2InitDepthBufferRegs(GX2DepthBuffer *depthBuffer);

void
GX2InitDepthBufferHiZEnable(GX2DepthBuffer *depthBuffer,
                            BOOL enable);

uint32_t
GX2GetSurfaceSwizzle(GX2Surface *surface);

void
GX2SetSurfaceSwizzle(GX2Surface *surface,
                     uint32_t swizzle);

void
GX2CopySurface(GX2Surface *src,
               uint32_t srcLevel,
               uint32_t srcDepth,
               GX2Surface *dst,
               uint32_t dstLevel,
               uint32_t dstDepth);

#ifdef __cplusplus
}
#endif

/** @} */
