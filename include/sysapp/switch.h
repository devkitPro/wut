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

//TODO
typedef void sysapp_input_struct;

typedef struct SysStandardArgs SysStandardArgs;
struct SysStandardArgs
{
    const char* anchor;
    u32         anchorSize;
    char*       result;
    u32         resultSize;
};

typedef struct SysStandardArgsIn SysStandardArgsIn;
struct SysStandardArgsIn
{
    const char* anchor;
    u32         anchorSize;
};

typedef struct SysBrowserArgsIn SysBrowserArgsIn;
struct SysBrowserArgsIn
{
    SysStandardArgsIn stdIn;
    const char*       url;
    u32               urlSize;
};

typedef struct SysBrowserArgsInForCallbackURL SysBrowserArgsInForCallbackURL;
struct SysBrowserArgsInForCallbackURL
{
    SysStandardArgsIn stdIn;
    const char*       url;
    u32               urlSize;
    const char*       callbackURL;
    u32               callbackUrlSize;
    BOOL              hbmDisable;
};

void
SYSSwitchToSyncControllerOnHBM();

void
SYSSwitchToEManual();

void
SYSSwitchToEShop();

void
_SYSSwitchToMainApp();

void
SYSSwitchToBrowserForViewer(sysapp_input_struct*);

int
SYSSwitchToBrowser(const SysBrowserArgsIn *args );

int
SYSSwitchToBrowserForCallbackURL(const SysBrowserArgsInForCallbackURL *args );

#ifdef __cplusplus
}
#endif

/** @} */
