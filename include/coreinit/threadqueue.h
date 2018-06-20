#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_threadq Thread Queue
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSThread OSThread;

typedef struct OSThreadLink OSThreadLink;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSThreadSimpleQueue OSThreadSimpleQueue;

struct OSThreadLink
{
   OSThread *prev;
   OSThread *next;
};
WUT_CHECK_OFFSET(OSThreadLink, 0x00, prev);
WUT_CHECK_OFFSET(OSThreadLink, 0x04, next);
WUT_CHECK_SIZE(OSThreadLink, 0x8);

struct OSThreadQueue
{
   OSThread *head;
   OSThread *tail;
   void *parent;
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(OSThreadQueue, 0x00, head);
WUT_CHECK_OFFSET(OSThreadQueue, 0x04, tail);
WUT_CHECK_OFFSET(OSThreadQueue, 0x08, parent);
WUT_CHECK_SIZE(OSThreadQueue, 0x10);

struct OSThreadSimpleQueue
{
   OSThread *head;
   OSThread *tail;
};
WUT_CHECK_OFFSET(OSThreadSimpleQueue, 0x00, head);
WUT_CHECK_OFFSET(OSThreadSimpleQueue, 0x04, tail);
WUT_CHECK_SIZE(OSThreadSimpleQueue, 0x08);

void
OSInitThreadQueue(OSThreadQueue *queue);

void
OSInitThreadQueueEx(OSThreadQueue *queue,
                    void *parent);

#ifdef __cplusplus
}
#endif

/** @} */
