#pragma once
#include <wut.h>

/**
 * \defgroup nn_cmpt
 * \ingroup nn_cmpt
 * Wii backwards compatibility (vWii)
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum CmptScreenType
{
   CMPT_SCREEN_TYPE_TV = 1,
   CMPT_SCREEN_TYPE_DRC,
   CMPT_SCREEN_TYPE_BOTH,
} CmptScreenType;

/**
 * Gets the required size which needs to be allocated for the "dataBuffer".
 * The allocated buffer needs to be aligned by 0x40.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTGetDataSize(uint32_t *outSize);

/**
 * Launches the specified vWii title.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTLaunchTitle(void *dataBuffer, uint32_t bufferSize, uint64_t titleId);

/**
 * Launches vWii System Menu.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTLaunchMenu(void *dataBuffer, uint32_t bufferSize);

/**
 * Launches vWii Data Management.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTLaunchDataManager(void *dataBuffer, uint32_t bufferSize);

/**
 * Sets the screen type.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTAcctSetScreenType(CmptScreenType type);

/**
 * Checks if the current screen configuration is valid.
 *
 * \return
 * 0 on success.
 */
int32_t
CMPTCheckScreenState(void);

#ifdef __cplusplus
}
#endif

/** @} */
