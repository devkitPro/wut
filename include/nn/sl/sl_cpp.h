#pragma once

#include <wut.h>
#include <nn/result.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/mcp.h>

#ifdef __cplusplus

namespace nn {

namespace sl {

typedef enum MediaType {
    NN_SL_MEDIA_TYPE_MLC  = 0x00,
    NN_SL_MEDIA_TYPE_SLC  = 0x01,
    NN_SL_MEDIA_TYPE_ODD  = 0x02,
    NN_SL_MEDIA_TYPE_USB  = 0x03,
    NN_SL_MEDIA_TYPE_HFIO = 0x04,
} MediaType;

typedef struct WUT_PACKED LaunchInfo {
    uint64_t titleId;
    MCPAppType appType;
    MediaType mediaType;
    WUT_UNKNOWN_BYTES(0x800);
} LaunchInfo;

WUT_CHECK_OFFSET(LaunchInfo, 0x00, titleId);
WUT_CHECK_OFFSET(LaunchInfo, 0x08, appType);
WUT_CHECK_OFFSET(LaunchInfo, 0x0C, mediaType);
WUT_CHECK_SIZE(LaunchInfo, 0x810);

typedef enum Region {
    REGION_JPN = 0,
    REGION_USA = 1,
    REGION_EUR = 2
} Region;

void
GetDefaultDatabasePath(char *, int size, uint64_t titleId)
    asm("GetDefaultDatabasePath__Q2_2nn2slFPcUiUL");

nn::Result
Initialize(MEMAllocFromDefaultHeapExFn, MEMFreeToDefaultHeapFn)
    asm("Initialize__Q2_2nn2slFPFUiT1_PvPFPv_v");

nn::Result
Finalize()
    asm("Finalize__Q2_2nn2slFv");

}; //namespace sl

}; //namespace nn

#endif