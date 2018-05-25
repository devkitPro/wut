#include "include/bits/gthr-default.h"

#include <coreinit/alarm.h>
#include <coreinit/systeminfo.h>
#include <coreinit/time.h>
#include <chrono>

void
__gthread_cond_init_function (__gthread_cond_t *__cond)
{
   OSInitCond(__cond);
}

int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

struct TimedWaitData
{
   __gthread_cond_t *cond;
   bool timed_out;
};

static void
__gthread_timedwait_alarm_callback(OSAlarm *alarm, OSContext *context)
{
   TimedWaitData *data = (TimedWaitData *)OSGetAlarmUserData(alarm);
   data->timed_out = true;
   OSSignalCond(data->cond);
}

int
__gthread_cond_timedwait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex,
                          const __gthread_time_t *__abs_timeout)
{
   auto time = std::chrono::system_clock::now();
   auto timeout = std::chrono::system_clock::time_point(
      std::chrono::seconds(__abs_timeout->tv_sec) +
      std::chrono::nanoseconds(__abs_timeout->tv_nsec));

   // Already timed out!
   if (timeout <= time) {
      return ETIMEDOUT;
   }

   auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(timeout - time);

   // Set an alarm
   OSAlarm alarm;
   TimedWaitData data;
   data.timed_out = false;
   data.cond = __cond;

   OSCreateAlarm(&alarm);
   OSSetAlarmUserData(&alarm, &data);
   OSSetAlarm(&alarm, OSNanoseconds(duration.count()),
              &__gthread_timedwait_alarm_callback);

   // Wait on the condition
   OSWaitCond(__cond, __mutex);

   OSCancelAlarm(&alarm);
   return data.timed_out ? ETIMEDOUT : 0;
}

int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
                               __gthread_recursive_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
   return 0;
}
