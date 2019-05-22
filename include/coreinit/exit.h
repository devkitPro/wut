#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_exit Exit
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

void
RPLWRAP(exit)(int code);

void
_Exit(int code);

#ifdef __cplusplus
}
#endif

/** @} */
