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

typedef struct CCRSysUpdateState CCRSysUpdateState;

typedef enum CCRSysPairingState
{
   //! Pairing is complete / hasn't started yet
   CCR_SYS_PAIRING_FINISHED        = 0,
   //! Pairing is in progress
   CCR_SYS_PAIRING_IN_PROGRESS     = 1,
   //! Pairing timed out
   CCR_SYS_PAIRING_TIMED_OUT       = 2,
} CCRSysPairingState;

typedef enum CCRSysInitBootFlag
{
    CCR_SYS_BOOT_FLAG_NONE        = 0,
    //! Shows "Turn on the TV and Wii U Console.." text on next DRC boot
    CCR_SYS_BOOT_FLAG_FIRST_BOOT  = 1,
} CCRSysInitBootFlag;

struct CCRSysUpdateState
{
   uint32_t state;
   //! Progress from 0-100
   uint32_t progress;
};

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

/**
 * Check if a DRC firmware update is needed.
 * This function additionally verifies the DRC area compared to \link __CCRSysNeedsDRCFWUpdate \endlink.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \param outNeedsUpdate
 * Pointer to store the result to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysNeedsDRCFWUpdate(uint32_t drcSlot,
                       BOOL *outNeedsUpdate);

/**
 * Check if a DRC firmware update is needed.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \param outNeedsUpdate
 * Pointer to store the result to.
 * 
 * \param allowDowngrade
 * Only check if the installed version doesn't match the running version,
 * instead of checking that it's greater.
 * 
 * \return
 * 0 on success.
 */
int32_t
__CCRSysNeedsDRCFWUpdate(uint32_t drcSlot,
                         BOOL *outNeedsUpdate,
                         BOOL allowDowngrade);

/**
 * Starts a DRC firmware update if necessary and region matches.
 * 
 * \note
 * This function will wait for \link CCRSysDRCFWUpdateForward \endlink to be called once done.
 * See \link CCRSysGetUpdateState \endlink for status and progress.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysDRCFWUpdate(uint32_t drcSlot);

/**
 * Starts a DRC firmware update if necessary.
 * 
 * \note
 * This function will wait for \link CCRSysDRCFWUpdateForward \endlink to be called once done.
 * See \link CCRSysGetUpdateState \endlink for status and progress.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \param allowDowngrade
 * Only check if the installed version doesn't match the running version,
 * instead of checking that it's greater.
 * There are additional checks on the IOS side and this doesn't actually allow downgrading the firmware.
 * 
 * \return
 * 0 on success.
 */
int32_t
__CCRSysDRCFWUpdate(uint32_t drcSlot,
                    BOOL allowDowngrade);


/**
 * Finish a pending DRC firmware update.
 */
void
CCRSysDRCFWUpdateForward(void);

/**
 * Get the update state during a pending DRC firmware update.
 * 
 * \param outUpdateState
 * Pointer to store the state to.
 */
void
CCRSysGetUpdateState(CCRSysUpdateState *outUpdateState);

/**
 * Initialize a DRC reattach.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 */
void
__CCRSysInitReattach(uint32_t drcSlot);

/**
 * Wait for the DRC to reattach.
 * This returns once the DRC disconnects and reconnects or a timeout is reached.
 * 
 * \param drcSlot
 * Slot from 0 to 1.
 * 
 * \return
 * 0 on success.
 */
int32_t
__CCRSysWaitReattach(uint32_t drcSlot,
                     BOOL unknown);

/**
 * Get the version check flag.
 * 
 * \param outFlag
 * Pointer to write the flag to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysGetVersionCheckFlag(uint32_t *outFlag);

/**
 * Set the version check flag.
 * 
 * \param outFlag
 * The flag to set.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRSysSetVersionCheckFlag(uint32_t flag);

int32_t
CCRSysCaffeineSetCaffeineSlot(uint32_t slot);

int32_t
CCRSysSetInitBootFlag(CCRSysInitBootFlag flag);

/**
 * Resets the DRC (It'll show "Turn on the TV and Wii U console" until paired)
 * @return 0 on success, -1 on error.
 */
int32_t
CCRSysInitializeSettings();

#ifdef __cplusplus
}
#endif

/** @} */
