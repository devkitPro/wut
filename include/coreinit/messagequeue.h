#pragma once
#include <wut.h>
#include "threadqueue.h"

/**
 * \defgroup coreinit_msgq Message Queue
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSMessage OSMessage;
typedef struct OSMessageQueue OSMessageQueue;

typedef enum OSMessageFlags
{
   OS_MESSAGE_FLAGS_NONE            = 0,
   OS_MESSAGE_FLAGS_BLOCKING        = 1 << 0,
   OS_MESSAGE_FLAGS_HIGH_PRIORITY   = 1 << 1,
} OSMessageFlags;

typedef enum OSFunctionType
{
  OS_FUNCTION_TYPE_HIO_OPEN                     = 1,
  OS_FUNCTION_TYPE_HIO_READ_ASYNC               = 2,
  OS_FUNCTION_TYPE_HIO_WRITE_ASYNC              = 3,
  OS_FUNCTION_TYPE_FSA_CMD_ASYNC                = 4,
  OS_FUNCTION_TYPE_FSA_PR_CMD_ASYNC             = 5,
  OS_FUNCTION_TYPE_FSA_PR_CMD_ASYNC_NO_ALLOC    = 6,
  OS_FUNCTION_TYPE_FSA_ATTACH_EVENT             = 7,
  OS_FUNCTION_TYPE_FS_CMD_ASYNC                 = 8,
  OS_FUNCTION_TYPE_FS_CMD_HANDLER               = 9,
  OS_FUNCTION_TYPE_FS_ATTACH_EVENT              = 10,
  OS_FUNCTION_TYPE_FS_STATE_CHANGE_EVENT        = 11,
} OSFunctionType;

struct OSMessage
{
   void *message;
   uint32_t args[3];
};
WUT_CHECK_OFFSET(OSMessage, 0x00, message);
WUT_CHECK_OFFSET(OSMessage, 0x04, args);
WUT_CHECK_SIZE(OSMessage, 0x10);

#define OS_MESSAGE_QUEUE_TAG 0x6D536751u

struct OSMessageQueue
{
   uint32_t tag;
   const char *name;
   WUT_UNKNOWN_BYTES(4);
   OSThreadQueue sendQueue;
   OSThreadQueue recvQueue;
   OSMessage *messages;
   uint32_t size;
   uint32_t first;
   uint32_t used;
};
WUT_CHECK_OFFSET(OSMessageQueue, 0x00, tag);
WUT_CHECK_OFFSET(OSMessageQueue, 0x04, name);
WUT_CHECK_OFFSET(OSMessageQueue, 0x0c, sendQueue);
WUT_CHECK_OFFSET(OSMessageQueue, 0x1c, recvQueue);
WUT_CHECK_OFFSET(OSMessageQueue, 0x2c, messages);
WUT_CHECK_OFFSET(OSMessageQueue, 0x30, size);
WUT_CHECK_OFFSET(OSMessageQueue, 0x34, first);
WUT_CHECK_OFFSET(OSMessageQueue, 0x38, used);
WUT_CHECK_SIZE(OSMessageQueue, 0x3c);

void
OSInitMessageQueue(OSMessageQueue *queue,
                   OSMessage *messages,
                   int32_t size);

void
OSInitMessageQueueEx(OSMessageQueue *queue,
                     OSMessage *messages,
                     int32_t size,
                     const char *name);

BOOL
OSSendMessage(OSMessageQueue *queue,
              OSMessage *message,
              OSMessageFlags flags);

BOOL
OSReceiveMessage(OSMessageQueue *queue,
                 OSMessage *message,
                 OSMessageFlags flags);

BOOL
OSPeekMessage(OSMessageQueue *queue,
              OSMessage *message);

OSMessageQueue *
OSGetSystemMessageQueue();

#ifdef __cplusplus
}
#endif

/** @} */
