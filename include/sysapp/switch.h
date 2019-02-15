#pragma once
#include <wut.h>

/**
 * \defgroup sysapp_switch SYSAPP Switch
 * \ingroup sysapp
 *
 * Functions to open overlay applications (eShop, manual etc.).
 * SYSAPP Switch provides functions to open overlay applications - such as the
 * Internet Browser or HOME menu overlay. Calling one of these functions moves
 * the current application to the background and opens the requested overlay.
 * Notable functions include \link SYSSwitchToSyncControllerOnHBM \endlink and
 * \link SYSSwitchToBrowserForViewer \endlink, to open the sync controller menu
 * or Internet Browser, respectivley.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! Argument struct for \link SYSSwitchToBrowserForViewer \endlink.
typedef struct SysAppBrowserArgs SysAppBrowserArgs;

/**
 * Initiate a switch into the controller sync menu. This is the same menu
 * that can be accessed from the HOME menu overlay (HBM).
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the sync menu is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
void
SYSSwitchToSyncControllerOnHBM();

/**
 * Initiate a switch to the current title's assosciated e-manual.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the e-manual is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
void
SYSSwitchToEManual();

/**
 * Initiate a switch to the Nintendo eShop application.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the Nintendo eShop is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
void
SYSSwitchToEShop();

/**
 * <!--
 *    ..?
 *    Current app moves into background then immediately back out again.
 *    Presumably meant for overlay apps to exit?
 * -->
 */
void
_SYSSwitchToMainApp();

/**
 * Initiates a switch to the Internet Browser application, with the given
 * arguments in the form of a \link SysAppBrowserArgs \endlink struct.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the Internet Browser is shown. Once the
 * user exits the menu, the application is moved back to the foreground.
 */
void
SYSSwitchToBrowserForViewer(SysAppBrowserArgs *);

#ifdef __cplusplus
}
#endif

/** @} */
