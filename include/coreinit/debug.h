#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

void
OSConsoleWrite(const char *msg,
               uint32_t size);

void
OSReport(const char *fmt, ...);

void
OSPanic(const char *file,
        uint32_t line,
        const char *fmt, ...);

void
OSFatal(const char *msg);

WUT_LIB_HEADER_END
