#pragma once
#include <wut.h>

/**
 * \defgroup whb_log_udp UDP Log Output
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

BOOL
WHBLogUdpInit();

BOOL
WHBLogUdpDeinit();

#ifdef __cplusplus
}
#endif

/** @} */
