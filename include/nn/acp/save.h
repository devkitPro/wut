#pragma once
#include <wut.h>
#include <nn/acp/result.h>
#include <nn/acp/device.h>

/**
 * \defgroup nn_acp_save Save
 * \ingroup nn_acp
 *
 * Save data services
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

ACPResult
ACPCreateSaveDir(uint32_t persistentId,
                 ACPDeviceType deviceType);

ACPResult
ACPIsExternalStorageRequired(BOOL* required);

ACPResult
ACPMountExternalStorage();

ACPResult
ACPMountSaveDir();

ACPResult
ACPRepairSaveMetaDir();

ACPResult
ACPUnmountExternalStorage();

ACPResult
ACPUnmountSaveDir();

#ifdef __cplusplus
}
#endif

/** @} */
