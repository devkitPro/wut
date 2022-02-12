#pragma once
#include <wut.h>

/**
 * \defgroup whb_log_module Log using the LoggingModule.
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

BOOL WHBLogModuleInit();

BOOL WHBLogModuleDeinit();

#ifdef __cplusplus
}
#endif

/** @} */
