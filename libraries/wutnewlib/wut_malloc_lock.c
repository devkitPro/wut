#include "wut_newlib.h"

#include <coreinit/spinlock.h>

static OSSpinLock sMallocSpinLock;

void
__wut_malloc_lock(struct _reent *r)
{
   OSUninterruptibleSpinLock_Acquire(&sMallocSpinLock);
}

void
__wut_malloc_unlock(struct _reent *r)
{
   OSUninterruptibleSpinLock_Release(&sMallocSpinLock);
}

void
__init_wut_malloc_lock()
{
   OSInitSpinLock(&sMallocSpinLock);
}
