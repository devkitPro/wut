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

/**
 * Deletes the given user's save data directory for the given title.
 * 
 * \param persistentId
 * The persistent ID of the user. Pass \c 0 to delete the 'common' directory.
 * 
 * \return
 * ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPRemoveSaveDir(uint32_t persistentId,
                 uint64_t titleId,
                 ACPDeviceType deviceType);

/**
 * Deletes the given user's save data directory for the given title.
 * 
 * \param persistentId
 * The persistent ID of the user. Pass \c 0 to delete the 'common' directory.
 * 
 * \return
 * ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPRemoveSaveDirWithoutFlush(uint32_t persistentId,
                             uint64_t titleId,
                             ACPDeviceType deviceType);

/**
 * Deletes the given user's save data directory for the given title.
 * 
 * \param persistentId
 * The persistent ID of the user. Pass \c 0 to delete the 'common' directory.
 * 
 * \return
 * ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPRemoveSaveDirWithoutMetaCheck(uint32_t persistentId,
                                 uint64_t titleId,
                                 ACPDeviceType deviceType);

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
