#pragma once
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int32_t BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if __cplusplus >= 201402L
#define WUT_ENUM_BITMASK_TYPE(_type)                                                      \
   extern "C++" {                                                                         \
   static constexpr inline _type                                                          \
   operator|(_type lhs, _type rhs)                                                        \
   {                                                                                      \
      return static_cast<_type>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs)); \
   }                                                                                      \
   }
#else
#define WUT_ENUM_BITMASK_TYPE(_type)
#endif
