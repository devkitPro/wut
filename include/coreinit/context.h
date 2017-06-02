#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSContext OSContext;

#define OS_CONTEXT_TAG 0x4F53436F6E747874ull

struct OSContext
{
   //! Should always be set to the value OS_CONTEXT_TAG.
   uint64_t tag;

   uint32_t gpr[32];
   uint32_t cr;
   uint32_t lr;
   uint32_t ctr;
   uint32_t xer;
   uint32_t srr0;
   uint32_t srr1;
   UNKNOWN(0x14);
   uint32_t fpscr;
   double fpr[32];
   uint16_t spinLockCount;
   uint16_t state;
   uint32_t gqr[8];
   UNKNOWN(4);
   double psf[32];
   uint64_t coretime[3];
   uint64_t starttime;
   uint32_t error;
   UNKNOWN(4);
   uint32_t pmc1;
   uint32_t pmc2;
   uint32_t pmc3;
   uint32_t pmc4;
   uint32_t mmcr0;
   uint32_t mmcr1;
};
CHECK_OFFSET(OSContext, 0x00, tag);
CHECK_OFFSET(OSContext, 0x08, gpr);
CHECK_OFFSET(OSContext, 0x88, cr);
CHECK_OFFSET(OSContext, 0x8c, lr);
CHECK_OFFSET(OSContext, 0x90, ctr);
CHECK_OFFSET(OSContext, 0x94, xer);
CHECK_OFFSET(OSContext, 0x98, srr0);
CHECK_OFFSET(OSContext, 0x9c, srr1);
CHECK_OFFSET(OSContext, 0xb4, fpscr);
CHECK_OFFSET(OSContext, 0xb8, fpr);
CHECK_OFFSET(OSContext, 0x1b8, spinLockCount);
CHECK_OFFSET(OSContext, 0x1ba, state);
CHECK_OFFSET(OSContext, 0x1bc, gqr);
CHECK_OFFSET(OSContext, 0x1e0, psf);
CHECK_OFFSET(OSContext, 0x2e0, coretime);
CHECK_OFFSET(OSContext, 0x2f8, starttime);
CHECK_OFFSET(OSContext, 0x300, error);
CHECK_OFFSET(OSContext, 0x308, pmc1);
CHECK_OFFSET(OSContext, 0x30c, pmc2);
CHECK_OFFSET(OSContext, 0x310, pmc3);
CHECK_OFFSET(OSContext, 0x314, pmc4);
CHECK_OFFSET(OSContext, 0x318, mmcr0);
CHECK_OFFSET(OSContext, 0x31c, mmcr1);
CHECK_SIZE(OSContext, 0x320);

#ifdef __cplusplus
}
#endif

/** @} */
