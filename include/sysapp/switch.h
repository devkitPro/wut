#pragma once
#include <wut.h>
#include "args.h"

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

typedef struct SysAppBrowserArgs SysAppBrowserArgs;
typedef struct SysAppBrowserArgsWithCallback SysAppBrowserArgsWithCallback;
typedef struct SysAppEShopArgs SysAppEShopArgs;
typedef struct SysAppEManualArgs SysAppEManualArgs;

struct SysAppEManualArgs
{
   SYSStandardArgsIn stdArgs;
   uint64_t titleId;
};
WUT_CHECK_OFFSET(SysAppEManualArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppEManualArgs, 0x8, titleId);
WUT_CHECK_SIZE(SysAppEManualArgs, 0x10);

struct SysAppEShopArgs
{
   SYSStandardArgsIn stdArgs;
   char *query;
   uint32_t querySize;
};
WUT_CHECK_OFFSET(SysAppEShopArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppEShopArgs, 0x8, query);
WUT_CHECK_OFFSET(SysAppEShopArgs, 0xc, querySize);
WUT_CHECK_SIZE(SysAppEShopArgs, 0x10);

struct SysAppBrowserArgs
{
   SYSStandardArgsIn stdArgs;
   char *url;
   uint32_t urlSize;
};
WUT_CHECK_OFFSET(SysAppBrowserArgs, 0x0, stdArgs);
WUT_CHECK_OFFSET(SysAppBrowserArgs, 0x8, url);
WUT_CHECK_OFFSET(SysAppBrowserArgs, 0xC, urlSize);
WUT_CHECK_SIZE(SysAppBrowserArgs, 0x10);

struct SysAppBrowserArgsWithCallback
{
   SysAppBrowserArgs browserArgs;
   char *cbUrl;
   uint32_t cbUrlSize;
   BOOL hbmDisable;
};
WUT_CHECK_OFFSET(SysAppBrowserArgsWithCallback, 0x0, browserArgs);
WUT_CHECK_OFFSET(SysAppBrowserArgsWithCallback, 0x10, cbUrl);
WUT_CHECK_OFFSET(SysAppBrowserArgsWithCallback, 0x14, cbUrlSize);
WUT_CHECK_OFFSET(SysAppBrowserArgsWithCallback, 0x18, hbmDisable);
WUT_CHECK_SIZE(SysAppBrowserArgsWithCallback, 0x1C);

typedef enum SysAppPFID
{
   SYSAPP_PFID_WII_U_MENU          = 2,
   SYSAPP_PFID_TVII                = 3,
   SYSAPP_PFID_EMANUAL             = 4,
   SYSAPP_PFID_HOME_MENU           = 5,
   SYSAPP_PFID_MINI_MIIVERSE       = 7,
   SYSAPP_PFID_BROWSER             = 8,
   SYSAPP_PFID_MIIVERSE            = 9,
   SYSAPP_PFID_ESHOP               = 10,
   SYSAPP_PFID_FRIENDLIST          = 11,
   SYSAPP_PFID_DOWNLOAD_MANAGEMENT = 12,
   SYSAPP_PFID_DOWNLOAD_GAME       = 15,
   SYSAPP_PFID_MINTU               = 16,
   SYSAPP_PFID_CABINETU            = 17,
   SYSAPP_PFID_TEST_OVERLAY        = 31,
} SysAppPFID;

/**
 * Initiate a switch into the controller sync menu. This is the same menu
 * that can be accessed from the HOME menu overlay (HBM).
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the sync menu is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
int32_t
SYSSwitchToSyncControllerOnHBM();

/**
 * Initiate a switch to the current title's assosciated e-manual.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the e-manual is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
int32_t
SYSSwitchToEManual();

int32_t
_SYSSwitchToEManual(SysAppEManualArgs *);

int32_t
_SYSSwitchToEManualFromHBM(SysAppEManualArgs *);

/**
 * Initiate a switch to the Nintendo eShop application.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the Nintendo eShop is shown. Once the user
 * exits the menu, the application is moved back to the foreground.
 */
int32_t
SYSSwitchToEShop(SysAppEShopArgs *);

int32_t
SYSSwitchToEShopTicketList(SYSStandardArgsIn *);

int32_t
_SYSSwitchToEShopFromHBM(SysAppEShopArgs *);

/**
 * <!--
 *    ..?
 *    Current app moves into background then immediately back out again.
 *    Presumably meant for overlay apps to exit?
 * -->
 */
int32_t
_SYSSwitchToMainApp();

int32_t
SYSSwitchToBrowser(SysAppBrowserArgs *);

/**
 * Initiates a switch to the Internet Browser application, with the given
 * arguments in the form of a \link SysBrowserArgsIn \endlink struct.
 *
 * The current application is moved into the background (see \link
 * proc_ui_procui ProcUI\endlink) and the Internet Browser is shown. Once the
 * user exits the menu, the application is moved back to the foreground.
 */
int32_t
SYSSwitchToBrowserForViewer(SysAppBrowserArgs *);

int32_t
SYSSwitchToBrowserForCallbackURL(SysAppBrowserArgsWithCallback *);

int32_t
_SYSSwitchToBrowserForCallbackURLFromHBM(SysAppBrowserArgsWithCallback *);

int32_t
_SYSSwitchToHBMWithMode(int32_t p1);

int32_t
_SYSSwitchToOverlayFromHBM(int32_t p1);

/**
 * Calls __OSClearCopyData then _SYSSwitchTo
 */
int32_t
SYSSwitchTo(SysAppPFID pfid);

int32_t
_SYSSwitchTo(SysAppPFID pfid);

int32_t
_SYSDirectlySwitchTo(SysAppPFID pfid);

#ifdef __cplusplus
}
#endif

/** @} */
