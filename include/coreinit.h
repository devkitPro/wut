#pragma once

/**
 * \defgroup coreinit coreinit
 *
 * Contains all core operating system functions such as threads, synchronisation
 * objects, filesystem, memory, exception handling, etc...
 */

#include <coreinit/alarm.h>
#include <coreinit/atomic.h>
#include <coreinit/atomic64.h>
#include <coreinit/bsp.h>
#include <coreinit/cache.h>
#include <coreinit/codegen.h>
#include <coreinit/condition.h>
#include <coreinit/context.h>
#include <coreinit/copydata.h>
#include <coreinit/core.h>
#include <coreinit/coroutine.h>
#include <coreinit/cosreport.h>
#include <coreinit/debug.h>
#include <coreinit/dynload.h>
#include <coreinit/energysaver.h>
#include <coreinit/event.h>
#include <coreinit/exception.h>
#include <coreinit/exit.h>
#include <coreinit/fastcondition.h>
#include <coreinit/fastmutex.h>
#include <coreinit/fiber.h>
#include <coreinit/filesystem.h>
#include <coreinit/filesystem_fsa.h>
#include <coreinit/foreground.h>
#include <coreinit/im.h>
#include <coreinit/internal.h>
#include <coreinit/interrupts.h>
#include <coreinit/ios.h>
#include <coreinit/ipcbufpool.h>
#include <coreinit/kernel.h>
#include <coreinit/launch.h>
#include <coreinit/mcp.h>
#include <coreinit/memallocator.h>
#include <coreinit/memblockheap.h>
#include <coreinit/memdefaultheap.h>
#include <coreinit/memexpheap.h>
#include <coreinit/memfrmheap.h>
#include <coreinit/memheap.h>
#include <coreinit/memlist.h>
#include <coreinit/memory.h>
#include <coreinit/memorymap.h>
#include <coreinit/memunitheap.h>
#include <coreinit/messagequeue.h>
#include <coreinit/mutex.h>
#include <coreinit/performancemonitor.h>
#include <coreinit/rendezvous.h>
#include <coreinit/savedframe.h>
#include <coreinit/scheduler.h>
#include <coreinit/screen.h>
#include <coreinit/semaphore.h>
#include <coreinit/smd.h>
#include <coreinit/spinlock.h>
#include <coreinit/stopwatch.h>
#include <coreinit/stopwatchatomic.h>
#include <coreinit/systeminfo.h>
#include <coreinit/taskqueue.h>
#include <coreinit/thread.h>
#include <coreinit/threadqueue.h>
#include <coreinit/time.h>
#include <coreinit/title.h>
#include <coreinit/transition.h>
#include <coreinit/userconfig.h>
