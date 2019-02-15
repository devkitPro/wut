#pragma once
#include <wut.h>

/**
 * \defgroup sysapp_launch SYSAPP Launch
 * \ingroup sysapp
 *
 * Functions to launch and restart titles or system applications.
 * SYSAPP Launch allows applications to launch other titles, restart their own
 * title, and to launch certain system titles.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Restarts the current title with new arguments once the running application
 * quits, and requests the application exit immediately (through \link
 * proc_ui_procui ProcUI\endlink). Instead of returning to the HOME menu upon
 * exit, the system will start the same title again.
 *
 * \param argc
 * The number of strings in the pa_Argv array. Passed in to the title's main
 * function as argc.
 *
 * \param pa_Argv
 * An array of strings to use as arguments. Passed into the title's main
 * function as argv.
 *
 * <!--
 *    meta: why pa_?
 *    do we need to include the rpx name in argv[0]?
 *    behaviour where pa_Argv = NULL?
 * -->
 */
void
SYSRelaunchTitle(uint32_t argc,
                 char *pa_Argv[]);

/**
 * Launches the HOME menu when the current application exits, and requests the
 * application exit immediately (through \link proc_ui_procui ProcUI\endlink).
 *
 * \note
 * This is the default behaviour upon application exit.
 */
void
SYSLaunchMenu();

/**
 * Launch the given title ID once the current application exits, and requests
 * the application exit immediately (through
 * \link proc_ui_procui ProcUI\endlink). Instead of opening the HOME menu once
 * the current application quits, the system will load the given title with
 * default arguments.
 *
 * <!--
 *    what happens on an incorrect titleid?
 *    argc/argv?
 * -->
 */
void
SYSLaunchTitle(uint64_t TitleId);

/**
 * Launch Mii Maker once the current application exits.
 * <!-- there's a version without the underscore, use that? -->
 */
void
_SYSLaunchMiiStudio();

/**
 * Launch System Settings once the current application exits.
 */
void
_SYSLaunchSettings();

/**
 * Launch Parental Controls once the current application exits.
 */
void
_SYSLaunchParental();

/**
 * Launch Notifications once the current application exits.
 *
 * <!--
 *    isn't this an overlay app? does this really run on exit?
 * -->
 */
void
_SYSLaunchNotifications();

#ifdef __cplusplus
}
#endif

/** @} */
