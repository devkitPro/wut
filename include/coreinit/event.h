#pragma once
#include <wut.h>
#include "thread.h"
#include "threadqueue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSEvent OSEvent;
typedef uint32_t OSEventMode;

enum OSEventMode
{
   OS_EVENT_MODE_MANUAL    = 0,
   OS_EVENT_MODE_AUTO      = 1,
};

#define OS_EVENT_TAG 0x65566E54u

struct OSEvent
{
   uint32_t tag;
   const char *name;
   UNKNOWN(4);
   BOOL value;
   OSThreadQueue queue;
   OSEventMode mode;
};
CHECK_OFFSET(OSEvent, 0x0, tag);
CHECK_OFFSET(OSEvent, 0x4, name);
CHECK_OFFSET(OSEvent, 0xc, value);
CHECK_OFFSET(OSEvent, 0x10, queue);
CHECK_OFFSET(OSEvent, 0x20, mode);
CHECK_SIZE(OSEvent, 0x24);

#pragma pack(pop)

void
OSInitEvent(OSEvent *event,
            BOOL value,
            OSEventMode mode);

void
OSInitEventEx(OSEvent *event,
              BOOL value,
              OSEventMode mode,
              char *name);

void
OSSignalEvent(OSEvent *event);

void
OSSignalEventAll(OSEvent *event);

void
OSWaitEvent(OSEvent *event);

void
OSResetEvent(OSEvent *event);

BOOL
OSWaitEventWithTimeout(OSEvent *event,
                       OSTime timeout);

#ifdef __cplusplus
}
#endif
