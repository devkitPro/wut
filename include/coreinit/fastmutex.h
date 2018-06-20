#pragma once
#include <wut.h>
#include "threadqueue.h"

/**
 * \defgroup coreinit_fastmutex Fast Mutex
 * \ingroup coreinit
 *
 * Similar to OSMutex but tries to acquire the mutex without using the global
 * scheduler lock, and does not test for thread cancel.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSFastMutex OSFastMutex;
typedef struct OSFastMutexLink OSFastMutexLink;
typedef struct OSFastCondition OSFastCondition;

struct OSFastMutexLink
{
   OSFastMutex *next;
   OSFastMutex *prev;
};
WUT_CHECK_OFFSET(OSFastMutexLink, 0x00, next);
WUT_CHECK_OFFSET(OSFastMutexLink, 0x04, prev);
WUT_CHECK_SIZE(OSFastMutexLink, 0x08);

#define OS_FAST_MUTEX_TAG 0x664D7458u

struct OSFastMutex
{
   uint32_t tag;
   const char *name;
   WUT_UNKNOWN_BYTES(4);
   OSThreadSimpleQueue queue;
   OSFastMutexLink link;
   WUT_UNKNOWN_BYTES(16);
};
WUT_CHECK_OFFSET(OSFastMutex, 0x00, tag);
WUT_CHECK_OFFSET(OSFastMutex, 0x04, name);
WUT_CHECK_OFFSET(OSFastMutex, 0x0c, queue);
WUT_CHECK_OFFSET(OSFastMutex, 0x14, link);
WUT_CHECK_SIZE(OSFastMutex, 0x2c);

void
OSFastMutex_Init(OSFastMutex *mutex,
                 const char *name);

void
OSFastMutex_Lock(OSFastMutex *mutex);

void
OSFastMutex_Unlock(OSFastMutex *mutex);

BOOL
OSFastMutex_TryLock(OSFastMutex *mutex);

#ifdef __cplusplus
}
#endif

/** @} */
