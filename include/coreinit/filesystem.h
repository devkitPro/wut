#pragma once
#include <wut.h>

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
   FS_STATUS_OK                     = 0,
   FS_STATUS_CANCELLED              = -1,
   FS_STATUS_END                    = -2,
   FS_STATUS_MAX                    = -3,
   FS_STATUS_ALREADY_OPEN           = -4,
   FS_STATUS_EXISTS                 = -5,
   FS_STATUS_NOT_FOUND              = -6,
   FS_STATUS_NOT_FILE               = -7,
   FS_STATUS_NOT_DIR                = -8,
   FS_STATUS_ACCESS_ERROR           = -9,
   FS_STATUS_PERMISSION_ERROR       = -10,
   FS_STATUS_FILE_TOO_BIG           = -11,
   FS_STATUS_STORAGE_FULL           = -12,
   FS_STATUS_JOURNAL_FULL           = -13,
   FS_STATUS_UNSUPPORTED_CMD        = -14,
   FS_STATUS_MEDIA_NOT_READY        = -15,
   FS_STATUS_MEDIA_ERROR            = -17,
   FS_STATUS_CORRUPTED              = -18,
   FS_STATUS_FATAL_ERROR            = -0x400,
} FSStatus;

typedef enum FSError
{
   FS_ERROR_NOT_INIT                = -0x30001,
   FS_ERROR_BUSY                    = -0x30002,
   FS_ERROR_CANCELLED               = -0x30003,
   FS_ERROR_END_OF_DIR              = -0x30004,
   FS_ERROR_END_OF_FILE             = -0x30005,
   FS_ERROR_MAX_MOUNT_POINTS        = -0x30010,
   FS_ERROR_MAX_VOLUMES             = -0x30011,
   FS_ERROR_MAX_CLIENTS             = -0x30012,
   FS_ERROR_MAX_FILES               = -0x30013,
   FS_ERROR_MAX_DIRS                = -0x30014,
   FS_ERROR_ALREADY_OPEN            = -0x30015,
   FS_ERROR_ALREADY_EXISTS          = -0x30016,
   FS_ERROR_NOT_FOUND               = -0x30017,
   FS_ERROR_NOT_EMPTY               = -0x30018,
   FS_ERROR_ACCESS_ERROR            = -0x30019,
   FS_ERROR_PERMISSION_ERROR        = -0x3001A,
   FS_ERROR_DATA_CORRUPTED          = -0x3001B,
   FS_ERROR_STORAGE_FULL            = -0x3001C,
   FS_ERROR_JOURNAL_FULL            = -0x3001D,
   FS_ERROR_UNAVAILABLE_COMMAND     = -0x3001F,
   FS_ERROR_UNSUPPORTED_COMMAND     = -0x30020,
   FS_ERROR_INVALID_PARAM           = -0x30021,
   FS_ERROR_INVALID_PATH            = -0x30022,
   FS_ERROR_INVALID_BUFFER          = -0x30023,
   FS_ERROR_INVALID_ALIGNMENT       = -0x30024,
   FS_ERROR_INVALID_CLIENTHANDLE    = -0x30025,
   FS_ERROR_INVALID_FILEHANDLE      = -0x30026,
   FS_ERROR_INVALID_DIRHANDLE       = -0x30027,
   FS_ERROR_NOT_FILE                = -0x30028,
   FS_ERROR_NOT_DIR                 = -0x30029,
   FS_ERROR_FILE_TOO_BIG            = -0x3002A,
   FS_ERROR_OUT_OF_RANGE            = -0x3002B,
   FS_ERROR_OUT_OF_RESOURCES        = -0x3002C,
   FS_ERROR_MEDIA_NOT_READY         = -0x30030,
   FS_ERROR_MEDIA_ERROR             = -0x30031,
   FS_ERROR_WRITE_PROTECTED         = -0x30032,
   FS_ERROR_INVALID_MEDIA           = -0x30033,
} FSError;

typedef enum FSStatFlags
{
   FS_STAT_DIRECTORY                = 0x80000000,
} FSStatFlags;

typedef enum FSVolumeState
{
   FS_VOLUME_STATE_INITIAL          = 0,
   FS_VOLUME_STATE_READY            = 1,
   FS_VOLUME_STATE_NO_MEDIA         = 2,
   FS_VOLUME_STATE_INVALID_MEDIA    = 3,
   FS_VOLUME_STATE_DIRTY_MEDIA      = 4,
   FS_VOLUME_STATE_WRONG_MEDIA      = 5,
   FS_VOLUME_STATE_MEDIA_ERROR      = 6,
   FS_VOLUME_STATE_DATA_CORRUPTED   = 7,
   FS_VOLUME_STATE_WRITE_PROTECTED  = 8,
   FS_VOLUME_STATE_JOURNAL_FULL     = 9,
   FS_VOLUME_STATE_FATAL            = 10,
   FS_VOLUME_STATE_INVALID          = 11,
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
