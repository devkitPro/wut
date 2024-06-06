#pragma once

#include <wut.h>
#include "spinlock.h"
#include "time.h"

/**
 * \defgroup coreinit_stopwatch Lock-based Stopwatch
 * \ingroup coreinit
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSStopwatch OSStopwatch;

struct OSStopwatch {
    //! Lock
    OSSpinLock lock;
    //! Tag
    char* name;
    //! Number of times the stopwatch has been stopped
    uint32_t hitCount;
    //! Total time from first start to last stop
    OSTime totalTime;
    //! Minimum time between stops
    OSTime minTime;
    //! Maximum time between stops
    OSTime maxTime;
    //! Last time the watch was started
    OSTime startTime;
    //! Whether the stopwatch is running
    BOOL running;
    WUT_PADDING_BYTES(0x4);
};
WUT_CHECK_OFFSET(OSStopwatch, 0x00, lock);
WUT_CHECK_OFFSET(OSStopwatch, 0x10, name);
WUT_CHECK_OFFSET(OSStopwatch, 0x14, hitCount);
WUT_CHECK_OFFSET(OSStopwatch, 0x18, totalTime);
WUT_CHECK_OFFSET(OSStopwatch, 0x20, minTime);
WUT_CHECK_OFFSET(OSStopwatch, 0x28, maxTime);
WUT_CHECK_OFFSET(OSStopwatch, 0x30, startTime);
WUT_CHECK_OFFSET(OSStopwatch, 0x38, running);
WUT_CHECK_SIZE(OSStopwatch, 0x40);

/**
 * Initialises the stopwatch,
 * stopwatches must be initialized before any other stopwatch functions are used
 */
void
OSInitStopwatch(OSStopwatch *stopwatch,
                const char* name);

/**
 *  Resets all stopwatch data
 */
void
OSResetStopWatch(OSStopwatch *stopwatch);

/**
 * Starts the stopwatch.
 * if already started, will update the start time without resetting the total time
 */
void
OSStartStopwatch(OSStopwatch *stopwatch);

/**
 * Stops the stopwatch and increments hit count.
 * Nothing happens if the stopwatch has already been stopped
 */
void
OSStopStopwatch(OSStopwatch *stopwatch);

/**
 * Returns the total time the stopwatch has been running
 */
OSTime
OSCheckStopwatch(OSStopwatch *stopwatch);

/**
 *  Dumps stopwatch info to the Cafe OS warn log
 */
void
OSDumpStopwatch(OSStopwatch *stopwatch);

#ifdef __cplusplus
}
#endif

/** @} */
