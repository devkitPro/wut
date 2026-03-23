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
 * Can be used to mask the return value of
 * \ref OSGetConsoleType
 * for determining the "group" of console. See the function for more
 * information around the values the mask gives.
 */
#define OS_CONSOLE_TYPE_MASK 0xF0000000


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


/**
 * Get the type of console this code is actively running on.
 *
 * Most of the field is relatively unknown but you can use
 * \ref OS_CONSOLE_TYPE_MASK
 * which returns whether the unit is a Retail/CAT-R unit with `0x00000000`,
 * a CAT-DEV or other CAFE development board with `0x10000000`, and an
 * orchestrax unit with `0x20000000`.
 *
 * \returns
 * A number representing the specific console types.
 */
uint32_t
OSGetConsoleType();


#ifdef __cplusplus
}
#endif

/** @} */
