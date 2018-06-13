#pragma once
#include <wut.h>

/**
 * \defgroup sysapp_switch SYSAPP Switch
 * \ingroup sysapp
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SysAppBrowserArgs SysAppBrowserArgs;

void
SYSSwitchToSyncControllerOnHBM();

void
SYSSwitchToEManual();

void
SYSSwitchToEShop();

void
_SYSSwitchToMainApp();

void
SYSSwitchToBrowserForViewer(SysAppBrowserArgs *);

#ifdef __cplusplus
}
#endif

/** @} */
