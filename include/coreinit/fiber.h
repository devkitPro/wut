#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_fiber Fiber
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*OSFiberEntryFn)();
typedef void (*OSFiberExEntryFn)(uint32_t arg1, uint32_t arg2,
                                 uint32_t arg3, uint32_t arg4);

int32_t
OSSwitchFiber(OSFiberEntryFn entry,
              void *stack);

int32_t
OSSwitchFiberEx(uint32_t arg1,
                uint32_t arg2,
                uint32_t arg3,
                uint32_t arg4,
                OSFiberExEntryFn entry,
                void *stack);

#ifdef __cplusplus
}
#endif

/** @} */
