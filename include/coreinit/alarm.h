#pragma once
#include <wut.h>
#include "thread.h"
#include "threadqueue.h"
#include "time.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OSThread;

typedef struct OSAlarm OSAlarm;
typedef struct OSAlarmLink OSAlarmLink;
typedef struct OSAlarmQueue OSAlarmQueue;

typedef void (*OSAlarmCallback)(OSAlarm *, OSContext *);

#define OS_ALARM_QUEUE_TAG 0x614C6D51u

struct OSAlarmQueue
{
   // OS_ALARM_QUEUE_TAG
   uint32_t tag;
   const char *name;
   UNKNOWN(4);
   OSThreadQueue threadQueue;
   OSAlarm *head;
   OSAlarm *tail;
};
CHECK_OFFSET(OSAlarmQueue, 0x00, tag);
CHECK_OFFSET(OSAlarmQueue, 0x04, name);
CHECK_OFFSET(OSAlarmQueue, 0x0c, threadQueue);
CHECK_OFFSET(OSAlarmQueue, 0x1c, head);
CHECK_OFFSET(OSAlarmQueue, 0x20, tail);
CHECK_SIZE(OSAlarmQueue, 0x24);

struct OSAlarmLink
{
   OSAlarm *prev;
   OSAlarm *next;
};
CHECK_OFFSET(OSAlarmLink, 0x00, prev);
CHECK_OFFSET(OSAlarmLink, 0x04, next);
CHECK_SIZE(OSAlarmLink, 0x08);

#define OS_ALARM_TAG 0x614C724Du
struct OSAlarm
{
   // OS_ALARM_TAG
   uint32_t tag;
   const char *name;
   UNKNOWN(4);
   OSAlarmCallback callback;
   uint32_t group;
   UNKNOWN(4);
   OSTime nextFire;
   OSAlarmLink link;
   OSTime period;
   OSTime tbrStart;
   void *userData;
   uint32_t state;
   OSThreadQueue threadQueue;
   OSAlarmQueue *alarmQueue;
   OSContext *context;
};
CHECK_OFFSET(OSAlarm, 0x00, tag);
CHECK_OFFSET(OSAlarm, 0x04, name);
CHECK_OFFSET(OSAlarm, 0x0c, callback);
CHECK_OFFSET(OSAlarm, 0x10, group);
CHECK_OFFSET(OSAlarm, 0x18, nextFire);
CHECK_OFFSET(OSAlarm, 0x20, link);
CHECK_OFFSET(OSAlarm, 0x28, period);
CHECK_OFFSET(OSAlarm, 0x30, tbrStart);
CHECK_OFFSET(OSAlarm, 0x38, userData);
CHECK_OFFSET(OSAlarm, 0x3c, state);
CHECK_OFFSET(OSAlarm, 0x40, threadQueue);
CHECK_OFFSET(OSAlarm, 0x50, alarmQueue);
CHECK_OFFSET(OSAlarm, 0x54, context);
CHECK_SIZE(OSAlarm, 0x58);

BOOL
OSCancelAlarm(OSAlarm *alarm);

void
OSCancelAlarms(uint32_t group);

void
OSCreateAlarm(OSAlarm *alarm);

void
OSCreateAlarmEx(OSAlarm *alarm,
                const char *name);

void *
OSGetAlarmUserData(OSAlarm *alarm);

void
OSInitAlarmQueue(OSAlarmQueue *queue);

BOOL
OSSetAlarm(OSAlarm *alarm,
           OSTime time,
           AlarmCallback callback);

BOOL
OSSetPeriodicAlarm(OSAlarm *alarm,
                   OSTime start,
                   OSTime interval,
                   AlarmCallback callback);

void
OSSetAlarmTag(OSAlarm *alarm,
              uint32_t group);

void
OSSetAlarmUserData(OSAlarm *alarm,
                   void *data);

BOOL
OSWaitAlarm(OSAlarm *alarm);

#ifdef __cplusplus
}
#endif
