#pragma once
#include <wut.h>
#include <coreinit/mcp.h>

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

typedef enum SYSTEM_APP_ID
{
   SYSTEM_APP_ID_HOME_MENU                = 0,
   SYSTEM_APP_ID_SYSTEM_SETTINGS          = 1,
   SYSTEM_APP_ID_PARENTAL_CONTROLS        = 2,
   SYSTEM_APP_ID_USER_SETTINGS            = 3,
   SYSTEM_APP_ID_MII_MAKER                = 4,
   SYSTEM_APP_ID_ACCOUNT_SETTINGS         = 5,
   SYSTEM_APP_ID_DAILY_LOG                = 6,
   SYSTEM_APP_ID_NOTIFICATIONS            = 7,
   SYSTEM_APP_ID_HEALTH_AND_SAFETY        = 8,
   SYSTEM_APP_ID_ELECTRONIC_MANUAL        = 9,
   SYSTEM_APP_ID_WIIU_CHAT                = 10,
   SYSTEM_APP_ID_SOFTWARE_DATA_TRANSFER   = 11,
} SYSTEM_APP_ID;

// for compatibility
WUT_DEPRECATED("This enum name is misleading and incorrect. Please use SYSTEM_APP_ID_HOME_MENU")
static const SYSTEM_APP_ID SYSTEM_APP_ID_UPDATER = SYSTEM_APP_ID_HOME_MENU;

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
 * Gets the PFID/UPID of the calling (current) application.
 *
 * \note
 * This function is identical to \link SYSGetCallerPFID \endlink.
 */
int32_t
SYSGetCallerUPID();

/**
 * Gets the PFID/UPID of the calling (current) application.
 *
 * \note
 * This function is identical to \link SYSGetCallerUPID \endlink.
 */
int32_t
SYSGetCallerPFID();

/**
 * Gets the title id for a given SYSTEM_APP_ID.
 *
 */
uint64_t
_SYSGetSystemApplicationTitleId(SYSTEM_APP_ID id);

/**
 * Gets the title id for a given SYSTEM_APP_ID in the given region.
 *
 */
uint64_t
_SYSGetSystemApplicationTitleIdByProdArea(SYSTEM_APP_ID id,
                                          MCPRegion prod_area);

/**
 * Gets the title id of the calling (current) application.
 *
 */
uint64_t
SYSGetCallerTitleId();

#ifdef __cplusplus
}
#endif

/** @} */
