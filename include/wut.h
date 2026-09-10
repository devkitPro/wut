#pragma once

/*
 * wut 1.0.0-beta
 *
 * https://github.com/devkitPro/wut
 */

#if defined(__GNUC__) || defined(__clang__)

#define WUT_DEPRECATED(reason)       __attribute__((__deprecated__(reason)))
#define WUT_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))
#define WUT_MALLOC  __attribute__((malloc))
#define WUT_FREED_BY(freeFn, ptrIndex)  __attribute__((malloc(freeFn, ptrIndex)))
#define WUT_ALLOC_SIZE(posIndex)  __attribute__((alloc_size(posIndex)))
#define WUT_ALLOC_ALIGN(posIndex)  __attribute__((alloc_align(posIndex)))

#else // not __GNUC__ and not __clang__

#define WUT_DEPRECATED(reason)
#define WUT_FORMAT_PRINTF(fmt, args)
#define WUT_MALLOC
#define WUT_FREED_BY(freeFn, ptrIndex)
#define WUT_ALLOC_SIZE(posIndex)
#define WUT_ALLOC_ALIGN(posIndex)
#endif //__GNUC__ or __clang__

#ifdef DEBUG
#define WUT_DEBUG_REPORT(fmt, ...) OSReport(fmt, ##__VA_ARGS__)
#else
#define WUT_DEBUG_REPORT(fmt, ...)
#endif

#include "wut_structsize.h"
#include "wut_types.h"
#include "wut_rplwrap.h"
#ifdef DEBUG
#include <coreinit/debug.h>
#endif
