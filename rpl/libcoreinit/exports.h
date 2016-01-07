// coreinit/alarm.h
EXPORT(OSCancelAlarm);
EXPORT(OSCancelAlarms);
EXPORT(OSCreateAlarm);
EXPORT(OSCreateAlarmEx);
EXPORT(OSGetAlarmUserData);
EXPORT(OSInitAlarmQueue);
EXPORT(OSInitAlarmQueueEx);
EXPORT(OSSetAlarm);
EXPORT(OSSetPeriodicAlarm);
EXPORT(OSSetAlarmTag);
EXPORT(OSSetAlarmUserData);
EXPORT(OSWaitAlarm);

// coreinit/atomic64.h
EXPORT(OSGetAtomic64);
EXPORT(OSSetAtomic64);
EXPORT(OSCompareAndSwapAtomic64);
EXPORT(OSCompareAndSwapAtomicEx64);
EXPORT(OSSwapAtomic64);
EXPORT(OSAddAtomic64);
EXPORT(OSAndAtomic64);
EXPORT(OSOrAtomic64);
EXPORT(OSXorAtomic64);
EXPORT(OSTestAndClearAtomic64);
EXPORT(OSTestAndSetAtomic64);

// coreinit/baseheap.h
EXPORT(MEMGetArena);
EXPORT(MEMGetBaseHeapHandle);
EXPORT(MEMSetBaseHeapHandle);

// coreinit/cache.h
EXPORT(DCInvalidateRange);
EXPORT(DCFlushRange);
EXPORT(DCStoreRange);
EXPORT(DCFlushRangeNoSync);
EXPORT(DCStoreRangeNoSync);
EXPORT(DCZeroRange);
EXPORT(DCTouchRange);

// coreinit/condition.h
EXPORT(OSInitCond);
EXPORT(OSInitCondEx);
EXPORT(OSWaitCond);
EXPORT(OSSignalCond);

// coreinit/core.h
EXPORT(OSGetCoreCount);
EXPORT(OSGetCoreId);
EXPORT(OSGetMainCoreId);
EXPORT(OSIsMainCore);

// coreinit/debug.h
EXPORT(OSConsoleWrite);
EXPORT(OSReport);
EXPORT(OSPanic);
EXPORT(OSFatal);

// coreinit/dynload.h
EXPORT(OSDynLoad_SetAllocator);
EXPORT(OSDynLoad_GetAllocator);
EXPORT(OSDynLoad_Acquire);
EXPORT(OSDynLoad_FindExport);
EXPORT(OSDynLoad_Release);

// coreinit/event.h
EXPORT(OSInitEvent);
EXPORT(OSInitEventEx);
EXPORT(OSSignalEvent);
EXPORT(OSSignalEventAll);
EXPORT(OSWaitEvent);
EXPORT(OSResetEvent);
EXPORT(OSWaitEventWithTimeout);

// coreinit/exception.h
EXPORT(OSSetExceptionCallback);
EXPORT(OSSetExceptionCallbackEx);

// coreinit/exit.h
EXPORT(exit);
EXPORT(_Exit);

// coreinit/expandedheap.h
EXPORT(MEMCreateExpHeap);
EXPORT(MEMCreateExpHeapEx);
EXPORT(MEMDestroyExpHeap);
EXPORT(MEMiDumpExpHeap);
EXPORT(MEMAllocFromExpHeap);
EXPORT(MEMAllocFromExpHeapEx);
EXPORT(MEMFreeToExpHeap);
EXPORT(MEMSetAllocModeForExpHeap);
EXPORT(MEMGetAllocModeForExpHeap);
EXPORT(MEMAdjustExpHeap);
EXPORT(MEMResizeForMBlockExpHeap);
EXPORT(MEMGetTotalFreeSizeForExpHeap);
EXPORT(MEMGetAllocatableSizeForExpHeap);
EXPORT(MEMGetAllocatableSizeForExpHeapEx);
EXPORT(MEMSetGroupIDForExpHeap);
EXPORT(MEMGetGroupIDForExpHeap);
EXPORT(MEMGetSizeForMBlockExpHeap);
EXPORT(MEMGetGroupIDForMBlockExpHeap);
EXPORT(MEMGetAllocDirForMBlockExpHeap);

// coreinit/fastcondition.h
EXPORT(OSFastCond_Init);
EXPORT(OSFastCond_Wait);
EXPORT(OSFastCond_Signal);

// coreinit/fastmutex.h
EXPORT(OSFastMutex_Init);
EXPORT(OSFastMutex_Lock);
EXPORT(OSFastMutex_Unlock);
EXPORT(OSFastMutex_TryLock);

// coreinit/frameheap.h
EXPORT(MEMCreateFrmHeap);
EXPORT(MEMCreateFrmHeapEx);
EXPORT(MEMDestroyFrmHeap);
EXPORT(MEMAllocFromFrmHeap);
EXPORT(MEMAllocFromFrmHeapEx);
EXPORT(MEMFreeToFrmHeap);
EXPORT(MEMRecordStateForFrmHeap);
EXPORT(MEMFreeByStateToFrmHeap);
EXPORT(MEMAdjustFrmHeap);
EXPORT(MEMResizeForMBlockFrmHeap);
EXPORT(MEMGetAllocatableSizeForFrmHeap);
EXPORT(MEMGetAllocatableSizeForFrmHeapEx);

// coreinit/memlist.h
EXPORT(MEMInitList);
EXPORT(MEMAppendListObject);
EXPORT(MEMPrependListObject);
EXPORT(MEMInsertListObject);
EXPORT(MEMRemoveListObject);
EXPORT(MEMGetNextListObject);
EXPORT(MEMGetPrevListObject);
EXPORT(MEMGetNthListObject);

// coreinit/mutex.h
EXPORT(OSInitMutex);
EXPORT(OSInitMutexEx);
EXPORT(OSLockMutex);
EXPORT(OSUnlockMutex);
EXPORT(OSTryLockMutex);

// coreinit/rendezvous.h
EXPORT(OSInitRendezvous);
EXPORT(OSWaitRendezvous);
EXPORT(OSWaitRendezvousWithTimeout);

// coreinit/semaphore.h
EXPORT(OSInitSemaphore);
EXPORT(OSInitSemaphoreEx);
EXPORT(OSGetSemaphoreCount);
EXPORT(OSSignalSemaphore);
EXPORT(OSWaitSemaphore);
EXPORT(OSTryWaitSemaphore);

// coreinit/spinlock.h
EXPORT(OSInitSpinLock);
EXPORT(OSAcquireSpinLock);
EXPORT(OSTryAcquireSpinLock);
EXPORT(OSTryAcquireSpinLockWithTimeout);
EXPORT(OSReleaseSpinLock);
EXPORT(OSUninterruptibleSpinLock_Acquire);
EXPORT(OSUninterruptibleSpinLock_TryAcquire);
EXPORT(OSUninterruptibleSpinLock_TryAcquireWithTimeout);
EXPORT(OSUninterruptibleSpinLock_Release);

// coreinit/thread.h
EXPORT(OSCancelThread);
EXPORT(OSCheckActiveThreads);
EXPORT(OSCheckThreadStackUsage);
EXPORT(OSClearThreadStackUsage);
EXPORT(OSContinueThread);
EXPORT(OSCreateThread);
EXPORT(OSDetachThread);
EXPORT(OSExitThread);
EXPORT(OSGetActiveThreadLink);
EXPORT(OSGetCurrentThread);
EXPORT(OSGetDefaultThread);
EXPORT(OSGetStackPointer);
EXPORT(OSGetThreadAffinity);
EXPORT(OSGetThreadName);
EXPORT(OSGetThreadPriority);
EXPORT(OSGetThreadSpecific);
EXPORT(OSIsThreadSuspended);
EXPORT(OSIsThreadTerminated);
EXPORT(OSJoinThread);
EXPORT(OSPrintCurrentThreadState);
EXPORT(OSResumeThread);
EXPORT(OSRunThread);
EXPORT(OSSetThreadAffinity);
EXPORT(OSSetThreadCancelState);
EXPORT(OSSetThreadCleanupCallback);
EXPORT(OSSetThreadDeallocator);
EXPORT(OSSetThreadName);
EXPORT(OSSetThreadPriority);
EXPORT(OSSetThreadRunQuantum);
EXPORT(OSSetThreadSpecific);
EXPORT(OSSetThreadStackUsage);
EXPORT(OSSleepThread);
EXPORT(OSSleepTicks);
EXPORT(OSSuspendThread);
EXPORT(OSTestThreadCancel);
EXPORT(OSWakeupThread);
EXPORT(OSYieldThread);

// coreinit/threadqueue.h
EXPORT(OSInitThreadQueue);
EXPORT(OSInitThreadQueueEx);

// coreinit/time.h
EXPORT(OSGetTime);
EXPORT(OSGetSystemTime);
EXPORT(OSGetTick);
EXPORT(OSGetSystemTick);
EXPORT(OSCalendarTimeToTicks);
EXPORT(OSTicksToCalendarTime);

// coreinit/unitheap.h
EXPORT(MEMCreateUnitHeapEx);
EXPORT(MEMDestroyUnitHeap);
EXPORT(MEMAllocFromUnitHeap);
EXPORT(MEMFreeToUnitHeap);
EXPORT(MEMiDumpUnitHeap);
EXPORT(MEMCountFreeBlockForUnitHeap);
EXPORT(MEMCalcHeapSizeForUnitHeap);
