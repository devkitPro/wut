#pragma once
#include <wut.h>

/**
 * \defgroup h264_enum Enums
 * \ingroup h264
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum H264Error
{
   H264_ERROR_OK                       = 0,
   H264_ERROR_INVALID_PPS              = 24,
   H264_ERROR_INVALID_SPS              = 26,
   H264_ERROR_INVALID_SLICEHEADER      = 61,
   H264_ERROR_GENERIC                  = 0x1000000,
   H264_ERROR_INVALID_PARAMETER        = 0x1010000,
   H264_ERROR_OUT_OF_MEMORY            = 0x1020000,
   H264_ERROR_INVALID_PROFILE          = 0x1080000,
} H264Error;

typedef enum H264Parameter
{
   H264_PARAMETER_FRAME_POINTER_OUTPUT = 1,
   H264_PARAMETER_OUTPUT_PER_FRAME     = 0x20000002,
   H264_PARAMETER_UNKNOWN_20000010     = 0x20000010,
   H264_PARAMETER_UNKNOWN_20000030     = 0x20000030,
   H264_PARAMETER_UNKNOWN_20000040     = 0x20000040,
   H264_PARAMETER_USER_MEMORY          = 0x70000001,
} H264Parameter;

#ifdef __cplusplus
}
#endif

/** @} */
