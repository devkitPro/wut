#pragma once
#include <wut.h>
#include <gx2/context.h>
#include <gx2/shaders.h>
#include <gx2/texture.h>

/**
 * \defgroup whb_gfx Graphics
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WHBGfxShaderGroup WHBGfxShaderGroup;

struct WHBGfxShaderGroup
{
   GX2FetchShader fetchShader;
   void *fetchShaderProgram;
   GX2PixelShader *pixelShader;
   GX2VertexShader *vertexShader;
   uint32_t numAttributes;
   GX2AttribStream attributes[16];
};

BOOL
WHBGfxInit();

void
WHBGfxShutdown();

BOOL
WHBGfxWaitForSwap();

BOOL
WHBGfxSwapScanBuffers();

WUT_DEPRECATED("Do not use WHBGfxBeginRender and WHBGfxFinishRender. "  \
               "Use WHBGfxSwapScanBuffers at end of the frame instead.")
inline void
WHBGfxBeginRender()
{
    WHBGfxWaitForSwap();
}

WUT_DEPRECATED("Do not use WHBGfxBeginRender and WHBGfxFinishRender. "  \
               "Use WHBGfxSwapScanBuffers at end of the frame instead.")
void
WHBGfxFinishRender();

void
WHBGfxClearColorOnly(float r, float g, float b, float a);

void
WHBGfxClearDepthStencil();

void
WHBGfxClearColorDepthStencil(float r, float g, float b, float a);

WUT_DEPRECATED("Use WHBGfxClearColorDepthStencil instead.")
inline void
WHBGfxClearColor(float r, float g, float b, float a)
{
    WHBGfxClearColorDepthStencil(r, g, b, a);
}

void
WHBGfxMakeDRCContextCurrent();

void
WHBGfxCopyDRCColorBufferTo(GX2ScanTarget scanBuffer);

inline void
WHBGfxCopyDRCColorBufferToDRCScanBuffer()
{
    WHBGfxCopyDRCColorBufferTo(GX2_SCAN_TARGET_DRC);
}

void
WHBGfxMakeTVContextCurrent();

void
WHBGfxCopyTVColorBufferTo(GX2ScanTarget scanBuffer);

inline void
WHBGfxCopyTVColorBufferToTVScanBuffer()
{
    WHBGfxCopyTVColorBufferTo(GX2_SCAN_TARGET_TV);
}

WUT_DEPRECATED("Use WHBGfxMakeDRCContextCurrent instead.")
inline void
WHBGfxBeginRenderDRC()
{
    WHBGfxMakeDRCContextCurrent();
}

WUT_DEPRECATED("Use WHBGfxCopyDRCColorBufferToDRCScanBuffer instead.")
inline void
WHBGfxFinishRenderDRC()
{
    WHBGfxCopyDRCColorBufferToDRCScanBuffer();
}

WUT_DEPRECATED("Use WHBGfxMakeTVContextCurrent instead.")
inline void
WHBGfxBeginRenderTV()
{
    WHBGfxMakeTVContextCurrent();
}

WUT_DEPRECATED("Use WHBGfxCopyTVColorBufferToTVScanBuffer instead.")
inline void
WHBGfxFinishRenderTV()
{
    WHBGfxCopyTVColorBufferToTVScanBuffer();
}

GX2PixelShader *
WHBGfxLoadGFDPixelShader(uint32_t index,
                         const void *file);

BOOL
WHBGfxFreePixelShader(GX2PixelShader *shader);

GX2VertexShader *
WHBGfxLoadGFDVertexShader(uint32_t index,
                          const void *file);

BOOL
WHBGfxFreeVertexShader(GX2VertexShader *shader);

BOOL
WHBGfxLoadGFDShaderGroup(WHBGfxShaderGroup *group,
                         uint32_t index,
                         const void *file);

BOOL
WHBGfxInitShaderAttribute(WHBGfxShaderGroup *group,
                          const char *name,
                          uint32_t buffer,
                          uint32_t offset,
                          GX2AttribFormat format);

BOOL
WHBGfxInitFetchShader(WHBGfxShaderGroup *group);

BOOL
WHBGfxFreeShaderGroup(WHBGfxShaderGroup *group);

GX2Texture *
WHBGfxLoadGFDTexture(uint32_t index,
                     const void *file);

BOOL
WHBGfxFreeTexture(GX2Texture *texture);

GX2ColorBuffer *
WHBGfxGetTVColourBuffer();

GX2DepthBuffer *
WHBGfxGetTVDepthBuffer();

GX2ContextState *
WHBGfxGetTVContextState();

GX2ColorBuffer *
WHBGfxGetDRCColourBuffer();

GX2DepthBuffer *
WHBGfxGetDRCDepthBuffer();

GX2ContextState *
WHBGfxGetDRCContextState();

#ifdef __cplusplus
}
#endif

/** @} */
