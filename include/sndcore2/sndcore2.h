#pragma once
#include <wut.h>

/**
 * \defgroup proc_ui_procui ProcUI
 * \ingroup proc_ui
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXProfile AXProfile;
typedef struct AXAuxCallbackData AXAuxCallbackData;
typedef struct AXFinalMixCallbackData AXFinalMixCallbackData;
typedef struct AXVolumeEnvelope AXVolumeEnvelope;
typedef struct AXBuxMix AXBuxMix;
typedef struct AXChannelMix AXChannelMix;
typedef struct AXVoiceOffsets AXVoiceOffsets;
typedef struct AXAdpcmState AXAdpcmState;
typedef struct AXSampleRateConversionState AXSampleRateConversionState;
typedef struct AXRemoteSampleRateConversionState AXRemoteSampleRateConversionState;
typedef struct AXAdpcmLoopData AXAdpcmLoopData;
typedef struct AXLowPassFilter AXLowPassFilter;
typedef struct AXBiquadFilter AXBiquadFilter;
typedef struct AXVoice AXVoice;
typedef struct AXMultiVoice AXMultiVoice;
typedef struct AXDspAdpcmHeader AXDspAdpcmHeader;
typedef struct AXDeviceFinalOutput AXDeviceFinalOutput;
typedef struct AXVoiceMix AXVoiceMix;
typedef struct AXDRCMix AXDRCMix;
typedef struct AXRemoteMix AXRemoteMix;
typedef struct AXInitParams AXInitParams;

typedef union AXRemoteFilter AXRemoteFilter;

TYPED_ENUM(u32, AISampleRate) {
    AI_SAMPLE_RATE_32KHZ = 0,
    AI_SAMPLE_RATE_48KHZ = 1
};

TYPED_ENUM(u32, AIExAddrState) {
    AI_EXADDR_NOT_SET = 0,
    AI_EXADDR_SET     = 1,
    AI_EXADDR_INVALID = 2
};

TYPED_ENUM(u32, AIChannel) {
    AI_CHANNEL_STEREO    = 0,
    AI_CHANNEL_MULTI_PCM = 1,
    AI_CHANNEL_BITSTREAM = 2
};

TYPED_ENUM(s32, AXSyncError) {
    AX_SYNC_ERROR_OK                = 0,
    AX_SYNC_ERROR_IN_USE            = -1,
    AX_SYNC_ERROR_IN_CALLBACK       = -2,
    AX_SYNC_ERROR_NOT_PROTECTED     = -3,
    AX_SYNC_ERROR_TOO_MANY_PROTECTS = -4
};

TYPED_ENUM(u16, AXLoopFlag) {
    AX_LOOP_OFF = 0,
    AX_LOOP_ON  = 1
};

TYPED_ENUM(u32, AXVoiceState) {
    AX_VOICE_STATE_STOP = 0,
    AX_VOICE_STATE_RUN  = 1
};

TYPED_ENUM(u16, AXVoiceType) {
    AX_VOICE_TYPE_NORMAL = 0,
    AX_VOICE_TYPE_STREAM = 1
};

TYPED_ENUM(u16, AXVoiceFormat) {
    AX_VOICE_FORMAT_ADPCM = 0,
    AX_VOICE_FORMAT_PCM16 = 10,
    AX_VOICE_FORMAT_PCM8  = 25
};

TYPED_ENUM(u16, AXVoiceRemoteState) {
    AX_VOICE_REMOTE_OFF = 0,
    AX_VOICE_REMOTE_ON  = 1
};

TYPED_ENUM(u32, AXMixerSelect) {
    AX_MIXER_DSP        = 0,
    AX_MIXER_PPC        = 1,
    AX_MIXER_DSP_OR_PPC = 2
};

TYPED_ENUM(u16, AXFilterType) {
    AX_FILTER_NONE     = 0,
    AX_FILTER_LOW_PASS = 1,
    AX_FILTER_BIQUAD   = 2
};

TYPED_ENUM(u32, AXDeviceMode) {
    AX_DEVICE_MODE_STEREO   = 0,
    AX_DEVICE_MODE_SURROUND = 1,
    AX_DEVICE_MODE_DPL2     = 2,
    AX_DEVICE_MODE_6CHAN    = 3,
    AX_DEVICE_MODE_MONO     = 5
};

TYPED_ENUM(u16, AXCompressorState) {
    AX_COMPRESSOR_OFF = 0,
    AX_COMPRESSOR_ON  = 1
};

TYPED_ENUM(u32, AXSrcType) {
    AX_SRC_TYPE_NONE     = 0,
    AX_SRC_TYPE_LINEAR   = 1,
    AX_SRC_TYPE_4TAP_8K  = 2,
    AX_SRC_TYPE_4TAP_12K = 3,
    AX_SRC_TYPE_4TAP_16K = 4
};

TYPED_ENUM(s32, AXSrcRatioError) {
    AX_SRC_RATIO_ERROR_OK        = 0,
    AX_SRC_RATIO_ERROR_TOO_SMALL = -1,
    AX_SRC_RATIO_ERROR_TOO_LARGE = -2
};

TYPED_ENUM(u32, AXSyncFlag) {
    AX_SYNC_NONE              = 0,
    AX_SYNC_USER_SRCSELECT    = 1 << 0,
    AX_SYNC_USER_MIXCTRL      = 1 << 1,
    AX_SYNC_USER_STATE        = 1 << 2,
    AX_SYNC_USER_TYPE         = 1 << 3,
    AX_SYNC_USER_MIX          = 1 << 4,
    AX_SYNC_USER_ITD          = 1 << 5,
    AX_SYNC_USER_ITDTARGET    = 1 << 6,
    AX_SYNC_USER_DPOP         = 1 << 7,
    AX_SYNC_USER_VE           = 1 << 8,
    AX_SYNC_USER_VEDELTA      = 1 << 9,
    AX_SYNC_USER_ADDR         = 1 << 10,
    AX_SYNC_USER_LOOP         = 1 << 11,
    AX_SYNC_USER_LOOPADDR     = 1 << 12,
    AX_SYNC_USER_ENDADDR      = 1 << 13,
    AX_SYNC_USER_CURRADDR     = 1 << 14,
    AX_SYNC_USER_ADPCM        = 1 << 15,
    AX_SYNC_USER_SRC          = 1 << 16,
    AX_SYNC_USER_SRCRATIO     = 1 << 17,
    AX_SYNC_USER_ADPCMLOOP    = 1 << 18,
    AX_SYNC_USER_LPF          = 1 << 19,
    AX_SYNC_USER_LPF_COEF     = 1 << 20,
    AX_SYNC_USER_BIQUAD       = 1 << 21,
    AX_SYNC_USER_BIQUAD_COEF  = 1 << 22,
    AX_SYNC_USER_REMOTE       = 1 << 23,
    AX_SYNC_USER_RMTMIXCTRL   = 1 << 24,
    AX_SYNC_USER_RMTMIX       = 1 << 25,
    AX_SYNC_USER_RMTDPOP      = 1 << 26,
    AX_SYNC_USER_RMTSRC       = 1 << 27,
    AX_SYNC_USER_RMTIIR       = 1 << 28,
    AX_SYNC_USER_RMTIIR_COEF1 = 1 << 29,
    AX_SYNC_USER_RMTIIR_COEF2 = 1 << 30,
    AX_SYNC_USER_DRCDPOP      = 1 << 31
};

TYPED_ENUM(u32, AXOutputBufferMode) {
    AX_OUTPUT_BUFFER_DOUBLE = 0,
    AX_OUTPUT_BUFFER_TRIPLE = 1
};

TYPED_ENUM(u32, AXVoiceCallbackReason) {
    AX_VOICE_CALLBACK_REASON_NO_RESOURCES  = 1,
    AX_VOICE_CALLBACK_REASON_SEG_VIOLATION = 2
};

TYPED_ENUM(u32, AXBusType) {
    AX_BUS_MAIN = 0,
    AX_BUS_AUXA = 1,
    AX_BUS_AUXB = 2,
    AX_BUS_AUXC = 3,
};

TYPED_ENUM(u32, AXDeviceType) {
    AX_DEVICE_TV  = 0,
    AX_DEVICE_DRC = 1,
    AX_DEVICE_RMT = 2
};

TYPED_ENUM(u32, AXRemoteID) {
    AX_REMOTE_ID0 = 0,
    AX_REMOTE_ID1 = 1,
    AX_REMOTE_ID2 = 2,
    AX_REMOTE_ID3 = 3,
};

TYPED_ENUM(u32, AXDRCID) {
    AX_DRC_ID0 = 0,
    AX_DRC_ID1 = 1,
};

TYPED_ENUM(u32, AXChannelID) {
    AX_CHANNEL_LEFT           = 0,
    AX_CHANNEL_RIGHT          = 1,
    AX_CHANNEL_SURROUND_LEFT  = 2,
    AX_CHANNEL_SURROUND_RIGHT = 3,
    AX_CHANNEL_CENTER         = 4,
    AX_CHANNEL_LFE            = 5
};

TYPED_ENUM(u32, AXTVID) {
    AX_TV_ID0 = 0
};

TYPED_ENUM(u32, AXAuxID) {
    AX_AUX_ID_A = 0,
    AX_AUX_ID_B = 1,
    AX_AUX_ID_C = 2,
};

TYPED_ENUM(u32, AXError) {
    AX_ERROR_NONE                                      = 0,
    AX_ERROR_DEVICE_TYPE                               = -1,
    AX_ERROR_DEVICE_ID                                 = -2,
    AX_ERROR_NULL_MIX_PTR                              = -3,
    AX_ERROR_NULL_VOICE_PTR                            = -4,
    AX_ERROR_AUX_ID                                    = -5,
    AX_ERROR_ILLEGAL_COMPRESSOR_SETTINGS               = -6,
    AX_ERROR_REMIX_ILLEGAL_IN_CHANNELS                 = -7,
    AX_ERROR_REMIX_ILLEGAL_OUT_CHANNELS                = -8,
    AX_ERRIR_REMIX_EXCEED_MAX_ALLOWED                  = -9,
    AX_ERRIR_REMIX_MATRIX_UNINITIALIZED                = -10,
    AX_ERROR_FINAL_OUTSIZE                             = -11,
    AX_ERROR_DRCVS_CONFIG                              = -12,
    AX_ERROR_DRCVS_MODE                                = -13,
    AX_ERROR_FRAMECB_TRY_AGAIN                         = -14,
    AX_ERROR_FRAMECB_MAX_DEPTH_REACHED                 = -15,
    AX_ERROR_FRAMECB_NOT_FOUND                         = -16,
    AX_ERROR_FRAMECB_NULL_FUNC                         = -17,
    AX_ERROR_VOICE_IS_RUNNING                          = -18,
    AX_ERROR_INITIAL_TIME_DELAY_IS_TOO_BIG             = -19,
    AX_ERROR_MULTI_VOICE_COUNT_EXCEEDED                = -20,
    AX_ERROR_MULTI_VOICE_INVALID_CHANNEL_COUNT         = -21,
    AX_ERROR_MULTI_VOICE_UNABLE_TO_ALLOCATE_ALL_VOICES = -22,
    AX_ERROR_MULTI_VOICE_INVALID_FORMAT                = -23,
};

TYPED_ENUM(u32, AXDRCVSModeType) {
    AX_DRC_VS_OFF             = 0,
    AX_DRC_VS_ON_NORMAL       = 1,
    AX_DRC_VS_ON_FRONT_BYPASS = 2
};

TYPED_ENUM(u32, AXDRCVSOutputMode) {
    AX_DRC_VS_OUTPUT_SPEAKER   = 0,
    AX_DRC_VS_OUTPUT_HEADPHONE = 1
};

TYPED_ENUM(u32, AXDRCVSSpeakerPosition) {
    AX_DRC_VS_SPEAKER_POS_WIDE   = 0,
    AX_DRC_VS_SPEAKER_POS_SQUARE = 1
};

TYPED_ENUM(u32, AXDRCVSSurroundLevelGain) {
    AX_DRC_VS_SLEV_1_0   = 0,
    AX_DRC_VS_SLEV_0_707 = 1,
    AX_DRC_VS_SLEV_0_5   = 2
};

TYPED_ENUM(u32, AXDRCVSLCMode) {
    AX_DRC_VS_LC_NOT_USE = 0,
    AX_DRC_VS_LC_USE     = 1,
    AX_DRC_VS_LC_USE_MAX = 2
};

TYPED_ENUM(u32, AXRendererFrequency) {
    AX_RENDERER_32K = 0,
    AX_RENDERER_48K = 1
};

TYPED_ENUM(u32, AXFrameSize) {
    AX_3MS_FRAME = 0
};

TYPED_ENUM(u32, AXPipelineStages) {
    AX_PIPELINE_STAGE_SINGLE = 0,
    AX_PIPELINE_STAGE_FOUR   = 1
};

TYPED_ENUM(u32, AXInitError) {
    AX_INIT_OK                     = 0,
    AX_INIT_ALREADY_INITIALIZED    = -1,
    AX_INIT_INVALID_RENDERER       = -2,
    AX_INIT_INVALID_FRAMESIZE      = -3,
    AX_INIT_INVALID_PIPELINE_STAGE = -4
};

typedef void (*AIDMACallback)         (void);
typedef void (*AXUserCallback)        (void);
typedef void (*AXAuxCallback)         (void* data, void* context);
typedef void (*AXUserAuxCallback)     (s32** data, void* context, AXAuxCallbackData* info);
typedef void (*AXVoiceCallback)       (void* p);
typedef void (*AXExceedCallback)      (u32 cycles);
typedef void (*AXUserFinalMixCallback)(AXFinalMixCallbackData* info);
typedef void (*AXVoiceCallbackEx)     (void* p, u32 context, AXVoiceCallbackReason reason);

struct AXProfile {
    OSTime axFrameStart;
    OSTime axFrameEnd;
    OSTime userAuxProcStart;
    OSTime userAuxProcEnd;
    OSTime userCallbackStart;
    OSTime userCallbackEnd;
    OSTime userFinalMixStart;
    OSTime userFinalMixEnd;
    u32    axNumVoices;
    u32    axNumDspVoices;
    OSTime axDSPStart;
    OSTime axDSPEnd;
    OSTime axPPCStart;
    OSTime axPPCEnd;
    OSTime axPPCPostStart;
    OSTime axPPCPostEnd;
    OSTime istLatency;
    OSTime istPostLatency;
};

struct AXAuxCallbackData {
    u32 numChannels;
    u32 numSamples;
};

struct AXFinalMixCallbackData {
    s32** data;
    u16   numChannelsIn;
    u16   numSamples;
    u16   numDevices;
    u16   numChannelsOut;
};

struct AXVolumeEnvelope {
    u16 currentVolume;
    s16 currentDelta;
};

struct AXBuxMix {
    u16 vol;
    s16 volDelta;
};

struct AXChannelMix {
    AXBuxMix bus[4];
};

struct AXVoiceOffsets {
    AXVoiceFormat format;
    AXLoopFlag    loopFlag;
    u32           loopOffset;
    u32           endOffset;
    u32           currentOffset;
    const void*   samples;
};

struct AXAdpcmState {
    u16 a[8][2];
    u16 gain;
    u16 predScale;
    u16 yn1;
    u16 yn2;
};

struct AXSampleRateConversionState {
    u16 ratioHi;
    u16 ratioLo;
    u16 currentAddressFrac;
    u16 lastSamples[4];
};

struct AXRemoteSampleRateConversionState {
    u16 currentAddressFrac;
    u16 lastSamples[4];
};

struct AXAdpcmLoopData {
    u16 loopPredScale;
    u16 loopYN1;
    u16 loopYN2;
};

struct AXLowPassFilter {
    AXFilterType on;
    u16          yn1;
    u16          a0;
    u16          b0;
};

struct AXBiquadFilter {
    AXFilterType on;
    s16          xn1;
    s16          xn2;
    s16          yn1;
    s16          yn2;
    s16          b0;
    s16          b1;
    s16          b2;
    s16          a1;
    s16          a2;
};

struct AXVoice {
    u32                   index;
    AXVoiceState          state;
    u32                   currentVolume;
    AXMixerSelect         mixerSelect;
    void*                 next;
    void*                 prev;
    void*                 next1;
    u32                   priority;
    AXVoiceCallback       callback;
    u32                   userContext;
    AXSyncFlag            sync;
    u32                   depop;
    void*                 itdBuffer;
    AXVoiceOffsets        offsets;
    AXVoiceCallbackEx     callbackEx;
    AXVoiceCallbackReason cbReason;
    f32                   dspLoadEstimate;
    f32                   ppcLoadEstimate;
};

struct AXMultiVoice {
    BOOL     active;
    u32      count;
    AXVoice* voices[6];
};

struct AXDspAdpcmHeader {
    u32           numSamples;
    u32           numAdpcmNibbles;
    u32           sampleRate;
    AXLoopFlag    loopFlag;
    AXVoiceFormat format;
    u32           loopStartOffset;
    u32           loopEndOffset;
    u32           firstSampleOffset;
    u16           coef[16];
    u16           gain;
    u16           ps;
    u16           yn1;
    u16           yn2;
    u16           lps;
    u16           lyn1;
    u16           lyn2;
    u16           multiChannelCount;
    u16           blockFrameCount;
    u16           pad[9];
};

struct AXDeviceFinalOutput {
    u32 numChannels;
    u32 sampFreq;
    u32 numDevices;
    u32 format;
    u32 length;
};

struct AXVoiceMix {
    u16 vL;
    s16 vDeltaL;
    u16 vR;
    s16 vDeltaR;
    u16 vAuxAL;
    s16 vDeltaAuxAL;
    u16 vAuxAR;
    s16 vDeltaAuxAR;
    u16 vAuxBL;
    s16 vDeltaAuxBL;
    u16 vAuxBR;
    s16 vDeltaAuxBR;
    u16 vAuxCL;
    s16 vDeltaAuxCL;
    u16 vAuxCR;
    s16 vDeltaAuxCR;
    u16 vS;
    s16 vDeltaS;
    u16 vAuxAS;
    s16 vDeltaAuxAS;
    u16 vAuxBS;
    s16 vDeltaAuxBS;
    u16 vAuxCS;
    s16 vDeltaAuxCS;
};

struct AXDRCMix {
    u16 vL;
    s16 vDeltaL;
    u16 vR;
    s16 vDeltaR;
    u16 vAuxL;
    s16 vDeltaAuxL;
    u16 vAuxR;
    s16 vDeltaAuxR;
    u16 vS;
    s16 vDeltaS;
    u16 vAuxS;
    s16 vDeltaAuxS;
};

struct AXRemoteMix {
    u16 vMain0;
    s16 vDeltaMain0;
    u16 vAux0;
    s16 vDeltaAux0;
    u16 vMain1;
    s16 vDeltaMain1;
    u16 vAux1;
    s16 vDeltaAux1;
    u16 vMain2;
    s16 vDeltaMain2;
    u16 vAux2;
    s16 vDeltaAux2;
    u16 vMain3;
    s16 vDeltaMain3;
    u16 vAux3;
    s16 vDeltaAux3;
};

struct AXInitParams {
    AXRendererFrequency rendererFreq;
    AXFrameSize         frameSize;
    AXPipelineStages    pipelineStages;
};

union AXRemoteFilter {
    AXLowPassFilter lpf;
    AXBiquadFilter  biquad;
};

void
AIInit(u8* stack);

void
AIReset(void);

void
AIQuit(void);

BOOL
AICheckInit(void);

AIDMACallback
AIRegisterDMACallback(AIDMACallback callback);

AIDMACallback
AIDRCRegisterDMACallback(AIDMACallback callback);

void
AIInitDMA(u32 startAddr, u32 length);

BOOL
AIGetDMAEnableFlag(void);

void
AIStartDMA(void);

void
AIStopDMA(void);

void
AIGetDMARange(u32 startAddr, u32* addrHi, u32* addrLow);

u32
AIGetDMABytesLeft(void);

u32
AIGetDMAStartAddr(void);

u32
AIDRCGetDMAStartAddr(void);

u32
AIGetDMALength(void);

u32
AIDRCGetDMALength(void);

u32
AIGetAudioFrameCount(void);

AISampleRate
AIGetDSPSampleRate(void);

void
AISetDSPSampleRate(AISampleRate rate);

void
AISetChannel(AIChannel channel, BOOL stuffing);

void
AXInit(void);

void
AXInitEx(AXOutputBufferMode outputBufferMode);

AXInitError
AXInitWithParams(AXInitParams* initParams);

void
AXGetCurrentParams(AXInitParams* currentParams);

BOOL
AXIsInit(void);

void
AXQuit(void);

u32
AXGetLibraryVersion(void);

BOOL
AXIsAudioOutReady(void);

u16
AXGetMasterVolume(void);

void
AXSetMasterVolume(u16 volume);

void
AXInitProfile(AXProfile* profile, u32 maxProfiles);

u32
AXGetProfile(void);

u32
AXGetSwapProfile(AXProfile* profile, u32 maxProfiles);

void
AXSetMaxDspCycles(u32 cycles);

u32
AXGetMaxDspCycles(void);

u32
AXGetDspCycles(void);

void
AXSetPpcLoadLimit(f32 limit);

f32
AXGetPpcLoadLimit(void);

f32
AXGetPpcLoad(void);

void
AXSetDspLoadLimit(f32 limit);

f32
AXGetDspLoadLimit(void);

f32
AXGetDspLoad(void);

u32
AXGetInputSamplesPerFrame(void);

u32
AXGetInputSamplesPerSec(void);

AXMixerSelect
AXSetDefaultMixerSelect(AXMixerSelect mixerSelect);

AXMixerSelect
AXGetDefaultMixerSelect(void);

AXRendererFrequency
AXGetRendererFreq(void);

AXUserCallback
AXRegisterCallback(AXUserCallback callback);

AXUserCallback
AXRegisterDRCCallback(AXUserCallback callback);

AXUserCallback
AXRegisterFrameCallback(AXUserCallback fcb);

void
AXRegisterExceedCallback(AXExceedCallback callback);

AXError
AXRegisterAppFrameCallback(AXUserCallback fcb);

AXError
AXDeregisterAppFrameCallback(AXUserCallback fcb);

AXError
AXRegisterDeviceFinalMixCallback(AXDeviceType device, AXUserFinalMixCallback fcb);

AXError
AXGetDeviceFinalMixCallback(AXDeviceType device, AXUserFinalMixCallback* fcb);

AXError
AXSetDeviceMode(AXDeviceType device, AXDeviceMode mode);

AXError
AXGetDeviceMode(AXDeviceType device, AXDeviceMode* mode);

AXError
AXGetDeviceChannelCount(AXDeviceType device, u32 id, u32* count);

AXError
AXSetDeviceVolume(AXDeviceType device, u32 id, u16 volume);

AXError
AXGetDeviceVolume(AXDeviceType device, u32 id, u16* volume);

AXError
AXSetDeviceRemixMatrix(AXDeviceType device, const u32 numInChns, const u32 numOutChns, const f32* matrixPtr);

AXError
AXGetDeviceRemixMatrix(AXDeviceType device, const u32 numInChns, const u32 numOutChns, const f32** matrixPtr);

AXError
AXGetDeviceUpsampleStage(AXDeviceType device, BOOL* post);

AXError
AXSetDeviceUpsampleStage(AXDeviceType device, BOOL post);

AXError
AXGetDeviceFinalOutput(AXDeviceType device, s16* dataPtr, const u32 size, AXDeviceFinalOutput* axDeviceFinalOutputStruct);

AXError
AXSetDeviceLinearUpsampler(AXDeviceType device, u32 deviceId, BOOL flag);

AXError
AXSetDeviceCompressor(AXDeviceType device, AXCompressorState state);

AXError
AXSetDeviceCompressorTable(AXDeviceType device, u16* table, u16 frames);

void
AXMakeCompressorTable(f32 gain, u16 frames, u16* table);

AXError
AXSetDRCVSMode(AXDRCVSModeType mode);

AXError
AXGetDRCVSMode(AXDRCVSModeType* mode);

AXError
AXSetDRCVSLC(AXDRCVSLCMode mode);

AXError
AXSetDRCVSSpeakerPosition(AXDRCVSOutputMode output, AXDRCVSSpeakerPosition pos);

AXError
AXSetDRCVSSurroundDepth(AXDRCVSOutputMode output, f32 depth);

AXError
AXSetDRCVSDownmixBalance(AXDRCVSOutputMode output, f32 balance);

AXError
AXSetDRCVSSurroundLevelGain(AXDRCVSSurroundLevelGain gain);

AXError
AXSetDRCVSOutputGain(AXDRCVSOutputMode output, f32 gain);

AXError
AXSetDRCVSLimiter(BOOL enable);

AXError
AXSetDRCVSLimiterThreshold(f32 level);

u16
AXGetMasterDRCVolume(void);

void
AXSetMasterDRCVolume(u16 volume);

u16
AXGetDRCAuxReturnVolume(void);

void
AXSetDRCAuxReturnVolume(u16 volume);

void
AXRegisterAuxDRCCallback(AXAuxCallback callback, void* context);

void
AXGetAuxDRCCallback(AXAuxCallback* callback, void** context);

AXError
AXRegisterAuxCallback(AXDeviceType device, u32 id, u32 auxId, AXUserAuxCallback fcb, void* context);

AXError
AXGetAuxCallback(AXDeviceType device, u32 id, u32 auxId, AXUserAuxCallback* fcb, void** context);

AXError
AXSetAuxReturnVolume(AXDeviceType device, u32 id, u32 auxId, u16 volume);

AXError
AXGetAuxReturnVolume(AXDeviceType device, u32 id, u32 auxId, u16* volume);

void
AXRegisterAuxACallback(AXAuxCallback callback, void* context);

void
AXRegisterAuxBCallback(AXAuxCallback callback, void* context);

void
AXRegisterAuxCCallback(AXAuxCallback callback, void* context);

void
AXGetAuxACallback(AXAuxCallback* callback, void** context);

void
AXGetAuxBCallback(AXAuxCallback* callback, void** context);

void
AXGetAuxCCallback(AXAuxCallback* callback, void** context);

u16
AXGetAuxAReturnVolume(void);

u16
AXGetAuxBReturnVolume(void);

u16
AXGetAuxCReturnVolume(void);

void
AXSetAuxAReturnVolume(u16 volume);

void
AXSetAuxBReturnVolume(u16 volume);

void
AXSetAuxCReturnVolume(u16 volume);

void
AXPrepareEfxData(const void* samples, u32 size);

void
AXSetStepMode(u32 mode);

void
AXComputeLpfCoefs(u16 freq, u16* a0, u16* b0);

s32
AXGetAdpcmOutputSize(s32 samples);

s32
AXGetAdpcmWorkSize(s32 samples);

s32
AXGetAdpcmData(const s16* input, s32 samples, s32 rate, s32 loopStart, s32 loopEnd, u8* output, AXDspAdpcmHeader* info, void* work);

s32
AXDecodeAdpcmData(const u8* input, AXDspAdpcmHeader* info, s32 samples, s16* output);

u32
AXGetMaxDspVoices(void);

void
AXSetMaxDspVoices(u32 maxVoices);

u32
AXGetMaxVoices(void);

u32
AXGetNumVoices(void);

u32
AXGetNumDspVoices(void);

u32
AXGetDroppedVoiceCount(void);

AXSyncError
AXUserBegin(void);

AXSyncError
AXUserEnd(void);

BOOL
AXUserIsProtected(void);

AXSyncError
AXVoiceBegin(AXVoice* voice);

AXSyncError
AXVoiceEnd(AXVoice* voice);

BOOL
AXVoiceIsProtected(AXVoice* voice);

AXVoice*
AXAcquireVoice(u32 priority, AXVoiceCallback callback, u32 userContext);

AXVoice*
AXAcquireVoiceEx(u32 priority, AXVoiceCallbackEx callback, u32 userContext);

void
AXFreeVoice(AXVoice* voice);

BOOL
AXIsVoiceRunning(AXVoice* voice);

u32
AXGetVoiceLoopCount(AXVoice* voice);

AXMixerSelect
AXSetVoiceMixerSelect(AXVoice* voice, AXMixerSelect mixerSelect);

AXMixerSelect
AXGetVoiceMixerSelect(AXVoice* voice);

void
AXSetVoicePriority(AXVoice* voice, u32 priority);

void
AXSetVoiceSrcType(AXVoice* voice, AXSrcType type);

void
AXSetVoiceState(AXVoice* voice, AXVoiceState state);

void
AXSetVoiceType(AXVoice* voice, AXVoiceType type);

void
AXSetVoiceVe(AXVoice* voice, const AXVolumeEnvelope* ve);

void
AXSetVoiceVeDelta(AXVoice* voice, s16 delta);

void
AXSetVoiceLoop(AXVoice* voice, AXLoopFlag loop);

void
AXGetVoiceOffsets(AXVoice* voice, AXVoiceOffsets* addr);

void
AXGetVoiceOffsetsEx(AXVoice* voice, AXVoiceOffsets* addr, const void* samples);

void
AXSetVoiceOffsets(AXVoice* voice, const AXVoiceOffsets* addr);

void
AXSetVoiceOffsetsEx(AXVoice* voice, const AXVoiceOffsets* addr, const void* samples);

void
AXSetVoiceLoopOffset(AXVoice* voice, u32 offset);

void
AXSetVoiceLoopOffsetEx(AXVoice* voice, u32 offset, const void* samples);

void
AXSetVoiceEndOffset(AXVoice* voice, u32 offset);

void
AXSetVoiceEndOffsetEx(AXVoice* voice, u32 offset, const void* samples);

void
AXSetVoiceCurrentOffset(AXVoice* voice, u32 offset);

void
AXSetVoiceCurrentOffsetEx(AXVoice* voice, u32 offset, const void* samples);

u32
AXGetVoiceCurrentOffsetEx(AXVoice* voice, const void* samples);

void
AXSetVoiceDRCMix(AXVoice* voice, const AXDRCMix* mix);

void
AXSetVoiceRmtMix(AXVoice* voice, const AXRemoteMix* mix);

void
AXSetVoiceSamplesAddr(AXVoice* voice, const void* samples);

void
AXSetVoiceAdpcm(AXVoice* voice, const AXAdpcmState* adpcm);

void
AXSetVoiceSrc(AXVoice* voice, const AXSampleRateConversionState* src);

AXSrcRatioError
AXSetVoiceSrcRatio(AXVoice* voice, f32 ratio);

void
AXSetVoiceAdpcmLoop(AXVoice* voice, const AXAdpcmLoopData* adpcmloop);

void
AXSetVoiceLpf(AXVoice* voice, const AXLowPassFilter* lpf);

void
AXSetVoiceLpfCoefs(AXVoice* voice, u16 a0, u16 b0);

void
AXSetVoiceBiquad(AXVoice* voice, const AXBiquadFilter* biquad);

void
AXSetVoiceBiquadCoefs(AXVoice* voice, u16 b0, u16 b1, u16 b2, u16 a1, u16 a2);

AXError
AXSetVoiceDeviceMix(AXVoice* voice, AXDeviceType device, u32 id, AXChannelMix* mix);

void
AXSetMaxVoices(u32 num);

void
AXSetVoiceRmtOn(AXVoice* voice, AXVoiceRemoteState on);

void
AXSetVoiceRmtSrc(AXVoice* voice, const AXRemoteSampleRateConversionState* src);

void
AXSetVoiceRmtIIR(AXVoice* voice, const AXRemoteFilter* iir);

void
AXSetVoiceRmtIIRCoefs(AXVoice* voice, AXFilterType type, ...);

s32
AXRmtGetSamplesLeft(void);

s32
AXRmtGetSamples(s32 chan, s16* buffer, s32 samples);

s32
AXRmtAdvancePtr(s32 samples);

u32
AXCheckVoiceOffsets(const AXVoiceOffsets* maddr);

void
AXSetVoiceMix(AXVoice* voice, const AXVoiceMix* mix);

void
AXSetVoiceItdOn(AXVoice* voice);

void
AXSetVoiceItdTarget(AXVoice* voice, u16 lShift, u16 rShift);

AXError
AXSetVoiceInitialTimeDelay(AXVoice* voice, u16 timeDelay);

AXError
AXAcquireMultiVoice(u32 priority, AXVoiceCallbackEx callback, u32 userContext, AXDspAdpcmHeader* mdsp, AXMultiVoice** mvp);

void
AXFreeMultiVoice(AXMultiVoice* multiVoice);

void
AXSetMultiVoicePriority(AXMultiVoice* multiVoice, u32 priority);

void
AXSetMultiVoiceSrcType(AXMultiVoice* multiVoice, AXSrcType type);

void
AXSetMultiVoiceState(AXMultiVoice* multiVoice, AXVoiceState state);

void
AXSetMultiVoiceType(AXMultiVoice* multiVoice, AXVoiceType type);

void
AXSetMultiVoiceVe(AXMultiVoice* multiVoice, const AXVolumeEnvelope* ve);

void
AXSetMultiVoiceVeDelta(AXMultiVoice* multiVoice, s16 delta);

void
AXSetMultiVoiceOffsets(AXMultiVoice* multiVoice, AXVoiceOffsets* offsets);

void
AXSetMultiVoiceLoop(AXMultiVoice* multiVoice, AXLoopFlag loop);

void
AXSetMultiVoiceAdpcm(AXMultiVoice* multiVoice, AXDspAdpcmHeader* data);

void
AXSetMultiVoiceSrc(AXMultiVoice* multiVoice, const AXSampleRateConversionState* src);

AXSrcRatioError
AXSetMultiVoiceSrcRatio(AXMultiVoice* multiVoice, f32 ratio);

void
AXSetMultiVoiceAdpcmLoop(AXMultiVoice* multiVoice, AXAdpcmLoopData* loops);

void
AXSetMultiVoiceLpf(AXMultiVoice* multiVoice, const AXLowPassFilter* lpf);

void
AXSetMultiVoiceLpfCoefs(AXMultiVoice* multiVoice, u16 a0, u16 b0);

void
AXSetMultiVoiceBiquad(AXMultiVoice* multiVoice, const AXBiquadFilter* biquad);

void
AXSetMultiVoiceBiquadCoefs(AXMultiVoice* multiVoice, u16 b0, u16 b1, u16 b2, u16 a1, u16 a2);

AXMixerSelect
AXSetMultiVoiceRenderer(AXMultiVoice* multiVoice, AXMixerSelect mixerSelect);

AXMixerSelect
AXGetMultiVoiceRenderer(AXMultiVoice* multiVoice);

void
AXSetMultiVoiceLoopOffset(AXMultiVoice* multiVoice, u32 offset);

void
AXSetMultiVoiceEndOffset(AXMultiVoice* multiVoice, u32 offset);

void
AXSetMultiVoiceCurrentOffset(AXMultiVoice* multiVoice, u32 offset);

void
AXGetMultiVoiceOffsets(AXMultiVoice* multiVoice, AXVoiceOffsets* addr);

BOOL
AXIsMultiVoiceRunning(AXMultiVoice* multiVoice);

AXError
AXSetMultiVoiceDeviceMix(AXMultiVoice* multiVoice, AXDeviceType device, u32 id, AXBusType bus, u16 vol, s16 volDelta);

AXError
AXGetMultiVoiceReformatBufferSize(u32 format, u32 numChans, u32 numBytes, u32* size);

u32
__AXGetMixMode(void);

#ifdef __cplusplus
}
#endif

/** @} */
