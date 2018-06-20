#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_rendezvous Rendezvous
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSRendezvous OSRendezvous;

struct OSRendezvous
{
   uint32_t core[3];
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(OSRendezvous, 0x00, core);
WUT_CHECK_SIZE(OSRendezvous, 0x10);

void
OSInitRendezvous(OSRendezvous *rendezvous);

BOOL
OSWaitRendezvous(OSRendezvous *rendezvous,
                 uint32_t coreMask);

BOOL
OSWaitRendezvousWithTimeout(OSRendezvous *rendezvous,
                            uint32_t coreMask,
                            OSTime timeout);

#ifdef __cplusplus
}
#endif

/** @} */
