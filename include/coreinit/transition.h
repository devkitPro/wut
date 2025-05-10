#pragma once

#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

int
__OSGetSavedAudioFlags();

int
__OSGetTransitionAudioBuffer(void **buffer,
                             uint32_t *size);

void
__OSSetTransitionAudioSize(uint32_t size);

#ifdef __cplusplus
}
#endif
