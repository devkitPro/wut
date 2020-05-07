#pragma once
#include <wut.h>
#include <coreinit/ios.h>

/**
 * \defgroup coreinit_userconfig User Config
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t UCError;
typedef struct UCSysConfig UCSysConfig;
typedef struct UCAsyncParams UCAsyncParams;

typedef enum UCCommand
{
   UC_CMD_READ_SYS_CONFIG        = 0x30,
   UC_CMD_WRITE_SYS_CONFIG       = 0x31,
   UC_CMD_DELETE_SYS_CONFIG      = 0x32,
   UC_CMD_QUERY_SYS_CONFIG       = 0x33,
   UC_CMD_LIST_SYS_CONFIG        = 0x34,
} UCCommand;

typedef enum UCDataType
{
   UC_DATATYPE_UNDEFINED         = 0x00,
   UC_DATATYPE_UNSIGNED_BYTE     = 0x01,
   UC_DATATYPE_UNSIGNED_SHORT    = 0x02,
   UC_DATATYPE_UNSIGNED_INT      = 0x03,
   UC_DATATYPE_SIGNED_INT        = 0x04,
   UC_DATATYPE_FLOAT             = 0x05,
   UC_DATATYPE_STRING            = 0x06,
   UC_DATATYPE_HEXBINARY         = 0x07,
   UC_DATATYPE_COMPLEX           = 0x08,
   UC_DATATYPE_INVALID           = 0xFF,
} UCDataType;

typedef enum UCErrors
{
   UC_ERROR_OK                   = 0,
   UC_ERROR_ERROR                = -1,
   UC_ERROR_OTHER                = -0x200001,
   UC_ERROR_SYSTEM               = -0x200002,
   UC_ERROR_ALLOC                = -0x200003,
   UC_ERROR_OPCODE               = -0x200004,
   UC_ERROR_INVALID_PARAM        = -0x200005,
   UC_ERROR_INVALID_TYPE         = -0x200006,
   UC_ERROR_UNSUPPORTED          = -0x200007,
   UC_ERROR_NON_LEAF_NODE        = -0x200008,
   UC_ERROR_KEY_NOT_FOUND        = -0x200009,
   UC_ERROR_MODIFY               = -0x20000A,
   UC_ERROR_STRING_TOO_LONG      = -0x20000B,
   UC_ERROR_ROOT_KEYS_DIFFER     = -0x20000C,
   UC_ERROR_INVALID_LOCATION     = -0x20000D,
   UC_ERROR_BAD_COMMENT          = -0x20000E,
   UC_ERROR_READ_ACCESS          = -0x20000F,
   UC_ERROR_WRITE_ACCESS         = -0x200010,
   UC_ERROR_CREATE_ACCESS        = -0x200011,
   UC_ERROR_FILE_SYS_NAME        = -0x200012,
   UC_ERROR_FILE_SYS_INIT        = -0x200013,
   UC_ERROR_FILE_SYS_MOUNT       = -0x200014,
   UC_ERROR_FILE_OPEN            = -0x200015,
   UC_ERROR_FILE_STAT            = -0x200016,
   UC_ERROR_FILE_READ            = -0x200017,
   UC_ERROR_FILE_WRITE           = -0x200018,
   UC_ERROR_FILE_TOO_BIG         = -0x200019,
   UC_ERROR_FILE_REMOVE          = -0x20001A,
   UC_ERROR_FILE_RENAME          = -0x20001B,
   UC_ERROR_FILE_CLOSE           = -0x20001C,
   UC_ERROR_FILE_SEEK            = -0x20001D,
   UC_ERROR_FILE_CONFIRM         = -0x20001E,
   UC_ERROR_FILE_BACKUP          = -0x20001F,
   UC_ERROR_MALFORMED_XML        = -0x200020,
   UC_ERROR_VERSION              = -0x200021,
   UC_ERROR_NO_IPC_BUFFERS       = -0x200022,
   UC_ERROR_FILE_LOCK_NEEDED     = -0x200024,
   UC_ERROR_SYS_PROT             = -0x200028,
} UCErrors;

typedef enum UCFileSys
{
   UC_FILE_SYS_INVALID           = 0x00,
   UC_FILE_SYS_SYS               = 0x01,
   UC_FILE_SYS_SLC               = 0x02,
   UC_FILE_SYS_RAM               = 0x03,
} UCFileSys;

#pragma pack(push, 1)
struct UCSysConfig
{
   char name[64];
   uint32_t access;
   UCDataType dataType;
   UCError error;
   uint32_t dataSize;
   void *data;
};
#pragma pack(pop)
WUT_CHECK_OFFSET(UCSysConfig, 0x00, name);
WUT_CHECK_OFFSET(UCSysConfig, 0x40, access);
WUT_CHECK_OFFSET(UCSysConfig, 0x44, dataType);
WUT_CHECK_OFFSET(UCSysConfig, 0x48, error);
WUT_CHECK_OFFSET(UCSysConfig, 0x4C, dataSize);
WUT_CHECK_OFFSET(UCSysConfig, 0x50, data);
WUT_CHECK_SIZE(UCSysConfig, 0x54);

typedef void (*UCAsyncCallbackFn)(UCError result,
                                  UCCommand command,
                                  uint32_t count,
                                  UCSysConfig *settings,
                                  void *context);
#pragma pack(push, 1)
struct UCAsyncParams
{
    UCAsyncCallbackFn callback;
    void *context;
    UCCommand command;
    uint32_t unk0x0C;
    uint32_t count;
    UCSysConfig *settings;
    IOSVec *vecs;
};
#pragma pack(pop)
WUT_CHECK_OFFSET(UCAsyncParams, 0x00, callback);
WUT_CHECK_OFFSET(UCAsyncParams, 0x04, context);
WUT_CHECK_OFFSET(UCAsyncParams, 0x08, command);
WUT_CHECK_OFFSET(UCAsyncParams, 0x0C, unk0x0C);
WUT_CHECK_OFFSET(UCAsyncParams, 0x10, count);
WUT_CHECK_OFFSET(UCAsyncParams, 0x14, settings);
WUT_CHECK_OFFSET(UCAsyncParams, 0x18, vecs);
WUT_CHECK_SIZE(UCAsyncParams, 0x1C);

UCError
UCOpen();

UCError
UCClose(IOSHandle handle);

UCError
UCDeleteSysConfig(int32_t handle,
                  uint32_t count,
                  UCSysConfig *settings);

UCError
UCDeleteSysConfigAsync(int32_t handle,
                       uint32_t count,
                       UCSysConfig *settings,
                       UCAsyncParams *asyncParams);

UCError
UCReadSysConfig(int32_t handle,
                uint32_t count,
                UCSysConfig *settings);

UCError
UCReadSysConfigAsync(int32_t handle,
                     uint32_t count,
                     UCSysConfig *settings,
                     UCAsyncParams *asyncParams);

UCError
UCWriteSysConfig(int32_t handle,
                 uint32_t count,
                 UCSysConfig *settings);

UCError
UCWriteSysConfigAsync(int32_t handle,
                      uint32_t count,
                      UCSysConfig *settings,
                      UCAsyncParams *asyncParams);

#ifdef __cplusplus
}
#endif

/** @} */
