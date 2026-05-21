#pragma once
#include <wut.h>
#include <vpadbase/base.h>

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

/**
 * Button processing mode.
 *
 * \sa
 * - `VPADRead()`
 */
typedef enum VPADButtonProcMode
{
   //! Make `VPADRead()` track only the most recent button state. This is the default.
   VPAD_BUTTON_PROC_MODE_LOOSE = 0,
   //! Make `VPADRead()` track all button changes.
   VPAD_BUTTON_PROC_MODE_TIGHT = 1,
} VPADButtonProcMode;

//! Wii U GamePad buttons.
typedef enum VPADButtons
{
   //! The A button.
   VPAD_BUTTON_A                = 0x8000,
   //! The B button.
   VPAD_BUTTON_B                = 0x4000,
   //! The X button.
   VPAD_BUTTON_X                = 0x2000,
   //! The Y button.
   VPAD_BUTTON_Y                = 0x1000,
   //! The left button of the D-pad.
   VPAD_BUTTON_LEFT             = 0x0800,
   //! The right button of the D-pad.
   VPAD_BUTTON_RIGHT            = 0x0400,
   //! The up button of the D-pad.
   VPAD_BUTTON_UP               = 0x0200,
   //! The down button of the D-pad.
   VPAD_BUTTON_DOWN             = 0x0100,
   //! The ZL button.
   VPAD_BUTTON_ZL               = 0x0080,
   //! The ZR button.
   VPAD_BUTTON_ZR               = 0x0040,
   //! The L button.
   VPAD_BUTTON_L                = 0x0020,
   //! The R button.
   VPAD_BUTTON_R                = 0x0010,
   //! The + button.
   VPAD_BUTTON_PLUS             = 0x0008,
   //! The - button.
   VPAD_BUTTON_MINUS            = 0x0004,
   //! The HOME button.
   VPAD_BUTTON_HOME             = 0x0002,
   //! The SYNC button.
   VPAD_BUTTON_SYNC             = 0x0001,
   //! The right stick button.
   VPAD_BUTTON_STICK_R          = 0x00020000,
   //! The left stick button.
   VPAD_BUTTON_STICK_L          = 0x00040000,
   //! The TV button.
   VPAD_BUTTON_TV               = 0x00010000,
   //! The emulated left button on the right stick.
   VPAD_STICK_R_EMULATION_LEFT  = 0x04000000,
   //! The emulated right button on the right stick.
   VPAD_STICK_R_EMULATION_RIGHT = 0x02000000,
   //! The emulated up button on the right stick.
   VPAD_STICK_R_EMULATION_UP    = 0x01000000,
   //! The emulated down button on the right stick.
   VPAD_STICK_R_EMULATION_DOWN  = 0x00800000,
   //! The emulated left button on the left stick.
   VPAD_STICK_L_EMULATION_LEFT  = 0x40000000,
   //! The emulated right button on the left stick.
   VPAD_STICK_L_EMULATION_RIGHT = 0x20000000,
   //! The emulated up button on the left stick.
   VPAD_STICK_L_EMULATION_UP    = 0x10000000,
   //! The emulated down button on the left stick.
   VPAD_STICK_L_EMULATION_DOWN  = 0x08000000,
   //! Flag set to indicate a repeat pulse.
   VPAD_BUTTON_REPEAT           = 0x80000000,
} VPADButtons;

WUT_ENUM_BITMASK_TYPE(VPADButtons)

//! Touch pad validity.
typedef enum VPADTouchPadValidity
{
   //! Both X and Y touchpad positions are accurate.
   VPAD_VALID     = 0x0,

   //! X position is inaccurate.
   VPAD_INVALID_X = 0x1,

   //! Y position is inaccurate.
   VPAD_INVALID_Y = 0x2,
} VPADTouchPadValidity;

WUT_ENUM_BITMASK_TYPE(VPADTouchPadValidity)

//! Touch pad resolution.
typedef enum VPADTouchPadResolution
{
   //! 1920 x 1080 resolution.
   VPAD_TP_1920X1080 = 0,
   //! 1280 x 720 resolution.
   VPAD_TP_1280X720  = 1,
   //! 854 x 480 resolution.
   VPAD_TP_854X480   = 2,
} VPADTouchPadResolution;

//! Read error.
typedef enum VPADReadError
{
   //! No error occurred, and data was written to the buffers.
   VPAD_READ_SUCCESS            = 0,
   //! There was no sample new data available to write.
   VPAD_READ_NO_SAMPLES         = -1,
   //! The requested controller or channel was invalid.
   VPAD_READ_INVALID_CONTROLLER = -2,
   //! VPAD channel is busy, perhaps being accessed by another thread
   VPAD_READ_BUSY               = -4,
   //! VPAD is uninitialized, need to call `VPADInit()`
   VPAD_READ_UNINITIALIZED      = -5,
} VPADReadError;

//! LCD mode.
typedef enum VPADLcdMode
{
   //! Display is in standby and will turn back on if any buttons are pressed.
   VPAD_LCD_STANDBY = 0,
   //! Display is completely off and will remain so until explicitly changed.
   VPAD_LCD_OFF     = 1,
   //! Display is on as normal.
   VPAD_LCD_ON      = 0xFF,
} VPADLcdMode;

//! Gyro zero drift mode.
typedef enum VPADGyroZeroDriftMode
{
   VPAD_GYRO_ZERODRIFT_LOOSE    = 0,
   VPAD_GYRO_ZERODRIFT_STANDARD = 1,
   VPAD_GYRO_ZERODRIFT_TIGHT    = 2,
   VPAD_GYRO_ZERODRIFT_NONE     = 3,
} VPADGyroZeroDriftMode;

//! Mode used for various input filtering algorithms.
typedef enum VPADPlayMode
{
   VPAD_PLAY_MODE_LOOSE = 0,
   VPAD_PLAY_MODE_TIGHT = 1,
} VPADPlayMode;

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

   //! Bitfield of `VPADTouchPadValidity` to indicate how touch sample accuracy.
   uint16_t validity;
};
WUT_CHECK_OFFSET(VPADTouchData, 0x00, x);
WUT_CHECK_OFFSET(VPADTouchData, 0x02, y);
WUT_CHECK_OFFSET(VPADTouchData, 0x04, touched);
WUT_CHECK_OFFSET(VPADTouchData, 0x06, validity);
WUT_CHECK_SIZE(VPADTouchData, 0x08);

struct VPADAccStatus
{
   //! 1.0 = 1 g (Earth's gravitational acceleration.)
   VPADVec3D acc;
   //! Length of the `acc` vector.
   float magnitude;
   //! Lenght of the `current.acc - previous.acc` vector.
   float variation;
   /**
    * "Verticality" of the gamepad.
    * - `.x` is in `[0, +1]`, where `0` means it's being held vertically, `+1` means it's laying flat on a surface.
    * - `.y` is in `[-1, +1]`, where `+1` means the screen is upright, `-1` means it's upside down.
    */
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

   //! Status of DRC accelerometer.
   VPADAccStatus accelerometer;

   //! Status of DRC gyro. 1.0 = 360° per second.
   VPADVec3D gyro;

   //! Status of DRC angle. 1.0 = 360°
   VPADVec3D angle;

   //! Error flag, only set when error is `VPAD_READ_INVALID_CONTROLLER`.
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
WUT_CHECK_OFFSET(VPADStatus, 0x1C, accelerometer);
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

typedef void (*VPADSamplingCallback)(VPADChan chan);

/**
 * Initialises the VPAD library for use.
 *
 * \deprecated
 * As of Cafe OS 5.5.x (OSv10 v15702) this function simply logs a deprecation
 * message and returns. However, this may not be the case on older versions.
 *
 * \sa
 * - `VPADShutdown()`
 */
void
VPADInit(void)
   WUT_DEPRECATED("VPADInit() is deprecated");

/**
 * Cleans up and frees the VPAD library.
 *
 * \deprecated
 * As of Cafe OS 5.5.x (OSv10 v15702) this function simply logs a deprecation
 * message and returns. However, this may not be the case on older versions.
 *
 * \sa
 * - `VPADInit()`
 */
void
VPADShutdown(void)
   WUT_DEPRECATED("VPADShutdown() is deprecated");

/**
 * Read controller data from the desired Gamepad.
 *
 * \note
 * When the button processing mode is `VPAD_BUTTON_PROC_MODE_LOOSE`, all read samples have
 * the exact same data. This is the default behavior.
 *
 * \note

 * The VPAD library can only store 16 samples, so it's useless to make `buffers` larger
 * than 16.
 *
 * \param chan
 * The channel to read from.
 *
 * \param buffers
 * Pointer to an array of `VPADStatus` to fill with samples, sorted from newest to
 * oldest.
 *
 * \param count
 * Capacity of the `buffers` array.
 *
 * \param outError
 * Pointer to write read error to (if any).
 *
 * \return
 * The amount of buffers read or `0` on failure. Check `outError` for reason.
 *
 * \sa
 * - `VPADGetButtonProcMode()`
 * - `VPADSetSamplingCallback()`
 */
int32_t
VPADRead(VPADChan chan,
         VPADStatus *buffers,
         uint32_t count,
         VPADReadError *outError);

/**
 * Get touch pad calibration parameters.
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

void
VPADSetAccParam(VPADChan chan,
                float playRadius,
                float sensitivity);

void
VPADGetAccParam(VPADChan chan,
                float *outPlayRadius,
                float *outSensitivity);

/**
 * Sets button repeat action for held buttons.
 *
 * The `hold` flag in `VPADStatus` will have the `VPAD_BUTTON_REPEAT` flag set
 * periodically.
 *
 * \param chan
 * Denotes which channel to set up button repeat on.
 *
 * \param delaySec
 * The amount of time, in seconds, to wait until a button should start
 * repeating.
 *
 * \param pulseSec
 * The amount of time between pulses, in seconds. Set to `0` to disable repeats. Default is `0`.
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
VPADGetGyroDirReviseParam(VPADChan chan,
                          float *param);

void
VPADGetGyroZeroDriftMode(VPADChan chan,
                         VPADGyroZeroDriftMode *mode);

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
VPADSetGyroDirReviseBase(VPADChan chan,
                         VPADDirection *base);

void
VPADSetGyroDirReviseParam(VPADChan chan,
                          float param);

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
VPADSetGyroZeroDriftMode(VPADChan chan,
                         VPADGyroZeroDriftMode mode);

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

/**
 * Resets the gyro acceleration correction parameters back to default values.
 *
 * The parameters are initialized to:
 * - `weight = 0.03f`
 * - `range = 0.4f`
 *
 * \sa
 * - `VPADGetGyroAccReviseParam()`
 * - `VPADSetGyroAccReviseParam()`
 */
void
VPADInitGyroAccReviseParam(VPADChan chan);

void
VPADStartGyroMagRevise(VPADChan chan);

void
VPADStopGyroMagRevise(VPADChan chan);

/**
 * Initializes the zero drift mode on the desired Gamepad.
 *
 * \param chan
 * The channel of the Gamepad to initialize.
 */
void
VPADInitGyroZeroDriftMode(VPADChan chan);

/**
 * Get the TV menu status.
 *
 * \param chan
 * The channel of the Gamepad to get the TV status from.
 *
 * \returns
 * TRUE if the TV menu is shown, FALSE otherwise.
 */
BOOL
VPADGetTVMenuStatus(VPADChan chan);

/**
 * Enable or disable the TV menu.
 *
 * \param chan
 * The channel of the Gamepad to enable or disable the TV menu from.
 *
 * \param invalid
 * Set to TRUE to disable the TV menu or FALSE to enable it.
 */
void
VPADSetTVMenuInvalid(VPADChan chan,
                     BOOL invalid);

/**
 * Disable the power button.
 *
 * \param chan
 * The channel of the Gamepad to disable the power button from.
 */
void
VPADDisablePowerButton(VPADChan chan);

/**
 * Enable the power button.
 *
 * \param chan
 * The channel of the Gamepad to enable the power button from.
 */
void
VPADEnablePowerButton(VPADChan chan);

/**
 * Controls the rumble motor on the desired Gamepad.
 *
 * Each bit in the pattern is played (`1` = motor on, `0` = motor off) at a rate of 120
 * Hz. Up to 1 second of rumble can be queued up (120 bits.)
 *
 * \param chan
 * The channel of the Gamepad to rumble.
 *
 * \param pattern
 * The rumble pattern. Must always be 15 bytes long.
 *
 * \param length
 * How many bits are in the rumble pattern, up to `120`. Set to `0` to stop all rumble.
 *
 * \return
 * `0` on success, or negative value on error.
 *
 * \sa
 * - `VPADStopMotor()`
 */
int32_t
VPADControlMotor(VPADChan chan,
                 const uint8_t *pattern,
                 uint8_t length);

/**
 * Stops the desired Gamepad's rumble motor and cancels any ongoing rumble
 * pattern.
 *
 * \param chan
 * The channel of the Gamepad to stop rumbling.
 *
 * \sa
 * - `VPADControlMotor()`
 */
void
VPADStopMotor(VPADChan chan);

/**
 * Sets the current mode of the display on the given Gamepad.
 *
 * This function can be used to turn the display on and off, or place it in standby.
 *
 * \param chan
 * The channel of the Gamepad to have its display mode changed.
 *
 * \param lcdMode
 * The LCD mode.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - `VPADGetLcdMode()`
 */
int32_t
VPADSetLcdMode(VPADChan chan,
               VPADLcdMode lcdMode);

/**
 * Get the current status of the given Gamepad's display.
 *
 * \param chan
 * The channel of the Gamepad to get the display mode from.
 *
 * \param outLcdMode
 * Pointer to store the mode.
 *
 * \returns
 * 0 on success, or a negative value on error.
 *
 * \sa
 * - `VPADSetLcdMode()`
 */
int32_t
VPADGetLcdMode(VPADChan chan,
               VPADLcdMode *outLcdMode);

/**
 * Turn the given Gamepad's sensor bar on or off. Enabling the sensor bar allows
 * any Wii Remote to position itself relative to the GamePad.
 *
 * \param chan
 * The channel of the Gamepad to control the sensor bar on.
 *
 * \param on
 * `true` to enable the sensor bar, `false` to disable it.
 *
 * \returns
 * `0` on success, or a negative value on error.
 */
int32_t
VPADSetSensorBar(VPADChan chan,
                 BOOL on);

VPADSamplingCallback
VPADSetSamplingCallback(VPADChan chan,
                        VPADSamplingCallback callback);

/**
 * Gets the button processing mode.
 *
 * \param chan The target Gamepad.
 *
 * \return The current mode.
 *
 * \sa
 * - `VPADRead()`
 * - `VPADSetButtonProcMode()`
 */
VPADButtonProcMode
VPADGetButtonProcMode(VPADChan chan);

/**
 * Calculates the calibration parameter from two reference points.
 *
 * \param param Pointer to store the calibration.
 * \param touchX1 Touch X of the first point.
 * \param touchY1 Touch Y of the first point.
 * \param screenX1 Screen X of the first point.
 * \param screenY1 Screen Y of the first point.
 * \param touchX2 Touch X of the second point.
 * \param touchY2 Touch Y of the second point.
 * \param screenX2 Screen X of the second point.
 * \param screenY2 Screen Y of the second point.
 *
 * \return `1` if calibration was calculated, `-1` if points are too close together.
 */
int32_t
VPADCalcTPCalibrationParam(VPADTouchCalibrationParam *param,
                           uint16_t touchX1,
                           uint16_t touchY1,
                           uint16_t screenX1,
                           uint16_t screenY1,
                           uint16_t touchX2,
                           uint16_t touchY2,
                           uint16_t screenX2,
                           uint16_t screenY2);

/**
 * Gets the accelerometer play mode.
 *
 * \param chan The target Gamepad.
 *
 * \return The current mode.
 */
VPADPlayMode
VPADGetAccPlayMode(VPADChan chan);

/**
 * Gets the gyro acceleration correction parameters.
 *
 * \param chan The target Gamepad.
 * \param weight Pointer to store the weight parameter.
 * \param range Pointer to store the range parameter.
 *
 * \sa
 * - `VPADInitGyroAccReviseParam()`
 * - `VPADSetGyroAccReviseParam()`
 */
void
VPADGetGyroAccReviseParam(VPADChan chan,
                          float *weight,
                          float *range);

/**
 * Gets the gyro magnetometer correction parameters.
 *
 * \param chan The target Gamepad.
 * \param weight Pointer to store the weight parameter.
 * \param tolerance Pointer to store the angular speed tolerance parameter.
 *
 * \sa
 * - `VPADSetGyroMagReviseParam()`
 */
void
VPADGetGyroMagReviseParam(VPADChan chan,
                          float *weight,
                          float *tolerance);

/**
 * Gets the gyro's zero play tolerance.
 *
 * \param chan The target Gamepad.
 * \param tolerance Pointer to store the tolerance.
 *
 * \sa
 * - `VPADInitGyroZeroPlayParam()`
 * - `VPADSetGyroZeroPlayParam()`
 */
void
VPADGetGyroZeroPlayParam(VPADChan chan,
                         float *tolerance);

/**
 * Gets the magnetometer correction being used on the gyro.
 *
 * \param chan The target Gamepad.
 *
 * \return `-1` when magnetometer correction is disabled, `>= 0` to indicate how much the
 *         magnetometer value is affecting the gyro.
 *
 * \sa
 * - `VPADStartGyroMagRevise()`
 * - `VPADStopGyroMagRevise()`
 */
float
VPADIsStartedGyroMagRevise(VPADChan chan);

/**
 * Resets the Gamepad's accelerometer calibration back to factory settings.
 *
 * \param chan The target Gamepad.
 *
 * \return `0` on success, `-1` if the calibration data could not be written to EEPROM.
 */
int32_t
VPADResetAccToDefault(VPADChan chan);

/**
 * Resets the Gamepad's touch screen calibration back to factory settings.
 *
 * \param chan The target Gamepad.
 *
 * \return `0` on success.
 */
int
VPADResetTPToDefault(VPADChan chan);

/**
 * Sets the accelerometer play mode.
 *
 * \param chan The target Gamepad.
 * \param mode `VPAD_PLAY_MODE_LOOSE` for smooth data, `VPAD_PLAY_MODE_TIGHT` for sharp
 *             data. The default is `VPAD_PLAY_MODE_LOOSE`.
 *
 * \sa
 * - `VPADGetAccPlayMode()`
 */
void
VPADSetAccPlayMode(VPADChan chan,
                   VPADPlayMode mode);

int32_t
VPADSetAudioVolumeOverride(VPADChan chan,
                           BOOL unknown1,
                           uint8_t unknown2);

/**
 * Sets the button processing mode.
 *
 * When mode is:

 * - `VPAD_BUTTON_PROC_MODE_TIGHT`: button state is tracked in-between calls to
 *   `VPADRead()`, and are stored in the status array from newest to oldest.
 * - `VPAD_BUTTON_PROC_MODE_LOOSE`: only the most recent button state is tracked. All
 *   samples produced by `VPADRead()` have the exact same button state.
 *
 * \param chan The target Gamepad.
 * \param mode The mode. Default is `VPAD_BUTTON_PROC_MODE_LOOSE`.
 *
 * \sa
 * - `VPADRead()`
 */
void
VPADSetButtonProcMode(VPADChan chan,
                      VPADButtonProcMode mode);

/**
 * Sets the gyro accelerometer correction parameters.
 *
 * \param chan The target Gamepad.
 * \param weight The weight parameter, in `[0, 1]`. It controls how much correction is applied.
 * \param range The range parameter, measured in g (Earth's gravity).
 *
 * \sa
 * - `VPADGetGyroAccReviseParam()`
 * - `VPADInitGyroAccReviseParam()`
 */
void
VPADSetGyroAccReviseParam(VPADChan chan,
                          float weight,
                          float range);

/**
 * Sets the gyro magnetometer correction parameters.
 *
 * \param chan The target Gamepad.

 * \param weight The weight parameter, in `[0, 1]`. It controls how much correction is
 *               applied. The default is `0` (no correction.)
 * \param tolerance The angular speed tolerance, in full revolutions (1 = 360°) per
 *                  second. Default is `0`.
 *
 * \sa
 - `VPADGetGyroDirReviseParam()`
 */
void
VPADSetGyroMagReviseParam(VPADChan chan,
                          float weight,
                          float tolerance);

void
VPADStartAccCalibration(VPADChan chan,
                        uint32_t unknown);

/**
 * Writes touchpad calibration data to EEPROM.
 *
 * \param chan The target Gamepad.
 * \param oldMinX Written directly.
 * \param oldMinY Written directly.
 * \param newMinX Scaled by `0.6672004f` (approx. `854.0f / 1280.0f`)
 * \param newMinY Scaled by `0.6666667f` (`480.0f / 720.0f`)
 * \param oldMaxX Written directly.
 * \param oldMaxY Written directly.
 * \param newMaxX Scaled by `0.6672004f` (approx. `854.0f / 1280.0f`)
 * \param newMaxY Scaled by `0.6666667f` (`480.0f / 720.0f`)
 *
 * \return `0` on success.
 */
int32_t
VPADWriteTPCalibrationValueToEEPROM(VPADChan chan,
                                    uint16_t oldMinX,
                                    uint16_t oldMinY,
                                    uint16_t newMinX,
                                    uint16_t newMinY,
                                    uint16_t oldMaxX,
                                    uint16_t oldMaxY,
                                    uint16_t newMaxX,
                                    uint16_t newMaxY);

#ifdef __cplusplus
}
#endif

/** @} */
