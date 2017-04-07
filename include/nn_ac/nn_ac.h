#pragma once
#include <wut.h>

/**
 * \defgroup nn_ac Auto Connect
 * \ingroup nn_ac
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ACResult
{
   OK = 0,
} ACResult;

typedef uint32_t ACConfigId;

ACResult
ACInitialize();

void
ACFinalize();

ACResult
ACGetStartupId(ACConfigId *configId);

ACResult
ACConnectWithConfigId(ACConfigId configId);

ACResult
ACGetAssignedAddress(uint32_t *ip);

#ifdef __cplusplus
}
#endif

/** @} */
