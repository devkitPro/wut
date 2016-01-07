#pragma once
#include <wut.h>
#include "threadqueue.h"

/**
 * \defgroup coreinit_cond Condition Variable
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSCondition OSCondition;
typedef struct OSMutex OSMutex;

#define OS_CONDITION_TAG 0x634E6456u

struct OSCondition
{
   //! Should always be set to the value OS_CONDITION_TAG.
   uint32_t tag;

   //! Name set by OSInitCondEx.
   const char *name;

   UNKNOWN(4);

   //! Queue of threads currently waiting on condition with OSWaitCond.
   OSThreadQueue queue;
};
CHECK_OFFSET(OSCondition, 0x00, tag);
CHECK_OFFSET(OSCondition, 0x04, name);
CHECK_OFFSET(OSCondition, 0x0c, queue);
CHECK_SIZE(OSCondition, 0x1c);

void
OSInitCond(OSCondition *condition);

void
OSInitCondEx(OSCondition *condition,
             const char *name);

void
OSWaitCond(OSCondition *condition,
           OSMutex *mutex);

void
OSSignalCond(OSCondition *condition);

#ifdef __cplusplus
}
#endif

/** @} */
