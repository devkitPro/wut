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
   uint32_t clockSpeed;
   UNKNOWN(0x4);
   OSTime baseTime;
   UNKNOWN(0x10);
};
CHECK_OFFSET(OSSystemInfo, 0x0, clockSpeed);
CHECK_OFFSET(OSSystemInfo, 0x8, baseTime);
CHECK_SIZE(OSSystemInfo, 0x20);


#define OSOneSecond ((OSGetSystemInfo()->clockSpeed) / 4)
#define OSMilliseconds(val) ((((uint64_t)(val)) * (uint64_t)(OSOneSecond)) / 1000ull)

OSSystemInfo *
OSGetSystemInfo();

#ifdef __cplusplus
}
#endif

/** @} */
