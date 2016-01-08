#pragma once
#include <wut.h>
#include "surface.h"

/**
 * \defgroup gx2_registers Registers
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2AAMaskReg GX2AAMaskReg;
typedef struct GX2AlphaTestReg GX2AlphaTestReg;
typedef struct GX2AlphaToMaskReg GX2AlphaToMaskReg;
typedef struct GX2BlendControlReg GX2BlendControlReg;
typedef struct GX2BlendConstantColorReg GX2BlendConstantColorReg;
typedef struct GX2ColorControlReg GX2ColorControlReg;
typedef struct GX2DepthStencilControlReg GX2DepthStencilControlReg;
typedef struct GX2StencilMaskReg GX2StencilMaskReg;
typedef struct GX2LineWidthReg GX2LineWidthReg;
typedef struct GX2PointSizeReg GX2PointSizeReg;
typedef struct GX2PointLimitsReg GX2PointLimitsReg;
typedef struct GX2PolygonControlReg GX2PolygonControlReg;
typedef struct GX2PolygonOffsetReg GX2PolygonOffsetReg;
typedef struct GX2ScissorReg GX2ScissorReg;
typedef struct GX2TargetChannelMaskReg GX2TargetChannelMaskReg;
typedef struct GX2ViewportReg GX2ViewportReg;

typedef enum GX2CompareFunction
{
   GX2_COMPARE_FUNC_NEVER                 = 0,
   GX2_COMPARE_FUNC_LESS                  = 1,
   GX2_COMPARE_FUNC_EQUAL                 = 2,
   GX2_COMPARE_FUNC_LEQUAL                = 3,
   GX2_COMPARE_FUNC_GREATER               = 4,
   GX2_COMPARE_FUNC_NOT_EQUAL             = 5,
   GX2_COMPARE_FUNC_GEQUAL                = 6,
   GX2_COMPARE_FUNC_ALWAYS                = 7,
} GX2CompareFunction;

typedef enum GX2AlphaToMaskMode
{
   GX2_ALPHA_TO_MASK_MODE_NON_DITHERED    = 0,
   GX2_ALPHA_TO_MASK_MODE_DITHER_0        = 1,
   GX2_ALPHA_TO_MASK_MODE_DITHER_90       = 2,
   GX2_ALPHA_TO_MASK_MODE_DITHER_180      = 3,
   GX2_ALPHA_TO_MASK_MODE_DITHER_270      = 4,
} GX2AlphaToMaskMode;

typedef enum GX2BlendMode
{
   GX2_BLEND_MODE_ZERO                    = 0,
   GX2_BLEND_MODE_ONE                     = 1,
   GX2_BLEND_MODE_SRC_COLOR               = 2,
   GX2_BLEND_MODE_INV_SRC_COLOR           = 3,
   GX2_BLEND_MODE_SRC_ALPHA               = 4,
   GX2_BLEND_MODE_INV_SRC_ALPHA           = 5,
   GX2_BLEND_MODE_DST_ALPHA               = 6,
   GX2_BLEND_MODE_INV_DST_ALPHA           = 7,
   GX2_BLEND_MODE_DST_COLOR               = 8,
   GX2_BLEND_MODE_INV_DST_COLOR           = 9,
   GX2_BLEND_MODE_SRC_ALPHA_SAT           = 10,
   GX2_BLEND_MODE_BOTH_SRC_ALPHA          = 11,
   GX2_BLEND_MODE_BOTH_INV_SRC_ALPHA      = 12,
   GX2_BLEND_MODE_BLEND_FACTOR            = 13,
   GX2_BLEND_MODE_INV_BLEND_FACTOR        = 14,
   GX2_BLEND_MODE_SRC1_COLOR              = 15,
   GX2_BLEND_MODE_INV_SRC1_COLOR          = 16,
   GX2_BLEND_MODE_SRC1_ALPHA              = 17,
   GX2_BLEND_MODE_INV_SRC1_ALPHA          = 18,
} GX2BlendMode;

typedef enum GX2BlendCombineMode
{
   GX2_BLEND_COMBINE_MODE_ADD             = 0,
   GX2_BLEND_COMBINE_MODE_SUB             = 1,
   GX2_BLEND_COMBINE_MODE_MIN             = 2,
   GX2_BLEND_COMBINE_MODE_MAX             = 3,
   GX2_BLEND_COMBINE_MODE_REV_SUB         = 4,
} GX2BlendCombineMode;

typedef enum GX2FrontFace
{
  GX2_FRONT_FACE_CCW                      = 0,
  GX2_FRONT_FACE_CW                       = 1,
} GX2FrontFace;

typedef enum GX2LogicOp
{
   GX2_LOGIC_OP_CLEAR                     = 0x00,
   GX2_LOGIC_OP_NOR                       = 0x11,
   GX2_LOGIC_OP_INV_AND                   = 0x22,
   GX2_LOGIC_OP_INV_COPY                  = 0x33,
   GX2_LOGIC_OP_REV_AND                   = 0x44,
   GX2_LOGIC_OP_INV                       = 0x55,
   GX2_LOGIC_OP_XOR                       = 0x66,
   GX2_LOGIC_OP_NOT_AND                   = 0x77,
   GX2_LOGIC_OP_AND                       = 0x88,
   GX2_LOGIC_OP_EQUIV                     = 0x99,
   GX2_LOGIC_OP_NOP                       = 0xAA,
   GX2_LOGIC_OP_INV_OR                    = 0xBB,
   GX2_LOGIC_OP_COPY                      = 0xCC,
   GX2_LOGIC_OP_REV_OR                    = 0xDD,
   GX2_LOGIC_OP_OR                        = 0xEE,
   GX2_LOGIC_OP_SET                       = 0xFF,
} GX2LogicOp;

typedef enum GX2StencilFunction
{
   GX2_STENCIL_FUNCTION_KEEP              = 0,
   GX2_STENCIL_FUNCTION_ZERO              = 1,
   GX2_STENCIL_FUNCTION_REPLACE           = 2,
   GX2_STENCIL_FUNCTION_INCR_CLAMP        = 3,
   GX2_STENCIL_FUNCTION_DECR_CLAMP        = 4,
   GX2_STENCIL_FUNCTION_INV               = 5,
   GX2_STENCIL_FUNCTION_INCR_WRAP         = 6,
   GX2_STENCIL_FUNCTION_DECR_WRAP         = 7,
} GX2StencilFunction;

typedef enum GX2PolygonMode
{
   GX2_POLYGON_MODE_POINT                 = 0,
   GX2_POLYGON_MODE_LINE                  = 1,
   GX2_POLYGON_MODE_TRIANGLE              = 2,
} GX2PolygonMode;


typedef enum GX2ChannelMask
{
   GX2_CHANNEL_MASK_R                     = 1,
   GX2_CHANNEL_MASK_G                     = 2,
   GX2_CHANNEL_MASK_RG                    = 3,
   GX2_CHANNEL_MASK_B                     = 4,
   GX2_CHANNEL_MASK_RB                    = 5,
   GX2_CHANNEL_MASK_GB                    = 6,
   GX2_CHANNEL_MASK_RGB                   = 7,
   GX2_CHANNEL_MASK_A                     = 8,
   GX2_CHANNEL_MASK_RA                    = 9,
   GX2_CHANNEL_MASK_GA                    = 10,
   GX2_CHANNEL_MASK_RGA                   = 11,
   GX2_CHANNEL_MASK_BA                    = 12,
   GX2_CHANNEL_MASK_RBA                   = 13,
   GX2_CHANNEL_MASK_GBA                   = 14,
   GX2_CHANNEL_MASK_RGBA                  = 15,
} GX2ChannelMask;

struct GX2AAMaskReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2AAMaskReg, 4);

struct GX2AlphaTestReg
{
   uint32_t regs[2];
};
CHECK_SIZE(GX2AlphaTestReg, 8);

struct GX2AlphaToMaskReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2AlphaToMaskReg, 4);

struct GX2BlendControlReg
{
   uint32_t regs[2];
};
CHECK_SIZE(GX2BlendControlReg, 8);

struct GX2BlendConstantColorReg
{
   uint32_t regs[4];
};
CHECK_SIZE(GX2BlendConstantColorReg, 16);

struct GX2ColorControlReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2ColorControlReg, 4);

struct GX2DepthStencilControlReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2DepthStencilControlReg, 4);

struct GX2StencilMaskReg
{
   uint32_t regs[2];
};
CHECK_SIZE(GX2StencilMaskReg, 8);

struct GX2LineWidthReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2LineWidthReg, 4);

struct GX2PointSizeReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2PointSizeReg, 4);

struct GX2PointLimitsReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2PointLimitsReg, 4);

struct GX2PolygonControlReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2PolygonControlReg, 4);

struct GX2PolygonOffsetReg
{
   uint32_t regs[5];
};
CHECK_SIZE(GX2PolygonOffsetReg, 20);

struct GX2ScissorReg
{
   uint32_t regs[2];
};
CHECK_SIZE(GX2ScissorReg, 8);

struct GX2TargetChannelMaskReg
{
   uint32_t regs[1];
};
CHECK_SIZE(GX2TargetChannelMaskReg, 4);

struct GX2ViewportReg
{
   uint32_t regs[12];
};
CHECK_SIZE(GX2ViewportReg, 48);

void
GX2SetAAMask(uint8_t upperLeft,
             uint8_t upperRight,
             uint8_t lowerLeft,
             uint8_t lowerRight);

void
GX2InitAAMaskReg(GX2AAMaskReg *reg,
                 uint8_t upperLeft,
                 uint8_t upperRight,
                 uint8_t lowerLeft,
                 uint8_t lowerRight);

void
GX2GetAAMaskReg(GX2AAMaskReg *reg,
                uint8_t *upperLeft,
                uint8_t *upperRight,
                uint8_t *lowerLeft,
                uint8_t *lowerRight);

void
GX2SetAAMaskReg(GX2AAMaskReg *reg);

void
GX2SetAlphaTest(BOOL alphaTest,
                GX2CompareFunction func,
                float ref);

void
GX2InitAlphaTestReg(GX2AlphaTestReg *reg,
                    BOOL alphaTest,
                    GX2CompareFunction func,
                    float ref);

void
GX2GetAlphaTestReg(const GX2AlphaTestReg *reg,
                   BOOL *alphaTest,
                   GX2CompareFunction *func,
                   float *ref);

void
GX2SetAlphaTestReg(GX2AlphaTestReg *reg);

void
GX2SetAlphaToMask(BOOL alphaToMask,
                  GX2AlphaToMaskMode mode);

void
GX2InitAlphaToMaskReg(GX2AlphaToMaskReg *reg,
                      BOOL alphaToMask,
                      GX2AlphaToMaskMode mode);

void
GX2GetAlphaToMaskReg(const GX2AlphaToMaskReg *reg,
                     BOOL *alphaToMask,
                     GX2AlphaToMaskMode *mode);

void
GX2SetAlphaToMaskReg(GX2AlphaToMaskReg *reg);

void
GX2SetBlendConstantColor(float red,
                         float green,
                         float blue,
                         float alpha);

void
GX2InitBlendConstantColorReg(GX2BlendConstantColorReg *reg,
                             float red,
                             float green,
                             float blue,
                             float alpha);

void
GX2GetBlendConstantColorReg(GX2BlendConstantColorReg *reg,
                            float *red,
                            float *green,
                            float *blue,
                            float *alpha);

void
GX2SetBlendConstantColorReg(GX2BlendConstantColorReg *reg);

void
GX2SetBlendControl(GX2RenderTarget target,
                   GX2BlendMode colorSrcBlend,
                   GX2BlendMode colorDstBlend,
                   GX2BlendCombineMode colorCombine,
                   BOOL useAlphaBlend,
                   GX2BlendMode alphaSrcBlend,
                   GX2BlendMode alphaDstBlend,
                   GX2BlendCombineMode alphaCombine);

void
GX2InitBlendControlReg(GX2BlendControlReg *reg,
                       GX2RenderTarget target,
                       GX2BlendMode colorSrcBlend,
                       GX2BlendMode colorDstBlend,
                       GX2BlendCombineMode colorCombine,
                       BOOL useAlphaBlend,
                       GX2BlendMode alphaSrcBlend,
                       GX2BlendMode alphaDstBlend,
                       GX2BlendCombineMode alphaCombine);

void
GX2GetBlendControlReg(GX2BlendControlReg *reg,
                      GX2RenderTarget *target,
                      GX2BlendMode *colorSrcBlend,
                      GX2BlendMode *colorDstBlend,
                      GX2BlendCombineMode *colorCombine,
                      BOOL *useAlphaBlend,
                      GX2BlendMode *alphaSrcBlend,
                      GX2BlendMode *alphaDstBlend,
                      GX2BlendCombineMode *alphaCombine);

void
GX2SetBlendControlReg(GX2BlendControlReg *reg);

void
GX2SetColorControl(GX2LogicOp rop3,
                   uint8_t targetBlendEnable,
                   BOOL multiWriteEnable,
                   BOOL colorWriteEnable);

void
GX2InitColorControlReg(GX2ColorControlReg *reg,
                       GX2LogicOp rop3,
                       uint8_t targetBlendEnable,
                       BOOL multiWriteEnable,
                       BOOL colorWriteEnable);

void
GX2GetColorControlReg(GX2ColorControlReg *reg,
                      GX2LogicOp *rop3,
                      uint8_t *targetBlendEnable,
                      BOOL *multiWriteEnable,
                      BOOL *colorWriteEnable);

void
GX2SetColorControlReg(GX2ColorControlReg *reg);

void
GX2SetDepthOnlyControl(BOOL depthTest,
                       BOOL depthWrite,
                       GX2CompareFunction depthCompare);

void
GX2SetDepthStencilControl(BOOL depthTest,
                          BOOL depthWrite,
                          GX2CompareFunction depthCompare,
                          BOOL stencilTest,
                          BOOL backfaceStencil,
                          GX2CompareFunction frontStencilFunc,
                          GX2StencilFunction frontStencilZPass,
                          GX2StencilFunction frontStencilZFail,
                          GX2StencilFunction frontStencilFail,
                          GX2CompareFunction backStencilFunc,
                          GX2StencilFunction backStencilZPass,
                          GX2StencilFunction backStencilZFail,
                          GX2StencilFunction backStencilFail);

void
GX2InitDepthStencilControlReg(GX2DepthStencilControlReg *reg,
                              BOOL depthTest,
                              BOOL depthWrite,
                              GX2CompareFunction depthCompare,
                              BOOL stencilTest,
                              BOOL backfaceStencil,
                              GX2CompareFunction frontStencilFunc,
                              GX2StencilFunction frontStencilZPass,
                              GX2StencilFunction frontStencilZFail,
                              GX2StencilFunction frontStencilFail,
                              GX2CompareFunction backStencilFunc,
                              GX2StencilFunction backStencilZPass,
                              GX2StencilFunction backStencilZFail,
                              GX2StencilFunction backStencilFail);

void
GX2GetDepthStencilControlReg(GX2DepthStencilControlReg *reg,
                             BOOL *depthTest,
                             BOOL *depthWrite,
                             GX2CompareFunction *depthCompare,
                             BOOL *stencilTest,
                             BOOL *backfaceStencil,
                             GX2CompareFunction *frontStencilFunc,
                             GX2StencilFunction *frontStencilZPass,
                             GX2StencilFunction *frontStencilZFail,
                             GX2StencilFunction *frontStencilFail,
                             GX2CompareFunction *backStencilFunc,
                             GX2StencilFunction *backStencilZPass,
                             GX2StencilFunction *backStencilZFail,
                             GX2StencilFunction *backStencilFail);

void
GX2SetDepthStencilControlReg(GX2DepthStencilControlReg *reg);

void
GX2SetStencilMask(uint8_t frontMask,
                  uint8_t frontWriteMask,
                  uint8_t frontRef,
                  uint8_t backMask,
                  uint8_t backWriteMask,
                  uint8_t backRef);

void
GX2InitStencilMaskReg(GX2StencilMaskReg *reg,
                      uint8_t frontMask,
                      uint8_t frontWriteMask,
                      uint8_t frontRef,
                      uint8_t backMask,
                      uint8_t backWriteMask,
                      uint8_t backRef);

void
GX2GetStencilMaskReg(GX2StencilMaskReg *reg,
                     uint8_t *frontMask,
                     uint8_t *frontWriteMask,
                     uint8_t *frontRef,
                     uint8_t *backMask,
                     uint8_t *backWriteMask,
                     uint8_t *backRef);

void
GX2SetStencilMaskReg(GX2StencilMaskReg *reg);

void
GX2SetLineWidth(float width);

void
GX2InitLineWidthReg(GX2LineWidthReg *reg,
                    float width);

void
GX2GetLineWidthReg(GX2LineWidthReg *reg,
                   float *width);

void
GX2SetLineWidthReg(GX2LineWidthReg *reg);

void
GX2SetPointSize(float width,
                float height);

void
GX2InitPointSizeReg(GX2PointSizeReg *reg,
                    float width,
                    float height);

void
GX2GetPointSizeReg(GX2PointSizeReg *reg,
                   float *width,
                   float *height);

void
GX2SetPointSizeReg(GX2PointSizeReg *reg);

void
GX2SetPointLimits(float min,
                  float max);

void
GX2InitPointLimitsReg(GX2PointLimitsReg *reg,
                      float min,
                      float max);

void
GX2GetPointLimitsReg(GX2PointLimitsReg *reg,
                     float *min,
                     float *max);

void
GX2SetPointLimitsReg(GX2PointLimitsReg *reg);

void
GX2SetCullOnlyControl(GX2FrontFace frontFace,
                      BOOL cullFront,
                      BOOL cullBack);

void
GX2SetPolygonControl(GX2FrontFace frontFace,
                     BOOL cullFront,
                     BOOL cullBack,
                     BOOL polyMode,
                     GX2PolygonMode polyModeFront,
                     GX2PolygonMode polyModeBack,
                     BOOL polyOffsetFrontEnable,
                     BOOL polyOffsetBackEnable,
                     BOOL polyOffsetParaEnable);

void
GX2InitPolygonControlReg(GX2PolygonControlReg *reg,
                         GX2FrontFace frontFace,
                         BOOL cullFront,
                         BOOL cullBack,
                         BOOL polyMode,
                         GX2PolygonMode polyModeFront,
                         GX2PolygonMode polyModeBack,
                         BOOL polyOffsetFrontEnable,
                         BOOL polyOffsetBackEnable,
                         BOOL polyOffsetParaEnable);

void
GX2GetPolygonControlReg(GX2PolygonControlReg *reg,
                        GX2FrontFace *frontFace,
                        BOOL *cullFront,
                        BOOL *cullBack,
                        BOOL *polyMode,
                        GX2PolygonMode *polyModeFront,
                        GX2PolygonMode *polyModeBack,
                        BOOL *polyOffsetFrontEnable,
                        BOOL *polyOffsetBackEnable,
                        BOOL *polyOffsetParaEnable);

void
GX2SetPolygonControlReg(GX2PolygonControlReg *reg);

void
GX2SetPolygonOffset(float frontOffset,
                    float frontScale,
                    float backOffset,
                    float backScale,
                    float clamp);

void
GX2InitPolygonOffsetReg(GX2PolygonOffsetReg *reg,
                        float frontOffset,
                        float frontScale,
                        float backOffset,
                        float backScale,
                        float clamp);

void
GX2GetPolygonOffsetReg(GX2PolygonOffsetReg *reg,
                       float *frontOffset,
                       float *frontScale,
                       float *backOffset,
                       float *backScale,
                       float *clamp);

void
GX2SetPolygonOffsetReg(GX2PolygonOffsetReg *reg);

void
GX2SetScissor(uint32_t x,
              uint32_t y,
              uint32_t width,
              uint32_t height);

void
GX2InitScissorReg(GX2ScissorReg *reg,
                  uint32_t x,
                  uint32_t y,
                  uint32_t width,
                  uint32_t height);

void
GX2GetScissorReg(GX2ScissorReg *reg,
                 uint32_t *x,
                 uint32_t *y,
                 uint32_t *width,
                 uint32_t *height);

void
GX2SetScissorReg(GX2ScissorReg *reg);

void
GX2SetTargetChannelMasks(GX2ChannelMask mask0,
                         GX2ChannelMask mask1,
                         GX2ChannelMask mask2,
                         GX2ChannelMask mask3,
                         GX2ChannelMask mask4,
                         GX2ChannelMask mask5,
                         GX2ChannelMask mask6,
                         GX2ChannelMask mask7);

void
GX2InitTargetChannelMasksReg(GX2TargetChannelMaskReg *reg,
                             GX2ChannelMask mask0,
                             GX2ChannelMask mask1,
                             GX2ChannelMask mask2,
                             GX2ChannelMask mask3,
                             GX2ChannelMask mask4,
                             GX2ChannelMask mask5,
                             GX2ChannelMask mask6,
                             GX2ChannelMask mask7);

void
GX2GetTargetChannelMasksReg(GX2TargetChannelMaskReg *reg,
                            GX2ChannelMask *mask0,
                            GX2ChannelMask *mask1,
                            GX2ChannelMask *mask2,
                            GX2ChannelMask *mask3,
                            GX2ChannelMask *mask4,
                            GX2ChannelMask *mask5,
                            GX2ChannelMask *mask6,
                            GX2ChannelMask *mask7);

void
GX2SetTargetChannelMasksReg(GX2TargetChannelMaskReg *reg);

void
GX2SetViewport(float x,
               float y,
               float width,
               float height,
               float nearZ,
               float farZ);

void
GX2InitViewportReg(GX2ViewportReg *reg,
                   float x,
                   float y,
                   float width,
                   float height,
                   float nearZ,
                   float farZ);

void
GX2GetViewportReg(GX2ViewportReg *reg,
                  float *x,
                  float *y,
                  float *width,
                  float *height,
                  float *nearZ,
                  float *farZ);

void
GX2SetViewportReg(GX2ViewportReg *reg);

#ifdef __cplusplus
}
#endif

/** @} */
