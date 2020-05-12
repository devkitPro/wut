#pragma once
#include <wut.h>

/**
 * \defgroup vpad_input VPAD Input
 * \ingroup vpad
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VPADAccStatus VPADAccStatus;
typedef struct VPADDirection VPADDirection;
typedef struct VPADGyroStatus VPADGyroStatus;
typedef struct VPADStatus VPADStatus;
typedef struct VPADTouchCalibrationParam VPADTouchCalibrationParam;
typedef struct VPADTouchData VPADTouchData;
typedef struct VPADVec2D VPADVec2D;
typedef struct VPADVec3D VPADVec3D;

//! Wii U GamePad buttons.
typedef enum VPADButtons
{
   //! The A button.
   VPAD_BUTTON_A                 = 0x8000,
   //! The B button.
   VPAD_BUTTON_B                 = 0x4000,
   //! The X button.
   VPAD_BUTTON_X                 = 0x2000,
   //! The Y button.
   VPAD_BUTTON_Y                 = 0x1000,
   //! The left button of the D-pad.
   VPAD_BUTTON_LEFT              = 0x0800,
   //! The right button of the D-pad.
   VPAD_BUTTON_RIGHT             = 0x0400,
   //! The up button of the D-pad.
   VPAD_BUTTON_UP                = 0x0200,
   //! The down button of the D-pad.
   VPAD_BUTTON_DOWN              = 0x0100,
   //! The ZL button.
   VPAD_BUTTON_ZL                = 0x0080,
   //! The ZR button.
   VPAD_BUTTON_ZR                = 0x0040,
   //! The L button.
   VPAD_BUTTON_L                 = 0x0020,
   //! The R button.
   VPAD_BUTTON_R                 = 0x0010,
   //! The + button.
   VPAD_BUTTON_PLUS              = 0x0008,
   //! The - button.
   VPAD_BUTTON_MINUS             = 0x0004,
   //! The HOME button.
   VPAD_BUTTON_HOME              = 0x0002,
   //! The SYNC button.
   VPAD_BUTTON_SYNC              = 0x0001,
   //! The right stick button.
   VPAD_BUTTON_STICK_R           = 0x00020000,
   //! The left stick button.
   VPAD_BUTTON_STICK_L           = 0x00040000,
   //! The TV button.
   VPAD_BUTTON_TV                = 0x00010000,
   //! The emulated left button on the right stick.
   VPAD_STICK_R_EMULATION_LEFT   = 0x04000000,
   //! The emulated right button on the right stick.
   VPAD_STICK_R_EMULATION_RIGHT  = 0x02000000,
   //! The emulated up button on the right stick.
   VPAD_STICK_R_EMULATION_UP     = 0x01000000,
   //! The emulated down button on the right stick.
   VPAD_STICK_R_EMULATION_DOWN   = 0x00800000,
   //! The emulated left button on the left stick.
   VPAD_STICK_L_EMULATION_LEFT   = 0x40000000,
   //! The emulated right button on the left stick.
   VPAD_STICK_L_EMULATION_RIGHT  = 0x20000000,
   //! The emulated up button on the left stick.
   VPAD_STICK_L_EMULATION_UP     = 0x10000000,
   //! The emulated down button on the left stick.
   VPAD_STICK_L_EMULATION_DOWN   = 0x08000000,
} VPADButtons;

//! Wii U GamePad channel.
typedef enum VPADChan
{
   //! Channel 0.
   VPAD_CHAN_0                   = 0,
} VPADChan;

//! Touch pad validity.
typedef enum VPADTouchPadValidity
{
   //! Both X and Y touchpad positions are accurate.
   VPAD_VALID                    = 0x0,

   //! X position is inaccurate.
   VPAD_INVALID_X                = 0x1,

   //! Y position is inaccurate.
   VPAD_INVALID_Y                = 0x2,
} VPADTouchPadValidity;

//! Touch pad resolution.
typedef enum VPADTouchPadResolution
{
   //! 1920 x 1080 resolution.
   VPAD_TP_1920X1080             = 0,
   //! 1280 x 720 resolution.
   VPAD_TP_1280X720              = 1,
   //! 854 x 480 resolution.
   VPAD_TP_854X480               = 2,
} VPADTouchPadResolution;

//! Read error.
typedef enum VPADReadError
{
   //! No error occurred, and data was written to the buffers.
   VPAD_READ_SUCCESS             = 0,
   //! There was no sample new data available to write.
   VPAD_READ_NO_SAMPLES          = -1,
   //! The requested controller or channel was invalid.
   VPAD_READ_INVALID_CONTROLLER  = -2,
} VPADReadError;

//! LCD mode.
typedef enum VPADLcdMode
{
   //! Display is in standby and will turn back on if any buttons are pressed.
   VPAD_LCD_STANDBY = 0,
   //! Display is completely off and will remain so until explicitly changed.
   VPAD_LCD_OFF = 1,
   //! Display is on as normal.
   VPAD_LCD_ON = 0xFF,
} VPADLcdMode;

//! 2D vector.
struct VPADVec2D
{
   //! x.
   float x;
   //! y.
   float y;
};
WUT_CHECK_OFFSET(VPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(VPADVec2D, 0x04, y);
WUT_CHECK_SIZE(VPADVec2D, 0x08);

//! 3D vector.
struct VPADVec3D
{
   //! x.
   float x;
   //! y.
   float y;
   //! z.
   float z;
};
WUT_CHECK_OFFSET(VPADVec3D, 0x00, x);
WUT_CHECK_OFFSET(VPADVec3D, 0x04, y);
WUT_CHECK_OFFSET(VPADVec3D, 0x08, z);
WUT_CHECK_SIZE(VPADVec3D, 0x0C);

//! Direction.
struct VPADDirection
{
   //! x.
   VPADVec3D x;
   //! y.
   VPADVec3D y;
   //! z.
   VPADVec3D z;
};
WUT_CHECK_OFFSET(VPADDirection, 0x00, x);
WUT_CHECK_OFFSET(VPADDirection, 0x0C, y);
WUT_CHECK_OFFSET(VPADDirection, 0x18, z);
WUT_CHECK_SIZE(VPADDirection, 0x24);

//! Touch calibration parameter.
struct VPADTouchCalibrationParam
{
   //! X offset.
   uint16_t adjustX;
   //! Y offset.
   uint16_t adjustY;
   //! X scale.
   float scaleX;
   //! Y scale.
   float scaleY;
};
WUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x00, adjustX);
WUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x02, adjustY);
WUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x04, scaleX);
WUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x08, scaleY);
WUT_CHECK_SIZE(VPADTouchCalibrationParam, 0x0C);

//! Touch data.
struct VPADTouchData
{
   //! The x-coordinate of a touched point.
   uint16_t x;
   //! The y-coordinate of a touched point.
   uint16_t y;

   //! 0 if screen is not currently being touched.
   uint16_t touched;

   //! Bitfield of #VPADTouchPadValidity to indicate how touch sample accuracy.
   uint16_t validity;
};
WUT_CHECK_OFFSET(VPADTouchData, 0x00, x);
WUT_CHECK_OFFSET(VPADTouchData, 0x02, y);
WUT_CHECK_OFFSET(VPADTouchData, 0x04, touched);
WUT_CHECK_OFFSET(VPADTouchData, 0x06, validity);
WUT_CHECK_SIZE(VPADTouchData, 0x08);

struct VPADAccStatus
{
   VPADVec3D acc;
   float magnitude;
   float variation;
   VPADVec2D vertical;
};
WUT_CHECK_OFFSET(VPADAccStatus, 0x00, acc);
WUT_CHECK_OFFSET(VPADAccStatus, 0x0C, magnitude);
WUT_CHECK_OFFSET(VPADAccStatus, 0x10, variation);
WUT_CHECK_OFFSET(VPADAccStatus, 0x14, vertical);
WUT_CHECK_SIZE(VPADAccStatus, 0x1c);

struct VPADStatus
{
   //! Indicates what VPADButtons are held down.
   uint32_t hold;

   //! Indicates what VPADButtons have been pressed since last sample.
   uint32_t trigger;

   //! Indicates what VPADButtons have been released since last sample.
   uint32_t release;

   //! Position of left analog stick.
   VPADVec2D leftStick;

   //! Position of right analog stick.
   VPADVec2D rightStick;

   //! Status of DRC accelorometer.
   VPADAccStatus accelorometer;

   //! Status of DRC gyro.
   VPADVec3D gyro;

   //! Status of DRC angle.
   VPADVec3D angle;

   uint8_t error;

   WUT_UNKNOWN_BYTES(0x01);

   //! Current touch position on DRC.
   VPADTouchData tpNormal;

   //! Filtered touch position, first level of smoothing.
   VPADTouchData tpFiltered1;

   //! Filtered touch position, second level of smoothing.
   VPADTouchData tpFiltered2;

   WUT_UNKNOWN_BYTES(0x02);

   VPADDirection direction;

   //! Set to 1 if headphones are plugged in, 0 otherwise.
   BOOL usingHeadphones;

   //! Status of DRC magnetometer.
   VPADVec3D mag;

   //! Current volume set by the slide control.
   uint8_t slideVolume;

   //! Battery level of controller.
   uint8_t battery;

   //! Status of DRC microphone.
   uint8_t micStatus;

   //! Unknown volume related value.
   uint8_t slideVolumeEx;

   WUT_UNKNOWN_BYTES(0x8);
};
WUT_CHECK_OFFSET(VPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(VPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(VPADStatus, 0x08, release);
WUT_CHECK_OFFSET(VPADStatus, 0x0C, leftStick);
WUT_CHECK_OFFSET(VPADStatus, 0x14, rightStick);
WUT_CHECK_OFFSET(VPADStatus, 0x1C, accelorometer);
WUT_CHECK_OFFSET(VPADStatus, 0x38, gyro);
WUT_CHECK_OFFSET(VPADStatus, 0x44, angle);
WUT_CHECK_OFFSET(VPADStatus, 0x50, error);
WUT_CHECK_OFFSET(VPADStatus, 0x52, tpNormal);
WUT_CHECK_OFFSET(VPADStatus, 0x5A, tpFiltered1);
WUT_CHECK_OFFSET(VPADStatus, 0x62, tpFiltered2);
WUT_CHECK_OFFSET(VPADStatus, 0x6C, direction);
WUT_CHECK_OFFSET(VPADStatus, 0x94, mag);
WUT_CHECK_OFFSET(VPADStatus, 0xA0, slideVolume);
WUT_CHECK_OFFSET(VPADStatus, 0xA1, battery);
WUT_CHECK_OFFSET(VPADStatus, 0xA2, micStatus);
WUT_CHECK_OFFSET(VPADStatus, 0xA3, slideVolumeEx);
WUT_CHECK_SIZE(VPADStatus, 0xAC);


/**
 * Initialises the VPAD library for use.
 *
 * \deprecated
 * As of Cafe OS 5.5.x (OSv10 v15702) this function simply logs a deprecation
 * message and returns. However, this may not be the case on older versions.
 *
 * \sa
 * - \link VPADShutdown \endlink
 */
void
VPADInit();

/**
 * Cleans up and frees the VPAD library.
 *
 * \deprecated
 * As of Cafe OS 5.5.x (OSv10 v15702) this function simply logs a deprecation
 * message and returns. However, this may not be the case on older versions.
 *
 * \sa
 * - \link VPADShutdown \endlink
 */
void
VPADShutdown();

/**
 * Read controller data from the desired Gamepad.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel to read from.
 *
 * \param buffers
 * Pointer to an array of VPADStatus buffers to fill.
 *
 * \param count
 * Number of buffers to fill.
 *
 * \param outError
 * Pointer to write read error to (if any). See #VPADReadError for meanings.
 *
 * \warning
 * You must check outError - the VPADStatus buffers may be filled with random
 * or invalid data on error, not necessarily zeroes.
 *
 * \return
 * 0 on success or 1 on failure. Check outError for reason.
 *
 * \sa
 * - VPADStatus
 */
int32_t
VPADRead(VPADChan chan,
         VPADStatus *buffers,
         uint32_t count,
         VPADReadError *outError);

/**
 * Get touch pad calibration parameters.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration parameter from.
 *
 * \param outParam
 * Pointer to the calibration to get.
 */
void
VPADGetTPCalibrationParam(VPADChan chan,
                          VPADTouchCalibrationParam *outParam);

/**
 * Set touch pad calibration parameters.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to set the calibration parameter to.
 *
 * \param param
 * Pointer to the calibration to set.
 */
void
VPADSetTPCalibrationParam(VPADChan chan,
                          const VPADTouchCalibrationParam *param);

/**
 * Transform touch data according to the current calibration data.
 * The calibration used may either be the system default or set by the
 * application via VPADSetTPCalibrationParam().
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration data from.
 *
 * \param calibratedData
 * Pointer to write calibrated touch data to.
 *
 * \param uncalibratedData
 * Pointer to the source data to apply the calibration to.
 *
 * \sa
 * - VPADTouchData
 */
void
VPADGetTPCalibratedPoint(VPADChan chan,
                         VPADTouchData *calibratedData,
                         const VPADTouchData *uncalibratedData);

/**
 * Transform touch data according to the current calibration data.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration data from.
 *
 * \param tpResolution
 * Touchpad resolution.
 *
 * \param calibratedData
 * Pointer to write calibrated touch data to.
 *
 * \param uncalibratedData
 * Pointer to the source data to apply the calibration to.
 *
 * \sa
 * - VPADTouchData
 */
void
VPADGetTPCalibratedPointEx(VPADChan chan,
                           VPADTouchPadResolution tpResolution,
                           VPADTouchData *calibratedData,
                           const VPADTouchData *uncalibratedData);

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
VPADSetAccParam(VPADChan chan,
                float playRadius,
                float sensitivity);

void
VPADGetAccParam(VPADChan chan,
                float *outPlayRadius,
                float *outSensitivity);

/**
 * Set a repeat for held buttons - instead of appearing to be continually held,
 * repeated presses and releases will be simulated at the given frequency. This
 * is similar to what happens with most computer keyboards when you hold a key.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to set up button repeat on.
 *
 * \param delaySec
 * The amount of time, in seconds, to wait until a button should start
 * repeating.
 *
 * \param pulseSec
 * The amount of time to wait between simulated presses - effectively setting
 * the period of the repetition.
 */
void
VPADSetBtnRepeat(VPADChan chan,
                 float delaySec,
                 float pulseSec);

void
VPADEnableStickCrossClamp(VPADChan chan);

void
VPADDisableStickCrossClamp(VPADChan chan);

void
VPADSetLStickClampThreshold(VPADChan chan,
                            int32_t max,
                            int32_t min);

void
VPADSetRStickClampThreshold(VPADChan chan,
                            int32_t max,
                            int32_t min);

void
VPADGetLStickClampThreshold(VPADChan chan,
                            int32_t *max,
                            int32_t *min);

void
VPADGetRStickClampThreshold(VPADChan chan,
                            int32_t *max,
                            int32_t *min);

void
VPADSetStickOrigin(VPADChan chan);

void
VPADDisableLStickZeroClamp(VPADChan chan);

void
VPADDisableRStickZeroClamp(VPADChan chan);

void
VPADEnableLStickZeroClamp(VPADChan chan);

void
VPADEnableRStickZeroClamp(VPADChan chan);

void
VPADSetCrossStickEmulationParamsL(VPADChan chan,
                                  float rotationDegree,
                                  float range,
                                  float radius);

void
VPADSetCrossStickEmulationParamsR(VPADChan chan,
                                  float rotationDegree,
                                  float range,
                                  float radius);

void
VPADGetCrossStickEmulationParamsL(VPADChan chan,
                                  float *outRotationDegree,
                                  float *outRange,
                                  float *outRadius);

void
VPADGetCrossStickEmulationParamsR(VPADChan chan,
                                  float *outRotationDegree,
                                  float *outRange,
                                  float *outRadius);

void
VPADSetGyroAngle(VPADChan chan,
                 float ax,
                 float ay,
                 float az);

void
VPADSetGyroDirection(VPADChan chan,
                     VPADDirection *dir);

void
VPADSetGyroDirectionMag(VPADChan chan,
                        float mag);

void
VPADSetGyroMagnification(VPADChan chan,
                         float pitch,
                         float yaw,
                         float roll);

void
VPADEnableGyroZeroPlay(VPADChan chan);

void
VPADEnableGyroDirRevise(VPADChan chan);

void
VPADEnableGyroAccRevise(VPADChan chan);

void
VPADDisableGyroZeroPlay(VPADChan chan);

void
VPADDisableGyroDirRevise(VPADChan chan);

void
VPADDisableGyroAccRevise(VPADChan chan);


float
VPADIsEnableGyroZeroPlay(VPADChan chan);

float
VPADIsEnableGyroZeroDrift(VPADChan chan);

float
VPADIsEnableGyroDirRevise(VPADChan chan);

float
VPADIsEnableGyroAccRevise(VPADChan chan);

void
VPADSetGyroZeroPlayParam(VPADChan chan,
                         float radius);

void
VPADInitGyroZeroPlayParam(VPADChan chan);

void
VPADInitGyroDirReviseParam(VPADChan chan);

void
VPADInitGyroAccReviseParam(VPADChan chan);

void
VPADInitGyroZeroDriftMode(VPADChan chan);

/**
 * Turns on the rumble motor on the desired Gamepad.
 * A custom rumble pattern can be set by setting bytes in the input buffer.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to rumble.
 *
 * \param pattern
 * Pointer to an array of bytes, where each byte represents the status of the
 * rumble at a given time. 0xFF denotes rumble while 0x00 denotes no rumble.
 *
 * \param length
 * The size of the rumble pattern, in bytes.
 *
 * \if false
 * meta: find out if the bytes in buffer are an analog intensity control (e.g
 * is 0x7F "half intensity"?) or are simply binary motor on/off toggles
 * \endif
 */
int32_t
VPADControlMotor(VPADChan chan,
                 uint8_t *pattern,
                 uint8_t length);

/**
 * Stops the desired Gamepad's rumble motor and cancels any ongoing rumble
 * pattern.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to stop rumbling.
 */
void
VPADStopMotor(VPADChan chan);

/**
 * Sets the current mode of the display on the given Gamepad. This function can
 * be used to turn the display on and off, or place it in standby.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to have its display mode changed.
 *
 * \param lcdMode
 * One of \link VPADLcdMode \endlink representing the new status of the display.
 *
 * \returns
 * 0 on success, or a negative value on error.
 */
int32_t
VPADSetLcdMode(VPADChan chan,
               VPADLcdMode lcdMode);

/**
 * Get the current status of the given Gamepad's display.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to get the display mode from.
 *
 * \param outLcdMode
 * Pointer to write a value of \link VPADLcdMode \endlink into.
 *
 * \returns
 * 0 on success, or a negative value on error.
 */
int32_t
VPADGetLcdMode(VPADChan chan,
               VPADLcdMode *outLcdMode);

void
VPADBASESetSensorBarSetting(VPADChan chan,
                            int8_t setting);

void
VPADBASEGetSensorBarSetting(VPADChan chan,
                            int8_t *outSetting);

/**
 * Turn the given Gamepad's sensor bar on or off. Enabling the sensor bar allows
 * any Wii Remote to position itself relative to the GamePad.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to control the sensor bar on.
 *
 * \param on
 * \c true to enable the sensor bar, \c false to disable it.
 *
 * \returns
 * 0 on success, or a negative value on error.
 */
int32_t
VPADSetSensorBar(VPADChan chan,
                 BOOL on);

#ifdef __cplusplus
}
#endif

/** @} */
