#pragma once

#include <coreinit/mcp.h>
#include <coreinit/memdefaultheap.h>
#include <nn/result.h>
#include <nn/sl/KillerNotification.h>
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

    struct WUT_PACKED IconInfo {
        uint8_t data[65580];
        char name[0x80];
    };
    WUT_CHECK_SIZE(IconInfo, 0x100ac);
    WUT_CHECK_OFFSET(IconInfo, 0, data);
    WUT_CHECK_OFFSET(IconInfo, 0x1002c, name);

    typedef struct WUT_PACKED TransferableInfo {
        WUT_UNKNOWN_BYTES(0xc1934);
    } TransferableInfo;
    WUT_CHECK_SIZE(TransferableInfo, 0xc1934);

    struct WUT_PACKED TitleInfo {
        uint64_t titleId;
        MCPAppType appType;
        MediaType mediaType;
        WUT_UNKNOWN_BYTES(0x10);
    };
    WUT_CHECK_SIZE(TitleInfo, 0x20);
    WUT_CHECK_OFFSET(TitleInfo, 0x00, titleId);
    WUT_CHECK_OFFSET(TitleInfo, 0x08, appType);
    WUT_CHECK_OFFSET(TitleInfo, 0x0C, mediaType);

    struct WUT_PACKED TitleMetaInfo {
        bool isPreOrder;
        WUT_PADDING_BYTES(3);
    };
    WUT_CHECK_SIZE(TitleMetaInfo, 0x4);
    WUT_CHECK_OFFSET(TitleMetaInfo, 0x00, isPreOrder);

    struct WUT_PACKED WhiteList {
        uint32_t titleTypes[50];
        uint32_t titleTypeCount;
        WUT_PADDING_BYTES(4);
        uint64_t titleIds[50];
        uint32_t titleIdCount;
    };
    WUT_CHECK_SIZE(WhiteList, 0x264);
    WUT_CHECK_OFFSET(WhiteList, 0x00, titleTypes);
    WUT_CHECK_OFFSET(WhiteList, 0xC8, titleTypeCount);
    WUT_CHECK_OFFSET(WhiteList, 0xD0, titleIds);
    WUT_CHECK_OFFSET(WhiteList, 0x260, titleIdCount);

    struct WUT_PACKED AccountInfo {
        WUT_UNKNOWN_BYTES(0x1f4);
    };
    WUT_CHECK_SIZE(AccountInfo, 0x1f4);

    struct WUT_PACKED Setting {
        WUT_UNKNOWN_BYTES(0x1C);
    };
    WUT_CHECK_SIZE(Setting, 0x1C);

    struct KillerNotificationTransferRecord {
        WUT_UNKNOWN_BYTES(0x18);
    };
    WUT_CHECK_SIZE(KillerNotificationTransferRecord, 0x18);

    typedef enum Region {
        REGION_JPN = 0,
        REGION_USA = 1,
        REGION_EUR = 2
    } Region;

    enum TransferMode {
        TRANSFER_MODE_UNKWN_1 = 1,
        TRANSFER_MODE_UNKWN_2 = 2,
        TRANSFER_MODE_UNKWN_3 = 3,
    };

    enum Language {
        Japanese           = 0,
        English            = 1,
        French             = 2,
        German             = 3,
        Italian            = 4,
        Spanish            = 5,
        SimplifiedChinese  = 6,
        Korean             = 7,
        Dutch              = 8,
        Portuguese         = 9,
        Russian            = 10,
        TraditionalChinese = 11,
    };
    enum SeekOrigin {
        SeekSet = 0
    };


    void
    GetDefaultDatabasePath(char *, int size, uint64_t titleId) asm("GetDefaultDatabasePath__Q2_2nn2slFPcUiUL");

    void
    GetDefaultDatabasePath(char *, int size) asm("GetDefaultDatabasePath__Q2_2nn2slFPcUi");

    void
    GetDefaultKillerNotificationTransferRecordPath(char *, int size, uint64_t titleId, const char *) asm("GetDefaultKillerNotificationTransferRecordPath__Q2_2nn2slFPcUiUL");

    void Initialize(MEMAllocFromDefaultHeapExFn, MEMFreeToDefaultHeapFn) asm("Initialize__Q2_2nn2slFPFUiT1_PvPFPv_v");

    void
    Finalize() asm("Finalize__Q2_2nn2slFv");

    void
    FinalizeForEcoProcess() asm("FinalizeForEcoProcess__Q2_2nn2slFv");

    void
    InitializeForEcoProcess(MEMAllocFromDefaultHeapExFn allocFn, MEMFreeToDefaultHeapFn freeFn) asm("InitializeForEcoProcess__Q2_2nn2slFPFUiT1_PvPFPv_v");

}; // namespace nn::sl

#endif