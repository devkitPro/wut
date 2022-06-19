#pragma once

#include "wut.h"
#include "filesystem.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t FSACommand;
typedef uint16_t FSAIpcRequestType;
typedef IOSHandle FSAClientHandle;
typedef uint32_t FSAFileHandle;
typedef uint32_t FSADirectoryHandle;
typedef uint32_t FSAEntryNum;
typedef FSDirectoryEntry FSADirectoryEntry;
typedef FSStat FSAStat;

typedef struct FSARequestRawOpen FSARequestRawOpen;
typedef struct FSARequestRawClose FSARequestRawClose;
typedef struct FSARequestRawRead FSARequestRawRead;
typedef struct FSARequestRawWrite FSARequestRawWrite;
typedef struct FSARequest FSARequest;
typedef struct FSAResponseRawOpen FSAResponseRawOpen;
typedef struct FSAResponse FSAResponse;
typedef struct FSAAsyncResult FSAAsyncResult;
typedef struct FSAShimBuffer FSAShimBuffer;
typedef struct FSAClientAttachAsyncData FSAClientAttachAsyncData;
typedef struct FSABlockInfo FSABlockInfo;
typedef struct FSADeviceInfo FSADeviceInfo;
typedef struct FSAFileSystemInfo FSAFileSystemInfo;
typedef struct FSVolumeInfo FSAVolumeInfo;

typedef void (*FSAAsyncCallbackFn)(FSError result,
                                   FSACommand command,
                                   FSARequest *request,
                                   FSAResponse *response,
                                   void *userContext);

struct FSARequestRawOpen {
    char path[0x280];
};
WUT_CHECK_OFFSET(FSARequestRawOpen, 0x0, path);
WUT_CHECK_SIZE(FSARequestRawOpen, 0x280);

struct FSARequestRawClose {
    int32_t handle;
};
WUT_CHECK_OFFSET(FSARequestRawClose, 0x0, handle);
WUT_CHECK_SIZE(FSARequestRawClose, 0x04);

struct WUT_PACKED FSARequestRawRead {
    WUT_UNKNOWN_BYTES(0x4);
    uint64_t blocks_offset;
    uint32_t count;
    uint32_t size;
    uint32_t device_handle;
};
WUT_CHECK_OFFSET(FSARequestRawRead, 0x04, blocks_offset);
WUT_CHECK_OFFSET(FSARequestRawRead, 0x0C, count);
WUT_CHECK_OFFSET(FSARequestRawRead, 0x10, size);
WUT_CHECK_OFFSET(FSARequestRawRead, 0x14, device_handle);
WUT_CHECK_SIZE(FSARequestRawRead, 0x18);

struct WUT_PACKED FSARequestRawWrite {
    WUT_UNKNOWN_BYTES(0x4);
    uint64_t blocks_offset;
    uint32_t count;
    uint32_t size;
    uint32_t device_handle;
};
WUT_CHECK_OFFSET(FSARequestRawWrite, 0x04, blocks_offset);
WUT_CHECK_OFFSET(FSARequestRawWrite, 0x0C, count);
WUT_CHECK_OFFSET(FSARequestRawWrite, 0x10, size);
WUT_CHECK_OFFSET(FSARequestRawWrite, 0x14, device_handle);
WUT_CHECK_SIZE(FSARequestRawWrite, 0x18);

struct FSARequest {
    FSError emulatedError;

    union {
        FSARequestRawOpen rawOpen;
        FSARequestRawClose rawClose;
        FSARequestRawRead rawRead;
        FSARequestRawWrite rawWrite;
        WUT_UNKNOWN_BYTES(0x51C);
    };
};
WUT_CHECK_OFFSET(FSARequest, 0x00, emulatedError);
WUT_CHECK_OFFSET(FSARequest, 0x04, rawOpen);
WUT_CHECK_SIZE(FSARequest, 0x520);


struct FSAResponseRawOpen {
    int handle;
};
WUT_CHECK_OFFSET(FSAResponseRawOpen, 0x0, handle);
WUT_CHECK_SIZE(FSAResponseRawOpen, 0x4);

struct WUT_PACKED FSAResponse {
    uint32_t word0;
    union WUT_PACKED {
        FSAResponseRawOpen rawOpen;
        WUT_UNKNOWN_BYTES(0x28F);
    };
};
WUT_CHECK_OFFSET(FSAResponse, 0x0, word0);
WUT_CHECK_OFFSET(FSAResponse, 0x4, rawOpen);
WUT_CHECK_SIZE(FSAResponse, 0x293);

enum FSACommandEnum {
    FSA_COMMAND_INVALID                   = 0x0,
    FSA_COMMAND_MOUNT                     = 0x1,
    FSA_COMMAND_UNMOUNT                   = 0x2,
    FSA_COMMAND_GET_VOLUME_INFO           = 0x3,
    FSA_COMMAND_GET_ATTACH                = 0x4,
    FSA_COMMAND_CHANGE_DIR                = 0x5,
    FSA_COMMAND_GET_CWD                   = 0x6,
    FSA_COMMAND_MAKE_DIR                  = 0x7,
    FSA_COMMAND_REMOVE                    = 0x8,
    FSA_COMMAND_RENAME                    = 0x9,
    FSA_COMMAND_OPEN_DIR                  = 0xA,
    FSA_COMMAND_READ_DIR                  = 0xB,
    FSA_COMMAND_REWIND_DIR                = 0xC,
    FSA_COMMAND_CLOSE_DIR                 = 0xD,
    FSA_COMMAND_OPEN_FILE                 = 0xE,
    FSA_COMMAND_READ_FILE                 = 0xF,
    FSA_COMMAND_WRITE_FILE                = 0x10,
    FSA_COMMAND_GET_POS_FILE              = 0x11,
    FSA_COMMAND_SET_POS_FILE              = 0x12,
    FSA_COMMAND_IS_EOF                    = 0x13,
    FSA_COMMAND_STAT_FILE                 = 0x14,
    FSA_COMMAND_CLOSE_FILE                = 0x15,
    FSA_COMMAND_GET_ERROR                 = 0x16,
    FSA_COMMAND_FLUSH_FILE                = 0x17,
    FSA_COMMAND_GET_INFO_BY_QUERY         = 0x18,
    FSA_COMMAND_APPEND_FILE               = 0x19,
    FSA_COMMAND_TRUNCATE_FILE             = 0x1A,
    FSA_COMMAND_FLUSH_VOLUME              = 0x1B,
    FSA_COMMAND_ROLLBACK_VOLUME           = 0x1C,
    FSA_COMMAND_MAKE_QUOTA                = 0x1D,
    FSA_COMMAND_FLUSH_QUOTA               = 0x1E,
    FSA_COMMAND_ROLLBACK_QUOTA            = 0x1F,
    FSA_COMMAND_CHANGE_MODE               = 0x20,
    FSA_COMMAND_OPEN_FILE_BY_STAT         = 0x21,
    FSA_COMMAND_REGISTER_FLUSH_QUOTA      = 0x22,
    FSA_COMMAND_FLUSH_MULTI_QUOTA         = 0x23,
    FSA_COMMAND_GET_FILE_BLOCK_ADDRESS    = 0x25,
    FSA_COMMAND_ADD_USER_PROCESS          = 0x65,
    FSA_COMMAND_DEL_USER_PROCESS          = 0x66,
    FSA_COMMAND_MOUNT_WITH_PROCESS        = 0x67,
    FSA_COMMAND_UNMOUNT_WITH_PROCESS      = 0x68,
    FSA_COMMAND_FORMAT                    = 0x69,
    FSA_COMMAND_RAW_OPEN                  = 0x6A,
    FSA_COMMAND_RAW_READ                  = 0x6B,
    FSA_COMMAND_RAW_WRITE                 = 0x6C,
    FSA_COMMAND_RAW_CLOSE                 = 0x6D,
    GET_LAST_FAILED_VOLUME                = 0x6E,
    GET_VOLUME_EXISTENCE                  = 0x6F,
    FSA_COMMAND_CHANGE_OWNER              = 0x70,
    FSA_COMMAND_CANCEL_GET_ATTACH         = 0x71,
    FSA_COMMAND_REMOVE_QUOTA              = 0x72,
    FSA_COMMAND_SET_CLIENT_PRIORITY       = 0x73,
    FSA_COMMAND_APPLY_MEMORY_CACHE        = 0x74,
    FSA_COMMAND_MAKE_LINK                 = 0x75,
    FSA_COMMAND_XFER_PARAMS               = 0x76,
    FSA_COMMAND_EXEC_DEBUG_PROC           = 0x78,
    FSA_COMMAND_DEBUG_SET_TITLE_ID        = 0x79,
    FSA_COMMAND_DEBUG_SET_CAPABILITY      = 0x7A,
    FSA_COMMAND_SET_PROCESS_CONFIG        = 0x82,
    FSA_COMMAND_CONFIG_SET_MEMORY_CACHE   = 0x83,
    FSA_COMMAND_CONFIG_UNSET_MEMORY_CACHE = 0x84,
    FSA_COMMAND_CONFIG_SET_PRF2_CHAR_CODE = 0x85,
    FSA_COMMAND_GET_PROC_RESOURCE_USAGE   = 0x8C,
    FSA_COMMAND_GET_ALL_RESOURCE_USAGE    = 0x8D,
    FSA_COMMAND_SEND_PROFILE_CMD          = 0x8E,
};

enum FSAIpcRequestTypeEnum {
    FSA_IPC_REQUEST_IOCTL  = 0,
    FSA_IPC_REQUEST_IOCTLV = 1,
};

struct FSAAsyncResult {
    //! Queue to put a message on when command is complete.
    OSMessageQueue *ioMsgQueue;

    //! Message used for ioMsgQueue.
    FSMessage msg;

    //! Callback to call when the command is complete.
    FSAAsyncCallbackFn userCallback;

    //! Result.
    FSError error;

    //! FSA command.
    FSACommand command;

    //! Pointer to allocated FSA IPC Request.
    FSARequest *request;

    //! Pointer to allocated FSA IPC Response.
    FSAResponse *response;

    //! Callback to call when the command is complete.
    void *userContext;
};
WUT_CHECK_OFFSET(FSAAsyncResult, 0x00, ioMsgQueue);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x04, msg);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x14, userCallback);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x18, error);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x1C, command);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x20, request);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x24, response);
WUT_CHECK_OFFSET(FSAAsyncResult, 0x28, userContext);
WUT_CHECK_SIZE(FSAAsyncResult, 0x2C);

struct WUT_PACKED FSAShimBuffer {
    //! Buffer for FSA IPC request.
    FSARequest request;
    WUT_UNKNOWN_BYTES(0x60);

    //! Buffer for FSA IPC response.
    FSAResponse response;
    WUT_UNKNOWN_BYTES(0x880 - 0x813);

    //! Memory to use for ioctlv calls, unknown maximum count - but at least 3.
    IOSVec ioctlvVec[3];

    WUT_UNKNOWN_BYTES(0x900 - 0x8A4);

    //! Command for FSA.
    FSACommand command;

    //! Handle to FSA device.
    uint32_t clientHandle;

    //! IOS IPC request type to use.
    FSAIpcRequestType ipcReqType;

    //! Number of ioctlv input vectors.
    uint8_t ioctlvVecIn;

    //! Number of ioctlv output vectors.
    uint8_t ioctlvVecOut;

    //! FSAAsyncResult used for FSA* functions.
    FSAAsyncResult fsaAsyncResult;
};
WUT_CHECK_OFFSET(FSAShimBuffer, 0x0, request);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x580, response);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x880, ioctlvVec);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x900, command);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x904, clientHandle);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x908, ipcReqType);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x90A, ioctlvVecIn);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x90B, ioctlvVecOut);
WUT_CHECK_OFFSET(FSAShimBuffer, 0x90C, fsaAsyncResult);
WUT_CHECK_SIZE(FSAShimBuffer, 0x938);

typedef void (*FSAClientAttachAsyncCallbackFn)(FSError result,
                                               FSACommand command,
                                               FSARequest *request,
                                               FSAResponse *response,
                                               void *userContext);

struct FSAClientAttachAsyncData {
    //! Callback to call when an attach has happened.
    FSAClientAttachAsyncCallbackFn userCallback;

    //! Callback context
    void *userContext;

    //! Queue to put a message on when command is complete.
    OSMessageQueue *ioMsgQueue;
};
WUT_CHECK_OFFSET(FSAClientAttachAsyncData, 0x00, userCallback);
WUT_CHECK_OFFSET(FSAClientAttachAsyncData, 0x04, userContext);
WUT_CHECK_OFFSET(FSAClientAttachAsyncData, 0x08, ioMsgQueue);
WUT_CHECK_SIZE(FSAClientAttachAsyncData, 0xC);

/**
 * Block information.
 */
struct FSABlockInfo {
    WUT_UNKNOWN_BYTES(0x14);
};
WUT_CHECK_SIZE(FSABlockInfo, 0x14);

/**
 * Device information.
 */
struct FSADeviceInfo {
    WUT_UNKNOWN_BYTES(0x08);
    uint64_t deviceSizeInSectors;
    uint32_t deviceSectorSize;
    WUT_UNKNOWN_BYTES(0x14);
};
WUT_CHECK_OFFSET(FSADeviceInfo, 0x08, deviceSizeInSectors);
WUT_CHECK_OFFSET(FSADeviceInfo, 0x10, deviceSectorSize);
WUT_CHECK_SIZE(FSADeviceInfo, 0x28);

/**
 * File System information.
 */
struct FSAFileSystemInfo {
    WUT_UNKNOWN_BYTES(0x1E);
};
WUT_CHECK_SIZE(FSAFileSystemInfo, 0x1E);

typedef enum FSAMountFlags {
    FSA_MOUNT_FLAG_LOCAL_MOUNT = 0,
    FSA_MOUNT_FLAG_BIND_MOUNT = 1,
    FSA_MOUNT_FLAG_GLOBAL_MOUNT = 2,
} FSAMountFlags;

typedef enum FSAUnmountFlags {
    FSA_UNMOUNT_FLAG_NONE = 0x00000000,
    FSA_UNMOUNT_FLAG_FORCE = 0x00000002,
    FSA_UNMOUNT_FLAG_BIND_MOUNT = 0x80000000,
} FSAUnmountFlags;

FSError
FSAInit();

void
FSAShutdown();

uint32_t
FSAGetClientNum();

FSAClientHandle
FSAAddClient(FSAClientAttachAsyncData *attachAsyncData);

FSError
FSADelClient(FSAClientHandle client);

const char *
FSAGetStatusStr(FSError error);

FSError
FSAFlushMultiQuota(FSAClientHandle client,
                   const char *path);

FSError
FSAFlushQuota(FSAClientHandle client,
              const char *path);

FSError
FSAFlushVolume(FSAClientHandle client,
               const char *path);

/**
 * Frees the FSAShimBuffer where the given asyncResult is part of
 * @param asyncResult
 */
void
FSAFreeAsyncResult(FSAAsyncResult *asyncResult);

FSAAsyncResult
FSAGetAsyncResult(OSMessage *asyncResult);

FSError
FSAMount(FSAClientHandle client,
         const char *source,
         const char *target,
         FSAMountFlags flags,
         void *arg_buf,
         uint32_t arg_len);

FSError
FSAUnmount(FSAClientHandle client,
           const char *mountedTarget,
           FSAUnmountFlags flags);

FSError
FSAChangeDir(FSAClientHandle client,
             const char *path);

FSError
FSAChangeMode(FSAClientHandle client,
              const char *path,
              FSMode permission);

FSError
FSOpenFileEx(FSAClientHandle client,
             const char *path,
             const char *mode,
             FSAFileHandle *outFileHandle);

FSError
FSAOpenFileEx(FSAClientHandle client,
              const char *path,
              const char *mode,
              FSMode createMode,
              FSOpenFileFlags openFlag,
              uint32_t preallocSize,
              FSAFileHandle *outFileHandle);

FSError
FSAOpenFileByStat(FSAClientHandle client,
                  FSAStat *stat,
                  const char *mode,
                  const char *path,
                  FSAFileHandle *outFileHandle);

FSError
FSAGetStatFile(FSAClientHandle client,
               FSAFileHandle fileHandle,
               FSAStat *stat);

FSError
FSAGetStat(FSAClientHandle client,
           const char *path,
           FSAStat *stat);

FSError
FSACloseFile(FSAClientHandle client,
             FSAFileHandle fileHandle);

FSError
FSAAppendFile(FSAClientHandle client,
              FSAFileHandle fileHandle,
              uint32_t size,
              uint32_t count);

FSError
FSAAppendFileEx(FSAClientHandle client,
                FSAFileHandle fileHandle,
                uint32_t size,
                uint32_t count,
                uint32_t flags);

FSError
FSAGetPosFile(FSAClientHandle client,
              FSAFileHandle fileHandle,
              uint32_t *outPos);

FSError
FSAFlushFile(FSAClientHandle client,
             FSAFileHandle fileHandle);

FSError
FSASetPosFile(FSAClientHandle client,
              FSAFileHandle fileHandle,
              uint32_t pos);

FSError
FSATruncateFile(FSAClientHandle client,
                FSAFileHandle handle);

FSError
FSAWriteFile(FSAClientHandle client,
             void *buffer,
             uint32_t size,
             uint32_t count,
             FSAFileHandle handle,
             uint32_t flags);

FSError
FSAWriteFileWithPos(FSAClientHandle client,
                    void *buffer,
                    uint32_t size,
                    uint32_t count,
                    uint32_t pos,
                    FSAFileHandle handle,
                    uint32_t flags);

FSError
FSAIsEof(FSAClientHandle client,
         FSAFileHandle fileHandle);

FSError
FSAReadFile(FSAClientHandle client,
            void *buffer,
            uint32_t size,
            uint32_t count,
            FSAFileHandle handle,
            uint32_t flags);

FSError
FSAReadFileWithPos(FSAClientHandle client,
                   void *buffer,
                   uint32_t size,
                   uint32_t count,
                   uint32_t pos,
                   FSAFileHandle handle,
                   uint32_t flags);

FSError
FSARemove(FSAClientHandle client,
          const char *path);

FSError
FSARename(FSAClientHandle client,
          const char *oldPath,
          const char *newPath);

FSError
FSAOpenDir(FSAClientHandle client,
           const char *path,
           FSADirectoryHandle *dirHandle);

FSError
FSAReadDir(FSAClientHandle client,
           FSADirectoryHandle dirHandle,
           FSADirectoryEntry *directoryEntry);

FSError
FSARewindDir(FSAClientHandle client,
             FSADirectoryHandle dirHandle);

FSError
FSACloseDir(FSAClientHandle client,
            FSADirectoryHandle dirHandle);

FSError
FSAMakeDir(FSAClientHandle client,
           const char *path,
           FSMode mode);

FSError
FSAGetCwd(FSAClientHandle client,
          char *outPath,
          uint32_t outPathLen);

FSError
FSAGetTransactionBlockPoolAttributes(uint32_t *messageSize,
                                     uint32_t *poolSize,
                                     uint32_t *numMessages);

FSError
FSAGetVolumeInfo(FSAClientHandle client,
                 const char *path,
                 FSAVolumeInfo *outVolumeInfo);


FSError
FSAMakeQuota(FSAClientHandle client,
             const char *name,
             uint32_t mode,
             uint64_t quota);

FSError
FSARegisterFlushQuota(FSAClientHandle client,
                      const char *path);

FSError
FSARollbackQuota(FSAClientHandle client,
                 const char *path);

FSError
FSARollbackQuotaForce(FSAClientHandle client,
                      const char *path);

FSError
FSARollbackVolume(FSAClientHandle client,
                  const char *path);

FSError
FSAGetFreeSpaceSize(FSAClientHandle client,
                    const char *path,
                    uint64_t *freeSpaceSize);

FSError
FSAGetJournalFreeSpaceSize(FSAClientHandle client,
                           const char *path,
                           uint64_t *journalFreeSpaceSize);

FSError
FSAGetDirSize(FSAClientHandle client,
              const char *path,
              uint64_t *freeDirSize);

FSError
FSAGetEntryNum(FSAClientHandle client,
               const char *path,
               FSAEntryNum *entryNum);

FSError
FSAGetFileSystemInfo(FSAClientHandle client,
                     const char *path,
                     FSAFileSystemInfo *fileSystemInfo);

FSError
FSAGetDeviceInfo(FSAClientHandle client,
                 const char *path,
                 FSADeviceInfo *fileSystemInfo);

FSError
FSAGetBadBlockInfo(FSAClientHandle client,
                   const char *path,
                   FSABlockInfo *blockInfo);

FSError
FSAGetFragmentBlockInfo(FSAClientHandle client,
                        const char *path,
                        FSABlockInfo *blockInfo);

#ifdef __cplusplus
}
#endif