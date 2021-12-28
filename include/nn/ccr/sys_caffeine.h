#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CCRAppLaunchParam CCRAppLaunchParam;

struct WUT_PACKED CCRAppLaunchParam
{
    uint64_t titleId;
    char uuid[16];
    WUT_UNKNOWN_BYTES(0xE7);
};
WUT_CHECK_OFFSET(CCRAppLaunchParam, 0x00, titleId);
WUT_CHECK_OFFSET(CCRAppLaunchParam, 0x08, uuid);
WUT_CHECK_SIZE(CCRAppLaunchParam, 0xFF);

void
CCRSysCaffeineGetAppLaunchParam(CCRAppLaunchParam * data);

uint32_t
CCRSysCaffeineBootCheck();

#ifdef __cplusplus
}
#endif