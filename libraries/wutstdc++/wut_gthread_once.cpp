#include "wut_gthread.h"

int __wut_once(__wut_once_t *once,
               void (*func)(void))
{
   uint32_t value = 0;

   if (OSCompareAndSwapAtomicEx(once,
                                __WUT_ONCE_VALUE_INIT,
                                __WUT_ONCE_VALUE_STARTED,
                                &value)) {
      func();
      OSCompareAndSwapAtomic(once,
                             __WUT_ONCE_VALUE_STARTED,
                             __WUT_ONCE_VALUE_DONE);
   } else if (value != __WUT_ONCE_VALUE_DONE) {
      while (!OSCompareAndSwapAtomic(once,
                                     __WUT_ONCE_VALUE_DONE,
                                     __WUT_ONCE_VALUE_DONE))
         ;
   }

   return 0;
}
