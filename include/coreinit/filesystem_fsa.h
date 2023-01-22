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
typedef uint32_t FSAFilePosition;

typedef struct FSAProcessInfo FSAProcessInfo;

typedef struct FSARequestRawOpen FSARequestRawOpen;
typedef struct FSARequestRawClose FSARequestRawClose;
typedef struct FSARequestRawRead FSARequestRawRead;
typedef struct FSARequestRawWrite FSARequestRawWrite;
typedef struct FSARequestAppendFile FSARequestAppendFile;
typedef struct FSARequestChangeDir FSARequestChangeDir;
typedef struct FSARequestChangeMode FSARequestChangeMode;
typedef struct FSARequestCloseDir FSARequestCloseDir;
typedef struct FSARequestCloseFile FSARequestCloseFile;
typedef struct FSARequestFlushFile FSARequestFlushFile;
typedef struct FSARequestFlushQuota FSARequestFlushQuota;
typedef struct FSARequestGetInfoByQuery FSARequestGetInfoByQuery;
typedef struct FSARequestGetPosFile FSARequestGetPosFile;
typedef struct FSARequestIsEof FSARequestIsEof;
typedef struct FSARequestMakeDir FSARequestMakeDir;
typedef struct FSARequestMakeQuota FSARequestMakeQuota;
typedef struct FSARequestMount FSARequestMount;
typedef struct FSARequestMountWithProcess FSARequestMountWithProcess;
typedef struct FSARequestOpenDir FSARequestOpenDir;
typedef struct FSARequestOpenFile FSARequestOpenFile;
typedef struct FSARequestReadDir FSARequestReadDir;
typedef struct FSARequestReadFile FSARequestReadFile;
typedef struct FSARequestRemove FSARequestRemove;
typedef struct FSARequestRename FSARequestRename;
typedef struct FSARequestRewindDir FSARequestRewindDir;
typedef struct FSARequestSetPosFile FSARequestSetPosFile;
typedef struct FSARequestStatFile FSARequestStatFile;
typedef struct FSARequestTruncateFile FSARequestTruncateFile;
typedef struct FSARequestUnmount FSARequestUnmount;
typedef struct FSARequestUnmountWithProcess FSARequestUnmountWithProcess;
typedef struct FSARequestWriteFile FSARequestWriteFile;
typedef struct FSARequestChangeOwner FSARequestChangeOwner;


typedef struct FSARequest FSARequest;
typedef struct FSAResponseRawOpen FSAResponseRawOpen;
typedef struct FSAResponseGetCwd FSAResponseGetCwd;
typedef struct FSAResponseGetFileBlockAddress FSAResponseGetFileBlockAddress;
typedef struct FSAResponseGetPosFile FSAResponseGetPosFile;
typedef struct FSAResponseGetVolumeInfo FSAResponseGetVolumeInfo;
typedef struct FSAResponseGetInfoByQuery FSAResponseGetInfoByQuery;
typedef struct FSAResponseOpenDir FSAResponseOpenDir;
typedef struct FSAResponseOpenFile FSAResponseOpenFile;
typedef struct FSAResponseReadDir FSAResponseReadDir;
typedef struct FSAResponseStatFile FSAResponseStatFile;

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

typedef enum FSAMountPriority {
    FSA_MOUNT_PRIORITY_BASE =             0x1,
    FSA_MOUNT_PRIORITY_RAM_DISK_CACHE =   0x4,
    FSA_MOUNT_PRIORITY_TITLE_UPDATE =     0x9,
    FSA_MOUNT_PRIORITY_UNMOUNT_ALL =      0x80000000,
} FSAMountPriority;

typedef enum FSAQueryInfoType {
    FSA_QUERY_INFO_FREE_SPACE_SIZE =         0x0,
    FSA_QUERY_INFO_DIR_SIZE =                0x1,
    FSA_QUERY_INFO_ENTRY_NUM =               0x2,
    FSA_QUERY_INFO_FILE_SYSTEM_INFO =        0x3,
    FSA_QUERY_INFO_DEVICE_INFO =             0x4,
    FSA_QUERY_INFO_STAT =                    0x5,
    FSA_QUERY_INFO_BAD_BLOCK_INFO =          0x6,
    FSA_QUERY_INFO_JOURNAL_FREE_SPACE_SIZE = 0x7,
    FSA_QUERY_INFO_FRAGMENT_BLOCK_INFO =     0x8,
} FSAQueryInfoType;

typedef enum FSAReadFlag {
    FSA_READ_FLAG_NONE          = 0x0,
    FSA_READ_FLAG_READ_WITH_POS = 0x1
} FSAReadFlag;

typedef enum FSAWriteFlag {
    FSA_WRITE_FLAG_NONE          = 0x0,
    FSA_WRITE_FLAG_READ_WITH_POS = 0x1
} FSAWriteFlag;

/**
 * Process information.
 */
struct FSAProcessInfo
{
    uint64_t titleId;
    uint32_t processId;
    uint32_t groupId;
};
WUT_CHECK_OFFSET(FSAProcessInfo, 0x00, titleId);
WUT_CHECK_OFFSET(FSAProcessInfo, 0x08, processId);
WUT_CHECK_OFFSET(FSAProcessInfo, 0x0C, groupId);
WUT_CHECK_SIZE(FSAProcessInfo, 0x10);

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

/**
 * Request data for Command::AppendFile
 */
struct FSARequestAppendFile
{
    uint32_t size;
    uint32_t count;
    FSAFileHandle handle;
    uint32_t unk0x0C;
};
WUT_CHECK_OFFSET(FSARequestAppendFile, 0x0, size);
WUT_CHECK_OFFSET(FSARequestAppendFile, 0x4, count);
WUT_CHECK_OFFSET(FSARequestAppendFile, 0x8, handle);
WUT_CHECK_OFFSET(FSARequestAppendFile, 0xC, unk0x0C);
WUT_CHECK_SIZE(FSARequestAppendFile, 0x10);

/**
 * Request data for Command::ChangeDir
 */
struct FSARequestChangeDir
{
    char path[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSARequestChangeDir, 0x0, path);
WUT_CHECK_SIZE(FSARequestChangeDir, 0x280);


/**
 * Request data for Command::ChangeMode
 */
struct FSARequestChangeMode
{
    char path[FS_MAX_PATH +1];
    uint32_t mode1;
    uint32_t mode2;
};
WUT_CHECK_OFFSET(FSARequestChangeMode, 0x0, path);
WUT_CHECK_OFFSET(FSARequestChangeMode, 0x280, mode1);
WUT_CHECK_OFFSET(FSARequestChangeMode, 0x284, mode2);
WUT_CHECK_SIZE(FSARequestChangeMode, 0x288);


/**
 * Request data for Command::CloseDir
 */
struct FSARequestCloseDir
{
    FSADirectoryHandle handle;
};
WUT_CHECK_OFFSET(FSARequestCloseDir, 0x0, handle);
WUT_CHECK_SIZE(FSARequestCloseDir, 0x4);


/**
 * Request data for Command::CloseFile
 */
struct FSARequestCloseFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestCloseFile, 0x0, handle);
WUT_CHECK_SIZE(FSARequestCloseFile, 0x4);


/**
 * Request data for Command::FlushFile
 */
struct FSARequestFlushFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestFlushFile, 0x0, handle);
WUT_CHECK_SIZE(FSARequestFlushFile, 0x4);


/**
 * Request data for Command::FlushQuota
 */
struct FSARequestFlushQuota
{
    char path[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSARequestFlushQuota, 0x0, path);
WUT_CHECK_SIZE(FSARequestFlushQuota, 0x280);


/**
 * Request data for Command::GetInfoByQuery
 */
struct FSARequestGetInfoByQuery
{
    char path[FS_MAX_PATH +1];
    FSAQueryInfoType type;
};
WUT_CHECK_OFFSET(FSARequestGetInfoByQuery, 0x0, path);
WUT_CHECK_OFFSET(FSARequestGetInfoByQuery, 0x280, type);
WUT_CHECK_SIZE(FSARequestGetInfoByQuery, 0x284);


/**
 * Request data for Command::GetPosFile
 */
struct FSARequestGetPosFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestGetPosFile, 0x0, handle);
WUT_CHECK_SIZE(FSARequestGetPosFile, 0x4);


/**
 * Request data for Command::IsEof
 */
struct FSARequestIsEof
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestIsEof, 0x0, handle);
WUT_CHECK_SIZE(FSARequestIsEof, 0x4);


/**
 * Request data for Command::MakeDir
 */
struct FSARequestMakeDir
{
    char path[FS_MAX_PATH +1];
    uint32_t permission;
};
WUT_CHECK_OFFSET(FSARequestMakeDir, 0x0, path);
WUT_CHECK_OFFSET(FSARequestMakeDir, 0x280, permission);
WUT_CHECK_SIZE(FSARequestMakeDir, 0x284);

/**
 * Request data for Command::MakeQuota
 */
struct WUT_PACKED FSARequestMakeQuota
{
    char path[FS_MAX_PATH +1];
    uint32_t mode;
    uint64_t size;
};
WUT_CHECK_OFFSET(FSARequestMakeQuota, 0x0, path);
WUT_CHECK_OFFSET(FSARequestMakeQuota, 0x280, mode);
WUT_CHECK_OFFSET(FSARequestMakeQuota, 0x284, size);
WUT_CHECK_SIZE(FSARequestMakeQuota, 0x28C);


/**
 * Request data for Command::Mount
 */
struct FSARequestMount
{
    char path[FS_MAX_PATH +1];
    char target[FS_MAX_PATH +1];
    uint32_t unk0x500;
    void* unkBuf;
    uint32_t unkBufLen;
};
WUT_CHECK_OFFSET(FSARequestMount, 0x0, path);
WUT_CHECK_OFFSET(FSARequestMount, 0x280, target);
WUT_CHECK_OFFSET(FSARequestMount, 0x500, unk0x500);
WUT_CHECK_OFFSET(FSARequestMount, 0x504, unkBuf);
WUT_CHECK_OFFSET(FSARequestMount, 0x508, unkBufLen);
WUT_CHECK_SIZE(FSARequestMount, 0x50C);


/**
 * Request data for Command::MountWithProcess
 */
struct WUT_PACKED FSARequestMountWithProcess
{
    char path[FS_MAX_PATH +1];
    char target[FS_MAX_PATH +1];
    FSAMountPriority priority;
    FSAProcessInfo process;
    void* unkBuf;
    uint32_t unkBufLen;
};
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x0, path);
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x280, target);
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x500, priority);
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x504, process);
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x514, unkBuf);
WUT_CHECK_OFFSET(FSARequestMountWithProcess, 0x518, unkBufLen);
WUT_CHECK_SIZE(FSARequestMountWithProcess, 0x51C);


/**
 * Request data for Command::OpenDir
 */
struct FSARequestOpenDir
{
    char path[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSARequestOpenDir, 0x0, path);
WUT_CHECK_SIZE(FSARequestOpenDir, 0x280);

/**
 * Request data for Command::OpenFile
 */
struct FSARequestOpenFile
{
    char path[FS_MAX_PATH +1];
    char mode[FS_MODE_LENGTH];
    uint32_t unk0x290;
    uint32_t unk0x294;
    uint32_t unk0x298;
};
WUT_CHECK_OFFSET(FSARequestOpenFile, 0x0, path);
WUT_CHECK_OFFSET(FSARequestOpenFile, 0x280, mode);
WUT_CHECK_OFFSET(FSARequestOpenFile, 0x290, unk0x290);
WUT_CHECK_OFFSET(FSARequestOpenFile, 0x294, unk0x294);
WUT_CHECK_OFFSET(FSARequestOpenFile, 0x298, unk0x298);
WUT_CHECK_SIZE(FSARequestOpenFile, 0x29C);


/**
 * Request data for Command::ReadDir
 */
struct FSARequestReadDir
{
    FSADirectoryHandle handle;
};
WUT_CHECK_OFFSET(FSARequestReadDir, 0x0, handle);
WUT_CHECK_SIZE(FSARequestReadDir, 0x4);


/**
 * Request data for Command::ReadFile
 */
struct FSARequestReadFile
{
    //! Virtual pointer used only by Cafe, for IOS we should use ioctlv.vecs[1]
    uint8_t* buffer;
    uint32_t size;
    uint32_t count;
    FSAFilePosition pos;
    FSAFileHandle handle;
    FSAReadFlag readFlags;
};
WUT_CHECK_OFFSET(FSARequestReadFile, 0x00, buffer);
WUT_CHECK_OFFSET(FSARequestReadFile, 0x04, size);
WUT_CHECK_OFFSET(FSARequestReadFile, 0x08, count);
WUT_CHECK_OFFSET(FSARequestReadFile, 0x0C, pos);
WUT_CHECK_OFFSET(FSARequestReadFile, 0x10, handle);
WUT_CHECK_OFFSET(FSARequestReadFile, 0x14, readFlags);
WUT_CHECK_SIZE(FSARequestReadFile, 0x18);


/**
 * Request data for Command::Remove
 */
struct FSARequestRemove
{
    char path[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSARequestRemove, 0x0, path);
WUT_CHECK_SIZE(FSARequestRemove, 0x280);


/**
 * Request data for Command::Rename
 */
struct FSARequestRename
{
    char oldPath[FS_MAX_PATH +1];
    char newPath[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSARequestRename, 0x0, oldPath);
WUT_CHECK_OFFSET(FSARequestRename, 0x280, newPath);
WUT_CHECK_SIZE(FSARequestRename, 0x500);


/**
 * Request data for Command::RewindDir
 */
struct FSARequestRewindDir
{
    FSADirectoryHandle handle;
};
WUT_CHECK_OFFSET(FSARequestRewindDir, 0x0, handle);
WUT_CHECK_SIZE(FSARequestRewindDir, 0x4);


/**
 * Request data for Command::SetPosFile
 */
struct FSARequestSetPosFile
{
    FSAFileHandle handle;
    FSAFilePosition pos;
};
WUT_CHECK_OFFSET(FSARequestSetPosFile, 0x0, handle);
WUT_CHECK_OFFSET(FSARequestSetPosFile, 0x4, pos);
WUT_CHECK_SIZE(FSARequestSetPosFile, 0x8);


/**
 * Request data for Command::StatFile
 */
struct FSARequestStatFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestStatFile, 0x0, handle);
WUT_CHECK_SIZE(FSARequestStatFile, 0x4);


/**
 * Request data for Command::TruncateFile
 */
struct FSARequestTruncateFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSARequestTruncateFile, 0x0, handle);
WUT_CHECK_SIZE(FSARequestTruncateFile, 0x4);


/**
 * Request data for Command::Unmount
 */
struct FSARequestUnmount
{
    char path[FS_MAX_PATH +1];
    uint32_t unk0x280;
};
WUT_CHECK_OFFSET(FSARequestUnmount, 0x0, path);
WUT_CHECK_OFFSET(FSARequestUnmount, 0x280, unk0x280);
WUT_CHECK_SIZE(FSARequestUnmount, 0x284);


/**
 * Request data for Command::UnmountWithProcess
 */
struct WUT_PACKED FSARequestUnmountWithProcess
{
    char path[FS_MAX_PATH +1];
    FSAMountPriority priority;
    FSAProcessInfo process;
};
WUT_CHECK_OFFSET(FSARequestUnmountWithProcess, 0x0, path);
WUT_CHECK_OFFSET(FSARequestUnmountWithProcess, 0x280, priority);
WUT_CHECK_OFFSET(FSARequestUnmountWithProcess, 0x284, process);
WUT_CHECK_SIZE(FSARequestUnmountWithProcess, 0x294);


/**
 * Request data for Command::WriteFile
 */
struct FSARequestWriteFile
{
    //! Virtual pointer used only by Cafe, for IOS we should use ioctlv.vecs[1]
    const uint8_t* buffer;
    uint32_t size;
    uint32_t count;
    FSAFilePosition pos;
    FSAFileHandle handle;
    FSAWriteFlag writeFlags;
};
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x00, buffer);
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x04, size);
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x08, count);
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x0C, pos);
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x10, handle);
WUT_CHECK_OFFSET(FSARequestWriteFile, 0x14, writeFlags);
WUT_CHECK_SIZE(FSARequestWriteFile, 0x18);

struct FSARequestChangeOwner
{
    char path[FS_MAX_PATH +1];
    WUT_UNKNOWN_BYTES(4);
    uint32_t owner;
    WUT_UNKNOWN_BYTES(4);
    uint32_t group;
};
WUT_CHECK_OFFSET(FSARequestChangeOwner, 0x0, path);
WUT_CHECK_OFFSET(FSARequestChangeOwner, 0x284, owner);
WUT_CHECK_OFFSET(FSARequestChangeOwner, 0x28C, group);
WUT_CHECK_SIZE(FSARequestChangeOwner, 0x290);

struct FSARequest {
    FSError emulatedError;

    union {
        FSARequestRawOpen rawOpen;
        FSARequestRawClose rawClose;
        FSARequestRawRead rawRead;
        FSARequestRawWrite rawWrite;
        FSARequestAppendFile appendFile;
        FSARequestChangeDir changeDir;
        FSARequestChangeMode changeMode;
        FSARequestCloseDir closeDir;
        FSARequestCloseFile closeFile;
        FSARequestFlushFile flushFile;
        FSARequestFlushQuota flushQuota;
        FSARequestGetInfoByQuery getInfoByQuery;
        FSARequestGetPosFile getPosFile;
        FSARequestIsEof isEof;
        FSARequestMakeDir makeDir;
        FSARequestMakeQuota makeQuota;
        FSARequestMount mount;
        FSARequestMountWithProcess mountWithProcess;
        FSARequestOpenDir openDir;
        FSARequestOpenFile openFile;
        FSARequestReadDir readDir;
        FSARequestReadFile readFile;
        FSARequestRemove remove;
        FSARequestRename rename;
        FSARequestRewindDir rewindDir;
        FSARequestSetPosFile setPosFile;
        FSARequestStatFile statFile;
        FSARequestTruncateFile truncateFile;
        FSARequestUnmount unmount;
        FSARequestUnmountWithProcess unmountWithProcess;
        FSARequestWriteFile writeFile;
        FSARequestChangeOwner changeOwner;
        WUT_UNKNOWN_BYTES(0x28C);
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

struct FSAResponseGetCwd
{
    char path[FS_MAX_PATH +1];
};
WUT_CHECK_OFFSET(FSAResponseGetCwd, 0x0, path);
WUT_CHECK_SIZE(FSAResponseGetCwd, 0x280);

struct FSAResponseGetFileBlockAddress
{
    uint32_t address;
};
WUT_CHECK_OFFSET(FSAResponseGetFileBlockAddress, 0x0, address);
WUT_CHECK_SIZE(FSAResponseGetFileBlockAddress, 0x4);

struct FSAResponseGetPosFile
{
    FSAFilePosition pos;
};
WUT_CHECK_OFFSET(FSAResponseGetPosFile, 0x0, pos);
WUT_CHECK_SIZE(FSAResponseGetPosFile, 0x4);

struct FSAResponseGetVolumeInfo
{
    FSAVolumeInfo volumeInfo;
};
WUT_CHECK_OFFSET(FSAResponseGetVolumeInfo, 0x0, volumeInfo);
WUT_CHECK_SIZE(FSAResponseGetVolumeInfo, 0x1BC);

struct WUT_PACKED FSAResponseGetInfoByQuery
{
    union WUT_PACKED {
        FSABlockInfo badBlockInfo;
        FSADeviceInfo deviceInfo;
        uint64_t dirSize;
        FSAEntryNum entryNum;
        FSAFileSystemInfo fileSystemInfo;
        FSABlockInfo fragmentBlockInfo;
        uint64_t freeSpaceSize;
        uint64_t journalFreeSpaceSize;
        FSAStat stat;
    };
};
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, badBlockInfo);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, deviceInfo);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, dirSize);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, entryNum);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, fragmentBlockInfo);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, freeSpaceSize);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, fileSystemInfo);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, journalFreeSpaceSize);
WUT_CHECK_OFFSET(FSAResponseGetInfoByQuery, 0x0, stat);
WUT_CHECK_SIZE(FSAResponseGetInfoByQuery, 0x64);

struct FSAResponseOpenFile
{
    FSAFileHandle handle;
};
WUT_CHECK_OFFSET(FSAResponseOpenFile, 0x0, handle);
WUT_CHECK_SIZE(FSAResponseOpenFile, 0x4);

struct FSAResponseOpenDir
{
    FSADirectoryHandle handle;
};
WUT_CHECK_OFFSET(FSAResponseOpenDir, 0x0, handle);
WUT_CHECK_SIZE(FSAResponseOpenDir, 0x4);

struct FSAResponseReadDir
{
    FSADirectoryEntry entry;
};
WUT_CHECK_OFFSET(FSAResponseReadDir, 0x0, entry);
WUT_CHECK_SIZE(FSAResponseReadDir, 0x164);

struct FSAResponseStatFile
{
    FSAStat stat;
};
WUT_CHECK_OFFSET(FSAResponseStatFile, 0x0, stat);
WUT_CHECK_SIZE(FSAResponseStatFile, 0x64);

struct WUT_PACKED FSAResponse {
    uint32_t word0;
    union WUT_PACKED {
        FSAResponseRawOpen rawOpen;
        FSAResponseGetCwd getCwd;
        FSAResponseGetFileBlockAddress getFileBlockAddress;
        FSAResponseGetPosFile getPosFile;
        FSAResponseGetVolumeInfo getVolumeInfo;
        FSAResponseGetInfoByQuery getInfoByQuery;
        FSAResponseOpenDir openDir;
        FSAResponseOpenFile openFile;
        FSAResponseReadDir readDir;
        FSAResponseStatFile statFile;
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
    FSA_COMMAND_GET_LAST_FAILED_VOLUME    = 0x6E,
    FSA_COMMAND_GET_VOLUME_EXISTENCE      = 0x6F,
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
