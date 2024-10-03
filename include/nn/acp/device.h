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

typedef enum ACPDeviceType
{
   ACP_DEVICE_TYPE_AUTO     = 1,
   ACP_DEVICE_TYPE_ODD      = 2,
   ACP_DEVICE_TYPE_HFIODISC = 2, /* when ApplicationDevice is emulated */
   ACP_DEVICE_TYPE_MLC      = 3,
   ACP_DEVICE_TYPE_HFIOMLC  = 3, /* when ApplicationDevice is emulated */
   ACP_DEVICE_TYPE_USB      = 4,
} ACPDeviceType;

ACPResult
ACPCheckApplicationDeviceEmulation(BOOL *emulation);

#ifdef __cplusplus
}
#endif

/** @} */
