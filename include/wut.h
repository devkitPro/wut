#pragma once
#include "wut_structsize.h"
#include "wut_types.h"

#ifdef __cplusplus

#define WUT_LIB_HEADER_START \
	extern "C" { \
	_Pragma("pack(push, 1)")

#define WUT_LIB_HEADER_END \
	_Pragma("pack(pop)") \
	}

#else

#define WUT_LIB_HEADER_START \
	_Pragma("pack(push, 1)")

#define WUT_LIB_HEADER_END \
	_Pragma("pack(pop)")

#endif
