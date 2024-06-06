#pragma once
#include <wut.h>

/**
 * \defgroup nn_ccr_sys_caffeine
 * \ingroup nn_ccr
 * (see nn::ccr)
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CCRAppLaunchParam CCRAppLaunchParam;

struct WUT_PACKED CCRAppLaunchParam
{
    uint64_t launchInfoDatabaseEntryId; // id used in the \link nn::sl::LaunchInfoDatabase
    char uuid[16];                      // account uuid
    WUT_UNKNOWN_BYTES(0xE7);
};
WUT_CHECK_OFFSET(CCRAppLaunchParam, 0x00, launchInfoDatabaseEntryId);
WUT_CHECK_OFFSET(CCRAppLaunchParam, 0x08, uuid);
WUT_CHECK_SIZE(CCRAppLaunchParam, 0xFF);

void
CCRSysCaffeineGetAppLaunchParam(CCRAppLaunchParam * data);

uint32_t
CCRSysCaffeineBootCheck();

void
CCRSysCaffeineBootCheckAbort();

/**
 * @return 0 on success, -1 on error
 */
int32_t
CCRSysCaffeineSetDRCEnableFlag(int32_t enabled);

/**
 * @return 0 on success, -1 on error
 */
int32_t
CCRSysCaffeineSetEnableFlag(int32_t enabled);

#ifdef __cplusplus
}
#endif

/** @} */
