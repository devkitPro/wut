#pragma once
#include <wut.h>

/**
 * \defgroup avm_drc DRC
 * \ingroup avm
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AVMDrcScanMode
{
   AVM_DRC_SCAN_MODE_UNKNOWN_0 = 0,
   AVM_DRC_SCAN_MODE_UNKNOWN_1 = 1,
   AVM_DRC_SCAN_MODE_UNKNOWN_3 = 3,
   AVM_DRC_SCAN_MODE_UNKNOWN_255 = 255,
} AVMDrcScanMode;

BOOL
AVMGetDRCScanMode(AVMDrcScanMode *outScanMode);

#ifdef __cplusplus
}
#endif

/** @} */
