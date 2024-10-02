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

// clang-format off
void
RPLWRAP(exit)(int code);
// clang-format on

void
_Exit(int code);

#ifdef __cplusplus
}
#endif

/** @} */
