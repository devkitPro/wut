#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

struct MEMMemoryLink
{
   void *prev;
   void *next;
};

CHECK_OFFSET(MemoryLink, 0x0, prev);
CHECK_OFFSET(MemoryLink, 0x4, next);
CHECK_SIZE(MemoryLink, 0x8);

struct MEMMemoryList
{
   void *head;
   void *tail;
   uint16_t count;
   uint16_t offsetToMemoryLink;
};
CHECK_OFFSET(MEMMemoryList, 0x0, head);
CHECK_OFFSET(MEMMemoryList, 0x4, tail);
CHECK_OFFSET(MEMMemoryList, 0x8, count);
CHECK_OFFSET(MEMMemoryList, 0xa, offsetToMemoryLink);
CHECK_SIZE(MEMMemoryList, 0xc);

void
MEMInitList(MEMMemoryList *list,
            uint16_t offsetToMemoryLink);

void
MEMAppendListObject(MEMMemoryList *list,
                    void *object);

void
MEMPrependListObject(MEMMemoryList *list,
                     void *object);

void
MEMInsertListObject(MEMMemoryList *list,
                    void *before,
                    void *object);

void
MEMRemoveListObject(MEMMemoryList *list,
                    void *object);

void *
MEMGetNextListObject(MEMMemoryList *list,
                     void *object);

void *
MEMGetPrevListObject(MEMMemoryList *list,
                     void *object);

void *
MEMGetNthListObject(MEMMEMMemoryList *list,
                    uint16_t n);

WUT_LIB_HEADER_END
