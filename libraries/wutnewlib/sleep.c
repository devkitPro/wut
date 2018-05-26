#include <coreinit/thread.h>
#include <coreinit/systeminfo.h>
#include <coreinit/time.h>
#include <unistd.h>

unsigned sleep(unsigned seconds)
{
   OSSleepTicks(OSSeconds(seconds));
   return 0;
}

int usleep(useconds_t microseconds)
{
   OSSleepTicks(OSMicroseconds(microseconds));
   return 0;
}
