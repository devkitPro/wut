#pragma once
#include <wut.h>
#include <coreinit/time.h>

/**
 * \defgroup nn_ccr_sys
 * \ingroup nn_ccr
 * (see nn::ccr)
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum CCRSysPairingState
{
    //! Pairing is complete / hasn't started yet
    CCR_SYS_PAIRING_FINISHED        = 0,
    //! Pairing is in progress
    CCR_SYS_PAIRING_IN_PROGRESS     = 1,
    //! Pairing timed out
    CCR_SYS_PAIRING_TIMED_OUT       = 2,
} CCRSysPairingState;

void
CCRSysInit(void);

void
CCRSysExit(void);

/**
 * Shutdown the DRC in slot 0.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysDRCShutdown(void);

/**
 * Invalidate the DRC pairing in slot 0.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysInvalidatePairing(void);

/**
 * Check if the DRC in the specified slot is attached.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \return
 * \c TRUE if attached.
 */
BOOL
__CCRSysDRCIsAttached(uint32_t drcSlot);

/**
 * Starts the pairing process for the specified slot.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \param timeout
 * Timeout in seconds.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysStartPairing(uint32_t drcSlot,
                   uint32_t timeout);

/**
 * Stops the pairing process.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysStopPairing(void);

/**
 * Gets the current pairing state.
 * 
 * \return
 * The pairing state.
 */
CCRSysPairingState
CCRSysGetPairingState(void);

/**
 * Gets the pin code used for pairing in decimal representation.
 * ♠ = 0, ♥ = 1, ♦ = 2, ♣ = 3
 * 
 * \param pin
 * Pointer to write the pin code to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysGetPincode(uint32_t *pin);

/**
 * Sets the DRH system time.
 * 
 * \param time
 * The system time in ticks.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysSetSystemTime(OSTime time);

#ifdef __cplusplus
}
#endif

/** @} */
