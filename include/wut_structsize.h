#pragma once
#include <assert.h>
#include <stddef.h>

// Ensure structs are correct size & offsets
#if defined(static_assert) || defined(__cplusplus)
#  define WUT_CHECK_SIZE(Type, Size) \
      static_assert(sizeof(Type) == Size, \
                    #Type " must be " #Size " bytes")

#  define WUT_CHECK_OFFSET(Type, Offset, Field) \
      static_assert(offsetof(Type, Field) == Offset, \
                    #Type "::" #Field " must be at offset " #Offset)
#else
#  define WUT_CHECK_SIZE(Type, Size)
#  define WUT_CHECK_OFFSET(Type, Offset, Field)
#endif

// Workaround weird macro concat ## behaviour
#define WUT_PP_CAT(a, b) WUT_PP_CAT_I(a, b)
#define WUT_PP_CAT_I(a, b) WUT_PP_CAT_II(~, a ## b)
#define WUT_PP_CAT_II(p, res) res

// Allow us to easily add UNKNOWN / PADDING bytes into our structs,
// generates unique variable names using __COUNTER__
#define WUT_UNKNOWN_BYTES(Size) char WUT_PP_CAT(__unk, __COUNTER__) [Size]
#define WUT_PADDING_BYTES(Size) WUT_UNKNOWN_BYTES(Size)

// Unknown struct size
#define WUT_UNKNOWN_SIZE(x)

// Marks a struct as packed
#define WUT_PACKED  __attribute__((__packed__))

// Sets alignment for a struct
#if defined(__alignas_is_defined) || defined(__cplusplus)
#define WUT_ALIGNAS(x) alignas(x)
#elif defined(__GNUC__) || defined(__clang__)
#define WUT_ALIGNAS(x) __attribute__((__aligned__(x)))
#endif
