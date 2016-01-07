#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

typedef struct MEMUnitHeap MEMUnitHeap;

struct MEMUnitHeap
{
};
UNKNOWN_SIZE(MEMUnitHeap);

MEMUnitHeap *
MEMCreateUnitHeapEx(MEMUnitHeap *heap,
                    uint32_t size,
                    uint32_t blockSize,
                    int32_t alignment,
                    uint16_t flags);

void *
MEMDestroyUnitHeap(MEMUnitHeap *heap);

void *
MEMAllocFromUnitHeap(MEMUnitHeap *heap);

void
MEMFreeToUnitHeap(MEMUnitHeap *heap,
                  void *block);

void
MEMiDumpUnitHeap(MEMUnitHeap *heap);

uint32_t
MEMCountFreeBlockForUnitHeap(MEMUnitHeap *heap);

uint32_t
MEMCalcHeapSizeForUnitHeap(uint32_t blockSize,
                           uint32_t count,
                           int32_t alignment);

WUT_LIB_HEADER_END
