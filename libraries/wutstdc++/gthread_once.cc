#include "include/bits/gthr-default.h"

int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
   uint32_t value = 0;

   if (OSCompareAndSwapAtomicEx(__once,
                                __GTHREAD_ONCE_VALUE_INIT,
                                __GTHREAD_ONCE_VALUE_STARTED,
                                &value)) {
      __func();
      OSCompareAndSwapAtomic(__once,
                             __GTHREAD_ONCE_VALUE_STARTED,
                             __GTHREAD_ONCE_VALUE_DONE);
   } else if (value != __GTHREAD_ONCE_VALUE_DONE) {
      while (!OSCompareAndSwapAtomic(__once,
                                     __GTHREAD_ONCE_VALUE_DONE,
                                     __GTHREAD_ONCE_VALUE_DONE));
   }

   return 0;
}
