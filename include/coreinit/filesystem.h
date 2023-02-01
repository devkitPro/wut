#pragma once
#include <wut.h>
#include <coreinit/messagequeue.h>
#include <coreinit/time.h>
#include <coreinit/ios.h>
#include <coreinit/fastmutex.h>
#include <coreinit/alarm.h>

/**
 * \defgroup coreinit_fs Filesystem
 * \ingroup coreinit
 *
 *  Mount, access and modify filesystems directly.
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

#define FS_MAX_PATH (0x27F)
#define FS_MODE_LENGTH (0x10)

typedef uint32_t FSDirectoryHandle;
typedef uint32_t FSFileHandle;
typedef uint32_t FSPriority;
typedef uint64_t FSTime;

typedef struct FSFsm FSFsm;
typedef struct FSCmdQueue FSCmdQueue;
typedef struct FSClientBodyLink FSClientBodyLink;
typedef struct FSAsyncData FSAsyncData;
typedef struct FSAsyncResult FSAsyncResult;
typedef struct FSClientBody FSClientBody;
typedef struct FSClient FSClient;
typedef struct FSCmdBlockBody FSCmdBlockBody;
typedef struct FSCmdBlock FSCmdBlock;
typedef struct FSDirectoryEntry FSDirectoryEntry;
typedef struct FSMessage FSMessage;
typedef struct FSMountSource FSMountSource;
typedef struct FSStat FSStat;
typedef struct FSStateChangeParams FSStateChangeParams;
typedef struct FSStateChangeParams FSStateChangeInfo;
typedef struct FSVolumeInfo FSVolumeInfo;

typedef enum FSErrorFlag
{
   FS_ERROR_FLAG_NONE               =  0x0,
   FS_ERROR_FLAG_MAX                =  0x1,
   FS_ERROR_FLAG_ALREADY_OPEN       =  0x2,
   FS_ERROR_FLAG_EXISTS             =  0x4,
   FS_ERROR_FLAG_NOT_FOUND          =  0x8,
   FS_ERROR_FLAG_NOT_FILE           =  0x10,
   FS_ERROR_FLAG_NOT_DIR            =  0x20,
   FS_ERROR_FLAG_ACCESS_ERROR       =  0x40,
   FS_ERROR_FLAG_PERMISSION_ERROR   =  0x80,
   FS_ERROR_FLAG_FILE_TOO_BIG       =  0x100,
   FS_ERROR_FLAG_STORAGE_FULL       =  0x200,
   FS_ERROR_FLAG_UNSUPPORTED_CMD    =  0x400,
   FS_ERROR_FLAG_JOURNAL_FULL       =  0x800,
   FS_ERROR_FLAG_ALL                =  0xFFFFFFFF,
} FSErrorFlag;

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
   FS_ERROR_OK                      = 0,
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
   FS_ERROR_MEDIA_NOT_READY         = -0x30040,
   FS_ERROR_MEDIA_ERROR             = -0x30041,
   FS_ERROR_WRITE_PROTECTED         = -0x30042,
   FS_ERROR_INVALID_MEDIA           = -0x30043,
} FSError;

typedef enum FSMode
{
   FS_MODE_READ_OWNER                   = 0x400,
   FS_MODE_WRITE_OWNER                  = 0x200,
   FS_MODE_EXEC_OWNER                   = 0x100,

   FS_MODE_READ_GROUP                   = 0x040,
   FS_MODE_WRITE_GROUP                  = 0x020,
   FS_MODE_EXEC_GROUP                   = 0x010,

   FS_MODE_READ_OTHER                   = 0x004,
   FS_MODE_WRITE_OTHER                  = 0x002,
   FS_MODE_EXEC_OTHER                   = 0x001,
} FSMode;

//! Flags for \link FSStat \endlink.
//! One can return multiple flags, so for example a file that's encrypted or a linked directory.
typedef enum FSStatFlags
{
   //! The retrieved file entry is a (link to a) directory.
   FS_STAT_DIRECTORY                = 0x80000000,
   //! The retrieved file entry also has a quota set.
   FS_STAT_QUOTA                    = 0x60000000,
   //! The retrieved file entry is a (link to a) file.
   FS_STAT_FILE                     = 0x01000000,
   //! The retrieved file entry also is encrypted and can't be opened (see vWii files for example).
   FS_STAT_ENCRYPTED_FILE           = 0x00800000,
   //! The retrieved file entry also is a link to a different file on the filesystem.
   //! Note: It's currently not known how one can read the linked-to file entry.
   FS_STAT_LINK                     = 0x00010000,
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

typedef enum FSMediaState {
    FS_MEDIA_STATE_READY = 0,
    FS_MEDIA_STATE_NO_MEDIA = 1,
    FS_MEDIA_STATE_INVALID_MEDIA = 2,
    FS_MEDIA_STATE_DIRTY_MEDIA = 3,
    FS_MEDIA_STATE_MEDIA_ERROR = 4,
} FSMediaState;

typedef enum FSMountSourceType {
    FS_MOUNT_SOURCE_SD  = 0,
    FS_MOUNT_SOURCE_UNK = 1,
} FSMountSourceType;

typedef enum FSOpenFileFlags
{
   //! Open file normally
   FS_OPEN_FLAG_NONE = (0 << 0),
   //! Open (new) unencrypted file. Used for vWii files since it allows for direct access without the Wii U filesystem through it's block address.
   FS_OPEN_FLAG_UNENCRYPTED = (1 << 0),
   //! Preallocates new file size using given size
   FS_OPEN_FLAG_PREALLOC_SIZE = (1 << 1)
} FSOpenFileFlags;

typedef void(*FSAsyncCallback)(FSClient *, FSCmdBlock *, FSStatus, uint32_t);
typedef void(*FSStateChangeCallback)(FSClient *, FSVolumeState, void *);

struct FSFsm
{
    WUT_UNKNOWN_BYTES(0x38);
};
WUT_CHECK_SIZE(FSFsm, 0x38);

struct FSCmdQueue
{
    WUT_UNKNOWN_BYTES(0x44);
};
WUT_CHECK_SIZE(FSCmdQueue, 0x44);

struct FSMessage
{
    //! Message data
    void *data;

    WUT_UNKNOWN_BYTES(8);

    //! Type of message
    OSFunctionType type;
};
WUT_CHECK_OFFSET(FSMessage, 0x00, data);
WUT_CHECK_OFFSET(FSMessage, 0x0C, type);
WUT_CHECK_SIZE(FSMessage, 0x10);

/**
 * Link entry used for FSClientBodyQueue.
 */
struct FSClientBodyLink
{
    FSClientBody* next;
    FSClientBody* prev;
};
WUT_CHECK_OFFSET(FSClientBodyLink, 0x00, next);
WUT_CHECK_OFFSET(FSClientBodyLink, 0x04, prev);
WUT_CHECK_SIZE(FSClientBodyLink, 0x8);

struct FSClientBody
{
    WUT_UNKNOWN_BYTES(0x1444);

    //! IOSHandle returned from fsaShimOpen.
    IOSHandle clientHandle;

    //! State machine.
    FSFsm fsm;

    //! Command queue of FS commands.
    FSCmdQueue cmdQueue;

    //! The last dequeued command.
    FSCmdBlockBody* lastDequeuedCommand;

    //! Emulated error, set with FSSetEmulatedError.
    FSError emulatedError;

    WUT_UNKNOWN_BYTES(0x1560 - 0x14CC);

    //! Mutex used to protect FSClientBody data.
    OSFastMutex mutex;

    WUT_UNKNOWN_BYTES(4);

    //! Alarm used by fsm for unknown reasons.
    OSAlarm fsmAlarm;

    //! Error of last FS command.
    FSError lastError;

    bool isLastErrorWithoutVolume;

    //! Message used to send FsCmdHandler message when FSA async callback is received.
    FSMessage fsCmdHandlerMsg;

    //! Device name of the last mount source returned by FSGetMountSourceNext.
    char lastMountSourceDevice[0x10];

    //! Mount source type to find with FSGetMountSourceNext.
    FSMountSourceType findMountSourceType;

    //! Link used for linked list of clients.
    FSClientBodyLink link;

    //! Pointer to unaligned FSClient structure.
    FSClient* client;
};
WUT_CHECK_OFFSET(FSClientBody, 0x1444, clientHandle);
WUT_CHECK_OFFSET(FSClientBody, 0x1448, fsm);
WUT_CHECK_OFFSET(FSClientBody, 0x1480, cmdQueue);
WUT_CHECK_OFFSET(FSClientBody, 0x14C4, lastDequeuedCommand);
WUT_CHECK_OFFSET(FSClientBody, 0x14C8, emulatedError);
WUT_CHECK_OFFSET(FSClientBody, 0x1560, mutex);
WUT_CHECK_OFFSET(FSClientBody, 0x1590, fsmAlarm);
WUT_CHECK_OFFSET(FSClientBody, 0x15E8, lastError);
WUT_CHECK_OFFSET(FSClientBody, 0x15EC, isLastErrorWithoutVolume);
WUT_CHECK_OFFSET(FSClientBody, 0x15F0, fsCmdHandlerMsg);
WUT_CHECK_OFFSET(FSClientBody, 0x1600, lastMountSourceDevice);
WUT_CHECK_OFFSET(FSClientBody, 0x1610, findMountSourceType);
WUT_CHECK_OFFSET(FSClientBody, 0x1614, link);
WUT_CHECK_OFFSET(FSClientBody, 0x161C, client);
WUT_CHECK_SIZE(FSClientBody, 0x1620);

struct FSClient
{
   WUT_UNKNOWN_BYTES(0x1700);
};
WUT_CHECK_SIZE(FSClient, 0x1700);

struct FSCmdBlock
{
   WUT_UNKNOWN_BYTES(0xA80);
};
WUT_CHECK_SIZE(FSCmdBlock, 0xA80);

struct WUT_PACKED FSStat
{
   FSStatFlags flags;
   FSMode mode;
   uint32_t owner;
   uint32_t group;
   uint32_t size;
   uint32_t allocSize;
   uint64_t quotaSize;
   uint32_t entryId;
   FSTime created;
   FSTime modified;
   WUT_UNKNOWN_BYTES(0x30);
};
WUT_CHECK_OFFSET(FSStat, 0x00, flags);
WUT_CHECK_OFFSET(FSStat, 0x04, mode);
WUT_CHECK_OFFSET(FSStat, 0x08, owner);
WUT_CHECK_OFFSET(FSStat, 0x0C, group);
WUT_CHECK_OFFSET(FSStat, 0x10, size);
WUT_CHECK_OFFSET(FSStat, 0x14, allocSize);
WUT_CHECK_OFFSET(FSStat, 0x18, quotaSize);
WUT_CHECK_OFFSET(FSStat, 0x20, entryId);
WUT_CHECK_OFFSET(FSStat, 0x24, created);
WUT_CHECK_OFFSET(FSStat, 0x2C, modified);
WUT_CHECK_SIZE(FSStat, 0x64);

struct FSStateChangeParams
{
   FSStateChangeCallback callback;
   void *param;
   OSMessageQueue *ioMsgQueue;
};
WUT_CHECK_OFFSET(FSStateChangeParams, 0x00, callback);
WUT_CHECK_OFFSET(FSStateChangeParams, 0x04, param);
WUT_CHECK_OFFSET(FSStateChangeParams, 0x08, ioMsgQueue);
WUT_CHECK_SIZE(FSStateChangeParams, 0x0C);

struct FSAsyncData
{
   FSAsyncCallback callback;
   uint32_t param;
   OSMessageQueue *ioMsgQueue;
};
WUT_CHECK_OFFSET(FSAsyncData, 0x00, callback);
WUT_CHECK_OFFSET(FSAsyncData, 0x04, param);
WUT_CHECK_OFFSET(FSAsyncData, 0x08, ioMsgQueue);
WUT_CHECK_SIZE(FSAsyncData, 0x0C);

/**
 * Stores the result of an async FS command.
 */
struct FSAsyncResult
{
   //! User supplied async data.
   FSAsyncData asyncData;

   //! Message to put into asyncdata.ioMsgQueue.
   FSMessage ioMsg;

   //! FSClient which owns this result.
   FSClient *client;

   //! FSCmdBlock which owns this result.
   FSCmdBlock *block;

   //! The result of the command.
   FSStatus status;
};
WUT_CHECK_OFFSET(FSAsyncResult, 0x00, asyncData);
WUT_CHECK_OFFSET(FSAsyncResult, 0x0c, ioMsg);
WUT_CHECK_OFFSET(FSAsyncResult, 0x1c, client);
WUT_CHECK_OFFSET(FSAsyncResult, 0x20, block);
WUT_CHECK_OFFSET(FSAsyncResult, 0x24, status);
WUT_CHECK_SIZE(FSAsyncResult, 0x28);

struct FSCmdBlockBody {
    WUT_UNKNOWN_BYTES(0x96C);
    FSAsyncResult asyncResult;
    WUT_UNKNOWN_BYTES(0x68);
};
WUT_CHECK_OFFSET(FSCmdBlockBody, 0x96C, asyncResult);
WUT_CHECK_SIZE(FSCmdBlockBody, 0x9FC);

struct FSDirectoryEntry
{
   FSStat info;
   char name[256];
};
WUT_CHECK_OFFSET(FSDirectoryEntry, 0x64, name);
WUT_CHECK_SIZE(FSDirectoryEntry, 0x164);

struct FSMountSource
{
   WUT_UNKNOWN_BYTES(0x300);
};
WUT_CHECK_SIZE(FSMountSource, 0x300);

struct WUT_PACKED FSVolumeInfo {
    uint32_t flags;
    FSMediaState mediaState;
    WUT_UNKNOWN_BYTES(0x4);
    uint32_t unk0x0C;
    uint32_t unk0x10;
    int32_t unk0x14;
    int32_t unk0x18;
    WUT_UNKNOWN_BYTES(0x10);
    char volumeLabel[128];
    char volumeId[128];
    char devicePath[16];
    char mountPath[128];
};
WUT_CHECK_OFFSET(FSVolumeInfo, 0x00, flags);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x04, mediaState);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x0C, unk0x0C);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x10, unk0x10);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x14, unk0x14);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x18, unk0x18);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x2C, volumeLabel);
WUT_CHECK_OFFSET(FSVolumeInfo, 0xAC, volumeId);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x12C, devicePath);
WUT_CHECK_OFFSET(FSVolumeInfo, 0x13C, mountPath);
WUT_CHECK_SIZE(FSVolumeInfo, 444);


/**
 * Get an aligned FSClientBody from an FSClient.
 */
static inline FSClientBody *
FSGetClientBody(FSClient *client) {
   if (!client) {
      return NULL;
   }
   return (FSClientBody *) ((((uint32_t) client) + 0x3F) & ~0x3F);
}

/**
 * Get an aligned FSCmdBlockBody from an FSCmdBlock.
 */
static inline FSCmdBlockBody *
FSGetCmdBlockBody(FSCmdBlock *cmdBlock) {
   if (!cmdBlock) {
      return NULL;
   }
   return (FSCmdBlockBody *) ((((uint32_t) cmdBlock) + 0x3F) & ~0x3F);
}

void
FSInit();

void
FSShutdown();

FSStatus
FSAddClient(FSClient *client,
            FSErrorFlag errorMask);

FSStatus
FSDelClient(FSClient *client,
            FSErrorFlag errorMask);

uint32_t
FSGetClientNum();

void
FSInitCmdBlock(FSCmdBlock *block);

FSStatus
FSSetCmdPriority(FSCmdBlock *block,
                 FSPriority priority);

void
FSSetStateChangeNotification(FSClient *client,
                             FSStateChangeParams *info);

FSStatus
FSGetCwd(FSClient *client,
         FSCmdBlock *block,
         char *buffer,
         uint32_t bufferSize,
         FSErrorFlag errorMask);

FSStatus
FSChangeDir(FSClient *client,
            FSCmdBlock *block,
            const char *path,
            FSErrorFlag errorMask);

FSStatus
FSChangeDirAsync(FSClient *client,
                 FSCmdBlock *block,
                 const char *path,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSAsyncResult *
FSGetAsyncResult(FSMessage *message);

FSStatus
FSGetStat(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSStat *stat,
          FSErrorFlag errorMask);

FSStatus
FSGetStatAsync(FSClient *client,
               FSCmdBlock *block,
               const char *path,
               FSStat *stat,
               FSErrorFlag errorMask,
               FSAsyncData *asyncData);

FSStatus
FSRemove(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSErrorFlag errorMask);

FSStatus
FSRemoveAsync(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSErrorFlag errorMask,
          FSAsyncData *asyncData);


FSStatus
FSOpenFile(FSClient *client,
           FSCmdBlock *block,
           const char *path,
           const char *mode,
           FSFileHandle *handle,
           FSErrorFlag errorMask);

FSStatus
FSOpenFileAsync(FSClient *client,
                FSCmdBlock *block,
                const char *path,
                const char *mode,
                FSFileHandle *outHandle,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
FSCloseFile(FSClient *client,
            FSCmdBlock *block,
            FSFileHandle handle,
            FSErrorFlag errorMask);

FSStatus
FSCloseFileAsync(FSClient *client,
                 FSCmdBlock *block,
                 FSFileHandle handle,
                 FSErrorFlag errorMask,
                 FSAsyncData *asyncData);

FSStatus
FSOpenFileEx(FSClient *client,
             FSCmdBlock *block,
             const char *path,
             const char *mode,
             FSMode createMode,
             FSOpenFileFlags openFlag,
             uint32_t preallocSize,
             FSFileHandle *handle,
             FSErrorFlag errorMask);

FSStatus
FSOpenFileExAsync(FSClient *client,
                  FSCmdBlock *block,
                  const char *path,
                  const char *mode,
                  FSMode createMode,
                  FSOpenFileFlags openFlag,
                  uint32_t preallocSize,
                  FSFileHandle *handle,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSOpenDir(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSDirectoryHandle *handle,
          FSErrorFlag errorMask);

FSStatus
FSOpenDirAsync(FSClient *client,
               FSCmdBlock *block,
               const char *path,
               FSDirectoryHandle *handle,
               FSErrorFlag errorMask,
               FSAsyncData *asyncData);

FSStatus
FSMakeDir(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSErrorFlag errorMask);

FSStatus
FSMakeDirAsync(FSClient *client,
          FSCmdBlock *block,
          const char *path,
          FSErrorFlag errorMask,
          FSAsyncData *asyncData);

FSStatus
FSReadDir(FSClient *client,
          FSCmdBlock *block,
          FSDirectoryHandle handle,
          FSDirectoryEntry *entry,
          FSErrorFlag errorMask);

FSStatus
FSReadDirAsync(FSClient *client,
               FSCmdBlock *block,
               FSDirectoryHandle handle,
               FSDirectoryEntry *entry,
               FSErrorFlag errorMask,
               FSAsyncData *asyncData);

FSStatus
FSRewindDir(FSClient *client,
           FSCmdBlock *block,
           FSDirectoryHandle handle,
           FSErrorFlag errorMask);

FSStatus
FSCloseDir(FSClient *client,
           FSCmdBlock *block,
           FSDirectoryHandle handle,
           FSErrorFlag errorMask);

FSStatus
FSGetVolumeInfo(FSClient *client, 
                FSCmdBlock *block, 
                const char *path, 
                FSVolumeInfo *volumeInfo, 
                FSErrorFlag  errorMask);

FSStatus
FSGetVolumeInfoAsync(FSClient *client, 
                     FSCmdBlock *block, 
                     const char *path, 
                     FSVolumeInfo *volumeInfo, 
                     FSErrorFlag  errorMask,
                     FSAsyncData *asyncData);

FSStatus
FSCloseDirAsync(FSClient *client,
                FSCmdBlock *block,
                FSDirectoryHandle handle,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);
FSStatus
FSChangeMode(FSClient *client,
             FSCmdBlock *block,
             const char *path,
             FSMode mode,
             FSMode modeMask,
             FSErrorFlag errorMask);

FSStatus
FSChangeModeAsync(FSClient *client,
                  FSCmdBlock *block,
                  const char *path,
                  FSMode mode,
                  FSMode modeMask,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSGetFreeSpaceSize(FSClient *client,
                   FSCmdBlock *block,
                   const char *path,
                   uint64_t *outSize,
                   FSErrorFlag errorMask);

FSStatus
FSGetFreeSpaceSizeAsync(FSClient *client,
                        FSCmdBlock *block,
                        const char *path,
                        uint64_t *outSize,
                        FSErrorFlag errorMask,
                        FSAsyncData *asyncData);

FSStatus
FSGetStatFile(FSClient *client,
              FSCmdBlock *block,
              FSFileHandle handle,
              FSStat *stat,
              FSErrorFlag errorMask);

FSStatus
FSGetStatFileAsync(FSClient *client,
                   FSCmdBlock *block,
                   FSFileHandle handle,
                   FSStat *stat,
                   FSErrorFlag errorMask,
                   FSAsyncData *asyncData);

FSStatus
FSReadFile(FSClient *client,
           FSCmdBlock *block,
           uint8_t *buffer,
           uint32_t size,
           uint32_t count,
           FSFileHandle handle,
           uint32_t unk1,
           FSErrorFlag errorMask);

FSStatus
FSReadFileAsync(FSClient *client,
                FSCmdBlock *block,
                uint8_t *buffer,
                uint32_t size,
                uint32_t count,
                FSFileHandle handle,
                uint32_t unk1,
                FSErrorFlag errorMask,
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
                  FSErrorFlag errorMask);

FSStatus
FSReadFileWithPosAsync(FSClient *client,
                       FSCmdBlock *block,
                       uint8_t *buffer,
                       uint32_t size,
                       uint32_t count,
                       uint32_t pos,
                       FSFileHandle handle,
                       uint32_t unk1,
                       FSErrorFlag errorMask,
                       FSAsyncData *asyncData);

FSStatus
FSWriteFile(FSClient *client,
           FSCmdBlock *block,
           uint8_t *buffer,
           uint32_t size,
           uint32_t count,
           FSFileHandle handle,
           uint32_t unk1,
           FSErrorFlag errorMask);

FSStatus
FSWriteFileAsync(FSClient *client,
                FSCmdBlock *block,
                uint8_t *buffer,
                uint32_t size,
                uint32_t count,
                FSFileHandle handle,
                uint32_t unk1,
                FSErrorFlag errorMask,
                FSAsyncData *asyncData);

FSStatus
FSWriteFileWithPos(FSClient *client,
                  FSCmdBlock *block,
                  uint8_t *buffer,
                  uint32_t size,
                  uint32_t count,
                  uint32_t pos,
                  FSFileHandle handle,
                  uint32_t unk1,
                  FSErrorFlag errorMask);

FSStatus
FSWriteFileWithPosAsync(FSClient *client,
                       FSCmdBlock *block,
                       uint8_t *buffer,
                       uint32_t size,
                       uint32_t count,
                       uint32_t pos,
                       FSFileHandle handle,
                       uint32_t unk1,
                       FSErrorFlag errorMask,
                       FSAsyncData *asyncData);

FSStatus
FSGetPosFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle fileHandle,
             uint32_t *pos,
             FSErrorFlag errorMask);

FSStatus
FSGetPosFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle fileHandle,
                  uint32_t *pos,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSSetPosFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle handle,
             uint32_t pos,
             FSErrorFlag errorMask);

FSStatus
FSSetPosFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle handle,
                  uint32_t pos,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSFlushFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle handle,
             FSErrorFlag errorMask);

FSStatus
FSFlushFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle handle,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSTruncateFile(FSClient *client,
             FSCmdBlock *block,
             FSFileHandle handle,
             FSErrorFlag errorMask);

FSStatus
FSTruncateFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  FSFileHandle handle,
                  FSErrorFlag errorMask,
                  FSAsyncData *asyncData);

FSStatus
FSRename(FSClient *client,
          FSCmdBlock *block,
          const char *oldPath,
          const char *newPath,
          FSErrorFlag errorMask);

FSStatus
FSRenameAsync(FSClient *client,
          FSCmdBlock *block,
          const char *oldPath,
          const char *newPath,
          FSErrorFlag errorMask,
          FSAsyncData *asyncData);

FSVolumeState
FSGetVolumeState(FSClient *client);

FSError
FSGetLastError(FSClient *client);

FSError
FSGetLastErrorCodeForViewer(FSClient *client);

FSStatus
FSGetMountSource(FSClient *client,
                 FSCmdBlock *cmd,
                 FSMountSourceType type,
                 FSMountSource *out,
                 FSErrorFlag errorMask);

FSStatus
FSMount(FSClient *client,
        FSCmdBlock *cmd,
        FSMountSource *source,
        const char *target,
        uint32_t bytes,
        FSErrorFlag errorMask);

FSStatus
FSUnmount(FSClient *client,
          FSCmdBlock *cmd,
          const char *target,
          FSErrorFlag errorMask);

FSStatus
FSBindMount(FSClient *client,
            FSCmdBlock *cmd,
            const char *source,
            const char *target,
            FSErrorFlag errorMask);

FSStatus
FSBindUnmount(FSClient *client,
              FSCmdBlock *cmd,
              const char *target,
              FSErrorFlag errorMask);

//! File times aren't always available in which case it returns the default 1980-01-01.
void
FSTimeToCalendarTime(FSTime time,
                     OSCalendarTime *outCalendarTime);

#ifdef __cplusplus
}
#endif

/** @} */
