#pragma once
#include <wut.h>
#include "time.h"

/**
 * \defgroup coreinit_systeminfo System Info
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSSystemInfo OSSystemInfo;

struct OSSystemInfo
{
   uint32_t busClockSpeed;
   uint32_t coreClockSpeed;
   OSTime baseTime;
   UNKNOWN(0x10);
};
CHECK_OFFSET(OSSystemInfo, 0x0, busClockSpeed);
CHECK_OFFSET(OSSystemInfo, 0x4, coreClockSpeed);
CHECK_OFFSET(OSSystemInfo, 0x8, baseTime);
CHECK_SIZE(OSSystemInfo, 0x20);

OSSystemInfo *
OSGetSystemInfo();

BOOL
OSEnableHomeButtonMenu(BOOL enable);

BOOL
OSIsHomeButtonMenuEnabled();

#ifdef __cplusplus
}
#endif

/** @} */
