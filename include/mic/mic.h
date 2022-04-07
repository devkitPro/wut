#pragma once
#include "wut.h"

/**
 * \defgroup mic Microphone
 * \ingroup mic
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int MICHandle;
typedef int MICError;

typedef struct mic_setup_t mic_setup_t;

typedef struct mic_status_t mic_status_t;

enum mic_error
{
    MIC_ERROR_OK                =  0,
    MIC_ERROR_NOT_OPENED        = -1,
    MIC_ERROR_INVALID_HANDLE    = -2,
    MIC_ERROR_INIT              = -5,
    MIC_ERROR_ALREADY_CLOSED    = -7,
    MIC_ERROR_INVALID_INSTANCE  = -8,
};

struct mic_setup_t
{
    /**
     * Maximum amount of samples at a time
     * must be at least 0x2800.
     */
    int sampleMaxCount;
    /**
     * A 0x40 aligned buffer to write data into.
     * Has to be of size sampleMaxCount * 2
     */
    void *sampleBuffer;
};
WUT_CHECK_OFFSET(mic_setup_t, 0x00, sampleMaxCount);
WUT_CHECK_OFFSET(mic_setup_t, 0x04, sampleBuffer);
WUT_CHECK_SIZE(mic_setup_t, 0x08);

struct mic_status_t
{
    int unk_0x00; // some kind of bitmask, possibly thread affinity
    int unk_0x04; // buffer Pos
    int unk_0x08; // dataAvailableToConsume
};
WUT_CHECK_OFFSET(mic_status_t, 0x00, unk_0x00);
WUT_CHECK_OFFSET(mic_status_t, 0x04, unk_0x04);
WUT_CHECK_OFFSET(mic_status_t, 0x08, unk_0x08);
WUT_CHECK_SIZE(mic_status_t, 0x0C);

MICHandle
MICInit(int mic_inst_t, int/*unknown*/, mic_setup_t*, MICError *err);

MICError
MICOpen(MICHandle handle);

MICError
MICGetState(MICHandle handle, int /*channel? 0-7*/, uint32_t *outState);

MICError
MICSetState(MICHandle handle, int /*channel? 0-7*/, uint32_t state);

MICError
MICGetStatus(MICHandle handle, mic_status_t *outStatus);

MICError
MICSetDataConsumed(MICHandle handle, int dataAmountConsumed);

MICError
MICClose(MICHandle handle);

MICError
MICUninit(MICHandle handle);

#ifdef __cplusplus
}
#endif

/** @} */