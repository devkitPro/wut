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
   MCP_APP_TYPE_UNKNOWN_0x0800000E     = 0x0800000E,
} MCPAppType;

typedef enum MCPInstallTarget
{
   MCP_INSTALL_TARGET_MLC              = 0,
   MCP_INSTALL_TARGET_USB              = 1,
} MCPInstallTarget;

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
   uint32_t version;
   uint32_t cmdFlags;
   uint64_t default_os_id;
   uint64_t default_title_id;

   struct
   {
      uint32_t enable;
      uint32_t max_size;
   } log;

   struct
   {
      uint32_t enable;
   } standby;

   struct
   {
      uint32_t cache_user_code;
      uint32_t max_file_size;
      uint32_t cache_delay_ms;
   } ramdisk;

   uint32_t simulated_ppc_mem2_size;
   uint32_t dev_mode;
   uint64_t prev_title_id;
   uint64_t prev_os_id;
   uint32_t default_app_type;
   char default_device_type[16];
   uint32_t default_device_index;
   uint32_t fast_relaunch_value;
   uint64_t default_eco_title_id;
};
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x00, version);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x04, cmdFlags);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x08, default_os_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x10, default_title_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x18, log.enable);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x1C, log.max_size);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x20, standby.enable);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x24, ramdisk.cache_user_code);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x28, ramdisk.max_file_size);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x2C, ramdisk.cache_delay_ms);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x30, simulated_ppc_mem2_size);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x34, dev_mode);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x38, prev_title_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x40, prev_os_id);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x48, default_app_type);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x4C, default_device_type);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x5C, default_device_index);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x60, fast_relaunch_value);
WUT_CHECK_OFFSET(MCPSysProdSettings, 0x64, default_eco_title_id);
WUT_CHECK_SIZE(MCPSysProdSettings, 0x6C);

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
