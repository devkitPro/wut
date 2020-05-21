#pragma once

/**
 * \defgroup h264_stream H264 Stream
 * \ingroup h264
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct H264DecodedVuiParameters H264DecodedVuiParameters;
typedef struct H264DecodeResult H264DecodeResult;
typedef struct H264DecodeOutput H264DecodeOutput;

typedef void (*H264DECFptrOutputFn)(H264DecodeOutput *output);

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

struct WUT_PACKED H264DecodedVuiParameters
{
   uint8_t aspect_ratio_info_present_flag;
   uint8_t aspect_ratio_idc;
   int16_t sar_width;
   int16_t sar_height;
   uint8_t overscan_info_present_flag;
   uint8_t overscan_appropriate_flag;
   uint8_t video_signal_type_present_flag;
   uint8_t video_format;
   uint8_t video_full_range_flag;
   uint8_t colour_description_present_flag;
   uint8_t colour_primaries;
   uint8_t transfer_characteristics;
   uint8_t matrix_coefficients;
   uint8_t chroma_loc_info_present_flag;
   uint8_t chroma_sample_loc_type_top_field;
   uint8_t chroma_sample_loc_type_bottom_field;
   uint8_t timing_info_present_flag;
   WUT_PADDING_BYTES(1);
   uint32_t num_units_in_tick;
   uint32_t time_scale;
   uint8_t fixed_frame_rate_flag;
   uint8_t nal_hrd_parameters_present_flag;
   uint8_t vcl_hrd_parameters_present_flag;
   uint8_t low_delay_hrd_flag;
   uint8_t pic_struct_present_flag;
   uint8_t bitstream_restriction_flag;
   uint8_t motion_vectors_over_pic_boundaries_flag;
   WUT_PADDING_BYTES(1);
   int16_t max_bytes_per_pic_denom;
   int16_t max_bits_per_mb_denom;
   int16_t log2_max_mv_length_horizontal;
   int16_t log2_max_mv_length_vertical;
   int16_t num_reorder_frames;
   int16_t max_dec_frame_buffering;
};
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x00, aspect_ratio_info_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x01, aspect_ratio_idc);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x02, sar_width);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x04, sar_height);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x06, overscan_info_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x07, overscan_appropriate_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x08, video_signal_type_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x09, video_format);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0A, video_full_range_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0B, colour_description_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0C, colour_primaries);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0D, transfer_characteristics);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0E, matrix_coefficients);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x0F, chroma_loc_info_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x10, chroma_sample_loc_type_top_field);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x11, chroma_sample_loc_type_bottom_field);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x12, timing_info_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x14, num_units_in_tick);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x18, time_scale);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x1C, fixed_frame_rate_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x1D, nal_hrd_parameters_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x1E, vcl_hrd_parameters_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x1F, low_delay_hrd_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x20, pic_struct_present_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x21, bitstream_restriction_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x22, motion_vectors_over_pic_boundaries_flag);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x24, max_bytes_per_pic_denom);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x26, max_bits_per_mb_denom);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x28, log2_max_mv_length_horizontal);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x2A, log2_max_mv_length_vertical);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x2C, num_reorder_frames);
WUT_CHECK_OFFSET(H264DecodedVuiParameters, 0x2E, max_dec_frame_buffering);
WUT_CHECK_SIZE(H264DecodedVuiParameters, 0x30);

struct WUT_PACKED H264DecodeResult
{
   int32_t status;
   WUT_PADDING_BYTES(4);
   double timestamp;
   int32_t width;
   int32_t height;
   int32_t nextLine;
   uint8_t cropEnableFlag;
   WUT_PADDING_BYTES(3);
   int32_t cropTop;
   int32_t cropBottom;
   int32_t cropLeft;
   int32_t cropRight;
   uint8_t panScanEnableFlag;
   WUT_PADDING_BYTES(3);
   int32_t panScanTop;
   int32_t panScanBottom;
   int32_t panScanLeft;
   int32_t panScanRight;
   void *framebuffer;
   uint8_t vui_parameters_present_flag;
   WUT_PADDING_BYTES(3);
   H264DecodedVuiParameters *vui_parameters;
   WUT_UNKNOWN_BYTES(40);
};
WUT_CHECK_OFFSET(H264DecodeResult, 0x00, status);
WUT_CHECK_OFFSET(H264DecodeResult, 0x08, timestamp);
WUT_CHECK_OFFSET(H264DecodeResult, 0x10, width);
WUT_CHECK_OFFSET(H264DecodeResult, 0x14, height);
WUT_CHECK_OFFSET(H264DecodeResult, 0x18, nextLine);
WUT_CHECK_OFFSET(H264DecodeResult, 0x1C, cropEnableFlag);
WUT_CHECK_OFFSET(H264DecodeResult, 0x20, cropTop);
WUT_CHECK_OFFSET(H264DecodeResult, 0x24, cropBottom);
WUT_CHECK_OFFSET(H264DecodeResult, 0x28, cropLeft);
WUT_CHECK_OFFSET(H264DecodeResult, 0x2C, cropRight);
WUT_CHECK_OFFSET(H264DecodeResult, 0x30, panScanEnableFlag);
WUT_CHECK_OFFSET(H264DecodeResult, 0x34, panScanTop);
WUT_CHECK_OFFSET(H264DecodeResult, 0x38, panScanBottom);
WUT_CHECK_OFFSET(H264DecodeResult, 0x3C, panScanLeft);
WUT_CHECK_OFFSET(H264DecodeResult, 0x40, panScanRight);
WUT_CHECK_OFFSET(H264DecodeResult, 0x44, framebuffer);
WUT_CHECK_OFFSET(H264DecodeResult, 0x48, vui_parameters_present_flag);
WUT_CHECK_OFFSET(H264DecodeResult, 0x4C, vui_parameters);
WUT_CHECK_SIZE(H264DecodeResult, 0x78);

struct WUT_PACKED H264DecodeOutput
{
   //! Number of frames output
   int32_t frameCount;
   
   //! Frames
   H264DecodeResult **decodeResults;
   
   //! User memory pointer passed into SetParam
   void *userMemory;
};
WUT_CHECK_OFFSET(H264DecodeOutput, 0x00, frameCount);
WUT_CHECK_OFFSET(H264DecodeOutput, 0x04, decodeResults);
WUT_CHECK_OFFSET(H264DecodeOutput, 0x08, userMemory);
WUT_CHECK_SIZE(H264DecodeOutput, 0x0C);


/**
 * Check that the stream contains sufficient data to decode an entire frame.
 */
H264Error
H264DECCheckDecunitLength(void *memory,
                          const uint8_t *buffer,
                          int32_t bufferLength,
                          int32_t offset,
                          int32_t *outLength);


/**
 * Check if the next NALU can be skipped without breaking decoding.
 */
H264Error
H264DECCheckSkipableFrame(const uint8_t *buffer,
                          int32_t bufferLength,
                          BOOL *outSkippable);


/**
 * Find the first SPS in the stream.
 */
H264Error
H264DECFindDecstartpoint(const uint8_t *buffer,
                         int32_t bufferLength,
                         int32_t *outOffset);


/**
 * Find the first "IDR point" in the stream.
 *
 * An IDR point is either:
 *  - If an SPS or PPS header is found before the IDR and there are no non-IDR
 *    inbetween the SPS/PPS and IDR then return the first of the SPS/PPS.
 *  - The first found IDR.
 */
int32_t
H264DECFindIdrpoint(const uint8_t *buffer,
                    int32_t bufferLength,
                    int32_t *outOffset);


/**
 * Parse the H264 stream and read the width & height from the first found SPS.
 */
H264Error
H264DECGetImageSize(const uint8_t *buffer,
                    int32_t bufferLength,
                    int32_t offset,
                    int32_t *outWidth,
                    int32_t *outHeight);


#ifdef __cplusplus
}
#endif

/** @} */
