#pragma once
#include <wut.h>

/**
 * \defgroup sysapp_title SYSAPP Title
 * \ingroup sysapp
 *
 * Functions to check titles and their IDs, as well as retreiving some metadata
 * about them.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SystemAppId
{
   SYSTEM_APP_ID_Updater                                = 0,
   SYSTEM_APP_ID_SystemSettings                         = 1,
   SYSTEM_APP_ID_ParentalControls                       = 2,
   SYSTEM_APP_ID_UserSettings                           = 3,
   SYSTEM_APP_ID_MiiMaker                               = 4,
   SYSTEM_APP_ID_AccountSettings                        = 5,
   SYSTEM_APP_ID_DailyLog                               = 6,
   SYSTEM_APP_ID_Notifications                          = 7,
   SYSTEM_APP_ID_HealthAndSafety                        = 8,
   SYSTEM_APP_ID_ElectronicManual                       = 9,
   SYSTEM_APP_ID_WiiUChat                               = 10,
   SYSTEM_APP_ID_SoftwareDataTransfer                   = 11
} SystemAppId;

/**
 * Check if a given title exists and is installed on the system.
 *
 * \param TitleId
 * The ID of the title to check.
 *
 * \return
 * \c TRUE if the title exists, or \c FALSE otherwise.
 */
BOOL
SYSCheckTitleExists(uint64_t TitleId);

/**
 * Gets the PFID/UPID for a given title.
 *
 * \param TitleId
 * The ID of the title to get the PFID/UPID from.
 *
 * \return
 * The PFID/UPID for the title, or a negative value on error.
 *
 * \note
 * This function is identical to \link SYSGetUPIDFromTitleID \endlink.
 */
int32_t
SYSGetPFIDFromTitleID(uint64_t TitleId);

/**
 * Gets the PFID/UPID for a given title.
 *
 * \param TitleId
 * The ID of the title to get the PFID/UPID from.
 *
 * \return
 * The PFID/UPID for the title, or a negative value on error.
 *
 * \note
 * This function is identical to \link SYSGetPFIDFromTitleID \endlink.
 */
int32_t
SYSGetUPIDFromTitleID(uint64_t TitleId);

/**
 * Gets the title id for a given SystemAppId.
 *
 */
uint64_t
_SYSGetSystemApplicationTitleId(SystemAppId id);

#ifdef __cplusplus
}
#endif

/** @} */
