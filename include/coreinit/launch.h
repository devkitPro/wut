#pragma once

#include <wut.h>

/**
 * \defgroup coreinit_launch Launch
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Magic title ID used for launching the current coldboot title.
 */
#define OS_TITLE_ID_COLDBOOT 0xFFFFFFFFFFFFFFFDllu

/**
 * Magic title ID used for triggering a full system reboot.
 */
#define OS_TITLE_ID_REBOOT 0xFFFFFFFFFFFFFFFEllu

/**
 * Forces a OS relaunch on the next title launch.
 */
void
OSForceFullRelaunch();

/**
 * Restarts the currently running title.
 * 
 * \param argc
 * The amount of arguments in \p argv.
 * 
 * \param argv
 * An array of argument strings.
 */
void
OSRestartGame(int argc,
              char *argv[]);

/**
 * Shuts down the system.
 */
BOOL
OSShutdown();

/**
 * Launches a title by path.
 * 
 * \param path
 * The path to launch the title from.
 * 
 * \param pathSize
 * The size of the path string.
 * 
 * \param argc
 * The amount of argument strings.
 * 
 * \param ...
 * Argument strings passed to the title as \c argv.
 * 
 * \note
 * Prefer using sysapp to launch titles instead.
 */
void
OSLaunchTitleByPathl(const char *path,
                     uint32_t pathSize,
                     int argc,
                     ...);

/**
 * Launches a title by path.
 * 
 * \param path
 * The path to launch the title from.
 * 
 * \param pathSize
 * The size of the path string.
 * 
 * \param argc
 * The amount of arguments in \p argv.
 * 
 * \param argv
 * An array of argument strings.
 * 
 * \note
 * Prefer using sysapp to launch titles instead.
 */
void
OSLaunchTitleByPathv(const char *path,
                     uint32_t pathSize,
                     int argc,
                     char *argv[]);

/**
 * Launches a title by its title ID.
 * 
 * \param titleId
 * The ID of the title to launch.
 * 
 * \param argc
 * The amount of argument strings.
 * 
 * \param ...
 * Argument strings passed to the title as \c argv.
 * 
 * \note
 * Prefer using sysapp to launch titles instead.
 */
void
OSLaunchTitlel(uint64_t titleId,
               int argc,
               ...);

/**
 * Launches a title by its title ID.
 * 
 * \param titleId
 * The ID of the title to launch.
 * 
 * \param argc
 * The amount of arguments in \p argv.
 * 
 * \param argv
 * An array of argument strings.
 * 
 * \note
 * Prefer using sysapp to launch titles instead.
 */
void
OSLaunchTitlev(uint64_t titleId,
               int argc,
               char *argv[]);

#ifdef __cplusplus
}
#endif

/** @} */
