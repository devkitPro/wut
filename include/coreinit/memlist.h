#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_memlist Memory List
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMMemoryLink MEMMemoryLink;
typedef struct MEMMemoryList MEMMemoryList;

struct MEMMemoryLink
{
   void *prev;
   void *next;
};
WUT_CHECK_OFFSET(MEMMemoryLink, 0x0, prev);
WUT_CHECK_OFFSET(MEMMemoryLink, 0x4, next);
WUT_CHECK_SIZE(MEMMemoryLink, 0x8);

struct MEMMemoryList
{
   void *head;
   void *tail;
   uint16_t count;
   uint16_t offsetToMemoryLink;
};
WUT_CHECK_OFFSET(MEMMemoryList, 0x0, head);
WUT_CHECK_OFFSET(MEMMemoryList, 0x4, tail);
WUT_CHECK_OFFSET(MEMMemoryList, 0x8, count);
WUT_CHECK_OFFSET(MEMMemoryList, 0xa, offsetToMemoryLink);
WUT_CHECK_SIZE(MEMMemoryList, 0xc);

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
MEMGetNthListObject(MEMMemoryList *list,
                    uint16_t n);

#ifdef __cplusplus
}
#endif

/** @} */
