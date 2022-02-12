#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_interrupts Interrupt Management
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSInterruptType
{
   OS_INTERRUPT_TYPE_ERROR      = 0,
   OS_INTERRUPT_TYPE_DSP        = 1,
   OS_INTERRUPT_TYPE_GPU7       = 2,
   OS_INTERRUPT_TYPE_GPIPPC     = 3,
   OS_INTERRUPT_TYPE_PRIMARYI2C = 4,
   OS_INTERRUPT_TYPE_DSPAI      = 5,
   OS_INTERRUPT_TYPE_DSPAI2     = 6,
   OS_INTERRUPT_TYPE_DSPACC     = 7,
   OS_INTERRUPT_TYPE_DSPDSP     = 8,
   OS_INTERRUPT_TYPE_IPCPPC0    = 9,
   OS_INTERRUPT_TYPE_IPCPPC1    = 10,
   OS_INTERRUPT_TYPE_IPCPPC2    = 11,
   OS_INTERRUPT_TYPE_AHB        = 12
} OSInterruptType;

typedef void (*OSUserInterruptHandler)(OSInterruptType type, OSContext *interruptedContext);

BOOL OSEnableInterrupts();

BOOL OSDisableInterrupts();

BOOL OSRestoreInterrupts(BOOL enable);

BOOL OSIsInterruptEnabled();

OSUserInterruptHandler
__OSSetInterruptHandler(OSInterruptType type,
                        OSUserInterruptHandler handler);

void __OSClearAndEnableInterrupt(OSInterruptType type);

void __OSDisableInterrupt(OSInterruptType type);

#ifdef __cplusplus
}
#endif

/** @} */
