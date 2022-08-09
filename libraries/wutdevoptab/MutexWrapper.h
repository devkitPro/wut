#pragma once

#include <coreinit/mutex.h>
#include "coreinit/cache.h"

class MutexWrapper {
public:
    MutexWrapper() = default;

    void init(const char *name) {
       OSInitMutexEx(&mutex, name);
    }

    void lock() {
       OSLockMutex(&mutex);
    }

    void unlock() {
       OSUnlockMutex(&mutex);
    }

private:
    OSMutex mutex{};
};
