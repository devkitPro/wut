#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_mcp MCP
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t MCPError;

typedef struct MCPDevice MCPDevice;
typedef struct MCPDeviceList MCPDeviceList;
typedef struct MCPInstallInfo MCPInstallInfo;
typedef struct MCPInstallProgress MCPInstallProgress;
typedef struct MCPInstallTitleInfo MCPInstallTitleInfo;
typedef struct MCPSysProdSettings MCPSysProdSettings;
typedef struct MCPTitleListType MCPTitleListType;

typedef enum MCPAppType
{
   MCP_APP_TYPE_GameUpdate             = 0x0800001B,
   MCP_APP_TYPE_GameDLC                = 0x0800000E,
   MCP_APP_TYPE_Boot1                  = 0x10000009,
   MCP_APP_TYPE_SystemLibraries        = 0x1000000A,
   MCP_APP_TYPE_BluetoothFirmware      = 0x10000012,
   MCP_APP_TYPE_DRHFirmware            = 0x10000013,
   MCP_APP_TYPE_DRCFirmware            = 0x10000014,
   MCP_APP_TYPE_SystemVersion          = 0x10000015,
   MCP_APP_TYPE_DRCLanguage            = 0x1000001A,
   MCP_APP_TYPE_UNKNOWN_0x18000010     = 0x18000010,
   MCP_APP_TYPE_SharedData             = 0x1800001C,
   MCP_APP_TYPE_CertStore              = 0x1800001E,
   MCP_APP_TYPE_UNKNOWN_0x18000023     = 0x18000023,
   MCP_APP_TYPE_UNKNOWN_0x18000029     = 0x18000029,
   MCP_APP_TYPE_UNKNOWN_0x18000030     = 0x18000030,
   MCP_APP_TYPE_UNKNOWN_0x18000031     = 0x18000031,   
   MCP_APP_TYPE_Game                   = 0x80000000,
   MCP_APP_TYPE_GameWii                = 0x8000002E,
   MCP_APP_TYPE_SystemMenu             = 0x90000001,
   MCP_APP_TYPE_SystemUpdater          = 0x9000000B,
   MCP_APP_TYPE_SystemApps             = 0x90000020,
   MCP_APP_TYPE_UNKNOWN_0x90000021     = 0x90000021,
   MCP_APP_TYPE_SystemSettings         = 0x90000022,
   MCP_APP_TYPE_UNKNOWN_0x9000002F     = 0x9000002F,
   MCP_APP_TYPE_eManual                = 0xD0000003,
   MCP_APP_TYPE_HomeMenu               = 0xD0000004,
   MCP_APP_TYPE_ErrorDisplay           = 0xD0000005,
   MCP_APP_TYPE_Browser                = 0xD0000006,
   MCP_APP_TYPE_UNKNOWN_0xD000000D     = 0xD000000D,
   MCP_APP_TYPE_MiiVerse               = 0xD0000016,
   MCP_APP_TYPE_eShop                  = 0xD0000017,
   MCP_APP_TYPE_FriendList             = 0xD0000018,
   MCP_APP_TYPE_DownloadManagement     = 0xD0000019,
   MCP_APP_TYPE_UNKNOWN_0xD000002C     = 0xD000002C,
   MCP_APP_TYPE_AmiiboSettings         = 0xD0000033,
} MCPAppType;

typedef enum MCPInstallTarget
{
   MCP_INSTALL_TARGET_MLC              = 0,
   MCP_INSTALL_TARGET_USB              = 1,
} MCPInstallTarget;

typedef enum MCPRegion
{
   MCP_REGION_JAPAN                    = 0x01,
   MCP_REGION_USA                      = 0x02,
   MCP_REGION_EUROPE                   = 0x04,
   MCP_REGION_CHINA                    = 0x10,
   MCP_REGION_KOREA                    = 0x20,
   MCP_REGION_TAIWAN                   = 0x40,
} MCPRegion;

struct MCPDevice
{
   char name[0x31B];
};
WUT_CHECK_SIZE(MCPDevice, 0x31B);

struct MCPDeviceList
{
   MCPDevice devices[32];
};
WUT_CHECK_SIZE(MCPDeviceList, 0x6360);

struct MCPInstallInfo
{
   WUT_UNKNOWN_BYTES(0x27F);
};
WUT_CHECK_SIZE(MCPInstallInfo, 0x27F);

struct WUT_PACKED MCPInstallProgress
{
   uint32_t inProgress;
   uint64_t tid;
   uint64_t sizeTotal;
   uint64_t sizeProgress;
   uint32_t contentsTotal;
   uint32_t contentsProgress;
};
WUT_CHECK_OFFSET(MCPInstallProgress, 0x00, inProgress);
WUT_CHECK_OFFSET(MCPInstallProgress, 0x04, tid);
WUT_CHECK_OFFSET(MCPInstallProgress, 0x0C, sizeTotal);
WUT_CHECK_OFFSET(MCPInstallProgress, 0x14, sizeProgress);
WUT_CHECK_OFFSET(MCPInstallProgress, 0x1C, contentsTotal);
WUT_CHECK_OFFSET(MCPInstallProgress, 0x20, contentsProgress);
WUT_CHECK_SIZE(MCPInstallProgress, 0x24);

struct MCPInstallTitleInfo
{
   WUT_UNKNOWN_BYTES(0x27F);
};
WUT_CHECK_SIZE(MCPInstallTitleInfo, 0x27F);

struct WUT_PACKED MCPSysProdSettings
{
   MCPRegion product_area;
   uint16_t eeprom_version;
   WUT_PADDING_BYTES(2);
   MCPRegion game_region;
   WUT_UNKNOWN_BYTES(4);
   char ntsc_pal[5];

   //! 5ghz_country_code in xml
   char wifi_5ghz_country_code[4];

   //! 5ghz_country_code_revision in xml
   uint8_t wifi_5ghz_country_code_revision;

   char code_id[8];
   char serial_id[12];
   WUT_UNKNOWN_BYTES(4);
   char model_number[16];
   uint32_t version;
};
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x00, product_area);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x04, eeprom_version);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x08, game_region);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x10, ntsc_pal);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x15, wifi_5ghz_country_code);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x19, wifi_5ghz_country_code_revision);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x1A, code_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x22, serial_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x32, model_number);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x42, version);
WUT_CHECK_SIZE(MCPSysProdSettings, 0x46);

struct WUT_PACKED MCPTitleListType
{
   uint64_t titleId;
   WUT_UNKNOWN_BYTES(4);
   char path[56];
   MCPAppType appType;
   WUT_UNKNOWN_BYTES(0x54 - 0x48);
   uint8_t device;
   WUT_UNKNOWN_BYTES(1);
   char indexedDevice[10];
   uint8_t unk0x60;
};
WUT_CHECK_OFFSET(MCPTitleListType, 0x00, titleId);
WUT_CHECK_OFFSET(MCPTitleListType, 0x0C, path);
WUT_CHECK_OFFSET(MCPTitleListType, 0x44, appType);
WUT_CHECK_OFFSET(MCPTitleListType, 0x54, device);
WUT_CHECK_OFFSET(MCPTitleListType, 0x56, indexedDevice);
WUT_CHECK_OFFSET(MCPTitleListType, 0x60, unk0x60);
WUT_CHECK_SIZE(MCPTitleListType, 0x61);

MCPError
MCP_Open();

MCPError
MCP_Close(int handle);

MCPError
MCP_DeviceList(int handle,
               int *numDevices,
               MCPDeviceList *outDevices,
               uint32_t outBufferSize);

MCPError
MCP_FullDeviceList(int handle,
                   int *numDevices,
                   MCPDeviceList *outDevices,
                   uint32_t outBufferSize);

MCPError
MCP_GetOwnTitleInfo(int32_t handle,
                    MCPTitleListType *titleInfo);

MCPError
MCP_GetSysProdSettings(int32_t handle,
                       MCPSysProdSettings *settings);

MCPError
MCP_GetTitleId(int32_t handle,
               uint64_t *outTitleId);

MCPError
MCP_GetTitleInfo(int32_t handle,
                 uint64_t titleId,
                 MCPTitleListType *titleInfo);

MCPError
MCP_InstallSetTargetDevice(int handle,
                           MCPInstallTarget device);

MCPError
MCP_InstallGetTargetDevice(int handle,
                           MCPInstallTarget *deviceOut);

MCPError
MCP_InstallSetTargetUsb(int handle,
                        int usb);

MCPError
MCP_InstallGetInfo(int handle,
                   char *path,
                   MCPInstallInfo *out);

MCPError
MCP_InstallTitleAsync(int handle,
                      char *path,
                      MCPInstallTitleInfo *out);

MCPError
MCP_InstallGetProgress(int handle,
                       MCPInstallProgress *installProgressOut);

MCPError
MCP_InstallTitleAbort(int handle);

MCPError
MCP_TitleCount(int32_t handle);

MCPError
MCP_TitleList(int32_t handle,
              uint32_t *outTitleCount,
              MCPTitleListType *titleList,
              uint32_t titleListSizeBytes);

MCPError
MCP_TitleListByAppType(int32_t handle,
                       MCPAppType appType,
                       uint32_t *outTitleCount,
                       MCPTitleListType *titleList,
                       uint32_t titleListSizeBytes);

MCPError
MCP_TitleListByUniqueId(int32_t handle,
                        uint32_t uniqueId,
                        uint32_t *outTitleCount,
                        MCPTitleListType *titleList,
                        uint32_t titleListSizeBytes);

MCPError
MCP_TitleListByUniqueIdAndIndexedDeviceAndAppType(int32_t handle,
                                                  uint32_t uniqueId,
                                                  const char *indexedDevice,
                                                  uint8_t unk0x60,
                                                  MCPAppType appType,
                                                  uint32_t *outTitleCount,
                                                  MCPTitleListType *titleList,
                                                  uint32_t titleListSizeBytes);

MCPError
MCP_UninstallTitleAsync(int handle,
                        char *path,
                        MCPInstallTitleInfo *out);

#ifdef __cplusplus
}
#endif

/** @} */
