#pragma once
#include <wut.h>

/**
 * \defgroup whb_align Align
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define WHBAlignUp(val, align) ((val + align - 1) & ~(align - 1))

#ifdef __cplusplus
}
#endif

/** @} */
