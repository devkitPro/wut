#pragma once
#include <wut.h>
#include "thread.h"
#include "time.h"

WUT_LIB_HEADER_START

typedef void *OSDynLoadModule;

typedef int (*OSDynLoadAllocFn)(int size, int align, void **outAddr);
typedef void (*OSDynLoadFreeFn)(void *addr);

int32_t
OSDynLoad_SetAllocator(OSDynLoadAllocFn allocFn,
                       OSDynLoadFreeFn freeFn);

int32_t
OSDynLoad_GetAllocator(OSDynLoadAllocFn *outAllocFn,
                       OSDynLoadFreeFn *outFreeFn);

int32_t
OSDynLoad_Acquire(char const *name,
                  OSDynLoadModule *outModule);

int32_t
OSDynLoad_FindExport(OSDynLoadModule module,
                     int32_t isData,
                     char const *name,
                     void **outAddr);

void
OSDynLoad_Release(OSDynLoadModule module);

WUT_LIB_HEADER_END
