#pragma once

#include <wut.h>
#include "time.h"

/**
 * \defgroup coreinit_stopwatchatomic Atomic Stopwatch
 * \ingroup coreinit
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSStopWatchAtomic OSStopWatchAtomic;

struct OSStopWatchAtomic
{
   //! Last time the watch was started
   OSTime startTime;
   //! Total time from first start to last stop
   OSTime totalTime;
};
WUT_CHECK_OFFSET(OSStopWatchAtomic, 0x00, startTime);
WUT_CHECK_OFFSET(OSStopWatchAtomic, 0x08, totalTime);
WUT_CHECK_SIZE(OSStopWatchAtomic, 0x10);

/**
 * Start the stopwatch.
 * Only updates the start time
 * \returns total time on stopwatch
 */
OSTime
OSStopWatchStart(OSStopWatchAtomic *stopWatch);

/**
 * Stop the stopwatch.
 * Resets the start time to 0
 * \returns total time on stopwatch
 */
OSTime
OSStopWatchStop(OSStopWatchAtomic *stopWatch);

/**
 * Get the current time on the stopwatch
 * \returns current time on stopwatch
 */
OSTime
OSStopWatchLap(OSStopWatchAtomic *stopWatch);


/**
 * Stops and resets the stop watch.
 * Clears start and total time
 * \returns previous total time
 */
OSTime
OSStopWatchReset(OSStopWatchAtomic *stopWatch);

#ifdef __cplusplus
}
#endif

/** @} */
