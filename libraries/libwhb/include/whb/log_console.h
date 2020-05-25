#pragma once
#include <wut.h>

/**
 * \defgroup whb_log_console On screen console log output
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define WHB_SERVER_BUFFER_SIZE 1024

BOOL
WHBLogConsoleInit();

void
WHBLogConsoleFree();

void
WHBLogConsoleSetColor(uint32_t color);

void
WHBLogConsoleDraw();

#ifdef __cplusplus
}
#endif

/** @} */
