#pragma once
#include <wut.h>

/**
 * \defgroup whb_proc ProcUI Utilities
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
WHBProcInit();

void
WHBProcShutdown();

void
WHBProcStopRunning();

BOOL
WHBProcIsRunning();

#ifdef __cplusplus
}
#endif

/** @} */
