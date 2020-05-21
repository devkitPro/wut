#pragma once
#include "stream.h"

/**
 * \defgroup h264_decode H264 Decode
 * \ingroup h264
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

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


/**
 * Calculate the amount of memory required for the specified parameters.
 */
H264Error
H264DECMemoryRequirement(int32_t profile,
                         int32_t level,
                         int32_t maxWidth,
                         int32_t maxHeight,
                         uint32_t *outMemoryRequirement);


/**
 * Initialise a H264 decoder in the given memory.
 */
H264Error
H264DECInitParam(int32_t memorySize,
                 void *memory);


/**
 * Set H264 decoder parameter.
 */
H264Error
H264DECSetParam(void *memory,
                H264Parameter parameter,
                void *value);


/**
 * Set the callback which is called when a frame is output from the decoder.
 */
H264Error
H264DECSetParam_FPTR_OUTPUT(void *memory,
                            H264DECFptrOutputFn value);


/**
 * Set whether the decoder should internally buffer frames or call the callback
 * immediately as soon as a frame is emitted.
 */
H264Error
H264DECSetParam_OUTPUT_PER_FRAME(void *memory,
                                 uint32_t value);


/**
 * Set a user memory pointer which is passed to the frame output callback.
 */
H264Error
H264DECSetParam_USER_MEMORY(void *memory,
                            void *value);


/**
 * Check if the provided memory can be used for decoding.
 */
H264Error
H264DECCheckMemSegmentation(void *memory,
                            uint32_t size);


/**
 * Open a H264 decoder.
 */
H264Error
H264DECOpen(void *memory);


/**
 * Prepare for decoding.
 */
H264Error
H264DECBegin(void *memory);


/**
 * Set the bit stream to be read for decoding.
 */
H264Error
H264DECSetBitstream(void *memory,
                    uint8_t *buffer,
                    uint32_t bufferLength,
                    double timestamp);


/**
 * Perform decoding of the bitstream and put the output frame into frameBuffer.
 */
H264Error
H264DECExecute(void *memory,
               void *frameBuffer);


/**
 * Flush any internally buffered frames.
 */
H264Error
H264DECFlush(void *memory);


/**
 * End decoding of the current stream.
 */
H264Error
H264DECEnd(void *memory);


/**
 * Cleanup the decoder.
 */
H264Error
H264DECClose(void *memory);


#ifdef __cplusplus
}
#endif

/** @} */
