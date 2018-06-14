#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_memorymap Memory Map
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSMemoryMapMode
{
   OS_MAP_MEMORY_INVALID      = 0,
   OS_MAP_MEMORY_READ_ONLY    = 1,
   OS_MAP_MEMORY_READ_WRITE   = 2,
   OS_MAP_MEMORY_FREE         = 3,
   OS_MAP_MEMORY_ALLOCATED    = 4,
} OSMemoryMapMode;

#define OS_PAGE_SIZE (128 * 1024)

uint32_t
OSEffectiveToPhysical(uint32_t virtualAddress);

uint32_t
OSAllocVirtAddr(uint32_t virtualAddress,
                uint32_t size,
                uint32_t align);

BOOL
OSFreeVirtAddr(uint32_t virtualAddress,
               uint32_t size);

OSMemoryMapMode
OSQueryVirtAddr(uint32_t virtualAddress);

BOOL
OSMapMemory(uint32_t virtualAddress,
            uint32_t physicalAddress,
            uint32_t size,
            OSMemoryMapMode mode);

BOOL
OSUnmapMemory(uint32_t virtualAddress,
              uint32_t size);

void
OSGetMapVirtAddrRange(uint32_t *outVirtualAddress,
                      uint32_t *outSize);

void
OSGetAvailPhysAddrRange(uint32_t *outPhysicalAddress,
                        uint32_t *outSize);

void
OSGetDataPhysAddrRange(uint32_t *outPhysicalAddress,
                       uint32_t *outSize);

#ifdef __cplusplus
}
#endif
