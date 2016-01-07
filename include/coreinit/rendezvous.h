#pragma once
#include <wut.h>

WUT_LIB_HEADER_START

typedef struct OSRendezvous OSRendezvous;

struct OSRendezvous
{
   uint32_t core[3];
   UNKNOWN(4);
};
CHECK_OFFSET(OSRendezvous, 0x00, core);
CHECK_SIZE(OSRendezvous, 0x10);

#pragma pack(pop)

void
OSInitRendezvous(OSRendezvous *rendezvous);

BOOL
OSWaitRendezvous(OSRendezvous *rendezvous,
                 uint32_t coreMask);

BOOL
OSWaitRendezvousWithTimeout(OSRendezvous *rendezvous,
                            uint32_t coreMask,
                            OSTime timeout);

WUT_LIB_HEADER_END
