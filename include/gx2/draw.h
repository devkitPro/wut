#pragma once
#include <wut.h>
#include "enum.h"

/**
 * \defgroup gx2_draw Draw
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2DispatchParams GX2DispatchParams;

struct GX2DispatchParams
{
   uint32_t numGroupsX;
   uint32_t numGroupsY;
   uint32_t numGroupsZ;
   uint32_t _padding;
};
WUT_CHECK_OFFSET(GX2DispatchParams, 0x00, numGroupsX);
WUT_CHECK_OFFSET(GX2DispatchParams, 0x04, numGroupsY);
WUT_CHECK_OFFSET(GX2DispatchParams, 0x08, numGroupsZ);
WUT_CHECK_OFFSET(GX2DispatchParams, 0x0C, _padding);
WUT_CHECK_SIZE(GX2DispatchParams, 0x10);

void
GX2SetAttribBuffer(uint32_t index,
                   uint32_t size,
                   uint32_t stride,
                   const void *buffer);

void
GX2DrawEx(GX2PrimitiveMode mode,
          uint32_t count,
          uint32_t offset,
          uint32_t numInstances);

void
GX2DrawEx2(GX2PrimitiveMode mode,
           uint32_t count,
           uint32_t offset,
           uint32_t numInstances,
           uint32_t baseInstance);

void
GX2DrawIndexedEx(GX2PrimitiveMode mode,
                 uint32_t count,
                 GX2IndexType indexType,
                 const void *indices,
                 uint32_t offset,
                 uint32_t numInstances);

void
GX2DrawIndexedEx2(GX2PrimitiveMode mode,
                  uint32_t count,
                  GX2IndexType indexType,
                  const void *indices,
                  uint32_t offset,
                  uint32_t numInstances,
                  uint32_t baseInstance);

void
GX2DrawIndexedImmediateEx(GX2PrimitiveMode mode,
                          uint32_t count,
                          GX2IndexType indexType,
                          const void *indices,
                          uint32_t offset,
                          uint32_t numInstances);

void
GX2SetPrimitiveRestartIndex(uint32_t index);

void
GX2DispatchCompute(GX2DispatchParams *dispatchParams);

#ifdef __cplusplus
}
#endif

/** @} */
