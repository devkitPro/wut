#pragma once
#include <nn/acp/result.h>
#include <wut.h>

/**
 * \defgroup nn_acp_device
 * \ingroup nn_acp
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t ACPDeviceType;

ACPResult
ACPCheckApplicationDeviceEmulation(BOOL *emulation);

#ifdef __cplusplus
}
#endif

/** @} */
