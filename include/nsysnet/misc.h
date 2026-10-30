#pragma once
#include <wut.h>

/**
 * \defgroup nsysnet_misc
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
   //! Prevents closing nsysnet sockets during socketclose_all
   //! Note: No-op if security level is prod
   SOLIB_OPT_AVOID_CLOSE_ALL = 0x3000,
} SocklibOpt;
WUT_CHECK_SIZE(SocklibOpt, 4);

int
set_multicast_state(BOOL multicastEnable);

int
socketclose_all(void);

int
setsocklibopt(SocklibOpt opt, uint32_t value);

#ifdef __cplusplus
}
#endif

/** @} */
