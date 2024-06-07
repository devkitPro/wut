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

typedef enum AVMDrcMode
{
   AVM_DRC_MODE_NONE = 0,
   AVM_DRC_MODE_SINGLE = 1,
   AVM_DRC_MODE_DOUBLE = 2,
} AVMDrcMode;

typedef enum AVMDrcSystemAudioMode
{
    AVM_DRC_SYSTEM_AUDIO_MODE_UNKNOWN_0 = 0, // mono?
    AVM_DRC_SYSTEM_AUDIO_MODE_UNKNOWN_1 = 1, // stereo?
    AVM_DRC_SYSTEM_AUDIO_MODE_SURROUND  = 2,
} AVMDrcSystemAudioMode;

/**
 * Uses AVMGetDRCSystemAudioMode internally
 * @param outAudioMode
 * @return 0 on success, -2 on error
 */
int
AVMGetSystemDRCAudioMode(AVMDrcSystemAudioMode *outAudioMode);

BOOL
AVMGetDRCSystemAudioMode(AVMDrcSystemAudioMode *outAudioMode);

uint32_t
AVMGetDRCVertCount();

BOOL
AVMIsDRCFirstFlippDone();

BOOL
AVMGetDRCScanMode(AVMDrcScanMode *outScanMode);

BOOL
AVMGetDRCMode(AVMDrcMode *outMode);

uint32_t
AVMProbeDRCNum(void);

BOOL
AVMSetDRCEnable(BOOL enable);

BOOL
AVMSetDRCGamma(float *gamma);

#ifdef __cplusplus
}
#endif

/** @} */
