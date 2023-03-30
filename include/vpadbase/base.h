#pragma once
#include <wut.h>

/**
 * \defgroup vpadbase_base VPAD Base
 * \ingroup vpadbase
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! Wii U GamePad channel.
typedef enum VPADChan
{
   //! Channel 0.
   VPAD_CHAN_0                   = 0,
   //! Channel 1.
   VPAD_CHAN_1                   = 1,
} VPADChan;

typedef enum
{
   //! Indicates that there is pending data which can be received
   VPAD_IRC_STATUS_FLAG_HAS_DATA    = 1,
   //! Indicates that another device is connected
   VPAD_IRC_STATUS_FLAG_CONNECTED   = 2,
} VPADIRCStatusFlags;

/**
 * Initializes the VPADBASE library for use.
 *
 * \note
 * This is internally called by vpad and does not need to be called manually.
 *
 * \sa
 * - \link VPADBASEShutdown \endlink
 */
void
VPADBASEInit();

/**
 * Deinitializes the VPADBASE library.
 *
 * \note
 * This is internally called by vpad and does not need to be called manually.
 *
 * \sa
 * - \link VPADBASEInit \endlink
 */
void
VPADBASEShutdown();

/**
 * Checks if VPADBASE is initialized.
 *
 * \returns
 * \c TRUE if initialized.
 */
BOOL
VPADBASEIsInit();

/**
 * Return a count representing the amount of time left for the given Gamepad's
 * rumble pattern.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the rumble time from.
 */
int32_t
VPADBASEGetMotorOnRemainingCount(VPADChan chan);

/**
 * Set a count representing the amount of time left for the given Gamepad's
 * rumble pattern.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to set the rumble count for.
 *
 * \param counter
 * The value of the new rumble count.
 *
 * <!-- meta: I assume this affects the index into the rumble pattern? -->
 */
int32_t
VPADBASESetMotorOnRemainingCount(VPADChan chan,
                                 int32_t counter);

void
VPADBASESetSensorBarSetting(VPADChan chan,
                            int8_t setting);

void
VPADBASEGetSensorBarSetting(VPADChan chan,
                            int8_t *outSetting);

/**
 * Get the headphone status.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to get the headphone status from.
 *
 * \returns
 * Returns 1 if headphones are connected, 0 otherwise.
 */
int32_t
VPADBASEGetHeadphoneStatus(VPADChan chan);

/**
 * Get the controller mode.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to get the controller mode from.
 *
 * \param mode
 * Pointer to write a value of the controller mode into.
 */
void
VPADBASEGetGameControllerMode(VPADChan chan,
                              int32_t *mode);

/**
 * Set the controller mode.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to set the controller mode to.
 *
 * \param mode
 * Any non-zero mode will turn off the display, like the "Display Off" button under Controller Settings.
 * Inputs are not disabled.
 */
void
VPADBASESetGameControllerMode(VPADChan chan,
                              int32_t mode);

/**
 * Get the POWER button press status.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to get the POWER button press status from.
 *
 * \param tick
 * The value given by \link OSGetTick \endlink when the button was pressed.
 *
 * \param status
 * The status is set to 0 if the POWER button is not pressed.
 */
void
VPADBASEGetPowerButtonPressStatus(VPADChan chan,
                                  uint32_t *tick,
                                  uint32_t *status);

/**
 * Set the POWER button press status.
 *
 * \param chan
 * The channel of the Gamepad to set the POWER button press status to.
 *
 * \param tick
 * The tick value to set.
 *
 * \param status
 * The status to set.
 */
void
VPADBASESetPowerButtonPressStatus(VPADChan chan,
                                  uint32_t tick,
                                  uint32_t status);

/**
 * Set the POWER button mode.
 *
 * \param chan
 * The channel of the Gamepad to set the POWER button disable mode to.
 *
 * \param mode
 * Set to 0 to enable and set to 1 to disable.
 *
 * \sa
 * - \link VPADDisablePowerButton \endlink
 * - \link VPADEnablePowerButton \endlink
 */
void
VPADBASESetPowerButtonDisableMode(VPADChan chan,
                                  uint32_t mode);

/**
 * Clear pending IRC events.
 *
 * \param chan
 * The channel of the Gamepad.
 */
void
VPADBASEClearIRCEvent(VPADChan chan);

/**
 * Get the current IRC status.
 *
 * \param chan
 * The channel of the Gamepad.
 * 
 * \returns
 * The current status flags (see \link VPADIRCStatusFlags \endlink).
 */
VPADIRCStatusFlags
VPADBASEGetIRCStatus(VPADChan chan);

#ifdef __cplusplus
}
#endif

/** @} */
