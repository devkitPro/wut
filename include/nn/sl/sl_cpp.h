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
        char parameter[0x800];
    } LaunchInfo;
    WUT_CHECK_OFFSET(LaunchInfo, 0x00, titleId);
    WUT_CHECK_OFFSET(LaunchInfo, 0x08, appType);
    WUT_CHECK_OFFSET(LaunchInfo, 0x0C, mediaType);
    WUT_CHECK_SIZE(LaunchInfo, 0x810);

    struct WUT_PACKED IconInfo {
        uint8_t data[65580]; // tga
        char name[0x80];
    };
    WUT_CHECK_SIZE(IconInfo, 0x100ac);
    WUT_CHECK_OFFSET(IconInfo, 0, data);
    WUT_CHECK_OFFSET(IconInfo, 0x1002c, name);

    struct WUT_PACKED AccountUUID {
        char uuid[10];
    };
    WUT_CHECK_SIZE(AccountUUID, 10);

    struct DRCImagePaletteColor {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t a;
    };
    WUT_CHECK_SIZE(DRCImagePaletteColor, 4);
    WUT_CHECK_OFFSET(DRCImagePaletteColor, 0, b);
    WUT_CHECK_OFFSET(DRCImagePaletteColor, 1, g);
    WUT_CHECK_OFFSET(DRCImagePaletteColor, 2, r);
    WUT_CHECK_OFFSET(DRCImagePaletteColor, 3, a);

    struct DRCImagePalette {
        DRCImagePaletteColor values[0x100];
    };
    WUT_CHECK_SIZE(DRCImagePalette, 0x400);
    WUT_CHECK_OFFSET(DRCImagePalette, 0, values);

    struct WUT_PACKED TransferableInfo {
        uint8_t numAccounts;
        uint8_t defaultAccountIndex;
        AccountUUID uuids[12];
        WUT_PADDING_BYTES(0x48);
        uint8_t isNetworkAccount[12];
        uint8_t isPasswordCacheEnabled[12];
        uint64_t titleIds[10];
        uint8_t isOnDisc[10];
        uint64_t killerNotificationsTitleId;
        uint32_t serialId;
        WUT_UNKNOWN_BYTES(192);
        struct {
            DRCImagePalette palette;
            uint8_t pixelIndex[206][412]; // index of color in palette
        } accountSceneImage;
        struct {
            DRCImagePalette palette;
            uint8_t pixelIndex[129][1630]; // index of color in palette
        } quickStartScene1;
        struct {
            DRCImagePalette palette;
            uint8_t pixelIndex[85][854]; // index of color in palette
        } quickStartScene2;
        struct {
            DRCImagePalette palette; // this is actually unused. The quick start menu uses the button color palette for the main image as well.
            uint8_t pixel[400][854]; // index of color in (button) palette
        } killerNotificationMain;
        struct {
            DRCImagePalette palette;
            uint8_t pixelIndex[160][487]; // index of color in palette
        } killerNotificationButton;
    };
    WUT_CHECK_SIZE(TransferableInfo, 0xc1934);
    WUT_CHECK_OFFSET(TransferableInfo, 0x00, numAccounts);
    WUT_CHECK_OFFSET(TransferableInfo, 0x01, defaultAccountIndex);
    WUT_CHECK_OFFSET(TransferableInfo, 0x02, uuids);
    WUT_CHECK_OFFSET(TransferableInfo, 0xC2, isNetworkAccount);
    WUT_CHECK_OFFSET(TransferableInfo, 0xCE, isPasswordCacheEnabled);
    WUT_CHECK_OFFSET(TransferableInfo, 0xda, titleIds);
    WUT_CHECK_OFFSET(TransferableInfo, 0x12a, isOnDisc);
    WUT_CHECK_OFFSET(TransferableInfo, 0x134, killerNotificationsTitleId);
    WUT_CHECK_OFFSET(TransferableInfo, 0x13C, serialId);
    WUT_CHECK_OFFSET(TransferableInfo, 0x200, accountSceneImage);
    WUT_CHECK_OFFSET(TransferableInfo, 0x15188, quickStartScene1);
    WUT_CHECK_OFFSET(TransferableInfo, 0x48ae6, quickStartScene2);
    WUT_CHECK_OFFSET(TransferableInfo, 0x5aa74, killerNotificationMain);
    WUT_CHECK_OFFSET(TransferableInfo, 0xae4d4, killerNotificationButton);

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
        MCPAppType titleTypes[50];
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

    struct WUT_PACKED Account {
        char uuid[0x10];
        uint32_t isNetworkAccount;
        uint8_t isPasswordCacheEnabled;
        uint8_t age;
        WUT_PADDING_BYTES(2);
        uint32_t gender;
        uint32_t simpleAddressId;
        uint8_t isMailAddressValidated;
        WUT_PADDING_BYTES(1);
        uint16_t bday_year;
        uint8_t bday_month;
        uint8_t bday_day;
        WUT_PADDING_BYTES(2);
    };
    WUT_CHECK_SIZE(Account, 0x28);
    WUT_CHECK_OFFSET(Account, 0x00, uuid);
    WUT_CHECK_OFFSET(Account, 0x10, isNetworkAccount);
    WUT_CHECK_OFFSET(Account, 0x14, isPasswordCacheEnabled);
    WUT_CHECK_OFFSET(Account, 0x15, age);
    WUT_CHECK_OFFSET(Account, 0x18, gender);
    WUT_CHECK_OFFSET(Account, 0x1C, simpleAddressId);
    WUT_CHECK_OFFSET(Account, 0x20, isMailAddressValidated);
    WUT_CHECK_OFFSET(Account, 0x22, bday_year);
    WUT_CHECK_OFFSET(Account, 0x24, bday_month);
    WUT_CHECK_OFFSET(Account, 0x25, bday_day);

    struct WUT_PACKED AccountInfo {
        uint8_t account_index[12];
        WUT_UNKNOWN_BYTES(4);
        uint32_t num_of_accounts;
        Account accounts[12];
    };
    WUT_CHECK_SIZE(AccountInfo, 0x1f4);
    WUT_CHECK_OFFSET(AccountInfo, 0, account_index);
    WUT_CHECK_OFFSET(AccountInfo, 0x10, num_of_accounts);
    WUT_CHECK_OFFSET(AccountInfo, 0x14, accounts);

    struct WUT_PACKED Setting {
        struct {
            bool enabled;
            bool pushEnabled;
            bool adEnabled;
            bool drcLedEnable;
            uint16_t pushInterval;
            WUT_PADDING_BYTES(2);
            uint32_t pushTimeSlot;
        } caffeine;
        bool pushAutoDelivery;
        WUT_PADDING_BYTES(3);
        uint32_t edmStandbyModeLength;
        uint32_t language;
        uint32_t prodArea;
    };
    WUT_CHECK_SIZE(Setting, 0x1C);
    WUT_CHECK_OFFSET(Setting, 0x0, caffeine.enabled);
    WUT_CHECK_OFFSET(Setting, 0x01, caffeine.pushEnabled);
    WUT_CHECK_OFFSET(Setting, 0x02, caffeine.adEnabled);
    WUT_CHECK_OFFSET(Setting, 0x03, caffeine.drcLedEnable);
    WUT_CHECK_OFFSET(Setting, 0x04, caffeine.pushInterval);
    WUT_CHECK_OFFSET(Setting, 0x08, caffeine.pushTimeSlot);
    WUT_CHECK_OFFSET(Setting, 0x0C, pushAutoDelivery);
    WUT_CHECK_OFFSET(Setting, 0x10, edmStandbyModeLength);
    WUT_CHECK_OFFSET(Setting, 0x14, language);
    WUT_CHECK_OFFSET(Setting, 0x18, prodArea);

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