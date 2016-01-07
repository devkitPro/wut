#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

void
DCInvalidateRange(void *addr,
                  uint32_t size);

void
DCFlushRange(void *addr,
             uint32_t size);

void
DCStoreRange(void *addr,
             uint32_t size);

void
DCFlushRangeNoSync(void *addr,
                   uint32_t size);

void
DCStoreRangeNoSync(void *addr,
                   uint32_t size);

void
DCZeroRange(void *addr,
            uint32_t size);

void
DCTouchRange(void *addr,
             uint32_t size);

#ifdef __cplusplus
}
#endif
