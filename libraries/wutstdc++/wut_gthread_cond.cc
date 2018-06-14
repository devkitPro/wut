#include "wut_gthread.h"

#include <sys/errno.h>

#include <coreinit/alarm.h>
#include <coreinit/systeminfo.h>
#include <coreinit/time.h>
#include <chrono>

void
__wut_cond_init_function(OSCondition *cond)
{
   OSInitCond(cond);
}

int
__wut_cond_broadcast(OSCondition *cond)
{
   OSSignalCond(cond);
   return 0;
}

int
__wut_cond_signal(OSCondition *cond)
{
   OSSignalCond(cond);
   return 0;
}

int
__wut_cond_wait(OSCondition *cond,
                OSMutex *mutex)
{
   OSWaitCond(cond, mutex);
   return 0;
}

struct __wut_cond_timedwait_data_t
{
   OSCondition *cond;
   bool timed_out;
};

static void
__wut_cond_timedwait_alarm_callback(OSAlarm *alarm,
                                    OSContext *context)
{
   __wut_cond_timedwait_data_t *data = (__wut_cond_timedwait_data_t *)OSGetAlarmUserData(alarm);
   data->timed_out = true;
   OSSignalCond(data->cond);
}

int
__wut_cond_timedwait(OSCondition *cond, OSMutex *mutex,
                     const __gthread_time_t *abs_timeout)
{
   __wut_cond_timedwait_data_t data;
   data.timed_out = false;
   data.cond = cond;

   auto time = std::chrono::system_clock::now();
   auto timeout = std::chrono::system_clock::time_point(
      std::chrono::seconds(abs_timeout->tv_sec) +
      std::chrono::nanoseconds(abs_timeout->tv_nsec));

   // Already timed out!
   if (timeout <= time) {
      return ETIMEDOUT;
   }

   auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(timeout - time);

   // Set an alarm
   OSAlarm alarm;
   OSCreateAlarm(&alarm);
   OSSetAlarmUserData(&alarm, &data);
   OSSetAlarm(&alarm, OSNanosecondsToTicks(duration.count()),
              &__wut_cond_timedwait_alarm_callback);

   // Wait on the condition
   OSWaitCond(cond, mutex);

   OSCancelAlarm(&alarm);
   return data.timed_out ? ETIMEDOUT : 0;
}

int
__wut_cond_wait_recursive(OSCondition *cond,
                        OSMutex *mutex)
{
   OSWaitCond(cond, mutex);
   return 0;
}

int
__wut_cond_destroy(OSCondition* cond)
{
   return 0;
}
