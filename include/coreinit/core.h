#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

uint32_t
OSGetCoreCount();

uint32_t
OSGetCoreId();

uint32_t
OSGetMainCoreId();

BOOL
OSIsMainCore();

WUT_LIB_HEADER_END
