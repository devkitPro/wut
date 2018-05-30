#pragma once
#include <wut.h>
#include "thread.h"
#include "time.h"

/**
 * \defgroup coreinit_dynload Dynamic Loading
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSDynLoad_Error
{
   OS_DYNLOAD_OK                          = 0,
   OS_DYNLOAD_OUT_OF_MEMORY               = 0xBAD10002,
   OS_DYNLOAD_INVALID_NOTIFY_PTR          = 0xBAD1000E,
   OS_DYNLOAD_INVALID_MODULE_NAME_PTR     = 0xBAD1000F,
   OS_DYNLOAD_INVALID_MODULE_NAME         = 0xBAD10010,
   OS_DYNLOAD_INVALID_ACQUIRE_PTR         = 0xBAD10011,
   OS_DYNLOAD_EMPTY_MODULE_NAME           = 0xBAD10012,
   OS_DYNLOAD_INVALID_ALLOCATOR_PTR       = 0xBAD10017,
   OS_DYNLOAD_OUT_OF_SYSTEM_MEMORY        = 0xBAD1002F,
   OS_DYNLOAD_TLS_ALLOCATOR_LOCKED        = 0xBAD10031,
} OSDynLoad_Error;

typedef void *OSDynLoadModule;

typedef OSDynLoad_Error (*OSDynLoadAllocFn)(int32_t size, int32_t align, void **outAddr);
typedef void (*OSDynLoadFreeFn)(void *addr);


/**
 * Load a module.
 *
 * If the module is already loaded, increase reference count.
 * Similar to LoadLibrary on Windows.
 */
OSDynLoad_Error
OSDynLoad_Acquire(char const *name,
                  OSDynLoadModule *outModule);


/**
 * Retrieve the address of a function or data export from a module.
 *
 * Similar to GetProcAddress on Windows.
 */
OSDynLoad_Error
OSDynLoad_FindExport(OSDynLoadModule module,
                     BOOL isData,
                     char const *name,
                     void **outAddr);


/**
 * Free a module handle returned from OSDynLoad_Acquire.
 *
 * Will decrease reference count and only unload the module if count reaches 0.
 * Similar to FreeLibrary on Windows.
 */
void
OSDynLoad_Release(OSDynLoadModule module);


/**
 * Set the allocator functions to use for dynamic loading.
 */
OSDynLoad_Error
OSDynLoad_SetAllocator(OSDynLoadAllocFn allocFn,
                       OSDynLoadFreeFn freeFn);


/**
 * Get the allocator functions used for dynamic loading.
 */
OSDynLoad_Error
OSDynLoad_GetAllocator(OSDynLoadAllocFn *outAllocFn,
                       OSDynLoadFreeFn *outFreeFn);

#ifdef __cplusplus
}
#endif

/** @} */
