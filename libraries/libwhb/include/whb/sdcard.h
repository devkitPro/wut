#pragma once
#include <wut.h>

/**
 * \defgroup whb_sdcard SDCard Access
 * \ingroup whb
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

BOOL
WHBMountSdCard();

char *
WHBGetSdCardMountPath();

BOOL
WHBUnmountSdCard();

#ifdef __cplusplus
}
#endif

/** @} */
