#pragma once
#include <wut.h>
#include "threadqueue.h"

/**
 * \defgroup coreinit_fs Filesystem
 * \ingroup coreinit
 *
 *  First call FSInit to initialise the file system library, then call
 *  FSAddClient to initialise your FSClient structure, then you need to use
 *  FSInitCmdBlock to initialise an FSCmdBlock structure for each command you
 *  want to run in parallel. You must ensure the previous filesystem command
 *  has been completed before reusing the same FSCmdBlock, you do not need to
 *  reinitialise an FSCmdBlock before reusing it.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t FSDirectoryHandle;
typedef uint32_t FSFileHandle;
typedef uint32_t FSPriority;

typedef struct FSAsyncData FSAsyncData;
typedef struct FSCmdBlock FSCmdBlock;
typedef struct FSClient FSClient;
typedef struct FSDirectoryEntry FSDirectoryEntry;
typedef struct FSStat FSStat;
typedef struct FSStateChangeInfo FSStateChangeInfo;

typedef enum FSStatus
{
   FS_STATUS_OK                  = 0,
   FS_STATUS_CANCELLED           = -1,
   FS_STATUS_END                 = -2,
   FS_STATUS_MAX                 = -3,
   FS_STATUS_ALREADY_OPEN        = -4,
   FS_STATUS_EXISTS              = -5,
   FS_STATUS_NOT_FOUND           = -6,
   FS_STATUS_NOT_FILE            = -7,
   FS_STATUS_NOT_DIR             = -8,
   FS_STATUS_ACCESS_ERROR        = -9,
   FS_STATUS_PERMISSION_ERROR    = -10,
   FS_STATUS_FILE_TOO_BIG        = -11,
   FS_STATUS_STORAGE_FULL        = -12,
   FS_STATUS_JOURNAL_FULL        = -13,
   FS_STATUS_UNSUPPORTED_CMD     = -14,
   FS_STATUS_MEDIA_NOT_READY     = -15,
   FS_STATUS_MEDIA_ERROR         = -17,
   FS_STATUS_CORRUPTED           = -18,
   FS_STATUS_FATAL_ERROR         = -0x400,
} FSStatus;

typedef enum FSError
{
   FS_ERROR_NOT_INIT = -0x30001,
} FSError;

typedef enum FSStatFlags
{
   FS_STAT_DIRECTORY = 0x80000000,
} FSStatFlags;

typedef enum FSVolumeState
{
   FS_VOLUME_STATE_INIT = 0,
} FSVolumeState;

typedef void(*FSAsyncCallback)(FSClient *, FSCmdBlock *, FSStatus, uint32_t);

struct FSClient
{
   UNKNOWN(0x1700);
};
CHECK_SIZE(FSClient, 0x1700);

struct FSCmdBlock
{
   UNKNOWN(0xA80);
};
CHECK_SIZE(FSCmdBlock, 0xA80);

struct FSStat
{
   FSStatFlags flags;
   UNKNOWN(0xC);
   uint32_t size;
   UNKNOWN(0x50);
};
CHECK_OFFSET(FSStat, 0x00, flags);
CHECK_OFFSET(FSStat, 0x10, size);
CHECK_SIZE(FSStat, 0x64);

struct FSStateChangeInfo
{
   UNKNOWN(0xC);
};
CHECK_SIZE(FSStateChangeInfo, 0xC);

struct FSAsyncData
{
   uint32_t callback;
   uint32_t param;
   UNKNOWN(4);
};
CHECK_OFFSET(FSAsyncData, 0x0, callback);
CHECK_OFFSET(FSAsyncData, 0x4, param);
CHECK_SIZE(FSAsyncData, 0xC);

struct FSDirectoryEntry
{
   FSStat info;
   char name[256];
};
CHECK_OFFSET(FSDirectoryEntry, 0x64, name);
CHECK_SIZE(FSDirectoryEntry, 0x164);

void
FSInit();

void
FSShutdown();

FSStatus
FSAddClient(FSClient *client,
            uint32_t flags);

FSStatus
FSDelClient(FSClient *client,
            uint32_t flags);

uint32_t
FSGetClientNum();

void
FSInitCmdBlock(FSCmdBlock *block);

FSStatus
FSSetCmdPriority(FSCmdBlock *block,
                 FSPriority priority);

void
FSSetStateChangeNotification(FSClient *client,
                             FSStateChangeInfo *info);

FSStatus
FSGetCwd(FSClient *client,
         FSCmdBlock *block,
         char *buffer,
         uint32_t bufferSize,
         uint32_t flags);

FSStatus
FSChangeDir(FSClient *client,
            FSCmdBlock *block,
            const char *path,
            uint32_t flags);

FSStatus
FSChangeDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 const char *path,
                 uint32_t flags,
                 FSAsyncData *asyncData);

FSStatus
FSGetStat(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSStat *stat,
          uint32_t flags);

FSStatus
FSGetStatAsync(FSClient *client,
               FSCmdBlock *block,
               const char *path,
               FSStat *stat,
               uint32_t flags,
               FSAsyncData *asyncData);

FSStatus
FSOpenFile(FSClient *client,
           FSCmdBlock *block,
           const char *path,
           const char *mode,
           FSFileHandle *handle,
           uint32_t flags);

FSStatus
FSOpenFileAsync(FSClient *client,
                FSCmdBlock *block,
                const char *path,
                const char *mode,
                FSFileHandle *outHandle,
                uint32_t flags,
                FSAsyncData *asyncData);

FSStatus
FSCloseFile(FSClient *client,
            FSCmdBlock *block,
            FSFileHandle handle,
            uint32_t flags);

FSStatus
FSCloseFileAsync(FSClient *client,
                 FSCmdBlock *block,
                 FSFileHandle handle,
                 uint32_t flags,
                 FSAsyncData *asyncData);

FSStatus
FSOpenDir(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSDirectoryHandle *handle,
          uint32_t flags);

FSStatus
FSOpenDirAsync(FSClient *client,
               FSCmdBlock *block,
               const char *path,
               FSDirectoryHandle *handle,
               uint32_t flags,
               FSAsyncData *asyncData);

FSStatus
FSReadDir(FSClient *client,
          FSCmdBlock *block,
          FSDirectoryHandle handle,
          FSDirectoryEntry *entry,
          uint32_t flags);

FSStatus
FSReadDirAsync(FSClient *client,
               FSCmdBlock *block,
               FSDirectoryHandle handle,
               FSDirectoryEntry *entry,
               uint32_t flags,
               FSAsyncData *asyncData);

FSStatus
FSCloseDir(FSClient *client,
           FSCmdBlock *block,
           FSDirectoryHandle handle,
           uint32_t flags);

FSStatus
FSCloseDirAsync(FSClient *client,
                FSCmdBlock *block,
                FSDirectoryHandle handle,
                uint32_t flags,
                FSAsyncData *asyncData);

FSStatus
FSGetStatFile(FSClient *client,
              FSCmdBlock *block,
              FSFileHandle handle,
              FSStat *stat,
              uint32_t flags);

FSStatus
FSGetStatFileAsync(FSClient *client,
                   FSCmdBlock *block,
                   FSFileHandle handle,
                   FSStat *stat,
                   uint32_t flags,
                   FSAsyncData *asyncData);

FSStatus
FSReadFile(FSClient *client,
           FSCmdBlock *block,
           uint8_t *buffer,
           uint32_t size,
           uint32_t count,
           FSFileHandle handle,
           uint32_t unk1,
           uint32_t flags);

FSStatus
FSReadFileAsync(FSClient *client,
                FSCmdBlock *block,
                uint8_t *buffer,
                uint32_t size,
                uint32_t count,
                FSFileHandle handle,
                uint32_t unk1,
                uint32_t flags,
                FSAsyncData *asyncData);

FSStatus
FSReadFileWithPos(FSClient *client,
                  FSCmdBlock *block,
                  uint8_t *buffer,
                  uint32_t size,
                  uint32_t count,
                  uint32_t pos,
                  FSFileHandle handle,
                  uint32_t unk1,
                  uint32_t flags);

FSStatus
FSReadFileWithPosAsync(FSClient *client,
                       FSCmdBlock *block,
                       uint8_t *buffer,
                       uint32_t size,
                       uint32_t count,
                       uint32_t pos,
                       FSFileHandle handle,
                       uint32_t unk1,
                       uint32_t flags,
                       FSAsyncData *asyncData);

FSStatus
FSGetPosFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle fileHandle,
             uint32_t *pos,
             uint32_t flags);

FSStatus
FSGetPosFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle fileHandle,
                  uint32_t *pos,
                  uint32_t flags,
                  FSAsyncData *asyncData);

FSStatus
FSSetPosFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle handle,
             uint32_t pos,
             uint32_t flags);

FSStatus
FSSetPosFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle handle,
                  uint32_t pos,
                  uint32_t flags,
                  FSAsyncData *asyncData);

FSVolumeState
FSGetVolumeState(FSClient *client);

FSError
FSGetLastErrorCodeForViewer(FSClient *client);

#ifdef __cplusplus
}
#endif

/** @} */
