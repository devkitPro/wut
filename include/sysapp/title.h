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

#ifdef __cplusplus
}
#endif

/** @} */
