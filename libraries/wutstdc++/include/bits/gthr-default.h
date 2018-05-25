/* Threads compatibility routines for libgcc2 and libobjc.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1997-2016 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef _GLIBCXX_GCC_GTHR_SINGLE_H
#define _GLIBCXX_GCC_GTHR_SINGLE_H

#define __GTHREADS 1
#define __GTHREADS_CXX0X 1

#include <coreinit/condition.h>
#include <coreinit/thread.h>
#include <coreinit/mutex.h>
#include <coreinit/baseheap.h>
#include <coreinit/expandedheap.h>

#include <string.h>
#include <sys/errno.h>

#define _GTHREAD_USE_MUTEX_TIMEDLOCK 0

typedef OSThread *__gthread_t;
typedef uint32_t __gthread_once_t;
typedef OSMutex __gthread_mutex_t;
typedef OSMutex __gthread_recursive_mutex_t;
typedef OSCondition __gthread_cond_t;
typedef struct timespec __gthread_time_t;

// Unimplemented
typedef void *__gthread_key_t;

#define __GTHREAD_HAS_COND 1

#define __GTHREAD_ONCE_INIT { }
#define __GTHREAD_MUTEX_INIT_FUNCTION __gthread_mutex_init_function
#define __GTHREAD_RECURSIVE_MUTEX_INIT_FUNCTION __gthread_recursive_mutex_init_function
#define __GTHREAD_COND_INIT_FUNCTION __gthread_cond_init_function
#define __GTHREAD_TIME_INIT { 0, 0 }

#define __GTHREAD_STACK_SIZE (4096*1024)

static inline int
__gthread_active_p (void)
{
   return 1;
}

static inline void
__gthread_thread_deallocator(OSThread *thread, void *stack)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   MEMFreeToExpHeap(heap, thread);
   MEMFreeToExpHeap(heap, stack);
}

static inline int
__gthread_create (__gthread_t *__threadid, void *(*__func) (void*),
        void *__args)
{
   MEMExpandedHeap *heap = (MEMExpandedHeap *)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
   OSThread *thread = (OSThread *)MEMAllocFromExpHeapEx(heap, sizeof(OSThread), 8);
   char *stack = (char *)MEMAllocFromExpHeapEx(heap, __GTHREAD_STACK_SIZE, 8);
   memset(thread, 0, sizeof(OSThread));

   if (!OSCreateThread(thread,
                       (OSThreadEntryPointFn)__func,
                       (int)__args,
                       NULL,
                       stack + __GTHREAD_STACK_SIZE,
                       __GTHREAD_STACK_SIZE,
                       16,
                       OS_THREAD_ATTRIB_AFFINITY_ANY)) {
      MEMFreeToExpHeap((MEMExpandedHeap*)MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), thread);
      return EINVAL;
   }

   *__threadid = thread;
   OSSetThreadDeallocator(thread, &__gthread_thread_deallocator);
   OSResumeThread(thread);
   return 0;
}

static inline int
__gthread_join (__gthread_t __threadid, void **__value_ptr)
{
   if (!OSJoinThread(__threadid, (int *)__value_ptr)) {
      return EINVAL;
   }
   return 0;
}

static inline int
__gthread_detach (__gthread_t __threadid)
{
   OSDetachThread(__threadid);
   return 0;
}

static inline int
__gthread_equal (__gthread_t __t1, __gthread_t __t2)
{
   return __t1 == __t2;
}

static inline __gthread_t
__gthread_self (void)
{
   return OSGetCurrentThread();
}

static inline int
__gthread_yield (void)
{
   OSYieldThread();
   return 0;
}

static inline int
__gthread_once (__gthread_once_t *__once, void (*__func) (void))
{
   // TODO: Implement __gthread_once
   return -1;
}

static inline int
__gthread_key_create (__gthread_key_t *__key, void (*__dtor) (void *))
{
   // TODO: Implement __gthread_key_create
   return -1;
}

static inline int
__gthread_key_delete (__gthread_key_t __key)
{
   // TODO: Implement __gthread_key_delete
   return -1;
}

static inline void *
__gthread_getspecific (__gthread_key_t __key)
{
   // TODO: Implement __gthread_getspecific
   return NULL;
}

static inline int
__gthread_setspecific (__gthread_key_t __key, const void *__ptr)
{
   // TODO: Implement __gthread_setspecific
   return -1;
}

static inline void
__gthread_mutex_init_function (__gthread_mutex_t *__mutex)
{
   OSInitMutex(__mutex);
}

static inline int
__gthread_mutex_destroy (__gthread_mutex_t *__mutex)
{
   return 0;
}

static inline int
__gthread_mutex_lock (__gthread_mutex_t *__mutex)
{
   OSLockMutex(__mutex);
   return 0;
}

static inline int
__gthread_mutex_trylock (__gthread_mutex_t *__mutex)
{
   if (!OSTryLockMutex(__mutex)) {
      return -1;
   }

   return 0;
}

static inline int
__gthread_mutex_unlock (__gthread_mutex_t *__mutex)
{
   OSUnlockMutex(__mutex);
   return 0;
}

static inline int
__gthread_recursive_mutex_init_function (__gthread_recursive_mutex_t *__mutex)
{
   OSInitMutex(__mutex);
   return 0;
}

static inline int
__gthread_recursive_mutex_lock (__gthread_recursive_mutex_t *__mutex)
{
   OSLockMutex(__mutex);
   return 0;
}

static inline int
__gthread_recursive_mutex_trylock (__gthread_recursive_mutex_t *__mutex)
{
   if (!OSTryLockMutex(__mutex)) {
      return -1;
   }

   return 0;
}

static inline int
__gthread_recursive_mutex_unlock (__gthread_recursive_mutex_t *__mutex)
{
   OSUnlockMutex(__mutex);
   return 0;
}

static inline int
__gthread_recursive_mutex_destroy (__gthread_recursive_mutex_t *__mutex)
{
   return 0;
}

static inline void
__gthread_cond_init_function (__gthread_cond_t *__cond)
{
   OSInitCond(__cond);
}

static inline int
__gthread_cond_broadcast (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

static inline int
__gthread_cond_signal (__gthread_cond_t *__cond)
{
   OSSignalCond(__cond);
   return 0;
}

static inline int
__gthread_cond_wait (__gthread_cond_t *__cond, __gthread_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

static inline int
__gthread_cond_wait_recursive (__gthread_cond_t *__cond,
                __gthread_recursive_mutex_t *__mutex)
{
   OSWaitCond(__cond, __mutex);
   return 0;
}

static inline int
__gthread_cond_destroy (__gthread_cond_t* __cond)
{
   return 0;
}

#endif /* ! _GLIBCXX_GCC_GTHR_SINGLE_H */
