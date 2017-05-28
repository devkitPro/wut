#include "gfx_heap.h"
#include <gfd.h>
#include <gx2r/surface.h>
#include <gx2/texture.h>
#include <whb/gfx.h>

GX2Texture *
WHBGfxLoadGFDTexture(uint32_t index,
                     const void *file)
{
   uint32_t headerSize, imageSize;
   GX2Texture *texture = NULL;
   void *image = NULL;

   if (index >= GFDGetTextureCount(file)) {
      goto error;
   }

   headerSize = GFDGetTextureHeaderSize(index, file);
   imageSize = GFDGetTextureImageSize(index, file);

   if (!headerSize || !imageSize) {
      goto error;
   }

   texture = (GX2Texture *)GfxHeapAllocMEM2(headerSize, 64);
   if (!texture) {
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
