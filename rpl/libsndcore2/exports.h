// sndcore2/core.h
EXPORT(AXInit);
EXPORT(AXInitWithParams);
EXPORT(AXIsInit);
EXPORT(AXInitProfile);
EXPORT(AXGetSwapProfile);
EXPORT(AXSetDefaultMixerSelect);
EXPORT(AXRegisterAppFrameCallback);
EXPORT(AXGetInputSamplesPerFrame);
EXPORT(AXGetInputSamplesPerSec);

// sndcore2/device.h
EXPORT(AXGetDeviceMode);
EXPORT(AXGetDeviceFinalMixCallback);
EXPORT(AXRegisterDeviceFinalMixCallback);
EXPORT(AXGetAuxCallback);
EXPORT(AXRegisterAuxCallback);
EXPORT(AXSetDeviceLinearUpsampler);
EXPORT(AXSetDeviceCompressor);
EXPORT(AXSetDeviceUpsampleStage);
EXPORT(AXSetDeviceVolume);

// sndcore2/drcvs.h
EXPORT(AXGetDRCVSMode);
EXPORT(AXSetDRCVSMode);
EXPORT(AXSetDRCVSDownmixBalance);
EXPORT(AXSetDRCVSLC);
EXPORT(AXSetDRCVSLimiter);
EXPORT(AXSetDRCVSLimiterThreshold);
EXPORT(AXSetDRCVSOutputGain);
EXPORT(AXSetDRCVSSpeakerPosition);
EXPORT(AXSetDRCVSSurroundDepth);
EXPORT(AXSetDRCVSSurroundLevelGain);

// sndcore2/voice.h
EXPORT(AXAcquireVoice);
EXPORT(AXAcquireVoiceEx);
EXPORT(AXCheckVoiceOffsets);
EXPORT(AXFreeVoice);
EXPORT(AXGetMaxVoices);
EXPORT(AXGetVoiceCurrentOffsetEx);
EXPORT(AXGetVoiceLoopCount);
EXPORT(AXGetVoiceOffsets);
EXPORT(AXIsVoiceRunning);
EXPORT(AXSetVoiceAdpcm);
EXPORT(AXSetVoiceAdpcmLoop);
EXPORT(AXSetVoiceCurrentOffset);
EXPORT(AXSetVoiceDeviceMix);
EXPORT(AXSetVoiceEndOffset);
EXPORT(AXSetVoiceEndOffsetEx);
EXPORT(AXSetVoiceInitialTimeDelay);
EXPORT(AXSetVoiceLoopOffset);
EXPORT(AXSetVoiceLoopOffsetEx);
EXPORT(AXSetVoiceLoop);
EXPORT(AXSetVoiceOffsets);
EXPORT(AXSetVoicePriority);
EXPORT(AXSetVoiceRmtIIRCoefs);
EXPORT(AXSetVoiceSrc);
EXPORT(AXSetVoiceSrcRatio);
EXPORT(AXSetVoiceSrcType);
EXPORT(AXSetVoiceState);
EXPORT(AXSetVoiceType);
EXPORT(AXSetVoiceVe);
EXPORT(AXSetVoiceVeDelta);
