#pragma once

#include <wut.h>
#include "args.h"
#include "switch.h"
#include "nn/ffl/miidata.h"

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

typedef struct SysAppMiiMakerArgs SysAppMiiMakerArgs;
typedef struct _SysAppMiiMakerArgs _SysAppMiiMakerArgs;
typedef struct SysAppSettingsArgs SysAppSettingsArgs;
typedef struct SysAppParentalArgs SysAppParentalArgs;
typedef struct SysAppNotificationArgs SysAppNotificationArgs;

struct SysAppMiiMakerArgs {
    SYSStandardArgsIn stdArgs;
    uint32_t slotId;
    FFLStoreData *mii;
};
WUT_CHECK_OFFSET(SysAppMiiMakerArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppMiiMakerArgs, 0x8, slotId);
WUT_CHECK_OFFSET(SysAppMiiMakerArgs, 0x0C, mii);
WUT_CHECK_SIZE(SysAppMiiMakerArgs, 0x10);

struct _SysAppMiiMakerArgs {
    SYSStandardArgsIn stdArgs;
    uint32_t mode;
    uint32_t slotId;
    FFLStoreData *mii;
};
WUT_CHECK_OFFSET(_SysAppMiiMakerArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(_SysAppMiiMakerArgs, 0x8, mode);
WUT_CHECK_OFFSET(_SysAppMiiMakerArgs, 0xC, slotId);
WUT_CHECK_OFFSET(_SysAppMiiMakerArgs, 0x10, mii);
WUT_CHECK_SIZE(_SysAppMiiMakerArgs, 0x14);

struct SysAppSettingsArgs {
    SYSStandardArgsIn stdArgs;
    int32_t jumpTo;
    uint32_t firstBootKind;
};
WUT_CHECK_OFFSET(SysAppSettingsArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppSettingsArgs, 0x8, jumpTo);
WUT_CHECK_OFFSET(SysAppSettingsArgs, 0x0C, firstBootKind);
WUT_CHECK_SIZE(SysAppSettingsArgs, 0x10);

struct SysAppParentalArgs {
    SYSStandardArgsIn stdArgs;
    uint32_t mode;
};
WUT_CHECK_OFFSET(SysAppParentalArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppParentalArgs, 0x8, mode);
WUT_CHECK_SIZE(SysAppParentalArgs, 0x0C);

struct SysAppNotificationArgs {
    SYSStandardArgsIn stdArgs;
    uint32_t notificationFile;
};
WUT_CHECK_OFFSET(SysAppNotificationArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppNotificationArgs, 0x8, notificationFile);
WUT_CHECK_SIZE(SysAppNotificationArgs, 0x0C);

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

void
_SYSLaunchTitleWithStdArgsInNoSplash(uint64_t titleId,
                                     SYSStandardArgsIn *stdArgs);

void
_SYSLaunchMenuWithCheckingAccount(uint8_t slot);

/**
 * Launch Mii Maker once the current application exits.
 */
void
SYSLaunchMiiStudio(SysAppMiiMakerArgs *args);


/**
 * Launch Mii Maker once the current application exits.
 * <!-- there's a version without the underscore, use that? -->
 */
void
_SYSLaunchMiiStudio(_SysAppMiiMakerArgs *args);

/**
 * Launch System Settings once the current application exits.
 */
void
_SYSLaunchSettings(SysAppSettingsArgs *args);

/**
 * Launch Parental Controls once the current application exits.
 */
void
_SYSLaunchParental(SysAppParentalArgs *args);

/**
 * Launch Notifications once the current application exits.
 *
 * <!--
 *    isn't this an overlay app? does this really run on exit?
 * -->
 */
void
_SYSLaunchNotifications(SysAppNotificationArgs *args);

void
_SYSLaunchTitleByPathFromLauncher(const char* path,
                                  uint32_t unused);

#ifdef __cplusplus
}
#endif

/** @} */
