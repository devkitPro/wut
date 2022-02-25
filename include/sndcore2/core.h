#pragma once
#include <wut.h>
#include <sndcore2/device.h>
#include "result.h"

/**
 * \defgroup sndcore2_core Core
 * \ingroup sndcore2
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXProfile AXProfile;
typedef struct AXInitParams AXInitParams;
typedef struct AXTransitionAudioBuffer AXTransitionAudioBuffer;

typedef void(*AXFrameCallback)(void);

//! A value from enum AX_INIT_RENDERER.
typedef uint32_t AXInitRenderer;

//! A value from enum AX_INIT_PIPELINE.
typedef uint32_t AXInitPipeline;

enum AX_INIT_RENDERER
{
  AX_INIT_RENDERER_32KHZ = 0,
  AX_INIT_RENDERER_48KHZ = 1,
};

enum AX_INIT_PIPELINE
{
  AX_INIT_PIPELINE_SINGLE = 0,
  AX_INIT_PIPELINE_FOUR_STAGE = 1,
};

struct AXProfile
{
  // Unknown
};

struct AXInitParams
{
   AXInitRenderer renderer;
   WUT_UNKNOWN_BYTES(4);
   AXInitPipeline pipeline;
};
WUT_CHECK_OFFSET(AXInitParams, 0x00, renderer);
WUT_CHECK_OFFSET(AXInitParams, 0x08, pipeline);
WUT_CHECK_SIZE(AXInitParams, 0x0C);

struct WUT_PACKED AXTransitionAudioBuffer {
    WUT_UNKNOWN_BYTES(0x8);
    uint32_t length;
    WUT_UNKNOWN_BYTES(0x4);
    void *audioBuffer;
    uint32_t audioBufferLen;
    AXDeviceMode tvMode;
    WUT_UNKNOWN_BYTES(0xC);
    AXDeviceMode drcMode;
    WUT_UNKNOWN_BYTES(0xC);
};
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x08, length);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x10, audioBuffer);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x14, audioBufferLen);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x18, tvMode);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x28, drcMode);
WUT_CHECK_SIZE(AXTransitionAudioBuffer, 0x38);

void
AXInit();

void
AXQuit();

void
AXInitWithParams(AXInitParams *params);

BOOL
AXIsInit();

void
AXInitProfile(AXProfile *profile,
              uint32_t count);

uint32_t
AXGetSwapProfile(AXProfile *profile,
                 uint32_t count);

AXResult
AXSetDefaultMixerSelect(uint32_t unk0);

AXResult
AXRegisterAppFrameCallback(AXFrameCallback callback);

AXResult
AXDeregisterAppFrameCallback(AXFrameCallback callback);

AXFrameCallback
AXRegisterFrameCallback(AXFrameCallback callback);

uint32_t
AXGetInputSamplesPerFrame();

uint32_t
AXGetInputSamplesPerSec();

void
AXStartTransitionAudio();

void
AXSetUpTransitionAudio(AXTransitionAudioBuffer *buffer);

#ifdef __cplusplus
}
#endif

/** @} */
