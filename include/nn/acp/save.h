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

typedef uint64_t ACPTitleId;
typedef struct ACPSaveDirInfo ACPSaveDirInfo;

struct WUT_PACKED ACPSaveDirInfo {
    WUT_UNKNOWN_BYTES(0x8);
    uint32_t persistentId;
    WUT_UNKNOWN_BYTES(0x14);
    char path[0x40];
    WUT_PADDING_BYTES(0x80 - 0x60);
};
WUT_CHECK_OFFSET(ACPSaveDirInfo, 0x08, persistentId);
WUT_CHECK_OFFSET(ACPSaveDirInfo, 0x20, path);
WUT_CHECK_SIZE(ACPSaveDirInfo,0x80);

ACPResult
ACPCreateSaveDir(uint32_t persistentId,
                 ACPDeviceType deviceType);

ACPResult
ACPIsExternalStorageRequired(BOOL *required);

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

/**
 * Gets all titles id which have save data
 *
 * @param deviceType
 * @param titlesOut needs to be aligned to 0x40
 * @param maxCount needs to be a multiple of 8
 * @param countOut
 * @return ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPGetSaveDataTitleIdList(ACPDeviceType deviceType,
                          uint64_t *titlesOut,
                          uint32_t maxCount,
                          uint32_t *countOut);

/**
 * Gets a list of all saves dir for a given title id
 *
 * @param titleId
 * @param deviceType
 * @param u1 seems to be always 0
 * @param saveDirInfo needs to be aligned to 0x40
 * @param maxCount
 * @param countOut
 * @return ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPGetTitleSaveDirEx(uint64_t titleId,
                     ACPDeviceType deviceType,
                     uint32_t u1,
                     ACPSaveDirInfo *saveDirInfo,
                     uint32_t maxCount,
                     uint32_t *countOut);

/**
 * Gets a list of all saves dir for a given title id
 *
 * @param titleId
 * @param deviceType
 * @param u1 seems to be always 0
 * @param saveDirInfo needs to be aligned to 0x40
 * @param maxCount
 * @param countOut
 * @return ACP_RESULT_SUCCESS on success.
 */
ACPResult
ACPGetTitleSaveDirExWithoutMetaCheck(uint64_t titleId,
                                     ACPDeviceType deviceType,
                                     uint32_t u1,
                                     ACPSaveDirInfo *saveDirInfo,
                                     uint32_t maxCount,
                                     uint32_t *countOut);

#ifdef __cplusplus
}
#endif

/** @} */
