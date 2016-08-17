/****************************************************************************
 * Copyright (C) 2015
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#pragma once
#include <wut.h>

/**
 * \defgroup sndcore2_sndcore2 SndCore2
 * \ingroup sndcore2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
AXInitWithParams(u32 * params);

void
AXInit(void);

void
AXQuit(void);

u32
AXGetInputSamplesPerSec(void);

s32
AXVoiceBegin(void *v);

s32
AXVoiceEnd(void *v);

void
AXSetVoiceType(void *v, u16 type);

void
AXSetVoiceOffsets(void *v, const void *buf);

void
AXSetVoiceSrcType(void *v, u32 type);

void
AXSetVoiceVe(void *v, const void *vol);

s32
AXSetVoiceDeviceMix(void *v, s32 device, u32 id, void *mix);

void
AXSetVoiceState(void *v, u16 state);

void
AXSetVoiceSrc(void *v, const void *src);

s32
AXSetVoiceSrcRatio(void *v, f32 ratio);

void *
AXAcquireVoice(u32 prio, void * callback, u32 arg);

void
AXFreeVoice(void *v);

void
AXRegisterFrameCallback(void * callback);

u32
AXGetVoiceLoopCount(void * v);

void
AXSetVoiceEndOffset(void * v, u32 offset);

void
AXSetVoiceLoopOffset(void * v, u32 offset);

#ifdef __cplusplus
}
#endif

/** @} */
