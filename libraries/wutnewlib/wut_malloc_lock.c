#include "wut_newlib.h"

#include <coreinit/mutex.h>

static OSMutex sMallocMutex;

void
__wut_malloc_lock(struct _reent *r)
{
   OSLockMutex(&sMallocMutex);
}

void
__wut_malloc_unlock(struct _reent *r)
{
   OSUnlockMutex(&sMallocMutex);
}

void
__init_wut_malloc_lock()
{
   OSInitMutex(&sMallocMutex);
}
