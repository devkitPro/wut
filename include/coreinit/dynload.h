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

typedef enum OSDynLoad_EntryReason
{
  OS_DYNLOAD_LOADED                       = 0,
  OS_DYNLOAD_UNLOADED                     = 1,
} OSDynLoad_EntryReason;

typedef void *OSDynLoad_Module;

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
* Gets the amount of currently loaded RPLs.
* This function is typically disabled in release versions of the SDK and will always return 0
* so you need to patch OSGetSecurityLevel() to always return a value > 0.
*/
int
OSDynLoad_GetNumberOfRPLs();

typedef struct _OSDynLoad_NotifyHdr _OSDynLoad_NotifyHdr;

struct _OSDynLoad_NotifyHdr {
	char *mpName;            		 /* allocated C string for full path of file */
	unsigned int mDebug_TextAddr;    /* address where TEXT segment of RPX/RPL is loaded */
	unsigned int mDebug_TextOffset;  /* offset from linked address for the loaded TEXT segment */
	unsigned int mDebug_TextSize;    /* size of loaded TEXT segment */
	unsigned int mDebug_DataAddr;    /* address where DATA and BSS segment of RPX/RPL is loaded */
	unsigned int mDebug_DataOffset;  /* offset from linked address for the loaded DATA and BSS segment */
	unsigned int mDebug_DataSize;    /* size of loaded DATA and BSS segment */
	unsigned int mDebug_ReadAddr;    /* address where RODATA segment of RPX/RPL is loaded */
	unsigned int mDebug_ReadOffset;  /* offset from linked address for the loaded RODATA segment */
	unsigned int mDebug_ReadSize;    /* size of loaded RODATA segment */
};

WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0, mpName);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 4, mDebug_TextAddr);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 8, mDebug_TextOffset);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0xC, mDebug_TextSize);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x10, mDebug_DataAddr);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x14, mDebug_DataOffset);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x18, mDebug_DataSize);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x1C, mDebug_ReadAddr);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x20, mDebug_ReadOffset);
WUT_CHECK_OFFSET(_OSDynLoad_NotifyHdr, 0x24, mDebug_ReadSize);

/**
 * This function will fill the info buffer with RPL information based on the index of the loaded RPL.
 * The count should be the number of loaded RPLs returned by the OSDynLoad_GetNumberOfRPLs() function.
 * The same caveat regarding the OSGetSecurityLevel() function applies.
 */
BOOL
OSDynLoad_GetRPLInfo(unsigned int index, unsigned int count, struct _OSDynLoad_NotifyHdr *info_buffer);

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
                        char * nameBuf,
                        int32_t * nameBufSize);

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
