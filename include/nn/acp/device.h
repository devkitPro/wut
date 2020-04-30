#pragma once
#include <wut.h>
#include <nn/acp/result.h>

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
ACPCheckApplicationDeviceEmulation(BOOL* emulation);

#ifdef __cplusplus
}
#endif

/** @} */
