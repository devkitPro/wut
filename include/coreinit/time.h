#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSCalendarTime OSCalendarTime;

typedef int32_t OSTick;
typedef int64_t OSTime;

struct OSCalendarTime
{
   int32_t tm_sec;
   int32_t tm_min;
   int32_t tm_hour;
   int32_t tm_mday;
   int32_t tm_mon;
   int32_t tm_year;
};
CHECK_OFFSET(OSCalendarTime, 0x00, tm_sec);
CHECK_OFFSET(OSCalendarTime, 0x04, tm_min);
CHECK_OFFSET(OSCalendarTime, 0x08, tm_hour);
CHECK_OFFSET(OSCalendarTime, 0x0C, tm_mday);
CHECK_OFFSET(OSCalendarTime, 0x10, tm_mon);
CHECK_OFFSET(OSCalendarTime, 0x14, tm_year);
CHECK_SIZE(OSCalendarTime, 0x18);

OSTime
OSGetTime();

OSTime
OSGetSystemTime();

OSTick
OSGetTick();

OSTick
OSGetSystemTick();

OSTime
OSCalendarTimeToTicks(OSCalendarTime *calendarTime);

void
OSTicksToCalendarTime(OSTime time,
                      OSCalendarTime *calendarTime);

#ifdef __cplusplus
}
#endif
