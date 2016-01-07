#pragma once
#include <wut.h>
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSemaphore OSSemaphore;

#define OS_SEMAPHORE_TAG 0x73506852u

struct OSSemaphore
{
   uint32_t tag;
   const char *name;
   UNKNOWN(4);
   int32_t count;
   OSThreadQueue queue;
};
CHECK_OFFSET(OSSemaphore, 0x00, tag);
CHECK_OFFSET(OSSemaphore, 0x04, name);
CHECK_OFFSET(OSSemaphore, 0x0C, count);
CHECK_OFFSET(OSSemaphore, 0x10, queue);
CHECK_SIZE(OSSemaphore, 0x20);

void
OSInitSemaphore(OSSemaphore *semaphore,
                int32_t count);

void
OSInitSemaphoreEx(OSSemaphore *semaphore,
                  int32_t count,
                  const char *name);

int32_t
OSGetSemaphoreCount(OSSemaphore *semaphore);

int32_t
OSSignalSemaphore(OSSemaphore *semaphore);

int32_t
OSWaitSemaphore(OSSemaphore *semaphore);

int32_t
OSTryWaitSemaphore(OSSemaphore *semaphore);

#ifdef __cplusplus
}
#endif
