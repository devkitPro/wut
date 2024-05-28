#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdalign.h>

typedef int32_t BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if defined(__cplusplus) && (__cplusplus >= 201402L)
#include <type_traits>

#define WUT_ENUM_BITMASK_TYPE(_type) \
   extern "C++" { \
      static constexpr inline _type operator~(_type lhs) { \
         return static_cast<_type>(~static_cast<std::underlying_type<_type>::type>(lhs)); \
      } \
      static constexpr inline _type operator&(_type lhs, _type rhs) { \
         return static_cast<_type>(static_cast<std::underlying_type<_type>::type>(lhs) & static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
      static constexpr inline _type operator|(_type lhs, _type rhs) { \
         return static_cast<_type>(static_cast<std::underlying_type<_type>::type>(lhs) | static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
      static constexpr inline _type operator^(_type lhs, _type rhs) { \
         return static_cast<_type>(static_cast<std::underlying_type<_type>::type>(lhs) ^ static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
      static inline _type& operator&=(_type &lhs, _type rhs) { \
         return reinterpret_cast<_type&>(reinterpret_cast<std::underlying_type<_type>::type&>(lhs) &= static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
      static inline _type& operator|=(_type &lhs, _type rhs) { \
         return reinterpret_cast<_type&>(reinterpret_cast<std::underlying_type<_type>::type&>(lhs) |= static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
      static inline _type& operator^=(_type &lhs, _type rhs) { \
         return reinterpret_cast<_type&>(reinterpret_cast<std::underlying_type<_type>::type&>(lhs) ^= static_cast<std::underlying_type<_type>::type>(rhs)); \
      } \
   }
#else
#define WUT_ENUM_BITMASK_TYPE(_type)
#endif
