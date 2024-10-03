#include "wut_gthread.h"
#include "../wutnewlib/wut_clock.h"

#include <sys/errno.h>
#include <sys/time.h>

#include <coreinit/alarm.h>
#include <coreinit/systeminfo.h>
#include <coreinit/time.h>

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
   data->timed_out                   = true;
   OSSignalCond(data->cond);
}

int
__wut_cond_timedwait(OSCondition *cond, OSMutex *mutex, const __gthread_time_t *abs_timeout)
{
   __wut_cond_timedwait_data_t data;
   data.timed_out = false;
   data.cond      = cond;

   OSTime time    = OSGetTime();
   OSTime timeout =
      OSSecondsToTicks(abs_timeout->tv_sec - EPOCH_DIFF_SECS(WIIU_OSTIME_EPOCH_YEAR)) +
      OSNanosecondsToTicks(abs_timeout->tv_nsec);

   // Already timed out!
   if (timeout <= time) {
      return ETIMEDOUT;
   }

   // Set an alarm
   OSAlarm alarm;
   OSCreateAlarm(&alarm);
   OSSetAlarmUserData(&alarm, &data);
   OSSetAlarm(&alarm, timeout - time,
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
__wut_cond_destroy(OSCondition *cond)
{
   return 0;
}
