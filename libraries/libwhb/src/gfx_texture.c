#include "gfx_heap.h"
#include <gfd.h>
#include <gx2r/surface.h>
#include <gx2/texture.h>
#include <whb/log.h>
#include <whb/gfx.h>

GX2Texture *
WHBGfxLoadGFDTexture(uint32_t index,
                     const void *file)
{
   uint32_t headerSize, imageSize;
   GX2Texture *texture = NULL;
   void *image = NULL;

   if (index >= GFDGetTextureCount(file)) {
      WHBLogPrintf("%s: invalid GFD texture index %u", __FUNCTION__, index);
      goto error;
   }

   headerSize = GFDGetTextureHeaderSize(index, file);
   imageSize = GFDGetTextureImageSize(index, file);

   if (!headerSize || !imageSize) {
      goto error;
   }

   texture = (GX2Texture *)GfxHeapAllocMEM2(headerSize, 64);
   if (!texture) {
      WHBLogPrintf("%s: GfxHeapAllocMEM2(0x%X, 64) failed", __FUNCTION__, headerSize);
      goto error;
   }

   if (!GFDGetGX2RTexture(texture, index, file)) {
      goto error;
   }

   return texture;

error:
   if (texture) {
      GX2RDestroySurfaceEx(&texture->surface, 0);
      GfxHeapFreeMEM2(texture);
   }

   return NULL;
}

BOOL
WHBGfxFreeTexture(GX2Texture *texture)
{
   GX2RDestroySurfaceEx(&texture->surface, 0);
   GfxHeapFreeMEM2(texture);
   return TRUE;
}
