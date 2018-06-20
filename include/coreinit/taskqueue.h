#pragma once
#include <wut.h>
#include "time.h"

/**
 * \defgroup coreinit_taskq Task Queue
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MPTask MPTask;
typedef struct MPTaskInfo MPTaskInfo;
typedef struct MPTaskQueue MPTaskQueue;
typedef struct MPTaskQueueInfo MPTaskQueueInfo;

typedef uint32_t (*MPTaskFunc)(uint32_t, uint32_t);

typedef enum MPTaskState
{
   MP_TASK_STATE_INITIALISED           = 1 << 0,
   MP_TASK_STATE_READY                 = 1 << 1,
   MP_TASK_STATE_RUNNING               = 1 << 2,
   MP_TASK_STATE_FINISHED              = 1 << 3,
} MPTaskState;

typedef enum MPTaskQueueState
{
   MP_TASK_QUEUE_STATE_INITIALISED     = 1 << 0,
   MP_TASK_QUEUE_STATE_READY           = 1 << 1,
   MP_TASK_QUEUE_STATE_STOPPING        = 1 << 2,
   MP_TASK_QUEUE_STATE_STOPPED         = 1 << 3,
   MP_TASK_QUEUE_STATE_FINISHED        = 1 << 4,
} MPTaskQueueState;

#pragma pack(push, 1)
struct MPTaskInfo
{
   MPTaskState state;
   uint32_t result;
   uint32_t coreID;
   OSTime duration;
};
#pragma pack(pop)
WUT_CHECK_OFFSET(MPTaskInfo, 0x00, state);
WUT_CHECK_OFFSET(MPTaskInfo, 0x04, result);
WUT_CHECK_OFFSET(MPTaskInfo, 0x08, coreID);
WUT_CHECK_OFFSET(MPTaskInfo, 0x0C, duration);
WUT_CHECK_SIZE(MPTaskInfo, 0x14);

#pragma pack(push, 1)
struct MPTask
{
   MPTask *self;
   MPTaskQueue *queue;
   MPTaskState state;
   MPTaskFunc func;
   uint32_t userArg1;
   uint32_t userArg2;
   uint32_t result;
   uint32_t coreID;
   OSTime duration;
   void *userData;
};
#pragma pack(pop)
WUT_CHECK_OFFSET(MPTask, 0x00, self);
WUT_CHECK_OFFSET(MPTask, 0x04, queue);
WUT_CHECK_OFFSET(MPTask, 0x08, state);
WUT_CHECK_OFFSET(MPTask, 0x0C, func);
WUT_CHECK_OFFSET(MPTask, 0x10, userArg1);
WUT_CHECK_OFFSET(MPTask, 0x14, userArg2);
WUT_CHECK_OFFSET(MPTask, 0x18, result);
WUT_CHECK_OFFSET(MPTask, 0x1C, coreID);
WUT_CHECK_OFFSET(MPTask, 0x20, duration);
WUT_CHECK_OFFSET(MPTask, 0x28, userData);
WUT_CHECK_SIZE(MPTask, 0x2C);

struct MPTaskQueueInfo
{
   MPTaskQueueState state;
   uint32_t tasks;
   uint32_t tasksReady;
   uint32_t tasksRunning;
   uint32_t tasksFinished;
};
WUT_CHECK_OFFSET(MPTaskQueueInfo, 0x00, state);
WUT_CHECK_OFFSET(MPTaskQueueInfo, 0x04, tasks);
WUT_CHECK_OFFSET(MPTaskQueueInfo, 0x08, tasksReady);
WUT_CHECK_OFFSET(MPTaskQueueInfo, 0x0C, tasksRunning);
WUT_CHECK_OFFSET(MPTaskQueueInfo, 0x10, tasksFinished);
WUT_CHECK_SIZE(MPTaskQueueInfo, 0x14);

struct MPTaskQueue
{
   MPTaskQueue *self;
   MPTaskQueueState state;
   uint32_t tasks;
   uint32_t tasksReady;
   uint32_t tasksRunning;
   WUT_UNKNOWN_BYTES(4);
   uint32_t tasksFinished;
   WUT_UNKNOWN_BYTES(8);
   uint32_t queueIndex;
   WUT_UNKNOWN_BYTES(8);
   uint32_t queueSize;
   WUT_UNKNOWN_BYTES(4);
   MPTask **queue;
   uint32_t queueMaxSize;
   OSSpinLock lock;
};
WUT_CHECK_OFFSET(MPTaskQueue, 0x00, self);
WUT_CHECK_OFFSET(MPTaskQueue, 0x04, state);
WUT_CHECK_OFFSET(MPTaskQueue, 0x08, tasks);
WUT_CHECK_OFFSET(MPTaskQueue, 0x0C, tasksReady);
WUT_CHECK_OFFSET(MPTaskQueue, 0x10, tasksRunning);
WUT_CHECK_OFFSET(MPTaskQueue, 0x18, tasksFinished);
WUT_CHECK_OFFSET(MPTaskQueue, 0x24, queueIndex);
WUT_CHECK_OFFSET(MPTaskQueue, 0x30, queueSize);
WUT_CHECK_OFFSET(MPTaskQueue, 0x38, queue);
WUT_CHECK_OFFSET(MPTaskQueue, 0x3C, queueMaxSize);
WUT_CHECK_OFFSET(MPTaskQueue, 0x40, lock);
WUT_CHECK_SIZE(MPTaskQueue, 0x50);

void
MPInitTaskQ(MPTaskQueue *queue,
            MPTask **queueBuffer,
            uint32_t queueBufferLen);

BOOL
MPTermTaskQ(MPTaskQueue *queue);

BOOL
MPGetTaskQInfo(MPTaskQueue *queue,
               MPTaskQueueInfo *info);

BOOL
MPStartTaskQ(MPTaskQueue *queue);

BOOL
MPStopTaskQ(MPTaskQueue *queue);

BOOL
MPResetTaskQ(MPTaskQueue *queue);

BOOL
MPEnqueTask(MPTaskQueue *queue,
            MPTask *task);

MPTask *
MPDequeTask(MPTaskQueue *queue);

uint32_t
MPDequeTasks(MPTaskQueue *queue,
             MPTask **queueBuffer,
             uint32_t queueBufferLen);

BOOL
MPWaitTaskQ(MPTaskQueue *queue,
            MPTaskQueueState mask);

BOOL
MPWaitTaskQWithTimeout(MPTaskQueue *queue,
                       MPTaskQueueState wmask,
                       OSTime timeout);

BOOL
MPPrintTaskQStats(MPTaskQueue *queue,
                  uint32_t unk);

void
MPInitTask(MPTask *task,
           MPTaskFunc func,
           uint32_t userArg1,
           uint32_t userArg2);

BOOL
MPTermTask(MPTask* task);

BOOL
MPGetTaskInfo(MPTask *task,
              MPTaskInfo *info);

void *
MPGetTaskUserData(MPTask *task);

void
MPSetTaskUserData(MPTask *task,
                  void *userData);

BOOL
MPRunTasksFromTaskQ(MPTaskQueue *queue,
                    uint32_t count);

BOOL
MPRunTask(MPTask *task);

#ifdef __cplusplus
}
#endif

/** @} */
