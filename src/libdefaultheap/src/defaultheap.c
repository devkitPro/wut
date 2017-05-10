#include "defaultheap.h"
#include <coreinit/dynload.h>

typedef void *(*MEMAllocFromDefaultHeapFn)(uint32_t size);
typedef void *(*MEMAllocFromDefaultHeapExFn)(uint32_t size,  int32_t alignment);
typedef void (*MEMFreeToDefaultHeapFn)(void *block);

static OSDynLoadModule sCoreinitHandle = 0;
static MEMAllocFromDefaultHeapFn *MEMAllocFromDefaultHeapPtr = NULL;
static MEMAllocFromDefaultHeapExFn *MEMAllocFromDefaultHeapExPtr = NULL;
static MEMFreeToDefaultHeapFn *MEMFreeToDefaultHeapPtr = NULL;

void *
MEMAllocFromDefaultHeap(uint32_t size)
{
   if (!sCoreinitHandle) {
      if (OSDynLoad_Acquire("coreinit.rpl", &sCoreinitHandle)) {
         return NULL;
      }
   }

   if (!MEMAllocFromDefaultHeapPtr) {
      if (OSDynLoad_FindExport(sCoreinitHandle,
                               TRUE,
                               "MEMAllocFromDefaultHeap",
                               (void **)&MEMAllocFromDefaultHeapPtr)) {
         return NULL;
      }
   }

   return (**MEMAllocFromDefaultHeapPtr)(size);
}

void *
MEMAllocFromDefaultHeapEx(uint32_t size,
                          int32_t alignment)
{
   if (!sCoreinitHandle) {
      if (OSDynLoad_Acquire("coreinit.rpl", &sCoreinitHandle)) {
         return NULL;
      }
   }

   if (!MEMAllocFromDefaultHeapExPtr) {
      if (OSDynLoad_FindExport(sCoreinitHandle,
                               TRUE,
                               "MEMAllocFromDefaultHeapEx",
                               (void **)&MEMAllocFromDefaultHeapExPtr)) {
         return NULL;
      }
   }

   return (**MEMAllocFromDefaultHeapExPtr)(size, alignment);
}

void
MEMFreeToDefaultHeap(void *block)
{
   if (!sCoreinitHandle) {
      if (OSDynLoad_Acquire("coreinit.rpl", &sCoreinitHandle)) {
         return;
      }
   }

   if (!MEMFreeToDefaultHeapPtr) {
      if (OSDynLoad_FindExport(sCoreinitHandle,
                               TRUE,
                               "MEMFreeToDefaultHeap",
                               (void **)&MEMFreeToDefaultHeapPtr)) {
         return;
      }
   }

   (**MEMFreeToDefaultHeapPtr)(block);
}
