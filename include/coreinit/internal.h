#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

int
__os_snprintf(char *buf, size_t n, const char *format, ... )
   WUT_FORMAT_PRINTF(3, 4);

#ifdef __cplusplus
}
#endif
