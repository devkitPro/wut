#pragma once

#include <wut.h>
#include "mutex.h"
#include "ios.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IPCBufPoolAttributes IPCBufPoolAttributes;
typedef struct IPCBufPoolFIFO IPCBufPoolFIFO;
typedef struct IPCBufPool IPCBufPool;

/**
* FIFO queue for IPCBufPool.
*
* Functions similar to a ring buffer.
*/
struct IPCBufPoolFIFO {
    //! The current message index to push to.
    int32_t pushIndex;

    //! The current message index to pop from.
    int32_t popIndex;

    //! The number of messages in the queue.
    int32_t count;

    //! Tracks the total number of messages in the count.
    int32_t maxCount;

    //! Messages in the queue.
    void **messages;
};
WUT_CHECK_OFFSET(IPCBufPoolFIFO, 0x00, pushIndex);
WUT_CHECK_OFFSET(IPCBufPoolFIFO, 0x04, popIndex);
WUT_CHECK_OFFSET(IPCBufPoolFIFO, 0x08, count);
WUT_CHECK_OFFSET(IPCBufPoolFIFO, 0x0C, maxCount);
WUT_CHECK_OFFSET(IPCBufPoolFIFO, 0x10, messages);
WUT_CHECK_SIZE(IPCBufPoolFIFO, 0x14);

/**
 * Attributes returned by IPCBufPoolGetAttributes.
 */
struct IPCBufPoolAttributes {
    //! Size of a message in the buffer pool.
    uint32_t messageSize;

    //! Size of the buffer pool.
    uint32_t poolSize;

    //! Number of pending messages in the pool fifo.
    uint32_t numMessages;
};
WUT_CHECK_OFFSET(IPCBufPoolAttributes, 0x00, messageSize);
WUT_CHECK_OFFSET(IPCBufPoolAttributes, 0x04, poolSize);
WUT_CHECK_OFFSET(IPCBufPoolAttributes, 0x08, numMessages);
WUT_CHECK_SIZE(IPCBufPoolAttributes, 0x0C);

#define IPC_BUF_POOL_MAGIC 0x0BADF00Du

/**
* A simple message buffer pool used for IPC communication.
*/
struct IPCBufPool {
    //! Magic header always set to IPCBufPool::MagicHeader.
    uint32_t magic;

    //! Pointer to buffer used for this IPCBufPool.
    void *buffer;

    //! Size of buffer.
    uint32_t size;

    uint32_t unk0x0C;
    uint32_t unk0x10;

    //! Message size from IPCBufPoolCreate.
    uint32_t messageSize0x14;

    //! Message size from IPCBufPoolCreate.
    uint32_t messageSize0x18;

    //! Number of messages in the IPCBufPoolFIFO.
    uint32_t messageCount;

    //! Pointer to start of messages.
    void *messages;

    //! Number of bytes used for the message pointers in IPCBufPoolFIFO.
    uint32_t *messageIndexSize;

    //! FIFO queue of messages.
    IPCBufPoolFIFO fifo;

    //! Mutex used to secure access to fifo.
    OSMutex mutex;

    WUT_UNKNOWN_BYTES(0x04);
};
WUT_CHECK_OFFSET(IPCBufPool, 0x00, magic);
WUT_CHECK_OFFSET(IPCBufPool, 0x04, buffer);
WUT_CHECK_OFFSET(IPCBufPool, 0x08, size);
WUT_CHECK_OFFSET(IPCBufPool, 0x0C, unk0x0C);
WUT_CHECK_OFFSET(IPCBufPool, 0x10, unk0x10);
WUT_CHECK_OFFSET(IPCBufPool, 0x14, messageSize0x14);
WUT_CHECK_OFFSET(IPCBufPool, 0x18, messageSize0x18);
WUT_CHECK_OFFSET(IPCBufPool, 0x1C, messageCount);
WUT_CHECK_OFFSET(IPCBufPool, 0x20, messages);
WUT_CHECK_OFFSET(IPCBufPool, 0x24, messageIndexSize);
WUT_CHECK_OFFSET(IPCBufPool, 0x28, fifo);
WUT_CHECK_OFFSET(IPCBufPool, 0x3C, mutex);
WUT_CHECK_SIZE(IPCBufPool, 0x6C);

IPCBufPool *
IPCBufPoolCreate(void *buffer,
                 uint32_t size,
                 uint32_t messageSize,
                 uint32_t *outNumMessages,
                 uint32_t unk0x0c);

void *
IPCBufPoolAllocate(IPCBufPool *pool,
                   uint32_t size);

IOSError
IPCBufPoolFree(IPCBufPool *pool,
               void *message);

IOSError
IPCBufPoolGetAttributes(IPCBufPool *pool,
                        IPCBufPoolAttributes *attribs);


#ifdef __cplusplus
}
#endif