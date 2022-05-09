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

typedef struct MICWorkMem MICWorkMem;
typedef struct MICStatus MICStatus;

typedef enum
{
    MIC_ERROR_OK                =  0,
    MIC_ERROR_NOT_OPENED        = -1,
    MIC_ERROR_INVALID_HANDLE    = -2,
    MIC_ERROR_INIT              = -5,
    MIC_ERROR_ALREADY_CLOSED    = -7,
    MIC_ERROR_INVALID_INSTANCE  = -8,
}MICERRORS;

typedef enum {
    MIC_INSTANCE_0 = 0,
    MIC_INSTANCE_1 = 1
}MICInstance;

struct MICWorkMem
{
    /**
     * Maximum amount of samples at a time
     * must be at least 0x2800.
     */
    size_t sampleMaxCount;
    /**
     * A 0x40 aligned buffer to write data into.
     * Has to be of size sampleMaxCount * 2
     */
    void *sampleBuffer;
};
WUT_CHECK_OFFSET(MICWorkMem, 0x00, sampleMaxCount);
WUT_CHECK_OFFSET(MICWorkMem, 0x04, sampleBuffer);
WUT_CHECK_SIZE(MICWorkMem, 0x08);

struct MICStatus
{
    int state;    // 1 << 1 = Open
    int availableData;
    int bufferPos;
};
WUT_CHECK_OFFSET(MICStatus, 0x00, state);
WUT_CHECK_OFFSET(MICStatus, 0x04, availableData);
WUT_CHECK_OFFSET(MICStatus, 0x08, bufferPos);
WUT_CHECK_SIZE(MICStatus, 0x0C);

MICHandle
MICInit(MICInstance inst, int/*unknown can be 0*/, MICWorkMem *, MICError *err);

MICError
MICOpen(MICHandle handle);

MICError
MICGetState(MICHandle handle, int state, uint32_t *outStateVal);

MICError
MICSetState(MICHandle handle, int state, uint32_t stateVal);

MICError
MICGetStatus(MICHandle handle, MICStatus *outStatus);

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