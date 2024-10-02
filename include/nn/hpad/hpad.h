#pragma once
#include <wut.h>

/**
 * \defgroup nn_hpad_hpad
 * \ingroup nn_hpad
 * Functions for using the USB Gamecube Controller Adapter.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! The minimum value of the stick axis
#define HPAD_STICK_AXIS_MIN  -56
//! The maximum value of the stick axis
#define HPAD_STICK_AXIS_MAX   56
//! The minimum value of the substick axis
#define HPAD_SUBSTICK_AXIS_MIN -44
//! The maximum value of the substick axis
#define HPAD_SUBSTICK_AXIS_MAX  44
//! The minimum value of the trigger
#define HPAD_TRIGGER_MIN      0
//! The maximum value of the trigger
#define HPAD_TRIGGER_MAX      150

typedef struct HPADStatus HPADStatus;
typedef struct HPADGGGGStatus HPADGGGGStatus;

typedef enum HPADChan
{
   HPAD_CHAN_0 = 0,
   HPAD_CHAN_1 = 1,
   HPAD_CHAN_2 = 2,
   HPAD_CHAN_3 = 3,
   HPAD_CHAN_4 = 4,
   HPAD_CHAN_5 = 5,
   HPAD_CHAN_6 = 6,
   HPAD_CHAN_7 = 7,
} HPADChan;

typedef enum HPADGGGGChan
{
   //! Adapter Channel 0
   HPAD_GGGG_CHAN_0 = 0,
   //! Adapter Channel 1
   HPAD_GGGG_CHAN_1 = 1,
} HPADGGGGChan;

typedef enum HPADButtons
{
   HPAD_BUTTON_A     = 0x0001,
   HPAD_BUTTON_B     = 0x0002,
   HPAD_BUTTON_X     = 0x0004,
   HPAD_BUTTON_Y     = 0x0008,
   HPAD_BUTTON_LEFT  = 0x0010,
   HPAD_BUTTON_RIGHT = 0x0020,
   HPAD_BUTTON_DOWN  = 0x0040,
   HPAD_BUTTON_UP    = 0x0080,
   HPAD_BUTTON_START = 0x0100,
   HPAD_TRIGGER_Z    = 0x0200,
   HPAD_TRIGGER_R    = 0x0400,
   HPAD_TRIGGER_L    = 0x0800,

   HPAD_STICK_EMULATION_LEFT     = 0x00001000,
   HPAD_STICK_EMULATION_RIGHT    = 0x00002000,
   HPAD_STICK_EMULATION_DOWN     = 0x00004000,
   HPAD_STICK_EMULATION_UP       = 0x00008000,
   HPAD_SUBSTICK_EMULATION_LEFT  = 0x00010000,
   HPAD_SUBSTICK_EMULATION_RIGHT = 0x00020000,
   HPAD_SUBSTICK_EMULATION_DOWN  = 0x00040000,
   HPAD_SUBSTICK_EMULATION_UP    = 0x00080000,
} HPADButtons;

typedef enum HPADMotorCommand
{
   HPAD_MOTOR_COMMAND_STOP      = 0,
   HPAD_MOTOR_COMMAND_RUMBLE    = 1,
   HPAD_MOTOR_COMMAND_STOP_HARD = 2,
} HPADMotorCommand;

struct HPADStatus
{
   //! Indicates what HPADButtons are held down.
   int32_t hold;
   //! Indicates what HPADButtons have been pressed since last sample.
   int32_t trigger;
   //! Indicates what HPADButtons have been released since last sample.
   int32_t release;
   //! X-Position of the analog stick
   int8_t stickX;
   //! Y-Position of the analog stick
   int8_t stickY;
   //! X-Position of the analog substick/C-Stick
   int8_t substickX;
   //! Y-Position of the analog substick/C-Stick
   int8_t substickY;
   //! Position of the left analog trigger
   uint8_t triggerL;
   //! Position of the right analog trigger
   uint8_t triggerR;
   //! Status of the controller
   uint8_t status;
   WUT_PADDING_BYTES(0x1);
   //! Read error, 0 for success
   int32_t error;
};
WUT_CHECK_OFFSET(HPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(HPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(HPADStatus, 0x08, release);
WUT_CHECK_OFFSET(HPADStatus, 0x0C, stickX);
WUT_CHECK_OFFSET(HPADStatus, 0x0D, stickY);
WUT_CHECK_OFFSET(HPADStatus, 0x0E, substickX);
WUT_CHECK_OFFSET(HPADStatus, 0x0F, substickY);
WUT_CHECK_OFFSET(HPADStatus, 0x10, triggerL);
WUT_CHECK_OFFSET(HPADStatus, 0x11, triggerR);
WUT_CHECK_OFFSET(HPADStatus, 0x12, status);
WUT_CHECK_OFFSET(HPADStatus, 0x14, error);
WUT_CHECK_SIZE(HPADStatus, 0x18);

struct HPADGGGGStatus
{
   //! \c TRUE if the adapeter is connected
   BOOL connected;
   //! \c TRUE if the power supply is connected
   BOOL powerSupplyConnected;
   //! \c TRUE if the adapter is active/is sending samples
   BOOL active;
};
WUT_CHECK_OFFSET(HPADGGGGStatus, 0x0, connected);
WUT_CHECK_OFFSET(HPADGGGGStatus, 0x4, powerSupplyConnected);
WUT_CHECK_OFFSET(HPADGGGGStatus, 0x8, active);
WUT_CHECK_SIZE(HPADGGGGStatus, 0xC);

typedef void (*HPADConnectCallback)(HPADChan chan, int32_t status);
typedef void (*HPADGGGGConnectCallback)(HPADGGGGChan chan, BOOL connected);
typedef void (*HPADPowerSupplyCallback)(HPADGGGGChan chan, BOOL connected);
typedef void (*HPADSamplingCallback)(HPADGGGGChan chan);
typedef void (*HPADResetCallback)(HPADGGGGChan chan, int32_t status);

/**
 * Initializes the HPAD library.
 *
 * \return
 * 0 on success.
 */
int32_t
HPADInit(void);

/**
 * Shuts down the HPAD library.
 *
 * \return
 * 0 on success.
 */
int32_t
HPADShutdown(void);

/**
 * Reads status buffers from a specified HPAD channel.
 * 
 * \warning
 * The count parameter is ignored and this function will always fill up to 16 sampling buffers.
 * Make sure to always make space for 16 buffers.
 * 
 * \param chan
 * The channel to read from.
 * 
 * \param buffers
 * Pointer to an array of HPADStatus buffers to fill.
 *
 * \param count
 * Number of buffers to fill.
 * 
 * \return
 * The amount of buffers read or a negative value on error.
 */
// clang-format off
int32_t
RPLWRAP(HPADRead)(HPADChan chan,
                  HPADStatus *buffers,
                  int32_t count);
// clang-format on

/**
 * Reads status buffers from a specified HPAD channel.
 * 
 * \param chan
 * The channel to read from.
 * 
 * \param buffers
 * Pointer to an array of HPADStatus buffers to fill.
 *
 * \param count
 * Number of buffers to fill. Must be 16.
 * 
 * \return
 * The amount of buffers read or a negative value on error.
 */
static inline int32_t
HPADRead(HPADChan chan,
         HPADStatus *buffers,
         int32_t count)
{
   // HPADRead ignores the count and will always fill up to 16 sampling buffers
   if (count != 16) {
      return -6;
   }

   return RPLWRAP(HPADRead)(chan, buffers, count);
}

/**
 * Sends a motor/rumble command to the specified HPAD channel.
 * 
 * \param chan
 * The channel to send the command to.
 * 
 * \param command
 * The motor command to send.
 * 
 * \return
 * 0 on success.
 */
int32_t
HPADControlMotor(HPADChan chan,
                 HPADMotorCommand command);

/**
 * Invalidates calibration data of the specified HPAD channel.
 * 
 * \param chan
 * The channel to invalidate data.
 * 
 * \return
 * 0 on success.
 */
int32_t
HPADRecalibrate(HPADChan chan);

/**
 * Sets a callback for once the specified HPAD channel is connected.
 *
 * \param chan
 * The channel to set the callback.
 *
 * \param callback
 * A pointer to the callback function.
 *
 * \return
 * A pointer to the previous callback or \c NULL.
 */
HPADConnectCallback
HPADSetConnectCallback(HPADChan chan,
                       HPADConnectCallback callback);

/**
 * Get the status of the specified GGGG channel (GC Adapter).
 * 
 * \param chan
 * The channel to get the status from.
 * 
 * \param status
 * A pointer to write the status to.
 * 
 * \return
 * 0 on success.
 */
int32_t
HPADGetGGGGStatus(HPADGGGGChan chan,
                  HPADGGGGStatus *status);

/**
 * Sets a callback for once the specified GGGG Adapter is connected.
 *
 * \param chan
 * The channel to set the callback.
 *
 * \param callback
 * A pointer to the callback function.
 *
 * \return
 * A pointer to the previous callback or \c NULL.
 */
HPADGGGGConnectCallback
HPADSetGgggConnectCallback(HPADGGGGChan chan,
                           HPADGGGGConnectCallback callback);

/**
 * Sets a callback for once the power supply of the specified GGGG Adapter is connected.
 *
 * \param chan
 * The channel to set the callback.
 *
 * \param callback
 * A pointer to the callback function.
 *
 * \return
 * A pointer to the previous callback or \c NULL.
 */
HPADPowerSupplyCallback
HPADSetPowerSupplyCallback(HPADGGGGChan chan,
                           HPADPowerSupplyCallback callback);

/**
 * Sets a callback for once a sample is received from the specified GGGG Adapter.
 *
 * \param chan
 * The channel to set the callback.
 *
 * \param callback
 * A pointer to the callback function.
 *
 * \return
 * A pointer to the previous callback or \c NULL.
 */
HPADSamplingCallback
HPADSetSamplingCallback(HPADGGGGChan chan,
                        HPADSamplingCallback callback);

/**
 * Resets the specified GGGG Adapter.
 *
 * \param chan
 * The channel to reset.
 *
 * \param callback
 * A pointer to a callback function after resetting is complete.
 *
 * \return
 * 0 on success.
 */
int32_t
HPADResetDevice(HPADGGGGChan chan,
                HPADResetCallback callback);

#ifdef __cplusplus
}
#endif

/** @} */
