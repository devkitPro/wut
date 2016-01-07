#pragma once
#include <wut.h>
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OSThread;

typedef struct OSCondition OSCondition;
typedef struct OSMutex OSMutex;
typedef struct OSMutexLink OSMutexLink;

struct OSMutexLink
{
   OSMutex *next;
   OSMutex *prev;
};
CHECK_OFFSET(OSMutexLink, 0x00, next);
CHECK_OFFSET(OSMutexLink, 0x04, prev);
CHECK_SIZE(OSMutexLink, 0x8);

struct OSMutex
{
   static const uint32_t Tag = 0x6D557458;

   // OSMutex::Tag
   uint32_t tag;

   // Name set by OSInitMutexEx(mutex, name)
   const char *name;
   UNKNOWN(4);

   // Queue of threads waiting for this mutex to unlock
   OSThreadQueue queue;

   // Current owner of mutex
   OSThread *owner;

   // Current recursion lock count of mutex
   int32_t count;

   // Link used inside OSThread's mutex queue
   OSMutexLink link;
};
CHECK_OFFSET(OSMutex, 0x00, tag);
CHECK_OFFSET(OSMutex, 0x04, name);
CHECK_OFFSET(OSMutex, 0x0c, queue);
CHECK_OFFSET(OSMutex, 0x1c, owner);
CHECK_OFFSET(OSMutex, 0x20, count);
CHECK_OFFSET(OSMutex, 0x24, link);
CHECK_SIZE(OSMutex, 0x2c);

struct OSCondition
{
   static const uint32_t Tag = 0x634E6456;

   // OSCondition::Tag
   uint32_t tag;

   // Name set by OSInitCondEx(condition, name)
   const char *name;

   UNKNOWN(4);

   // Queue of threads waiting on condition
   OSThreadQueue queue;
};
CHECK_OFFSET(OSCondition, 0x00, tag);
CHECK_OFFSET(OSCondition, 0x04, name);
CHECK_OFFSET(OSCondition, 0x0c, queue);
CHECK_SIZE(OSCondition, 0x1c);

void
OSInitMutex(OSMutex *mutex);

void
OSInitMutexEx(OSMutex *mutex,
              const char *name);

void
OSLockMutex(OSMutex *mutex);

void
OSLockMutexNoLock(OSMutex *mutex);

void
OSUnlockMutex(OSMutex *mutex);

void
OSUnlockMutexNoLock(OSMutex *mutex);

BOOL
OSTryLockMutex(OSMutex *mutex);

#ifdef __cplusplus
}
#endif
