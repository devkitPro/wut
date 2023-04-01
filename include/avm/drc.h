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
WUT_CHECK_SIZE(AVMDrcScanMode, 4);

typedef enum AVMDrcMode
{
   AVM_DRC_MODE_NONE = 0,
   AVM_DRC_MODE_SINGLE = 1,
   AVM_DRC_MODE_DOUBLE = 2,
} AVMDrcMode;
WUT_CHECK_SIZE(AVMDrcMode, 4);

BOOL
AVMGetDRCScanMode(AVMDrcScanMode *outScanMode);

BOOL
AVMGetDRCMode(AVMDrcMode *outMode);

uint32_t
AVMProbeDRCNum(void);

#ifdef __cplusplus
}
#endif

/** @} */
