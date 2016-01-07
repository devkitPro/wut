#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

typedef uint32_t MEMBaseHeapType;
typedef void *MEMHeapHandle;

enum MEMBaseHeapType
{
   MEM_BASE_HEAP_MEM1   = 0,
   MEM_BASE_HEAP_MEM2   = 1,
   MEM_BASE_HEAP_FG     = 8,
};

MEMBaseHeapType
MEMGetArena(MEMHeapHandle handle);

MEMHeapHandle
MEMGetBaseHeapHandle(MEMBaseHeapType type);

MEMHeapHandle
MEMSetBaseHeapHandle(MEMBaseHeapType type,
                     MEMHeapHandle handle);

WUT_LIB_HEADER_END
