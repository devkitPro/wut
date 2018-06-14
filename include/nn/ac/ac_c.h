#pragma once
#include <wut.h>
#include <nn/result.h>

/**
 * \ingroup nn_ac
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t ACConfigId;

NNResult
ACInitialize();

void
ACFinalize();

NNResult
ACGetStartupId(ACConfigId *configId);

NNResult
ACConnectWithConfigId(ACConfigId configId);

NNResult
ACGetAssignedAddress(uint32_t *ip);

#ifdef __cplusplus
}
#endif

/** @} */
