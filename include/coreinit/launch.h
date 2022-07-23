#pragma once

#include <wut.h>

/**
 * \defgroup coreinit_launch Launch
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
OSForceFullRelaunch();

void
OSRestartGame(int argc, char *argv[]);

BOOL
OSShutdown();

#ifdef __cplusplus
}
#endif

/** @} */
