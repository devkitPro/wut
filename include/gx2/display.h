#pragma once
#include <wut.h>
#include "surface.h"

/**
 * \defgroup gx2_display Display
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GX2TVRenderMode
{
   GX2_TV_RENDER_MODE_STANDARD_480P    = 1,
   GX2_TV_RENDER_MODE_WIDE_480P        = 2,
   GX2_TV_RENDER_MODE_WIDE_720P        = 3,
   GX2_TV_RENDER_MODE_WIDE_1080P       = 5,
} GX2TVRenderMode;

typedef enum GX2DrcRenderMode
{
   GX2_DRC_RENDER_MODE_DISABLED        = 0,
   GX2_DRC_RENDER_MODE_SINGLE          = 1,
} GX2DrcRenderMode;

typedef enum GX2BufferingMode
{
   GX2_BUFFERING_MODE_SINGLE           = 1,
   GX2_BUFFERING_MODE_DOUBLE           = 2,
   GX2_BUFFERING_MODE_TRIPLE           = 3,
} GX2BufferingMode;

typedef enum GX2TVScanMode
{
  GX2_TV_SCAN_MODE_NONE                = 0,
} GX2TVScanMode;

void
GX2SetTVEnable(BOOL enable);

void
GX2SetDRCEnable(BOOL enable);

void
GX2CalcTVSize(GX2TVRenderMode tvRenderMode,
              GX2SurfaceFormat surfaceFormat,
              GX2BufferingMode bufferingMode,
              uint32_t *size,
              uint32_t *unkOut);

void
GX2CalcDRCSize(GX2DrcRenderMode drcRenderMode,
               GX2SurfaceFormat surfaceFormat,
               GX2BufferingMode bufferingMode,
               uint32_t *size,
               uint32_t *unkOut);

void
GX2SetTVBuffer(void *buffer,
               uint32_t size,
               GX2TVRenderMode tvRenderMode,
               GX2SurfaceFormat surfaceFormat,
               GX2BufferingMode bufferingMode);

void
GX2SetDRCBuffer(void *buffer,
                uint32_t size,
                GX2DrcRenderMode drcRenderMode,
                GX2SurfaceFormat surfaceFormat,
                GX2BufferingMode bufferingMode);

void
GX2SetTVScale(uint32_t x,
              uint32_t y);

void
GX2SetDRCScale(uint32_t x,
               uint32_t y);

GX2TVScanMode
GX2GetSystemTVScanMode();

GX2DrcRenderMode
GX2GetSystemDRCMode();

#ifdef __cplusplus
}
#endif

/** @} */
