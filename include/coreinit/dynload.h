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

typedef struct OSDynLoad_NotifyData OSDynLoad_NotifyData;
typedef void *OSDynLoad_Module;

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

typedef OSDynLoad_Error (*OSDynLoadAllocFn)(int32_t size, int32_t align, void **outAddr);
typedef void (*OSDynLoadFreeFn)(void *addr);

typedef enum OSDynLoad_EntryReason
{
  OS_DYNLOAD_LOADED                       = 0,
  OS_DYNLOAD_UNLOADED                     = 1,
} OSDynLoad_EntryReason;

struct OSDynLoad_NotifyData
{
   char *name;

   uint32_t textAddr;
   uint32_t textOffset;
   uint32_t textSize;

   uint32_t dataAddr;
   uint32_t dataOffset;
   uint32_t dataSize;

   uint32_t readAddr;
   uint32_t readOffset;
   uint32_t readSize;
};
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x00, name);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x04, textAddr);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x08, textOffset);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x0C, textSize);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x10, dataAddr);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x14, dataOffset);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x18, dataSize);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x1C, readAddr);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x20, readOffset);
WUT_CHECK_OFFSET(OSDynLoad_NotifyData, 0x24, readSize);
WUT_CHECK_SIZE(OSDynLoad_NotifyData, 0x28);


/**
 * Load a module.
 *
 * If the module is already loaded, increase reference count.
 * Similar to LoadLibrary on Windows.
 */
OSDynLoad_Error
OSDynLoad_Acquire(char const *name,
                  OSDynLoad_Module *outModule);


/**
 * Retrieve the address of a function or data export from a module.
 *
 * Similar to GetProcAddress on Windows.
 */
OSDynLoad_Error
OSDynLoad_FindExport(OSDynLoad_Module module,
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
OSDynLoad_Release(OSDynLoad_Module module);


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


/**
 * Set the allocator functions to use for thread local storage.
 */
OSDynLoad_Error
OSDynLoad_SetTLSAllocator(OSDynLoadAllocFn allocFn,
                          OSDynLoadFreeFn freeFn);


/**
 * Get the allocator functions used for thread local storage.
 */
OSDynLoad_Error
OSDynLoad_GetTLSAllocator(OSDynLoadAllocFn *outAllocFn,
                          OSDynLoadFreeFn *outFreeFn);


/**
* Gets the name for a given module handle.
* Using the value "-1" as module handle gets the name of the running main rpl
**/
OSDynLoad_Error
OSDynLoad_GetModuleName(OSDynLoad_Module module,
                        char *nameBuf,
                        int32_t *nameBufSize);


/**
 * Gets the number of currently loaded RPLs.
 *
 * Always returns 0 on release versions of CafeOS.
 * Requires OSGetSecurityLevel() > 0.
 */
int32_t
OSDynLoad_GetNumberOfRPLs();


/**
 * Get information about the currently loaded RPLs.
 *
 * \param first the index of the first RPL to retrieve info for.
 * \param count the number of RPLs to retrieve info for
 * \param outInfos buffer of RPL info to be filled, should be an array of at
 *                 least count size.
 *
 * Always returns FALSE on release versions of CafeOS.
 * Requires OSGetSecurityLevel() > 0.
 */
BOOL
OSDynLoad_GetRPLInfo(uint32_t first,
                     uint32_t count,
                     OSDynLoad_NotifyData *outInfos);


/**
 * The prototype for an RPL entry point.
 *
 * Use this instead of main when creating .rpl files
 */
int
rpl_entry(OSDynLoad_Module module,
          OSDynLoad_EntryReason reason);

#ifdef __cplusplus
}
#endif

/** @} */
