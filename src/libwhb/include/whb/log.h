#pragma once
#include <wut.h>

/**
 * \defgroup whb_log Logger
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*LogHandlerFn)(const char *msg);

BOOL
WHBAddLogHandler(LogHandlerFn fn);

BOOL
WHBRemoveLogHandler(LogHandlerFn fn);

BOOL
WHBLogWrite(const char *str);

BOOL
WHBLogPrint(const char *str);

BOOL
WHBLogWritef(const char *fmt, ...);

BOOL
WHBLogPrintf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

/** @} */
