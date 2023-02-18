#pragma once

#include <wut.h>
#include <nn/acp/device.h>
#include <coreinit/filesystem.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SAVEStatus
{
    SAVE_STATUS_OK = 0,
    SAVE_STATUS_NOT_FOUND = -6,
    SAVE_STATUS_STORAGE_FULL = -12,
} SAVEStatus;
WUT_CHECK_SIZE(SAVEStatus, 4);

SAVEStatus
SAVEInit();

void
SAVEShutdown();

SAVEStatus
SAVEInitSaveDir(uint8_t slotNo);

SAVEStatus
SAVEInitCommonSaveDir();

SAVEStatus
SAVEInitAccountSaveDir(uint8_t slotNo);

void
SAVEInitNoDeleteGroupSaveDir();

SAVEStatus
SAVEUpdateSaveDir();

FSStatus
SAVEChangeDir(FSClient *client,
              FSCmdBlock *block,
              uint8_t slotNo,
              const char *path,
              FSErrorFlag errorMask);

FSStatus
SAVEChangeDirAsync(FSClient *client,
                   FSCmdBlock *block,
                   uint8_t slotNo,
                   const char *path,
                   FSErrorFlag errorMask,
                   FSAsyncData *asyncData);

/**
 * Only FS_MODE_READ_GROUP, FS_MODE_WRITE_GROUP, FS_MODE_READ_OTHER and FS_MODE_WRITE_OTHER can be changed.
 */
FSStatus
SAVEChangeGroupAndOthersMode(FSClient *client,
                             FSCmdBlock *block,
                             uint8_t slotNo,
                             const char *path,
                             FSMode mode,
                             FSErrorFlag errorMask);

/**
 * Only FS_MODE_READ_GROUP, FS_MODE_WRITE_GROUP, FS_MODE_READ_OTHER and FS_MODE_WRITE_OTHER can be changed.
 */
FSStatus
SAVEChangeGroupAndOthersModeAsync(FSClient *client,
                                  FSCmdBlock *block,
                                  uint8_t slotNo,
                                  const char *path,
                                  FSMode mode,
                                  FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);

/**
 * Only FS_MODE_READ_GROUP, FS_MODE_WRITE_GROUP can be changed.
 */
FSStatus
SAVEChangeGroupMode(FSClient *client,
                    FSCmdBlock *block,
                    uint8_t slotNo,
                    const char *path,
                    FSMode mode,
                    FSErrorFlag errorMask);

/**
 * Only FS_MODE_READ_GROUP, FS_MODE_WRITE_GROUP can be changed.
 */
FSStatus
SAVEChangeGroupModeAsync(FSClient *client,
                         FSCmdBlock *block,
                         uint8_t slotNo,
                         const char *path,
                         FSMode mode,
                         FSErrorFlag errorMask,
                         FSAsyncData *asyncData);

SAVEStatus
SAVECheckSaveDirRequiredUpdate(int *unk1,
                               uint64_t *unk2);

FSStatus
SAVEFlushQuota(FSClient *client,
               FSCmdBlock *block,
               uint8_t slotNo,
               FSErrorFlag errorMask);

FSStatus
SAVEFlushQuotaAsync(FSClient *client,
                    FSCmdBlock *block,
                    uint8_t slotNo,
                    FSErrorFlag errorMask,
                    FSAsyncData *asyncData);

FSStatus
SAVEGetFreeSpaceSize(FSClient *client,
                     FSCmdBlock *block,
                     uint8_t slotNo,
                     uint64_t *outSize,
                     FSErrorFlag errorMask);

FSStatus
SAVEGetFreeSpaceSizeAsync(FSClient *client,
                          FSCmdBlock *block,
                          uint8_t slotNo,
                          int64_t *outSize,
                          FSErrorFlag errorMask,
                          FSAsyncData *asyncData);

SAVEStatus
SAVEGetFreeSpaceSizeOfDevice(ACPDeviceType deviceType);

SAVEStatus
SAVEGetNoDeleteGroupSaveDirPath(char *buffer,
                                uint32_t bufferSize);

/*
 * /vol/storage_mlc01/usr/save/system/no_delete/%08x/%08x/%s
 */

SAVEStatus
SAVEGetNoDeleteSaveDataPath(uint64_t titleID,
                            const char *path,
                            char *buffer,
                            uint32_t bufferSize);

/*
 * /vol/storage_mlc01/sys/title/%08x/%08x/content/%s
 */
SAVEStatus
SAVEGetSharedDataTitlePath(uint64_t titleID,
                           const char *path,
                           char *buffer,
                           uint32_t bufferSize);

/*
 * /vol/storage_mlc01/usr/save/%08x/%08x/user/common/%s
 */
SAVEStatus
SAVEGetSharedSaveDataPath(uint64_t titleID,
                          const char *path,
                          char *buffer,
                          uint32_t bufferSize);

FSStatus
SAVEGetStat(FSClient *client,
            FSCmdBlock *block,
            uint8_t slotNo,
            FSStat *stat,
            FSErrorFlag errorMask);

FSStatus
SAVEGetStatAsync(FSClient *client,
                 FSCmdBlock *block,
                 uint8_t slotNo,
                 FSStat *stat,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
SAVEGetStatOtherApplication(FSClient *client,
                            FSCmdBlock *block,
                            uint64_t titleId,
                            const char *path,
                            FSStat *stat,
                            FSErrorFlag errorMask);

FSStatus
SAVEGetStatOtherApplicationAsync(FSClient *client,
                                 FSCmdBlock *block,
                                 uint64_t titleId,
                                 const char *path,
                                 FSStat *stat,
                                 FSErrorFlag errorMask,
                                 FSAsyncData *asyncData);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEGetStatOtherDemoApplication(FSClient *client,
                                FSCmdBlock *block,
                                uint32_t uniqueId,
                                uint8_t slotNo,
                                const char *path,
                                FSStat *stat,
                                FSErrorFlag errorMask);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEGetStatOtherDemoApplicationAsync(FSClient *client,
                                     FSCmdBlock *block,
                                     uint32_t uniqueId,
                                     uint8_t slotNo,
                                     const char *path,
                                     FSStat *stat,
                                     FSErrorFlag errorMask,
                                     FSAsyncData *asyncData);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | varation
 */
FSStatus
SAVEGetStatOtherDemoApplicationVariation(FSClient *client,
                                         FSCmdBlock *block,
                                         uint32_t uniqueId,
                                         uint8_t variation,
                                         uint8_t slotNo,
                                         const char *path,
                                         FSStat *stat,
                                         FSErrorFlag errorMask);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | varation
 */
FSStatus
SAVEGetStatOtherDemoApplicationVariationAsync(FSClient *client,
                                              FSCmdBlock *block,
                                              uint32_t uniqueId,
                                              uint8_t variation,
                                              uint8_t slotNo,
                                              const char *path,
                                              FSStat *stat,
                                              FSErrorFlag errorMask,
                                              FSAsyncData *asyncData);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEGetStatOtherNormalApplication(FSClient *client,
                                  FSCmdBlock *block,
                                  uint32_t uniqueId,
                                  uint8_t slotNo,
                                  const char *path,
                                  FSStat *stat,
                                  FSErrorFlag errorMask);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEGetStatOtherNormalApplicationAsync(FSClient *client,
                                       FSCmdBlock *block,
                                       uint32_t uniqueId,
                                       uint8_t slotNo,
                                       const char *path,
                                       FSStat *stat,
                                       FSErrorFlag errorMask,
                                       FSAsyncData *asyncData);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | varation
 */
FSStatus
SAVEGetStatOtherNormalApplicationVariation(FSClient *client,
                                           FSCmdBlock *block,
                                           uint32_t uniqueId,
                                           uint8_t variation,
                                           uint8_t slotNo,
                                           const char *path,
                                           FSStat *stat,
                                           FSErrorFlag errorMask);

/*
 * Calls SAVEGetStatOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | varation
 */
FSStatus
SAVEGetStatOtherNormalApplicationVariationAsync(FSClient *client,
                                                FSCmdBlock *block,
                                                uint32_t uniqueId,
                                                uint8_t variation,
                                                uint8_t slotNo,
                                                const char *path,
                                                FSStat *stat,
                                                FSErrorFlag errorMask,
                                                FSAsyncData *asyncData);

/**
 *
 * @param slotNo
 * @param metaXmlPath
 * @param metaXmlBuffer must be 0x40 aligned
 * @param metaXmlBufferSize  must be multiple of 0x40, must be >= 0x8000
 * @param iconPath
 * @param iconBuffer must be 0x40 aligned
 * @param iconBufferSize  must be multiple of 0x40, must be >= 0x10040
 * @return
 */
SAVEStatus
SAVEInitSaveDirByAppMeta(uint8_t slotNo,
                         const char *metaXmlPath,
                         uint8_t *metaXmlBuffer,
                         uint32_t metaXmlBufferSize,
                         const char *iconPath,
                         uint8_t *iconBuffer,
                         uint32_t iconBufferSize);

FSStatus
SAVEMakeDir(FSClient *client,
            FSCmdBlock *block,
            uint8_t slotNo,
            const char *path,
            FSErrorFlag errorMask);

FSStatus
SAVEMakeDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 uint8_t slotNo,
                 const char *path,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
SAVEOpenDir(FSClient *client,
            FSCmdBlock *block,
            uint8_t slotNo,
            const char *path,
            FSDirectoryHandle *handle,
            FSErrorFlag errorMask);

FSStatus
SAVEOpenDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 uint8_t slotNo,
                 const char *path,
                 FSDirectoryHandle *handle,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
SAVEOpenDirOtherApplication(FSClient *client,
                            FSCmdBlock *block,
                            uint64_t titleId,
                            uint8_t slotNo,
                            const char *path,
                            FSDirectoryHandle *handle,
                            FSErrorFlag errorMask);

FSStatus
SAVEOpenDirOtherApplicationAsync(FSClient *client,
                                 FSCmdBlock *block,
                                 uint64_t titleId,
                                 uint8_t slotNo,
                                 const char *path,
                                 FSDirectoryHandle *handle,
                                 FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplication
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenDirOtherDemoApplication(FSClient *client,
                                FSCmdBlock *block,
                                uint32_t uniqueId,
                                uint8_t slotNo,
                                const char *path,
                                FSDirectoryHandle *handle,
                                FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenDirOtherDemoApplicationAsync(FSClient *client,
                                     FSCmdBlock *block,
                                     uint32_t uniqueId,
                                     uint8_t slotNo,
                                     const char *path,
                                     FSDirectoryHandle *handle,
                                     FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplication
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenDirOtherDemoApplicationVariation(FSClient *client,
                                         FSCmdBlock *block,
                                         uint32_t uniqueId,
                                         uint8_t variation,
                                         uint8_t slotNo,
                                         const char *path,
                                         FSDirectoryHandle *handle,
                                         FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenDirOtherDemoApplicationVariationAsync(FSClient *client,
                                              FSCmdBlock *block,
                                              uint32_t uniqueId,
                                              uint8_t variation,
                                              uint8_t slotNo,
                                              const char *path,
                                              FSDirectoryHandle *handle,
                                              FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplication
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenDirOtherNormalApplication(FSClient *client,
                                  FSCmdBlock *block,
                                  uint32_t uniqueId,
                                  uint8_t slotNo,
                                  const char *path,
                                  FSDirectoryHandle *handle,
                                  FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenDirOtherNormalApplicationAsync(FSClient *client,
                                       FSCmdBlock *block,
                                       uint32_t uniqueId,
                                       uint8_t slotNo,
                                       const char *path,
                                       FSDirectoryHandle *handle,
                                       FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplication
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenDirOtherNormalApplicationVariation(FSClient *client,
                                           FSCmdBlock *block,
                                           uint32_t uniqueId,
                                           uint8_t variation,
                                           uint8_t slotNo,
                                           const char *path,
                                           FSDirectoryHandle *handle,
                                           FSErrorFlag errorMask);

/*
 * Calls SAVEOpenDirOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenDirOtherNormalApplicationVariationAsync(FSClient *client,
                                                FSCmdBlock *block,
                                                uint32_t uniqueId,
                                                uint8_t variation,
                                                uint8_t slotNo,
                                                const char *path,
                                                FSDirectoryHandle *handle,
                                                FSErrorFlag errorMask);

FSStatus
SAVEOpenFile(FSClient *client,
             FSCmdBlock *block,
             uint8_t slotNo,
             const char *path,
             const char *mode,
             FSFileHandle *handle,
             FSErrorFlag errorMask);

FSStatus
SAVEOpenFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  uint8_t slotNo,
                  const char *path,
                  const char *mode,
                  FSFileHandle *outHandle,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
SAVEOpenFileOtherApplication(FSClient *client,
                             FSCmdBlock *block,
                             uint64_t titleId,
                             uint8_t slotNo,
                             const char *path,
                             const char *mode,
                             FSFileHandle *handle,
                             FSErrorFlag errorMask);

FSStatus
SAVEOpenFileOtherApplicationAsync(FSClient *client,
                                  FSCmdBlock *block,
                                  uint64_t titleId,
                                  uint8_t slotNo,
                                  const char *path,
                                  const char *mode,
                                  FSFileHandle *outHandle,
                                  FSErrorFlag errorMask,
                                  FSAsyncData *asyncData);

/*
 * Calls SAVEOpenFileOtherApplication
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenFileOtherDemoApplication(FSClient *client,
                                 FSCmdBlock *block,
                                 uint32_t uniqueId,
                                 uint8_t slotNo,
                                 const char *path,
                                 const char *mode,
                                 FSFileHandle *handle,
                                 FSErrorFlag errorMask);

/*
 * Calls SAVEOpenFileOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenFileOtherDemoApplicationAsync(FSClient *client,
                                      FSCmdBlock *block,
                                      uint32_t uniqueId,
                                      uint8_t slotNo,
                                      const char *path,
                                      const char *mode,
                                      FSFileHandle *outHandle,
                                      FSErrorFlag errorMask,
                                      FSAsyncData *asyncData);

/*
 * Calls SAVEOpenFileOtherApplication
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenFileOtherDemoApplicationVariation(FSClient *client,
                                          FSCmdBlock *block,
                                          uint32_t uniqueId,
                                          uint8_t variation,
                                          uint8_t slotNo,
                                          const char *path,
                                          const char *mode,
                                          FSFileHandle *handle,
                                          FSErrorFlag errorMask);

/*
 * Calls SAVEOpenFileOtherApplicationAsync
 * titleId: 0x0005000210000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenFileOtherDemoApplicationVariationAsync(FSClient *client,
                                               FSCmdBlock *block,
                                               uint32_t uniqueId,
                                               uint8_t variation,
                                               uint8_t slotNo,
                                               const char *path,
                                               const char *mode,
                                               FSFileHandle *outHandle,
                                               FSErrorFlag errorMask,
                                               FSAsyncData *asyncData);

/*
 * Calls SAVEOpenFileOtherApplication
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenFileOtherNormalApplication(FSClient *client,
                                   FSCmdBlock *block,
                                   uint32_t uniqueId,
                                   uint8_t slotNo,
                                   const char *path,
                                   const char *mode,
                                   FSFileHandle *handle,
                                   FSErrorFlag errorMask);

/*
 * Calls SAVEOpenFileOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8)
 */
FSStatus
SAVEOpenFileOtherNormalApplicationAsync(FSClient *client,
                                        FSCmdBlock *block,
                                        uint32_t uniqueId,
                                        uint8_t slotNo,
                                        const char *path,
                                        const char *mode,
                                        FSFileHandle *outHandle,
                                        FSErrorFlag errorMask,
                                        FSAsyncData *asyncData);

/*
 * Calls SAVEOpenFileOtherApplication
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenFileOtherNormalApplicationVariation(FSClient *client,
                                            FSCmdBlock *block,
                                            uint32_t uniqueId,
                                            uint8_t variation,
                                            uint8_t slotNo,
                                            const char *path,
                                            const char *mode,
                                            FSFileHandle *handle,
                                            FSErrorFlag errorMask);

/*
 * Calls SAVEOpenFileOtherApplicationAsync
 * titleId: 0x0005000010000000L | (uniqueId << 0x8) | variation
 */
FSStatus
SAVEOpenFileOtherNormalApplicationVariationAsync(FSClient *client,
                                                 FSCmdBlock *block,
                                                 uint32_t uniqueId,
                                                 uint8_t variation,
                                                 uint8_t slotNo,
                                                 const char *path,
                                                 const char *mode,
                                                 FSFileHandle *outHandle,
                                                 FSErrorFlag errorMask,
                                                 FSAsyncData *asyncData);

FSStatus
SAVERemove(FSClient *client,
           FSCmdBlock *block,
           uint8_t slotNo,
           const char *path,
           FSErrorFlag errorMask);

FSStatus
SAVERemoveAsync(FSClient *client,
                FSCmdBlock *block,
                uint8_t slotNo,
                const char *path,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
SAVERename(FSClient *client,
           FSCmdBlock *block,
           uint8_t slotNo,
           const char *oldPath,
           const char *newPath,
           FSErrorFlag errorMask);

FSStatus
SAVERenameAsync(FSClient *client,
                FSCmdBlock *block,
                uint8_t slotNo,
                const char *oldPath,
                const char *newPath,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
SAVERollbackQuota(FSClient *client,
                  FSCmdBlock *block,
                  uint8_t slotNo,
                  FSErrorFlag errorMask);

FSStatus
SAVERollbackQuotaAsync(FSClient *client,
                       FSCmdBlock *block,
                       uint8_t slotNo,
                       FSErrorFlag errorMask,
                       FSAsyncData *asyncData);

#ifdef __cplusplus
}
#endif