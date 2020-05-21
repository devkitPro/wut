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

//! h264 library errors.
typedef enum H264Error
{
   //! No errors.
   H264_ERROR_OK                       = 0,
   //! Invalid picture parameter set.
   H264_ERROR_INVALID_PPS              = 24,
   //! Invalid sequence parameter set. 
   H264_ERROR_INVALID_SPS              = 26,
   //! Invalid slice header.
   H264_ERROR_INVALID_SLICEHEADER      = 61,
   //! Generic h264 error.
   H264_ERROR_GENERIC                  = 0x1000000,
   //! Invalid parameters passed.
   H264_ERROR_INVALID_PARAMETER        = 0x1010000,
   //! The amount of memory provided to the h264 library
   //! is insufficient.
   H264_ERROR_OUT_OF_MEMORY            = 0x1020000,
   //! Invalid h264 stream profile. Only the baseline (66),
   //! main (77) and high (100) profiles are allowed.
   H264_ERROR_INVALID_PROFILE          = 0x1080000,
} H264Error;

//! h264 decoder parameters for H264DECSetParam.
typedef enum H264Parameter
{
   //! Set the callback which is called when a frame is output from the decoder.
   H264_PARAMETER_FRAME_POINTER_OUTPUT = 1,
   //! Set whether the decoder should internally buffer frames or call the callback
   //! immediately as soon as a frame is emitted.
   H264_PARAMETER_OUTPUT_PER_FRAME     = 0x20000002,
   H264_PARAMETER_UNKNOWN_20000010     = 0x20000010,
   H264_PARAMETER_UNKNOWN_20000030     = 0x20000030,
   H264_PARAMETER_UNKNOWN_20000040     = 0x20000040,
   //! Set a user memory pointer which is passed to the frame output callback.
   H264_PARAMETER_USER_MEMORY          = 0x70000001,
} H264Parameter;

#ifdef __cplusplus
}
#endif

/** @} */
