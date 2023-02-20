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
typedef struct OSDynLoad_LoaderHeapStatistics OSDynLoad_LoaderHeapStatistics;
typedef void *OSDynLoad_Module;

typedef struct OSDynLoad_LoaderUserFileInfo OSDynLoad_LoaderUserFileInfo;
typedef struct OSDynLoad_LoaderSectionInfo OSDynLoad_LoaderSectionInfo;
typedef struct OSDynLoad_InternalData OSDynLoad_InternalData;

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
   OS_DYNLOAD_MODULE_NOT_FOUND            = 0xFFFFFFFA,
} OSDynLoad_Error;

typedef OSDynLoad_Error (*OSDynLoadAllocFn)(int32_t size, int32_t align, void **outAddr);
typedef void (*OSDynLoadFreeFn)(void *addr);

typedef enum OSDynLoad_ExportType {
  OS_DYNLOAD_EXPORT_FUNC = 0,
  OS_DYNLOAD_EXPORT_DATA = 1,
} OSDynLoad_ExportType;

typedef enum OSDynLoad_EntryReason
{
  OS_DYNLOAD_LOADED                       = 1,
  OS_DYNLOAD_UNLOADED                     = 2,
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

struct OSDynLoad_LoaderHeapStatistics
{
   uint32_t codeHeapUsed;
   uint32_t unk_0x04;
   uint32_t codeHeapFree;
   uint32_t codeHeapLargestFree;
   uint32_t dataHeapUsed;
   uint32_t unk_0x14;
};
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x00, codeHeapUsed);
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x04, unk_0x04);
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x08, codeHeapFree);
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x0C, codeHeapLargestFree);
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x10, dataHeapUsed);
WUT_CHECK_OFFSET(OSDynLoad_LoaderHeapStatistics, 0x14, unk_0x14);
WUT_CHECK_SIZE(OSDynLoad_LoaderHeapStatistics, 0x18);

struct OSDynLoad_LoaderUserFileInfo
{
    uint32_t size;
    uint32_t magic;
    uint32_t pathStringLength;
    char *pathString;
    uint32_t fileInfoFlags;
    int16_t tlsModuleIndex;
    int16_t tlsAlignShift;
    void *tlsAddressStart;
    uint32_t tlsSectionSize;
    uint32_t shstrndx;
    uint32_t titleLocation;
    WUT_UNKNOWN_BYTES(0x60 - 0x28);
};
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x00, size);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x04, magic);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x08, pathStringLength);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x0C, pathString);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x10, fileInfoFlags);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x14, tlsModuleIndex);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x16, tlsAlignShift);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x18, tlsAddressStart);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x1C, tlsSectionSize);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x20, shstrndx);
WUT_CHECK_OFFSET(OSDynLoad_LoaderUserFileInfo, 0x24, titleLocation);
WUT_CHECK_SIZE(OSDynLoad_LoaderUserFileInfo, 0x60);


struct OSDynLoad_LoaderSectionInfo
{
    uint32_t type;
    uint32_t flags;
    void *address;

    union {
        //! Size of the section, set when type != SHT_RPL_IMPORTS
        uint32_t size;

        //! Name offset of the section, set when type == SHT_RPL_IMPORTS
        uint32_t name;
    };
};
WUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x00, type);
WUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x04, flags);
WUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x08, address);
WUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x0C, size);
WUT_CHECK_OFFSET(OSDynLoad_LoaderSectionInfo, 0x0C, name);
WUT_CHECK_SIZE(OSDynLoad_LoaderSectionInfo, 0x10);


struct OSDynLoad_InternalData
{
    uint32_t handle;
    void *loaderHandle;
    char *moduleName;
    uint32_t moduleNameLen;
    uint32_t sectionInfoCount;
    OSDynLoad_LoaderSectionInfo *sectionInfo;
    OSDynLoad_InternalData **importModules;
    uint32_t importModuleCount;
    uint32_t userFileInfoSize;
    OSDynLoad_LoaderUserFileInfo *userFileInfo;
    OSDynLoad_NotifyData *notifyData;
    void *entryPoint;
    uint32_t dataSectionSize;
    void *dataSection;
    uint32_t loadSectionSize;
    void *loadSection;
    OSDynLoadFreeFn dynLoadFreeFn;
    void *codeExports;
    uint32_t numCodeExports;
    void *dataExports;
    uint32_t numDataExports;
    OSDynLoad_InternalData *next;
    WUT_UNKNOWN_BYTES(0x94 - 0x58);
};
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x00, handle);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x04, loaderHandle);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x08, moduleName);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x0C, moduleNameLen);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x10, sectionInfoCount);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x14, sectionInfo);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x18, importModules);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x1C, importModuleCount);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x20, userFileInfoSize);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x24, userFileInfo);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x28, notifyData);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x2C, entryPoint);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x30, dataSectionSize);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x34, dataSection);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x38, loadSectionSize);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x3C, loadSection);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x40, dynLoadFreeFn);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x44, codeExports);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x48, numCodeExports);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x4C, dataExports);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x50, numDataExports);
WUT_CHECK_OFFSET(OSDynLoad_InternalData, 0x54, next);
WUT_CHECK_SIZE(OSDynLoad_InternalData, 0x94);

typedef enum OSDynLoad_NotifyReason
{
  OS_DYNLOAD_NOTIFY_UNLOADED              = 0,
  OS_DYNLOAD_NOTIFY_LOADED                = 1
} OSDynLoad_NotifyReason;

typedef void (*OSDynLoadNotifyFunc)(OSDynLoad_Module module,
                                    void *userContext,
                                    OSDynLoad_NotifyReason notifyReason,
                                    OSDynLoad_NotifyData *infos);

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
                     OSDynLoad_ExportType exportType,
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
 * Get loader heap statistics.
 */
OSDynLoad_Error
OSDynLoad_GetLoaderHeapStatistics(OSDynLoad_LoaderHeapStatistics *outLoaderHeapStatistics);


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
* Checks if a module is already loaded. Does not load any modules.
*
* Returns OS_DYNLOAD_OK on success.
**/
OSDynLoad_Error
OSDynLoad_IsModuleLoaded(char const *name,
                         OSDynLoad_Module *outModule);

/**
* Registers a callback that's called whenever a new .rpl is loaded or unloaded
**/
OSDynLoad_Error
OSDynLoad_AddNotifyCallback(OSDynLoadNotifyFunc notifyFn, 
                            void *userContext);

/**
* Removes a previously added a callback
**/
OSDynLoad_Error
OSDynLoad_DelNotifyCallback(OSDynLoadNotifyFunc notifyFn, 
                            void *userContext);

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
