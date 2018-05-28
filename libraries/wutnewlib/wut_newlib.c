#include "wut_newlib.h"
#include <coreinit/exit.h>

static void
__init_wut_syscall_array()
{
   __syscalls.sbrk_r = __wut_sbrk_r;
   __syscalls.lock_init = __wut_lock_init;
   __syscalls.lock_close = __wut_lock_close;
   __syscalls.lock_acquire = __wut_lock_acquire;
   __syscalls.lock_release = __wut_lock_release;
   __syscalls.malloc_lock = __wut_malloc_lock;
   __syscalls.malloc_unlock = __wut_malloc_unlock;
   __syscalls.exit = exit;
   __syscalls.gettod_r = __wut_gettod_r;
   __syscalls.clock_gettime = __wut_clock_gettime;
   __syscalls.clock_settime = __wut_clock_settime;
   __syscalls.clock_getres = __wut_clock_getres;
   __syscalls.nanosleep = __wut_nanosleep;
}

void
__init_wut_newlib()
{
   __init_wut_sbrk_heap();
   __init_wut_malloc_lock();
   __init_wut_syscall_array();
}

void
__fini_wut_newlib()
{
   __fini_wut_sbrk_heap();
}
