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
typedef struct AXTransitionAudioBufferDevice AXTransitionAudioBufferDevice;

typedef void (*AXFrameCallback)(void);

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
   AX_INIT_PIPELINE_SINGLE     = 0,
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

struct WUT_PACKED AXTransitionAudioBufferDevice
{
   AXDeviceMode mode;
   float unk1;
   uint32_t unk2;
   BOOL enabled;
};
WUT_CHECK_SIZE(AXTransitionAudioBufferDevice, 0x10);

struct WUT_PACKED AXTransitionAudioBuffer
{
   uint32_t unk1;
   uint32_t unk2;
   uint32_t length;
   uint32_t loopPoint;
   void *audioBuffer;
   uint32_t audioBufferLen;
   AXTransitionAudioBufferDevice tv;
   AXTransitionAudioBufferDevice drc;
};
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x00, unk1);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x04, unk2);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x08, length);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x0C, loopPoint);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x10, audioBuffer);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x14, audioBufferLen);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x18, tv.mode);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x24, tv.enabled);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x28, drc.mode);
WUT_CHECK_OFFSET(AXTransitionAudioBuffer, 0x34, drc.enabled);
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
