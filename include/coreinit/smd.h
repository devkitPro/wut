#pragma once
#include <wut.h>
#include <coreinit/mutex.h>

/**
 * \defgroup coreinit_smd SMD
 * \ingroup coreinit
 *
 * IOS <-> PPC message dequeue
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SmdVectorSpec SmdVectorSpec;
typedef struct SmdVector SmdVector;
typedef struct SmdElement SmdElement;
typedef struct SmdReceiveData SmdReceiveData;
typedef struct SmdInterface SmdInterface;
typedef struct SmdCtrlTable SmdCtrlTable;
typedef struct SmdPpcCtrlTableVectors SmdPpcCtrlTableVectors;
typedef struct SmdPpc SmdPpc;
typedef struct SmdSimpleBufPool SmdSimpleBufPool;

typedef enum SmdLockType
{
    //! Locking is done with a mutex
    SMD_LOCK_TYPE_MUTEX                 = 0,
    //! Locking is done by disabling interrupts
    SMD_LOCK_TYPE_DISABLE_INTERRUPTS    = 1,
    //! No locking is done
    SMD_LOCK_TYPE_NONE                  = 2,
} SmdLockType;

typedef enum SmdPpcState
{
    SMD_PPC_STATE_INVALID       = 0,
    SMD_PPC_STATE_INITIALIZED   = 1,
    SMD_PPC_STATE_CLOSED        = 2,
    SMD_PPC_STATE_OPENED        = 3,
} SmdPpcState;

typedef enum SmdInterfaceState
{
    SMD_INTERFACE_STATE_OPENED = 0x2222,
    SMD_INTERFACE_STATE_CLOSED = 0x3333,
} SmdInterfaceState;

typedef enum SmdElementType
{
    SMD_ELEMENT_TYPE_MESSAGE        = 0,
    SMD_ELEMENT_TYPE_VECTOR_SPEC    = 1,
    SMD_ELEMENT_TYPE_VECTOR         = 2,
} SmdElementType;

struct SmdVectorSpec
{
    void *ptr;
    uint32_t size;
};
WUT_CHECK_OFFSET(SmdVectorSpec, 0x00, ptr);
WUT_CHECK_OFFSET(SmdVectorSpec, 0x04, size);
WUT_CHECK_SIZE(SmdVectorSpec, 0x8);

struct SmdVector
{
    uint32_t command;
    int32_t count;
    SmdVectorSpec vecs[4];
};
WUT_CHECK_OFFSET(SmdVector, 0x00, command);
WUT_CHECK_OFFSET(SmdVector, 0x04, count);
WUT_CHECK_OFFSET(SmdVector, 0x08, vecs);
WUT_CHECK_SIZE(SmdVector, 0x28);

struct SmdElement
{
    SmdElementType type;
    uint32_t size;
    union {
        uint8_t data[0xf8];
        SmdVector spec;
        uint32_t vectorPaddr;
    };
};
WUT_CHECK_OFFSET(SmdElement, 0x00, type);
WUT_CHECK_OFFSET(SmdElement, 0x04, size);
WUT_CHECK_OFFSET(SmdElement, 0x08, data);
WUT_CHECK_OFFSET(SmdElement, 0x08, spec);
WUT_CHECK_OFFSET(SmdElement, 0x08, vectorPaddr);
WUT_CHECK_SIZE(SmdElement, 0x100);

struct SmdReceiveData
{
    SmdElementType type;
    uint32_t size;
    union {
        uint8_t message[0x80];
        SmdVector spec;
        SmdVector *vector;
    };
};
WUT_CHECK_OFFSET(SmdReceiveData, 0x00, type);
WUT_CHECK_OFFSET(SmdReceiveData, 0x04, size);
WUT_CHECK_OFFSET(SmdReceiveData, 0x08, message);
WUT_CHECK_OFFSET(SmdReceiveData, 0x08, spec);
WUT_CHECK_OFFSET(SmdReceiveData, 0x08, vector);
WUT_CHECK_SIZE(SmdReceiveData, 0x88);

struct SmdInterface
{
    SmdInterfaceState state;
    WUT_PADDING_BYTES(0x7C);
    uint32_t elementCount;
    WUT_PADDING_BYTES(0x7C);
    int32_t readOffset;
    WUT_PADDING_BYTES(0x7C);
    int32_t writeOffset;
    WUT_PADDING_BYTES(0x7C);
    uint32_t bufPaddr;
    WUT_PADDING_BYTES(0x7C);
};
WUT_CHECK_OFFSET(SmdInterface, 0x000, state);
WUT_CHECK_OFFSET(SmdInterface, 0x080, elementCount);
WUT_CHECK_OFFSET(SmdInterface, 0x100, readOffset);
WUT_CHECK_OFFSET(SmdInterface, 0x180, writeOffset);
WUT_CHECK_OFFSET(SmdInterface, 0x200, bufPaddr);
WUT_CHECK_SIZE(SmdInterface, 0x280);

struct SmdCtrlTable
{
    char name[0x10];
    uint32_t reusedCount;
    WUT_PADDING_BYTES(0x6C);
    SmdInterface iopInterface;
    WUT_PADDING_BYTES(0x40);
    SmdInterface ppcInterface;
    WUT_PADDING_BYTES(0x40);
};
WUT_CHECK_OFFSET(SmdCtrlTable, 0x000, name);
WUT_CHECK_OFFSET(SmdCtrlTable, 0x010, reusedCount);
WUT_CHECK_OFFSET(SmdCtrlTable, 0x080, iopInterface);
WUT_CHECK_OFFSET(SmdCtrlTable, 0x340, ppcInterface);
WUT_CHECK_SIZE(SmdCtrlTable, 0x600);

struct SmdPpcCtrlTableVectors
{
    SmdCtrlTable *ctrlTable;
    uint32_t ctrlTableSize;
    SmdElement *writeBuf;
    uint32_t writeBufSize;
    SmdElement *readBuf;
    uint32_t readBufSize;
};
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x00, ctrlTable);
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x04, ctrlTableSize);
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x08, writeBuf);
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x0C, writeBufSize);
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x10, readBuf);
WUT_CHECK_OFFSET(SmdPpcCtrlTableVectors, 0x14, readBufSize);
WUT_CHECK_SIZE(SmdPpcCtrlTableVectors, 0x18);

struct SmdPpc
{
    SmdPpc *self;
    SmdCtrlTable *ctrlTable;
    SmdLockType lockType;
    OSMutex mutex;
    uint32_t messageCount;
    SmdElement *writeBuf;
    SmdElement *readBuf;
    SmdPpcState state;
    WUT_PADDING_BYTES(0x38);
};
WUT_CHECK_OFFSET(SmdPpc, 0x00, self);
WUT_CHECK_OFFSET(SmdPpc, 0x04, ctrlTable);
WUT_CHECK_OFFSET(SmdPpc, 0x08, lockType);
WUT_CHECK_OFFSET(SmdPpc, 0x0C, mutex);
WUT_CHECK_OFFSET(SmdPpc, 0x38, messageCount);
WUT_CHECK_OFFSET(SmdPpc, 0x3C, writeBuf);
WUT_CHECK_OFFSET(SmdPpc, 0x40, readBuf);
WUT_CHECK_OFFSET(SmdPpc, 0x44, state);
WUT_CHECK_SIZE(SmdPpc, 0x80);

struct SmdSimpleBufPool
{
    SmdSimpleBufPool *self;
    OSMutex mutex;
    void *poolData;
    uint32_t poolDataSize;
    SmdLockType lockType;
    uint32_t allocSize;
    uint32_t realAllocSize;
    uint32_t maxAllocCount;
    void *allocPoolStart;
    void *allocPoolEnd;
    uint32_t elementsIn;
    uint32_t freeErrorCount;
    WUT_PADDING_BYTES(0x28);
};
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x00, self);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x04, mutex);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x30, poolData);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x34, poolDataSize);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x38, lockType);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x3C, allocSize);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x40, realAllocSize);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x44, maxAllocCount);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x48, allocPoolStart);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x4C, allocPoolEnd);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x50, elementsIn);
WUT_CHECK_OFFSET(SmdSimpleBufPool, 0x54, freeErrorCount);
WUT_CHECK_SIZE(SmdSimpleBufPool, 0x80);

SmdPpc *
smdPpcInit(void *buf,
           uint32_t bufSize,
           uint32_t messageCount,
           const char *name,
           SmdLockType lockType);

int32_t
smdPpcGetCtrlTableVectors(SmdPpc *smd,
                          SmdPpcCtrlTableVectors *outVectors);

int32_t
smdPpcOpen(SmdPpc *smd);

int32_t
smdPpcClose(SmdPpc *smd);

int32_t
smdPpcGetInterfaceState(SmdPpc *smd,
                        SmdInterfaceState *outPpcState,
                        SmdInterfaceState *outIopState);

int32_t
smdPpcReceive(SmdPpc *smd,
              SmdReceiveData *data);

int32_t
smdPpcSendMessage(SmdPpc *smd,
                  void *message,
                  uint32_t messageSize);

int32_t
smdPpcSendVectorSpec(SmdPpc *smd,
                     uint32_t command,
                     SmdVectorSpec *specs,
                     int32_t specsCount);

int32_t
smdPpcSendVector(SmdPpc *smd,
                 SmdVector *vector);

SmdSimpleBufPool *
smdSimpleBufPoolCreate(void *poolData,
                       uint32_t poolDataSize,
                       uint32_t allocSize,
                       uint32_t allocCount,
                       SmdLockType lockType);

int32_t
smdSimpleBufAlloc(SmdSimpleBufPool *pool,
                  void **outAlloc);

int32_t
smdSimpleBufFree(SmdSimpleBufPool *pool,
                 void *alloc);

int32_t
smdSimpleBufGetStatistics(SmdSimpleBufPool *pool,
                          uint32_t *allocCount,
                          uint32_t *freeErrorCount);

#ifdef __cplusplus
}
#endif

/** @} */
