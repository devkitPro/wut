#pragma once
#include <wut.h>

/**
 * \defgroup gx2_draw Draw
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum GX2PrimitiveMode
{
   GX2_PRIMITIVE_MODE_TRIANGLES         = 4,
   GX2_PRIMITIVE_MODE_TRIANGLE_STRIP    = 6,
   GX2_PRIMITIVE_MODE_QUADS             = 19,
   GX2_PRIMITIVE_MODE_QUAD_STRIP        = 20,
} GX2PrimitiveMode;

typedef enum GX2IndexType
{
   GX2_INDEX_TYPE_U16_LE                = 0,
   GX2_INDEX_TYPE_U32_LE                = 1,
   GX2_INDEX_TYPE_U16                   = 4,
   GX2_INDEX_TYPE_U32                   = 9,
} GX2IndexType;

void
GX2SetAttribBuffer(uint32_t index,
                   uint32_t size,
                   uint32_t stride,
                   void *buffer);

void
GX2DrawEx(GX2PrimitiveMode mode,
          uint32_t numVertices,
          uint32_t offset,
          uint32_t numInstances);

void
GX2DrawIndexedEx(GX2PrimitiveMode mode,
                 uint32_t numVertices,
                 GX2IndexType indexType,
                 void *indices,
                 uint32_t offset,
                 uint32_t numInstances);

void
GX2SetPrimitiveRestartIndex(uint32_t index);

#ifdef __cplusplus
}
#endif

/** @} */
