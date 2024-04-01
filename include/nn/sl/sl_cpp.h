#pragma once

#include <coreinit/mcp.h>
#include <coreinit/memdefaultheap.h>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
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

    void
    GetDefaultDatabasePath(char *, int size)
      asm("GetDefaultDatabasePath__Q2_2nn2slFPcUi");

    void
    GetDefaultKillerNotificationTransferRecordPath(char *, int size, uint64_t titleId, const char*)
      asm("GetDefaultKillerNotificationTransferRecordPath__Q2_2nn2slFPcUiUL");

    void Initialize(MEMAllocFromDefaultHeapExFn, MEMFreeToDefaultHeapFn)
      asm("Initialize__Q2_2nn2slFPFUiT1_PvPFPv_v");

    void
    Finalize()
      asm("Finalize__Q2_2nn2slFv");

    void
    FinalizeForEcoProcess()
      asm("FinalizeForEcoProcess__Q2_2nn2slFv");

    void
    InitializeForEcoProcess(MEMAllocFromDefaultHeapExFn allocFn, MEMFreeToDefaultHeapFn freeFn)
      asm("InitializeForEcoProcess__Q2_2nn2slFPFUiT1_PvPFPv_v");

}; // namespace nn::sl

#endif