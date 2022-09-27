#pragma once
#include <wut.h>

/**
 * \defgroup sysapp_args SYSAPP Arguments
 * \ingroup sysapp
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t SYSArgID;
typedef uint32_t SYSArgType;

typedef struct SYSArgDataBlock SYSArgDataBlock;
typedef struct SYSCallerInfo SYSCallerInfo;
typedef struct SYSDeserializeArg SYSDeserializeArg;
typedef struct SYSStandardArgs SYSStandardArgs;
typedef struct SYSStandardArgsIn SYSStandardArgsIn;
typedef struct SYSStandardArgsOut SYSStandardArgsOut;

typedef void (*SYSDeserializeCallback)(SYSDeserializeArg *arg, void *userArg);

typedef enum SYSArgIDEnum
{
   SYS_ARG_ID_END       = 0x0,
   SYS_ARG_ID_ANCHOR    = 0x64,
   SYS_ARG_ID_RESULT    = 0x65,
   SYS_ARG_ID_URL       = 0xc8,
   SYS_ARG_ID_MIV_DATA  = 0x12c,
   SYS_ARG_ID_JOIN_PID  = 0x190,
} SYSArgIDEnum;

typedef enum SYSArgTypeEnum
{
   SYS_ARG_TYPE_UINT32  = 1,
   SYS_ARG_TYPE_UINT64  = 2,
   SYS_ARG_TYPE_DATA    = 3,
   SYS_ARG_TYPE_STRING  = 4,
} SYSArgTypeEnum;

struct SYSArgDataBlock
{
   SYSArgID id;
   SYSArgType type;
   union 
   {
      uint32_t uint32;
      uint64_t uint64;
      struct 
      {
         void *ptr;
         uint32_t size;
      } data;
      struct 
      {
         const char *ptr;
         uint32_t size;
      } string;
   };
};
WUT_CHECK_OFFSET(SYSArgDataBlock, 0x0, id);
WUT_CHECK_OFFSET(SYSArgDataBlock, 0x4, type);
WUT_CHECK_OFFSET(SYSArgDataBlock, 0x8, data);
WUT_CHECK_SIZE(SYSArgDataBlock, 0x10);

struct SYSCallerInfo
{
   uint32_t upid;
   WUT_PADDING_BYTES(0x4);
   uint64_t titleID;
};
WUT_CHECK_OFFSET(SYSCallerInfo, 0x0, upid);
WUT_CHECK_OFFSET(SYSCallerInfo, 0x8, titleID);
WUT_CHECK_SIZE(SYSCallerInfo, 0x10);

struct SYSDeserializeArg
{
   const char *argName;
   uint32_t size;
   void *data;
};
WUT_CHECK_OFFSET(SYSDeserializeArg, 0x0, argName);
WUT_CHECK_OFFSET(SYSDeserializeArg, 0x4, size);
WUT_CHECK_OFFSET(SYSDeserializeArg, 0x8, data);
WUT_CHECK_SIZE(SYSDeserializeArg, 0xC);

struct SYSStandardArgsOut
{
   const void *data;
   uint32_t size;
};
WUT_CHECK_OFFSET(SYSStandardArgsOut, 0x0, data);
WUT_CHECK_OFFSET(SYSStandardArgsOut, 0x4, size);
WUT_CHECK_SIZE(SYSStandardArgsOut, 0x8);

struct SYSStandardArgsIn
{
   const char *argString;
   uint32_t size;
};
WUT_CHECK_OFFSET(SYSStandardArgsIn, 0x0, argString);
WUT_CHECK_OFFSET(SYSStandardArgsIn, 0x4, size);
WUT_CHECK_SIZE(SYSStandardArgsIn, 0x8);

struct SYSStandardArgs
{
   void *anchorData;
   uint32_t anchorSize;
   void *resultData;
   uint32_t resultSize;
};
WUT_CHECK_OFFSET(SYSStandardArgs, 0x0, anchorData);
WUT_CHECK_OFFSET(SYSStandardArgs, 0x4, anchorSize);
WUT_CHECK_OFFSET(SYSStandardArgs, 0x8, resultData);
WUT_CHECK_OFFSET(SYSStandardArgs, 0xC, resultSize);
WUT_CHECK_SIZE(SYSStandardArgs, 0x10);

/**
 * Gets current arguments and caller information.
 * 
 * \param args
 * A pointer to one or more <tt>SYSArgDataBlock</tt>s with the \c id fields set to which
 * arguments should be read. The last block should be set to \c SYS_ARG_ID_END .
 * 
 * \param callerInfo
 * A pointer to write the caller information to.
 * 
 * \return
 * 0 on success.
 */
int32_t
SYSGetArguments(SYSArgDataBlock *args,
                SYSCallerInfo *callerInfo);

int32_t
SYSGetStandardArgs(SYSStandardArgs *stdArgs);

void
SYSClearSysArgs();

int32_t
SYSPackArgs();

int32_t
SYSSerializeSysArgs(const char *argName,
                    const void *data,
                    uint32_t size);

int32_t
SYSSerializeSysArgsToBuffer(char *buffer,
                            uint32_t *bytesWritten,
                            uint32_t bufferSize,
                            const char *argName,
                            const void *data,
                            uint32_t dataSize);

int32_t
SYSDeserializeSysArgs(SYSDeserializeCallback callback,
                      void *userArg);

int32_t
SYSDeserializeSysArgsFromBlock(void *block,
                               uint32_t blockSize,
                               SYSDeserializeCallback callback,
                               void *userArg);

int32_t
_SYSDirectlyReturnToCaller(SYSStandardArgsOut *arg);

int32_t
_SYSSerializeStandardArgsIn(SYSStandardArgsIn *arg);

BOOL
_SYSDeserializeStandardArg(SYSDeserializeArg *deserializeArg,
                           SYSStandardArgs *standardArg);

#ifdef __cplusplus
}
#endif

/** @} */
