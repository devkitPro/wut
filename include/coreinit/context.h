#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_context Context
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSContext OSContext;

#define OS_CONTEXT_TAG 0x4F53436F6E747874ull

struct WUT_ALIGNAS(8) OSContext
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
   uint32_t dsisr;
   uint32_t dar;
   WUT_UNKNOWN_BYTES(0xC);
   uint32_t fpscr;
   double fpr[32];
   uint16_t spinLockCount;
   uint16_t state;
   uint32_t gqr[8];
   WUT_UNKNOWN_BYTES(4);
   double psf[32];
   uint64_t coretime[3];
   uint64_t starttime;
   uint32_t error;
   WUT_UNKNOWN_BYTES(4);
   uint32_t pmc1;
   uint32_t pmc2;
   uint32_t pmc3;
   uint32_t pmc4;
   uint32_t mmcr0;
   uint32_t mmcr1;
};
WUT_CHECK_OFFSET(OSContext, 0x00, tag);
WUT_CHECK_OFFSET(OSContext, 0x08, gpr);
WUT_CHECK_OFFSET(OSContext, 0x88, cr);
WUT_CHECK_OFFSET(OSContext, 0x8c, lr);
WUT_CHECK_OFFSET(OSContext, 0x90, ctr);
WUT_CHECK_OFFSET(OSContext, 0x94, xer);
WUT_CHECK_OFFSET(OSContext, 0x98, srr0);
WUT_CHECK_OFFSET(OSContext, 0x9c, srr1);
WUT_CHECK_OFFSET(OSContext, 0xa0, dsisr);
WUT_CHECK_OFFSET(OSContext, 0xa4, dar);
WUT_CHECK_OFFSET(OSContext, 0xb4, fpscr);
WUT_CHECK_OFFSET(OSContext, 0xb8, fpr);
WUT_CHECK_OFFSET(OSContext, 0x1b8, spinLockCount);
WUT_CHECK_OFFSET(OSContext, 0x1ba, state);
WUT_CHECK_OFFSET(OSContext, 0x1bc, gqr);
WUT_CHECK_OFFSET(OSContext, 0x1e0, psf);
WUT_CHECK_OFFSET(OSContext, 0x2e0, coretime);
WUT_CHECK_OFFSET(OSContext, 0x2f8, starttime);
WUT_CHECK_OFFSET(OSContext, 0x300, error);
WUT_CHECK_OFFSET(OSContext, 0x308, pmc1);
WUT_CHECK_OFFSET(OSContext, 0x30c, pmc2);
WUT_CHECK_OFFSET(OSContext, 0x310, pmc3);
WUT_CHECK_OFFSET(OSContext, 0x314, pmc4);
WUT_CHECK_OFFSET(OSContext, 0x318, mmcr0);
WUT_CHECK_OFFSET(OSContext, 0x31c, mmcr1);
WUT_CHECK_SIZE(OSContext, 0x320);

void
OSInitContext(OSContext *context,
              void *entry,
              void *stack);

void
OSDumpContext(OSContext *context);

void
OSLoadContext(OSContext *context);

uint32_t
OSSaveContext(OSContext *context);

void
OSLoadFPUContext(OSContext *context);

void
OSSaveFPUContext(OSContext *context);

OSContext *
OSGetCurrentContext();

void
OSSetCurrentContext(OSContext *context);

void *
OSSwitchStack(void *stack);

#ifdef __cplusplus
}
#endif

/** @} */
