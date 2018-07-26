#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_core Core
 * \ingroup coreinit
 *
 * Provides information about each core of the system's processor.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Gets the number of cores in the system. On a retail Wii U, this is always 3.
 *
 * \returns
 * The core count of the system.
 */
uint32_t
OSGetCoreCount();


/**
 * Gets the core executing the current thread.
 *
 * \returns
 * The ID of the current core.
 */
uint32_t
OSGetCoreId();


/**
 * Gets the main core of the system. On a retail Wii U, this is always core 1.
 *
 * \returns
 * The ID of the main core.
 */
uint32_t
OSGetMainCoreId();


/**
 * Determines whether the current thread is running on the main core.
 * On a retail Wii U, the main core is always core 1.
 *
 * \returns
 * \c true if the current core is the main core.
 *
 * \sa
 * <ul><li>\link OSGetMainCoreId \endlink</li></ul>
 */
BOOL
OSIsMainCore();


#ifdef __cplusplus
}
#endif

/** @} */
