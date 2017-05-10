#pragma once
#include <wut.h>

/**
 * \defgroup latte_enum_sq Latte SQ Enums
 * \ingroup latte
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum LATTE_SQ_SEL
{
   LATTE_SQ_SEL_X       = 0,
   LATTE_SQ_SEL_Y       = 1,
   LATTE_SQ_SEL_Z       = 2,
   LATTE_SQ_SEL_W       = 3,
   LATTE_SQ_SEL_0       = 4,
   LATTE_SQ_SEL_1       = 5,
   LATTE_SQ_SEL_MASK    = 7,
} LATTE_SQ_SEL;

#define LATTE_SQ_SEL_MASK(x, y, z, w) (((x) << 24) | ((y) << 16) | ((z) << 8) | (w))

#ifdef __cplusplus
}
#endif

/** @} */
