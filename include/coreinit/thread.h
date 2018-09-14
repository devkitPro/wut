#pragma once
#include <wut.h>
#include "context.h"
#include "time.h"
#include "threadqueue.h"

/**
 * \defgroup coreinit_thread Thread
 * \ingroup coreinit
 *
 * Manage and run threads on each of the system's cores.
 *
 * The thread scheduler in the Wii U uses co-operative scheduling, this is different
 * to the usual pre-emptive scheduling that most operating systems use (such as
 * Windows, Linux, etc). In co-operative scheduling threads must voluntarily yield
 * execution to other threads. In pre-emptive threads are switched by the operating
 * system after an amount of time.
 *
 * With the Wii U's scheduling model the thread with the highest priority which
 * is in a non-waiting state will always be running (where 0 is the highest
 * priority and 31 is the lowest). Execution will only switch to other threads
 * once this thread has been forced to wait, such as when waiting to acquire a
 * mutex, or when the thread voluntarily yields execution to other threads which
 * have the same priority using OSYieldThread. OSYieldThread will never yield to
 * a thread with lower priority than the current thread.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSFastMutex OSFastMutex;
typedef struct OSFastMutexQueue OSFastMutexQueue;
typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSThread OSThread;

//! A value from enum OS_THREAD_STATE.
typedef uint8_t OSThreadState;

//! A value from enum OS_THREAD_REQUEST.
typedef uint32_t OSThreadRequest;

//! A bitfield of enum OS_THREAD_ATTRIB.
typedef uint8_t OSThreadAttributes;

typedef int (*OSThreadEntryPointFn)(int argc, const char **argv);
typedef void (*OSThreadCleanupCallbackFn)(OSThread *thread, void *stack);
typedef void (*OSThreadDeallocatorFn)(OSThread *thread, void *stack);

enum OS_THREAD_STATE
{
   OS_THREAD_STATE_NONE             = 0,

   //! Thread is ready to run
   OS_THREAD_STATE_READY            = 1 << 0,

   //! Thread is running
   OS_THREAD_STATE_RUNNING          = 1 << 1,

   //! Thread is waiting, i.e. on a mutex
   OS_THREAD_STATE_WAITING          = 1 << 2,

   //! Thread is about to terminate
   OS_THREAD_STATE_MORIBUND         = 1 << 3,
};

enum OS_THREAD_REQUEST
{
   OS_THREAD_REQUEST_NONE           = 0,
   OS_THREAD_REQUEST_SUSPEND        = 1,
   OS_THREAD_REQUEST_CANCEL         = 2,
};

enum OS_THREAD_ATTRIB
{
   //! Allow the thread to run on CPU0.
   OS_THREAD_ATTRIB_AFFINITY_CPU0   = 1 << 0,

   //! Allow the thread to run on CPU1.
   OS_THREAD_ATTRIB_AFFINITY_CPU1   = 1 << 1,

   //! Allow the thread to run on CPU2.
   OS_THREAD_ATTRIB_AFFINITY_CPU2   = 1 << 2,

   //! Allow the thread to run any CPU.
   OS_THREAD_ATTRIB_AFFINITY_ANY    = ((1 << 0) | (1 << 1) | (1 << 2)),

   //! Start the thread detached.
   OS_THREAD_ATTRIB_DETACHED        = 1 << 3,

   //! Enables tracking of stack usage.
   OS_THREAD_ATTRIB_STACK_USAGE     = 1 << 5
};

struct OSMutexQueue
{
   OSMutex *head;
   OSMutex *tail;
   void *parent;
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(OSMutexQueue, 0x0, head);
WUT_CHECK_OFFSET(OSMutexQueue, 0x4, tail);
WUT_CHECK_OFFSET(OSMutexQueue, 0x8, parent);
WUT_CHECK_SIZE(OSMutexQueue, 0x10);

struct OSFastMutexQueue
{
   OSFastMutex *head;
   OSFastMutex *tail;
};
WUT_CHECK_OFFSET(OSFastMutexQueue, 0x00, head);
WUT_CHECK_OFFSET(OSFastMutexQueue, 0x04, tail);
WUT_CHECK_SIZE(OSFastMutexQueue, 0x08);

#define OS_THREAD_TAG 0x74487244u
#pragma pack(push, 1)
struct WUT_ALIGNAS(8) OSThread
{
   OSContext context;

   //! Should always be set to the value OS_THREAD_TAG.
   uint32_t tag;

   //! Bitfield of OS_THREAD_STATE
   OSThreadState state;

   //! Bitfield of OS_THREAD_ATTRIB
   OSThreadAttributes attr;

   //! Unique thread ID
   uint16_t id;

   //! Suspend count (increased by OSSuspendThread).
   int32_t suspendCounter;

   //! Actual priority of thread.
   int32_t priority;

   //! Base priority of thread, 0 is highest priority, 31 is lowest priority.
   int32_t basePriority;

   //! Exit value
   int32_t exitValue;

   WUT_UNKNOWN_BYTES(0x35C - 0x338);

   //! Queue the thread is currently waiting on
   OSThreadQueue *queue;

   //! Link used for thread queue
   OSThreadLink link;

   //! Queue of threads waiting to join this thread
   OSThreadQueue joinQueue;

   //! Mutex this thread is waiting to lock
   OSMutex *mutex;

   //! Queue of mutexes this thread owns
   OSMutexQueue mutexQueue;

   //! Link for global active thread queue
   OSThreadLink activeLink;

   //! Stack start (top, highest address)
   void *stackStart;

   //! Stack end (bottom, lowest address)
   void *stackEnd;

   //! Thread entry point
   OSThreadEntryPointFn entryPoint;

   WUT_UNKNOWN_BYTES(0x57c - 0x3a0);

   //! Thread specific values, accessed with OSSetThreadSpecific and OSGetThreadSpecific.
   void *specific[0x10];

   WUT_UNKNOWN_BYTES(0x5c0 - 0x5bc);

   //! Thread name, accessed with OSSetThreadName and OSGetThreadName.
   const char *name;

   WUT_UNKNOWN_BYTES(0x4);

   //! The stack pointer passed in OSCreateThread.
   void *userStackPointer;

   //! Called just before thread is terminated, set with OSSetThreadCleanupCallback
   OSThreadCleanupCallbackFn cleanupCallback;

   //! Called just after a thread is terminated, set with OSSetThreadDeallocator
   OSThreadDeallocatorFn deallocator;

   //! If TRUE then a thread can be cancelled or suspended, set with OSSetThreadCancelState
   BOOL cancelState;

   //! Current thread request, used for cancelleing and suspending the thread.
   OSThreadRequest requestFlag;

   //! Pending suspend request count
   int32_t needSuspend;

   //! Result of thread suspend
   int32_t suspendResult;

   //! Queue of threads waiting for a thread to be suspended.
   OSThreadQueue suspendQueue;

   WUT_UNKNOWN_BYTES(0x6a0 - 0x5f4);
};
#pragma pack(pop)
WUT_CHECK_OFFSET(OSThread, 0x320, tag);
WUT_CHECK_OFFSET(OSThread, 0x324, state);
WUT_CHECK_OFFSET(OSThread, 0x325, attr);
WUT_CHECK_OFFSET(OSThread, 0x326, id);
WUT_CHECK_OFFSET(OSThread, 0x328, suspendCounter);
WUT_CHECK_OFFSET(OSThread, 0x32c, priority);
WUT_CHECK_OFFSET(OSThread, 0x330, basePriority);
WUT_CHECK_OFFSET(OSThread, 0x334, exitValue);
WUT_CHECK_OFFSET(OSThread, 0x35c, queue);
WUT_CHECK_OFFSET(OSThread, 0x360, link);
WUT_CHECK_OFFSET(OSThread, 0x368, joinQueue);
WUT_CHECK_OFFSET(OSThread, 0x378, mutex);
WUT_CHECK_OFFSET(OSThread, 0x37c, mutexQueue);
WUT_CHECK_OFFSET(OSThread, 0x38c, activeLink);
WUT_CHECK_OFFSET(OSThread, 0x394, stackStart);
WUT_CHECK_OFFSET(OSThread, 0x398, stackEnd);
WUT_CHECK_OFFSET(OSThread, 0x39c, entryPoint);
WUT_CHECK_OFFSET(OSThread, 0x57c, specific);
WUT_CHECK_OFFSET(OSThread, 0x5c0, name);
WUT_CHECK_OFFSET(OSThread, 0x5c8, userStackPointer);
WUT_CHECK_OFFSET(OSThread, 0x5cc, cleanupCallback);
WUT_CHECK_OFFSET(OSThread, 0x5d0, deallocator);
WUT_CHECK_OFFSET(OSThread, 0x5d4, cancelState);
WUT_CHECK_OFFSET(OSThread, 0x5d8, requestFlag);
WUT_CHECK_OFFSET(OSThread, 0x5dc, needSuspend);
WUT_CHECK_OFFSET(OSThread, 0x5e0, suspendResult);
WUT_CHECK_OFFSET(OSThread, 0x5e4, suspendQueue);
WUT_CHECK_SIZE(OSThread, 0x6a0);


/**
 * Cancels a thread.
 *
 * This sets the threads requestFlag to OS_THREAD_REQUEST_CANCEL, the thread will
 * be terminated next time OSTestThreadCancel is called.
 */
void
OSCancelThread(OSThread *thread);


/**
 * Returns the count of active threads.
 */
int32_t
OSCheckActiveThreads();


/**
 * Get the maximum amount of stack the thread has used.
 */
int32_t
OSCheckThreadStackUsage(OSThread *thread);


/**
 * Disable tracking of thread stack usage
 */
void
OSClearThreadStackUsage(OSThread *thread);


/**
 * Clears a thread's suspend counter and resumes it.
 */
void
OSContinueThread(OSThread *thread);


/**
 * Create a new thread.
 *
 * \param thread Thread to initialise.
 * \param entry Thread entry point.
 * \param argc argc argument passed to entry point.
 * \param argv argv argument passed to entry point.
 * \param stack Top of stack (highest address).
 * \param stackSize Size of stack.
 * \param priority Thread priority, 0 is highest priorty, 31 is lowest.
 * \param attributes Thread attributes, see OSThreadAttributes.
 */
BOOL
OSCreateThread(OSThread *thread,
               OSThreadEntryPointFn entry,
               int32_t argc,
               char *argv,
               void *stack,
               uint32_t stackSize,
               int32_t priority,
               OSThreadAttributes attributes);


/**
 * Detach thread.
 */
void
OSDetachThread(OSThread *thread);


/**
 * Exit the current thread with a exit code.
 *
 * This function is implicitly called when the thread entry point returns.
 */
void
OSExitThread(int32_t result);


/**
 * Get the next and previous thread in the thread's active queue.
 */
void
OSGetActiveThreadLink(OSThread *thread,
                      OSThreadLink *link);


/**
 * Return pointer to OSThread object for the current thread.
 */
OSThread *
OSGetCurrentThread();


/**
 * Returns the default thread for a specific core.
 *
 * Each core has 1 default thread created before the game boots. The default
 * thread for core 1 calls the RPX entry point, the default threads for core 0
 * and 2 are suspended and can be used with OSRunThread.
 */
OSThread *
OSGetDefaultThread(uint32_t coreID);


/**
 * Return current stack pointer, value of r1 register.
 */
uint32_t
OSGetStackPointer();


/**
 * Get a thread's affinity.
 */
uint32_t
OSGetThreadAffinity(OSThread *thread);


/**
 * Get a thread's name.
 */
const char *
OSGetThreadName(OSThread *thread);


/**
 * Get a thread's base priority.
 */
int32_t
OSGetThreadPriority(OSThread *thread);


/**
 * Get a thread's specific value set by OSSetThreadSpecific.
 */
void *
OSGetThreadSpecific(uint32_t id);


/**
 * Returns TRUE if a thread is suspended.
 */
BOOL
OSIsThreadSuspended(OSThread *thread);


/**
 * Returns TRUE if a thread is terminated.
 */
BOOL
OSIsThreadTerminated(OSThread *thread);


/**
 * Wait until thread is terminated.
 *
 * If the target thread is detached, returns FALSE.
 *
 * \param thread Thread to wait for
 * \param threadResult Pointer to store thread exit value in.
 * \returns Returns TRUE if thread has terminated, FALSE if thread is detached.
 */
BOOL
OSJoinThread(OSThread *thread,
             int *threadResult);


/**
 * Resumes a thread.
 *
 * Decrements the thread's suspend counter, if the counter reaches 0 the thread
 * is resumed.
 *
 * \returns Returns the previous value of the suspend counter.
 */
int32_t
OSResumeThread(OSThread *thread);


/**
 * Run a function on an already created thread.
 *
 * Can only be used on idle threads.
 */
BOOL
OSRunThread(OSThread *thread,
            OSThreadEntryPointFn entry,
            int argc,
            const char **argv);


/**
 * Set a thread's affinity.
 */
BOOL
OSSetThreadAffinity(OSThread *thread,
                    uint32_t affinity);


/**
 * Set a thread's cancellation state.
 *
 * If the state is TRUE then the thread can be suspended or cancelled when
 * OSTestThreadCancel is called.
 */
BOOL
OSSetThreadCancelState(BOOL state);


/**
 * Set the callback to be called just before a thread is terminated.
 */
OSThreadCleanupCallbackFn
OSSetThreadCleanupCallback(OSThread *thread,
                           OSThreadCleanupCallbackFn callback);


/**
 * Set the callback to be called just after a thread is terminated.
 */
OSThreadDeallocatorFn
OSSetThreadDeallocator(OSThread *thread,
                       OSThreadDeallocatorFn deallocator);


/**
 * Set a thread's name.
 */
void
OSSetThreadName(OSThread *thread,
                const char *name);


/**
 * Set a thread's priority.
 */
BOOL
OSSetThreadPriority(OSThread *thread,
                    int32_t priority);


/**
 * Set a thread's run quantum.
 *
 * This is the maximum amount of time the thread can run for before being forced
 * to yield.
 */
BOOL
OSSetThreadRunQuantum(OSThread *thread,
                      uint32_t quantum);

/**
 * Set a thread specific value.
 *
 * Can be read with OSGetThreadSpecific.
 */
void
OSSetThreadSpecific(uint32_t id,
                    void *value);


/**
 * Set thread stack usage tracking.
 */
BOOL
OSSetThreadStackUsage(OSThread *thread);


/**
 * Sleep the current thread and add it to a thread queue.
 *
 * Will sleep until the thread queue is woken with OSWakeupThread.
 */
void
OSSleepThread(OSThreadQueue *queue);


/**
 * Sleep the current thread for a period of time.
 */
void
OSSleepTicks(OSTime ticks);


/**
 * Suspend a thread.
 *
 * Increases a thread's suspend counter, if the counter is >0 then the thread is
 * suspended.
 *
 * \returns Returns the thread's previous suspend counter value
 */
uint32_t
OSSuspendThread(OSThread *thread);


/**
 * Check to see if the current thread should be cancelled or suspended.
 *
 * This is implicitly called in:
 * - OSLockMutex
 * - OSTryLockMutex
 * - OSUnlockMutex
 * - OSAcquireSpinLock
 * - OSTryAcquireSpinLock
 * - OSTryAcquireSpinLockWithTimeout
 * - OSReleaseSpinLock
 * - OSCancelThread
 */
void
OSTestThreadCancel();


/**
 * Wake up all threads in queue.
 *
 * Clears the thread queue.
 */
void
OSWakeupThread(OSThreadQueue *queue);


/**
 * Yield execution to waiting threads with same priority.
 *
 * This will never switch to a thread with a lower priority than the current
 * thread.
 */
void
OSYieldThread();


#ifdef __cplusplus
}
#endif

/** @} */
