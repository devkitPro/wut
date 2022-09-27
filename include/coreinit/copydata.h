#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_copydata CopyData
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
__OSClearCopyData();

BOOL
__OSAppendCopyData(const void *data,
                   uint32_t size);

void *
__OSGetCopyDataPtr();

uint32_t
__OSGetCopyDataSize();

BOOL
__OSResizeCopyData(uint32_t size);

#ifdef __cplusplus
}
#endif

/** @} */
