#pragma once
#include <wut.h>
#include "time.h"
#include "threadqueue.h"

WUT_LIB_HEADER_START

typedef struct OSContext OSContext;
typedef struct OSFastMutex OSFastMutex;
typedef struct OSFastMutexQueue OSFastMutexQueue;
typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSThread OSThread;

typedef uint8_t OSThreadState;
typedef uint32_t OSThreadRequest;
typedef uint8_t OSThreadAttributes;

typedef int (*OSThreadEntryPointFn)(int argc, const char **argv);
typedef void (*OSThreadCleanupCallbackFn)(OSThread *thread, void *stack);
typedef void (*OSThreadDeallocatorFn)(OSThread *thread, void *stack);

enum OSThreadState
{
   OS_THREAD_STATE_NONE             = 0,
   OS_THREAD_STATE_READY            = 1 << 0,
   OS_THREAD_STATE_RUNNING          = 1 << 1,
   OS_THREAD_STATE_WAITING          = 1 << 2,
   OS_THREAD_STATE_MORIBUND         = 1 << 3,
};

enum OSThreadRequest
{
   OS_THREAD_REQUEST_NONE           = 0,
   OS_THREAD_REQUEST_SUSPEND        = 1,
   OS_THREAD_REQUEST_CANCEL         = 2,
};

enum OSThreadAttributes
{
   OS_THREAD_ATTRIB_AFFINITY_CPU0   = 1 << 0,
   OS_THREAD_ATTRIB_AFFINITY_CPU1   = 1 << 1,
   OS_THREAD_ATTRIB_AFFINITY_CPU2   = 1 << 2,
   OS_THREAD_ATTRIB_AFFINITY_ANY    = 1 << 3,
   OS_THREAD_ATTRIB_DETACHED        = 1 << 4
};

#define OS_CONTEXT_TAG 0x4F53436F6E747874ull

struct OSContext
{
   uint64_t tag;
   uint32_t gpr[32];
   uint32_t cr;
   uint32_t lr;
   uint32_t ctr;
   uint32_t xer;
   uint32_t srr0;
   uint32_t srr1;
   UNKNOWN(0x14);
   uint32_t fpscr;
   double fpr[32];
   uint16_t spinLockCount;
   uint16_t state;
   uint32_t gqr[8];
   UNKNOWN(4);
   double psf[32];
   uint64_t coretime[3];
   uint64_t starttime;
   uint32_t error;
   UNKNOWN(4);
   uint32_t pmc1;
   uint32_t pmc2;
   uint32_t pmc3;
   uint32_t pmc4;
   uint32_t mmcr0;
   uint32_t mmcr1;
};
CHECK_OFFSET(OSContext, 0x00, tag);
CHECK_OFFSET(OSContext, 0x08, gpr);
CHECK_OFFSET(OSContext, 0x88, cr);
CHECK_OFFSET(OSContext, 0x8c, lr);
CHECK_OFFSET(OSContext, 0x90, ctr);
CHECK_OFFSET(OSContext, 0x94, xer);
CHECK_OFFSET(OSContext, 0x98, srr0);
CHECK_OFFSET(OSContext, 0x9c, srr1);
CHECK_OFFSET(OSContext, 0xb4, fpscr);
CHECK_OFFSET(OSContext, 0xb8, fpr);
CHECK_OFFSET(OSContext, 0x1b8, spinLockCount);
CHECK_OFFSET(OSContext, 0x1ba, state);
CHECK_OFFSET(OSContext, 0x1bc, gqr);
CHECK_OFFSET(OSContext, 0x1e0, psf);
CHECK_OFFSET(OSContext, 0x2e0, coretime);
CHECK_OFFSET(OSContext, 0x2f8, starttime);
CHECK_OFFSET(OSContext, 0x300, error);
CHECK_OFFSET(OSContext, 0x308, pmc1);
CHECK_OFFSET(OSContext, 0x30c, pmc2);
CHECK_OFFSET(OSContext, 0x310, pmc3);
CHECK_OFFSET(OSContext, 0x314, pmc4);
CHECK_OFFSET(OSContext, 0x318, mmcr0);
CHECK_OFFSET(OSContext, 0x31c, mmcr1);
CHECK_SIZE(OSContext, 0x320);

struct OSMutexQueue
{
   OSMutex *head;
   OSMutex *tail;
   void *parent;
   UNKNOWN(4);
};
CHECK_OFFSET(OSMutexQueue, 0x0, head);
CHECK_OFFSET(OSMutexQueue, 0x4, tail);
CHECK_OFFSET(OSMutexQueue, 0x8, parent);
CHECK_SIZE(OSMutexQueue, 0x10);

struct OSFastMutexQueue
{
   OSFastMutex *head;
   OSFastMutex *tail;
};
CHECK_OFFSET(OSFastMutexQueue, 0x00, head);
CHECK_OFFSET(OSFastMutexQueue, 0x04, tail);
CHECK_SIZE(OSFastMutexQueue, 0x08);

#define OS_THREAD_TAG 0x74487244u

struct OSThread
{
   OSContext context;
   uint32_t tag;
   OSThreadState state;
   OSThreadAttributes attr;
   uint16_t id;
   int32_t suspendCounter;
   int32_t priority;                      // Actual priority of thread
   int32_t basePriority;                  // Base priority of thread
   int32_t exitValue;                     // Value from OSExitThread
   UNKNOWN(0x35C - 0x338);
   OSThreadQueue *queue;                  // Queue the thread is on
   OSThreadLink link;                     // Thread queue link
   OSThreadQueue joinQueue;               // Queue of threads waiting to join this
   OSMutex *mutex;                        // Mutex we are waiting to lock
   OSMutexQueue mutexQueue;               // Mutexes owned by this thread
   OSThreadLink activeLink;               // Link on active thread queue
   void *stackStart;                      // Stack starting value (top, highest address)
   void *stackEnd;                        // Stack end value (bottom, lowest address)
   OSThreadEntryPointFn entryPoint;       // Entry point from OSCreateThread
   UNKNOWN(0x57c - 0x3a0);
   uint32_t specific[0x10];               // OSSetThreadSpecific / OSGetThreadSpecific
   UNKNOWN(0x5c0 - 0x5bc);
   const char *name;                      // Thread name
   UNKNOWN(0x4);
   void *userStackPointer;                // The stack specified in OSCreateThread
   OSThreadCleanupCallbackFn cleanupCallback; // Set with OSSetThreadCleanupCallback
   OSThreadDeallocatorFn deallocator;     // Set with OSSetThreadDeallocator
   uint32_t cancelState;                  // Is listening to requestFlag enabled
   OSThreadRequest requestFlag;           // Request flag for cancel or suspend
   int32_t needSuspend;                   // How many pending suspends we have
   int32_t suspendResult;                 // Result of suspend
   OSThreadQueue suspendQueue;            // Queue of threads waiting for suspend to finish
   UNKNOWN(0x69c - 0x5f4);
};
CHECK_OFFSET(OSThread, 0x320, tag);
CHECK_OFFSET(OSThread, 0x324, state);
CHECK_OFFSET(OSThread, 0x325, attr);
CHECK_OFFSET(OSThread, 0x326, id);
CHECK_OFFSET(OSThread, 0x328, suspendCounter);
CHECK_OFFSET(OSThread, 0x32c, priority);
CHECK_OFFSET(OSThread, 0x330, basePriority);
CHECK_OFFSET(OSThread, 0x334, exitValue);
CHECK_OFFSET(OSThread, 0x35c, queue);
CHECK_OFFSET(OSThread, 0x360, link);
CHECK_OFFSET(OSThread, 0x368, joinQueue);
CHECK_OFFSET(OSThread, 0x378, mutex);
CHECK_OFFSET(OSThread, 0x37c, mutexQueue);
CHECK_OFFSET(OSThread, 0x38c, activeLink);
CHECK_OFFSET(OSThread, 0x394, stackStart);
CHECK_OFFSET(OSThread, 0x398, stackEnd);
CHECK_OFFSET(OSThread, 0x39c, entryPoint);
CHECK_OFFSET(OSThread, 0x57c, specific);
CHECK_OFFSET(OSThread, 0x5c0, name);
CHECK_OFFSET(OSThread, 0x5c8, userStackPointer);
CHECK_OFFSET(OSThread, 0x5cc, cleanupCallback);
CHECK_OFFSET(OSThread, 0x5d0, deallocator);
CHECK_OFFSET(OSThread, 0x5d4, cancelState);
CHECK_OFFSET(OSThread, 0x5d8, requestFlag);
CHECK_OFFSET(OSThread, 0x5dc, needSuspend);
CHECK_OFFSET(OSThread, 0x5e0, suspendResult);
CHECK_OFFSET(OSThread, 0x5e4, suspendQueue);
CHECK_SIZE(OSThread, 0x69c);

void
OSCancelThread(OSThread *thread);

int32_t
OSCheckActiveThreads();

int32_t
OSCheckThreadStackUsage(OSThread *thread);

void
OSClearThreadStackUsage(OSThread *thread);

void
OSContinueThread(OSThread *thread);

BOOL
OSCreateThread(OSThread *thread,
               OSThreadEntryPointFn entry,
               int32_t argc,
               char *argv,
               void *stack,
               uint32_t stackSize,
               int32_t priority,
               OSThreadAttributes attributes);

void
OSDetachThread(OSThread *thread);

void
OSExitThread(int32_t result);

void
OSGetActiveThreadLink(OSThread *thread,
                      OSThreadLink *link);

OSThread *
OSGetCurrentThread();

OSThread *
OSGetDefaultThread(uint32_t coreID);

uint32_t
OSGetStackPointer();

uint32_t
OSGetThreadAffinity(OSThread *thread);

const char *
OSGetThreadName(OSThread *thread);

int32_t
OSGetThreadPriority(OSThread *thread);

uint32_t
OSGetThreadSpecific(uint32_t id);

BOOL
OSIsThreadSuspended(OSThread *thread);

BOOL
OSIsThreadTerminated(OSThread *thread);

BOOL
OSJoinThread(OSThread *thread,
             int *threadResult);

void
OSPrintCurrentThreadState();

int32_t
OSResumeThread(OSThread *thread);

BOOL
OSRunThread(OSThread *thread,
            OSThreadEntryPointFn entry,
            int argc,
            const char **argv);

BOOL
OSSetThreadAffinity(OSThread *thread,
                    uint32_t affinity);

BOOL
OSSetThreadCancelState(BOOL state);

OSThreadCleanupCallbackFn
OSSetThreadCleanupCallback(OSThread *thread,
                           OSThreadCleanupCallbackFn callback);

OSThreadDeallocatorFn
OSSetThreadDeallocator(OSThread *thread,
                       OSThreadDeallocatorFn deallocator);

void
OSSetThreadName(OSThread *thread,
                const char *name);

BOOL
OSSetThreadPriority(OSThread *thread,
                    int32_t priority);

BOOL
OSSetThreadRunQuantum(OSThread *thread,
                      uint32_t quantum);

void
OSSetThreadSpecific(uint32_t id,
                    uint32_t value);

BOOL
OSSetThreadStackUsage(OSThread *thread);

void
OSSleepThread(OSThreadQueue *queue);

void
OSSleepTicks(OSTime ticks);

uint32_t
OSSuspendThread(OSThread *thread);

void
OSTestThreadCancel();

void
OSWakeupThread(OSThreadQueue *queue);

void
OSYieldThread();

WUT_LIB_HEADER_END
