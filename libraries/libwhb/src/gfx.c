#include "gfx_heap.h"

#include <gx2/clear.h>
#include <gx2/context.h>
#include <gx2/display.h>
#include <gx2/event.h>
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <gx2/shaders.h>
#include <gx2/state.h>
#include <gx2/surface.h>
#include <gx2/swap.h>
#include <gx2/temp.h>
#include <gx2r/mem.h>
#include <proc_ui/procui.h>
#include <string.h>
#include <whb/gfx.h>
#include <whb/log.h>

#define WHB_GFX_COMMAND_BUFFER_POOL_SIZE (0x400000)

static void *
sCommandBufferPool = NULL;

static GX2DrcRenderMode
sDrcRenderMode;

static void *
sDrcScanBuffer = NULL;

static uint32_t
sDrcScanBufferSize = 0;

static GX2SurfaceFormat
sDrcSurfaceFormat;

static GX2TVRenderMode
sTvRenderMode;

static void *
sTvScanBuffer = NULL;

static uint32_t
sTvScanBufferSize = 0;

static GX2SurfaceFormat
sTvSurfaceFormat;

static GX2ColorBuffer
sTvColourBuffer = { 0 };

static GX2DepthBuffer
sTvDepthBuffer = { 0 };

static GX2ColorBuffer
sDrcColourBuffer = { 0 };

static GX2DepthBuffer
sDrcDepthBuffer = { 0 };

static GX2ContextState *
sTvContextState = NULL;

static GX2ContextState *
sDrcContextState = NULL;

static BOOL
sDrawingTv = FALSE;

static BOOL
sGpuTimedOut = FALSE;

static BOOL
sGfxHasForeground = TRUE;

static void *
GfxGX2RAlloc(GX2RResourceFlags flags,
             uint32_t size,
             uint32_t alignment)
{
   // Color, depth, scan buffers all belong in MEM1
   if ((flags & (GX2R_RESOURCE_BIND_COLOR_BUFFER
                | GX2R_RESOURCE_BIND_DEPTH_BUFFER
                | GX2R_RESOURCE_BIND_SCAN_BUFFER
                | GX2R_RESOURCE_USAGE_FORCE_MEM1))
      && !(flags & GX2R_RESOURCE_USAGE_FORCE_MEM2)) {
      return GfxHeapAllocMEM1(size, alignment);
   } else {
      return GfxHeapAllocMEM2(size, alignment);
   }
}

static void
GfxGX2RFree(GX2RResourceFlags flags, void *block)
{
   if ((flags & (GX2R_RESOURCE_BIND_COLOR_BUFFER
                | GX2R_RESOURCE_BIND_DEPTH_BUFFER
                | GX2R_RESOURCE_BIND_SCAN_BUFFER
                | GX2R_RESOURCE_USAGE_FORCE_MEM1))
      && !(flags & GX2R_RESOURCE_USAGE_FORCE_MEM2)) {
      return GfxHeapFreeMEM1(block);
   } else {
      return GfxHeapFreeMEM2(block);
   }
}

static void
GfxInitTvColourBuffer(GX2ColorBuffer *cb,
                      uint32_t width,
                      uint32_t height,
                      GX2SurfaceFormat format,
                      GX2AAMode aa)
{
   memset(cb, 0, sizeof(GX2ColorBuffer));
   cb->surface.use = GX2_SURFACE_USE_TEXTURE_COLOR_BUFFER_TV;
   cb->surface.dim = GX2_SURFACE_DIM_TEXTURE_2D;
   cb->surface.width = width;
   cb->surface.height = height;
   cb->surface.depth = 1;
   cb->surface.mipLevels = 1;
   cb->surface.format = format;
   cb->surface.aa = aa;
   cb->surface.tileMode = GX2_TILE_MODE_DEFAULT;
   cb->viewNumSlices = 1;
   GX2CalcSurfaceSizeAndAlignment(&cb->surface);
   GX2InitColorBufferRegs(cb);
}

static void
GfxInitDepthBuffer(GX2DepthBuffer *db,
                   uint32_t width,
                   uint32_t height,
                   GX2SurfaceFormat format,
                   GX2AAMode aa)
{
   memset(db, 0, sizeof(GX2DepthBuffer));

   if (format == GX2_SURFACE_FORMAT_UNORM_R24_X8 || format == GX2_SURFACE_FORMAT_FLOAT_D24_S8) {
      db->surface.use = GX2_SURFACE_USE_DEPTH_BUFFER;
   } else {
      db->surface.use = GX2_SURFACE_USE_DEPTH_BUFFER | GX2_SURFACE_USE_TEXTURE;
   }

   db->surface.dim = GX2_SURFACE_DIM_TEXTURE_2D;
   db->surface.width = width;
   db->surface.height = height;
   db->surface.depth = 1;
   db->surface.mipLevels = 1;
   db->surface.format = format;
   db->surface.aa = aa;
   db->surface.tileMode = GX2_TILE_MODE_DEFAULT;
   db->viewNumSlices = 1;
   db->depthClear = 1.0f;
   GX2CalcSurfaceSizeAndAlignment(&db->surface);
   GX2InitDepthBufferRegs(db);
}

static uint32_t
GfxProcCallbackAcquired(void *context)
{
   sGfxHasForeground = TRUE;

   if (!GfxHeapInitMEM1()) {
      WHBLogPrintf("%s: GfxHeapInitMEM1 failed", __FUNCTION__);
      goto error;
   }

   if (!GfxHeapInitForeground()) {
      WHBLogPrintf("%s: GfxHeapInitForeground failed", __FUNCTION__);
      goto error;
   }

   // Allocate TV scan buffer.
   sTvScanBuffer = GfxHeapAllocForeground(sTvScanBufferSize, GX2_SCAN_BUFFER_ALIGNMENT);
   if (!sTvScanBuffer) {
      WHBLogPrintf("%s: sTvScanBuffer = GfxHeapAllocForeground(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sTvScanBufferSize,
                   GX2_SCAN_BUFFER_ALIGNMENT);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sTvScanBuffer, sTvScanBufferSize);
   GX2SetTVBuffer(sTvScanBuffer, sTvScanBufferSize, sTvRenderMode, sTvSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE);

   // Allocate TV colour buffer.
   sTvColourBuffer.surface.image = GfxHeapAllocMEM1(sTvColourBuffer.surface.imageSize, sTvColourBuffer.surface.alignment);
   if (!sTvColourBuffer.surface.image) {
      WHBLogPrintf("%s: sTvColourBuffer = GfxHeapAllocMEM1(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sTvColourBuffer.surface.imageSize,
                   sTvColourBuffer.surface.alignment);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sTvColourBuffer.surface.image, sTvColourBuffer.surface.imageSize);

   // Allocate TV depth buffer.
   sTvDepthBuffer.surface.image = GfxHeapAllocMEM1(sTvDepthBuffer.surface.imageSize, sTvDepthBuffer.surface.alignment);
   if (!sTvDepthBuffer.surface.image) {
      WHBLogPrintf("%s: sTvDepthBuffer = GfxHeapAllocMEM1(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sTvDepthBuffer.surface.imageSize,
                   sTvDepthBuffer.surface.alignment);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sTvDepthBuffer.surface.image, sTvDepthBuffer.surface.imageSize);

   // Allocate DRC scan buffer.
   sDrcScanBuffer = GfxHeapAllocForeground(sDrcScanBufferSize, GX2_SCAN_BUFFER_ALIGNMENT);
   if (!sDrcScanBuffer) {
      WHBLogPrintf("%s: sDrcScanBuffer = GfxHeapAllocForeground(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sDrcScanBufferSize,
                   GX2_SCAN_BUFFER_ALIGNMENT);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sDrcScanBuffer, sDrcScanBufferSize);
   GX2SetDRCBuffer(sDrcScanBuffer, sDrcScanBufferSize, sDrcRenderMode, sDrcSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE);

   // Allocate DRC colour buffer.
   sDrcColourBuffer.surface.image = GfxHeapAllocMEM1(sDrcColourBuffer.surface.imageSize, sDrcColourBuffer.surface.alignment);
   if (!sDrcColourBuffer.surface.image) {
      WHBLogPrintf("%s: sDrcColourBuffer = GfxHeapAllocMEM1(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sDrcColourBuffer.surface.imageSize,
                   sDrcColourBuffer.surface.alignment);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sDrcColourBuffer.surface.image, sDrcColourBuffer.surface.imageSize);

   // Allocate DRC depth buffer.
   sDrcDepthBuffer.surface.image = GfxHeapAllocMEM1(sDrcDepthBuffer.surface.imageSize, sDrcDepthBuffer.surface.alignment);
   if (!sDrcDepthBuffer.surface.image) {
      WHBLogPrintf("%s: sDrcDepthBuffer = GfxHeapAllocMEM1(0x%X, 0x%X) failed",
                   __FUNCTION__,
                   sDrcDepthBuffer.surface.imageSize,
                   sDrcDepthBuffer.surface.alignment);
      goto error;
   }
   GX2Invalidate(GX2_INVALIDATE_MODE_CPU, sDrcDepthBuffer.surface.image, sDrcDepthBuffer.surface.imageSize);
   return 0;

error:
   return -1;
}

static uint32_t
GfxProcCallbackReleased(void *context)
{
   GX2DrawDone();

   if (sTvScanBuffer) {
      GfxHeapFreeForeground(sTvScanBuffer);
      sTvScanBuffer = NULL;
   }

   if (sTvColourBuffer.surface.image) {
      GfxHeapFreeMEM1(sTvColourBuffer.surface.image);
      sTvColourBuffer.surface.image = NULL;
   }

   if (sTvDepthBuffer.surface.image) {
      GfxHeapFreeMEM1(sTvDepthBuffer.surface.image);
      sTvDepthBuffer.surface.image = NULL;
   }

   if (sDrcScanBuffer) {
      GfxHeapFreeForeground(sDrcScanBuffer);
      sDrcScanBuffer = NULL;
   }

   if (sDrcColourBuffer.surface.image) {
      GfxHeapFreeMEM1(sDrcColourBuffer.surface.image);
      sDrcColourBuffer.surface.image = NULL;
   }

   if (sDrcDepthBuffer.surface.image) {
      GfxHeapFreeMEM1(sDrcDepthBuffer.surface.image);
      sDrcDepthBuffer.surface.image = NULL;
   }

   GfxHeapDestroyMEM1();
   GfxHeapDestroyForeground();
   sGfxHasForeground = FALSE;
   return 0;
}

BOOL
WHBGfxInit()
{
   uint32_t drcWidth, drcHeight;
   uint32_t tvWidth, tvHeight;
   uint32_t unk;

   sCommandBufferPool = GfxHeapAllocMEM2(WHB_GFX_COMMAND_BUFFER_POOL_SIZE,
                                         GX2_COMMAND_BUFFER_ALIGNMENT);
   if (!sCommandBufferPool) {
      WHBLogPrintf("%s: failed to allocate command buffer pool", __FUNCTION__);
      goto error;
   }

   uint32_t initAttribs[] = {
      GX2_INIT_CMD_BUF_BASE, (uintptr_t)sCommandBufferPool,
      GX2_INIT_CMD_BUF_POOL_SIZE, WHB_GFX_COMMAND_BUFFER_POOL_SIZE,
      GX2_INIT_ARGC, 0,
      GX2_INIT_ARGV, 0,
      GX2_INIT_END
   };
   GX2Init(initAttribs);

   sDrcRenderMode = GX2GetSystemDRCMode();
   sTvSurfaceFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
   sDrcSurfaceFormat = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;

   switch(GX2GetSystemTVScanMode())
   {
   case GX2_TV_SCAN_MODE_480I:
   case GX2_TV_SCAN_MODE_480P:
      sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_480P;
      tvWidth = 854;
      tvHeight = 480;
      break;
   case GX2_TV_SCAN_MODE_1080I:
   case GX2_TV_SCAN_MODE_1080P:
      sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_1080P;
      tvWidth = 1920;
      tvHeight = 1080;
      break;
   case GX2_TV_SCAN_MODE_720P:
   default:
      sTvRenderMode = GX2_TV_RENDER_MODE_WIDE_720P;
      tvWidth = 1280;
      tvHeight = 720;
      break;
   }

   drcWidth = 854;
   drcHeight = 480;

   // Setup TV and DRC buffers - they will be allocated in GfxProcCallbackAcquired.
   GX2CalcTVSize(sTvRenderMode, sTvSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE, &sTvScanBufferSize, &unk);
   GfxInitTvColourBuffer(&sTvColourBuffer, tvWidth, tvHeight, sTvSurfaceFormat, GX2_AA_MODE1X);
   GfxInitDepthBuffer(&sTvDepthBuffer, sTvColourBuffer.surface.width, sTvColourBuffer.surface.height, GX2_SURFACE_FORMAT_FLOAT_R32, sTvColourBuffer.surface.aa);

   GX2CalcDRCSize(sDrcRenderMode, sDrcSurfaceFormat, GX2_BUFFERING_MODE_DOUBLE, &sDrcScanBufferSize, &unk);
   GfxInitTvColourBuffer(&sDrcColourBuffer, drcWidth, drcHeight, sDrcSurfaceFormat, GX2_AA_MODE1X);
   GfxInitDepthBuffer(&sDrcDepthBuffer, sDrcColourBuffer.surface.width, sDrcColourBuffer.surface.height, GX2_SURFACE_FORMAT_FLOAT_R32, sDrcColourBuffer.surface.aa);
   if (GfxProcCallbackAcquired(NULL) != 0) {
      WHBLogPrintf("%s: GfxProcCallbackAcquired failed", __FUNCTION__);
      goto error;
   }

   GX2RSetAllocator(&GfxGX2RAlloc, &GfxGX2RFree);
   ProcUIRegisterCallback(PROCUI_CALLBACK_ACQUIRE, GfxProcCallbackAcquired, NULL, 100);
   ProcUIRegisterCallback(PROCUI_CALLBACK_RELEASE, GfxProcCallbackReleased, NULL, 100);

   // Initialise TV context state.
   sTvContextState = GfxHeapAllocMEM2(sizeof(GX2ContextState), GX2_CONTEXT_STATE_ALIGNMENT);
   if (!sTvContextState) {
      WHBLogPrintf("%s: failed to allocate sTvContextState", __FUNCTION__);
      goto error;
   }
   GX2SetupContextStateEx(sTvContextState, TRUE);
   GX2SetContextState(sTvContextState);
   GX2SetColorBuffer(&sTvColourBuffer, GX2_RENDER_TARGET_0);
   GX2SetDepthBuffer(&sTvDepthBuffer);
   GX2SetViewport(0, 0, (float)sTvColourBuffer.surface.width, (float)sTvColourBuffer.surface.height, 0.0f, 1.0f);
   GX2SetScissor(0, 0, (float)sTvColourBuffer.surface.width, (float)sTvColourBuffer.surface.height);
   GX2SetTVScale((float)sTvColourBuffer.surface.width, (float)sTvColourBuffer.surface.height);

   // Initialise DRC context state.
   sDrcContextState = GfxHeapAllocMEM2(sizeof(GX2ContextState), GX2_CONTEXT_STATE_ALIGNMENT);
   if (!sDrcContextState) {
      WHBLogPrintf("%s: failed to allocate sDrcContextState", __FUNCTION__);
      goto error;
   }
   GX2SetupContextStateEx(sDrcContextState, TRUE);
   GX2SetContextState(sDrcContextState);
   GX2SetColorBuffer(&sDrcColourBuffer, GX2_RENDER_TARGET_0);
   GX2SetDepthBuffer(&sDrcDepthBuffer);
   GX2SetViewport(0, 0, (float)sDrcColourBuffer.surface.width, (float)sDrcColourBuffer.surface.height, 0.0f, 1.0f);
   GX2SetScissor(0, 0, (float)sDrcColourBuffer.surface.width, (float)sDrcColourBuffer.surface.height);
   GX2SetDRCScale((float)sDrcColourBuffer.surface.width, (float)sDrcColourBuffer.surface.height);

   // Set 60fps VSync
   GX2SetSwapInterval(1);

   return TRUE;

error:
   if (sCommandBufferPool) {
      GfxHeapFreeMEM2(sCommandBufferPool);
      sCommandBufferPool = NULL;
   }

   if (sTvScanBuffer) {
      GfxHeapFreeForeground(sTvScanBuffer);
      sTvScanBuffer = NULL;
   }

   if (sTvColourBuffer.surface.image) {
      GfxHeapFreeMEM1(sTvColourBuffer.surface.image);
      sTvColourBuffer.surface.image = NULL;
   }

   if (sTvDepthBuffer.surface.image) {
      GfxHeapFreeMEM1(sTvDepthBuffer.surface.image);
      sTvDepthBuffer.surface.image = NULL;
   }

   if (sTvContextState) {
      GfxHeapFreeMEM2(sTvContextState);
      sTvContextState = NULL;
   }

   if (sDrcScanBuffer) {
      GfxHeapFreeForeground(sDrcScanBuffer);
      sDrcScanBuffer = NULL;
   }

   if (sDrcColourBuffer.surface.image) {
      GfxHeapFreeMEM1(sDrcColourBuffer.surface.image);
      sDrcColourBuffer.surface.image = NULL;
   }

   if (sDrcDepthBuffer.surface.image) {
      GfxHeapFreeMEM1(sDrcDepthBuffer.surface.image);
      sDrcDepthBuffer.surface.image = NULL;
   }

   if (sDrcContextState) {
      GfxHeapFreeMEM2(sDrcContextState);
      sDrcContextState = NULL;
   }

   return FALSE;
}

void
WHBGfxShutdown()
{
   if (sGpuTimedOut) {
      GX2ResetGPU(0);
      sGpuTimedOut = FALSE;
   }

   if (sGfxHasForeground) {
      GfxProcCallbackReleased(NULL);
   }

   GX2RSetAllocator(NULL, NULL);
   GX2Shutdown();

   if (sTvContextState) {
      GfxHeapFreeMEM2(sTvContextState);
      sTvContextState = NULL;
   }

   if (sDrcContextState) {
      GfxHeapFreeMEM2(sDrcContextState);
      sDrcContextState = NULL;
   }

   if (sCommandBufferPool) {
      GfxHeapFreeMEM2(sCommandBufferPool);
      sCommandBufferPool = NULL;
   }
}

void
WHBGfxBeginRender()
{
   uint32_t swapCount, flipCount;
   OSTime lastFlip, lastVsync;
   uint32_t waitCount = 0;

   while (1) {
      GX2GetSwapStatus(&swapCount, &flipCount, &lastFlip, &lastVsync);

      if (flipCount >= swapCount) {
         break;
      }

      if (waitCount >= 10) {
         WHBLogPrint("WHBGfxBeginRender wait for swap timed out");
         sGpuTimedOut = TRUE;
         break;
      }

      waitCount++;
      GX2WaitForVsync();
   }
}

void
WHBGfxFinishRender()
{
   GX2SwapScanBuffers();
   GX2Flush();
   GX2DrawDone();
   GX2SetTVEnable(TRUE);
   GX2SetDRCEnable(TRUE);
}

void
WHBGfxClearColor(float r, float g, float b, float a)
{
   if (sDrawingTv) {
      GX2ClearColor(&sTvColourBuffer, r, g, b, a);
      GX2ClearDepthStencilEx(&sTvDepthBuffer, sTvDepthBuffer.depthClear, sTvDepthBuffer.stencilClear, GX2_CLEAR_FLAGS_DEPTH | GX2_CLEAR_FLAGS_STENCIL);
      GX2SetContextState(sTvContextState);
   } else {
      GX2ClearColor(&sDrcColourBuffer, r, g, b, a);
      GX2ClearDepthStencilEx(&sDrcDepthBuffer, sDrcDepthBuffer.depthClear, sDrcDepthBuffer.stencilClear, GX2_CLEAR_FLAGS_DEPTH | GX2_CLEAR_FLAGS_STENCIL);
      GX2SetContextState(sDrcContextState);
   }
}

void
WHBGfxBeginRenderDRC()
{
   GX2SetContextState(sDrcContextState);
   sDrawingTv = FALSE;
}

void
WHBGfxFinishRenderDRC()
{
   GX2CopyColorBufferToScanBuffer(&sDrcColourBuffer, GX2_SCAN_TARGET_DRC);
}

void
WHBGfxBeginRenderTV()
{
   GX2SetContextState(sTvContextState);
   sDrawingTv = TRUE;
}

void
WHBGfxFinishRenderTV()
{
   GX2CopyColorBufferToScanBuffer(&sTvColourBuffer, GX2_SCAN_TARGET_TV);
}

GX2ColorBuffer *
WHBGfxGetTVColourBuffer()
{
   return &sTvColourBuffer;
}

GX2DepthBuffer *
WHBGfxGetTVDepthBuffer()
{
   return &sTvDepthBuffer;
}

GX2ContextState *
WHBGfxGetTVContextState()
{
   return sTvContextState;
}

GX2ColorBuffer *
WHBGfxGetDRCColourBuffer()
{
   return &sDrcColourBuffer;
}

GX2DepthBuffer *
WHBGfxGetDRCDepthBuffer()
{
   return &sDrcDepthBuffer;
}

GX2ContextState *
WHBGfxGetDRCContextState()
{
   return sDrcContextState;
}
