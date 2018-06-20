#pragma once
#include <wut.h>
#include "systeminfo.h"

/**
 * \defgroup coreinit_time Time
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSCalendarTime OSCalendarTime;

typedef int32_t OSTick;
typedef int64_t OSTime;

//! Same as std c struct tm but with msec and usec added.
struct OSCalendarTime
{
   int32_t tm_sec;
   int32_t tm_min;
   int32_t tm_hour;
   int32_t tm_mday;
   int32_t tm_mon;
   int32_t tm_year;
   int32_t tm_wday;
   int32_t tm_yday;
   int32_t tm_msec;
   int32_t tm_usec;
};
WUT_CHECK_OFFSET(OSCalendarTime, 0x00, tm_sec);
WUT_CHECK_OFFSET(OSCalendarTime, 0x04, tm_min);
WUT_CHECK_OFFSET(OSCalendarTime, 0x08, tm_hour);
WUT_CHECK_OFFSET(OSCalendarTime, 0x0C, tm_mday);
WUT_CHECK_OFFSET(OSCalendarTime, 0x10, tm_mon);
WUT_CHECK_OFFSET(OSCalendarTime, 0x14, tm_year);
WUT_CHECK_OFFSET(OSCalendarTime, 0x18, tm_wday);
WUT_CHECK_OFFSET(OSCalendarTime, 0x1C, tm_yday);
WUT_CHECK_OFFSET(OSCalendarTime, 0x20, tm_msec);
WUT_CHECK_OFFSET(OSCalendarTime, 0x24, tm_usec);
WUT_CHECK_SIZE(OSCalendarTime, 0x28);

#define OSTimerClockSpeed ((OSGetSystemInfo()->busClockSpeed) / 4)

#define OSSecondsToTicks(val)        ((uint64_t)(val) * (uint64_t)OSTimerClockSpeed)
#define OSMillisecondsToTicks(val)  (((uint64_t)(val) * (uint64_t)OSTimerClockSpeed) / 1000ull)
#define OSMicrosecondsToTicks(val)  (((uint64_t)(val) * (uint64_t)OSTimerClockSpeed) / 1000000ull)
#define OSNanosecondsToTicks(val)   (((uint64_t)(val) * ((uint64_t)OSTimerClockSpeed) / 31250ull) / 32000ull)

#define OSTicksToSeconds(val)        ((uint64_t)(val) / (uint64_t)OSTimerClockSpeed)
#define OSTicksToMilliseconds(val)  (((uint64_t)(val) * 1000ull) / (uint64_t)OSTimerClockSpeed)
#define OSTicksToMicroseconds(val)  (((uint64_t)(val) * 1000000ull) / (uint64_t)OSTimerClockSpeed)
#define OSTicksToNanoseconds(val)   (((uint64_t)(val) * 32000ull) / ((uint64_t)OSTimerClockSpeed / 31250ull))

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

/** @} */
