#pragma once

#include <wut.h>
#include <coreinit/filesystem.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TEMPTargetPreference
{
    TEMP_PREF_DEFAULT = 0,
    TEMP_PREF_INTERNAL_STORAGE = 1,
} TEMPTargetPreference;
WUT_CHECK_SIZE(TEMPTargetPreference, 4);

typedef uint64_t TEMPDirId;

FSStatus
TEMPInit();

void
TEMPShutdown();

FSStatus
TEMPCreateAndInitTempDir(uint32_t size,
                         TEMPTargetPreference pref,
                         TEMPDirId *outDir);

FSStatus
TEMPShutdownTempDir(TEMPDirId tempId);

FSStatus
TEMPGetDirGlobalPath(TEMPDirId dirId,
                     char *path,
                     uint32_t pathLen);

FSStatus
TEMPGetDirPath(TEMPDirId dirId,
               char *path,
               uint32_t pathLen);

FSStatus
TEMPChangeDir(FSClient *client,
              FSCmdBlock *block,
              TEMPDirId dirId,
              const char *path,
              FSErrorFlag errorMask);

FSStatus
TEMPChangeDirAsync(FSClient *client,
                   FSCmdBlock *block,
                   TEMPDirId dirId,
                   const char *path,
                   FSErrorFlag errorMask,
                   FSAsyncData *asyncData);

/*
 * Only FS_MODE_READ_OTHER can be set
 */
FSStatus
TEMPChangeOthersMode(FSClient *client,
                     FSCmdBlock *block,
                     TEMPDirId dirId,
                     const char *path,
                     FSMode mode,
                     FSErrorFlag errorMask);

/*
 * Only FS_MODE_READ_OTHER can be set
 */
FSStatus
TEMPChangeOthersModeAsync(FSClient *client,
                          FSCmdBlock *block,
                          TEMPDirId dirId,
                          const char *path,
                          FSMode mode,
                          FSErrorFlag errorMask,
                          FSAsyncData *asyncData);

FSStatus
TEMPGetFreeSpaceSize(FSClient *client,
                     FSCmdBlock *block,
                     TEMPDirId dirId,
                     uint64_t *outSize,
                     FSErrorFlag errorMask);

FSStatus
TEMPGetFreeSpaceSizeAsync(FSClient *client,
                          FSCmdBlock *block,
                          TEMPDirId dirId,
                          uint64_t *outSize,
                          FSErrorFlag errorMask,
                          FSAsyncData *asyncData);


FSStatus
TEMPGetStat(FSClient *client,
            FSCmdBlock *block,
            TEMPDirId dirId,
            const char *path,
            FSStat *stat,
            FSErrorFlag errorMask);

FSStatus
TEMPGetStatAsync(FSClient *client,
                 FSCmdBlock *block,
                 TEMPDirId dirId,
                 const char *path,
                 FSStat *stat,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
TEMPMakeDir(FSClient *client,
            FSCmdBlock *block,
            TEMPDirId dirId,
            const char *path,
            FSErrorFlag errorMask);

FSStatus
TEMPMakeDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 TEMPDirId dirId,
                 const char *path,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);


FSStatus
TEMPOpenDir(FSClient *client,
            FSCmdBlock *block,
            TEMPDirId dirId,
            const char *path,
            FSDirectoryHandle *handle,
            FSErrorFlag errorMask);

FSStatus
TEMPOpenDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 TEMPDirId dirId,
                 const char *path,
                 FSDirectoryHandle *handle,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
TEMPOpenFile(FSClient *client,
             FSCmdBlock *block,
             TEMPDirId dirId,
             const char *path,
             const char *mode,
             FSFileHandle *handle,
             FSErrorFlag errorMask);

FSStatus
TEMPOpenFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  TEMPDirId dirId,
                  const char *path,
                  const char *mode,
                  FSFileHandle *outHandle,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
TEMPRemove(FSClient *client,
           FSCmdBlock *block,
           TEMPDirId dirId,
           const char *path,
           FSErrorFlag errorMask);

FSStatus
TEMPRemoveAsync(FSClient *client,
                FSCmdBlock *block,
                TEMPDirId dirId,
                const char *path,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
TEMPRename(FSClient *client,
           FSCmdBlock *block,
           TEMPDirId dirId,
           const char *oldPath,
           const char *newPath,
           FSErrorFlag errorMask);

FSStatus
TEMPRenameAsync(FSClient *client,
                FSCmdBlock *block,
                TEMPDirId dirId,
                const char *oldPath,
                const char *newPath,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
TEMPMountTempDir(TEMPDirId dirId);

FSStatus
TEMPUnmountTempDir(TEMPDirId dirId);

/**
 * Always returns FS_STATUS_UNSUPPORTED_CMD
 */
FSStatus
TEMPOpenNewFile();

/**
 * Always returns FS_STATUS_UNSUPPORTED_CMD
 */
FSStatus
TEMPOpenNewFileAsync();

#ifdef __cplusplus
}
#endif

/** @} */