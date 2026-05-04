#pragma once
#include <wut.h>
#include <padscore/wbc.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_kpad KPAD
 * \ingroup padscore
 *
 * KPAD is a high-level library over WPAD.
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Button repeat flag.
 *
 * \sa
 * - `KPADRead()`
 * - `KPADReadEx()`
 * - `KPADSetBtnRepeat()`
 */
#define KPAD_BUTTON_REPEAT 0x80000000u

//! Wii Remote channel.
typedef enum WPADChan KPADChan;
//! Data format.
typedef enum WPADDataFormat KPADDataFormat;
//! Extension type.
typedef enum WPADExtensionType KPADExtensionType;
//! MotionPlus Mode.
typedef enum WPADMplsMode KPADMplsMode;

typedef struct KPADBase3D KPADBase3D;
typedef struct KPADRect KPADRect;
typedef struct KPADStatus KPADStatus;
typedef struct KPADUnifiedWpadStatus KPADUnifiedWpadStatus;
typedef struct KPADVec2D KPADVec2D;
typedef struct KPADVec3D KPADVec3D;

typedef enum KPADButtonProcMode
{
   //! Make `KPADRead()` track only the most recent button state. This is the default.
   KPAD_BUTTON_PROC_MODE_LOOSE = 0,
   //! Make `KPADRead()` track all button changes.
   KPAD_BUTTON_PROC_MODE_TIGHT = 1,
} KPADButtonProcMode;

//! Status codes for `KPADControlDpdCallback`.
typedef enum KPADControlDpdStatus
{
   KPAD_CONTROL_DPD_STATUS_STARTED  = 0,
   KPAD_CONTROL_DPD_STATUS_FINISHED = 1,
} KPADControlDpdStatus;

//! Error.
typedef enum KPADError
{
   //! No error occurred, and data was written to the buffers.
   KPAD_ERROR_OK                 = 0,
   //! There was no sample new data available to write.
   KPAD_ERROR_NO_SAMPLES         = -1,
   //! The requested controller or channel was invalid.
   KPAD_ERROR_INVALID_CONTROLLER = -2,
   //! WPAD is uninitialized, shouldn't happen unless WPADShutdown() is manually called
   KPAD_ERROR_WPAD_UNINIT        = -3,
   //! KPAD channel is busy, perhaps being accessed by another thread
   KPAD_ERROR_BUSY               = -4,
   //! KPAD is uninitialized, need to call KPADInit()
   KPAD_ERROR_UNINITIALIZED      = -5,
} KPADError;

//! Status codes for `KPADControlMplsCallback`.
typedef enum KPADControlMplsStatus
{
   //! When `KPADEnableMpls()` is called.
   KPAD_CONTROL_MPLS_STATUS_STARTED             = 0,
   //! When MotionPlus mode was set correctly, or wiimote disconnected prematurely.
   KPAD_CONTROL_MPLS_STATUS_FINISHED            = 1,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_ONLY)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_ONLY    = -1,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_NUNCHUK)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_NUNCHUK = -2,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_CLASSIC)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_CLASSIC = -3,
} KPADControlMplsStatus;

typedef enum KPADMplsZeroDriftMode
{
   KPAD_MPLS_ZERO_DRIFT_MODE_LOOSE,
   KPAD_MPLS_ZERO_DRIFT_MODE_STANDARD,
   KPAD_MPLS_ZERO_DRIFT_MODE_TIGHT,
} KPADMplsZeroDriftMode;

typedef enum KPADPlayMode
{
   //! Use a smoothing filter.
   KPAD_PLAY_MODE_LOOSE = 0,
   //! Use a sharper, more responsive filter.
   KPAD_PLAY_MODE_TIGHT = 1,
} KPADPlayMode;

//! 2D vector.
struct KPADVec2D
{
   //! x.
   float x;
   //! y.
   float y;
};
WUT_CHECK_OFFSET(KPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(KPADVec2D, 0x04, y);
WUT_CHECK_SIZE(KPADVec2D, 0x08);

//! 3D vector.
struct KPADVec3D
{
   //! x.
   float x;
   //! y.
   float y;
   //! z.
   float z;
};
WUT_CHECK_OFFSET(KPADVec3D, 0x00, x);
WUT_CHECK_OFFSET(KPADVec3D, 0x04, y);
WUT_CHECK_OFFSET(KPADVec3D, 0x08, z);
WUT_CHECK_SIZE(KPADVec3D, 0x0C);

struct KPADBase3D
{
   KPADVec3D x;
   KPADVec3D y;
   KPADVec3D z;
};
WUT_CHECK_OFFSET(KPADBase3D, 0x00, x);
WUT_CHECK_OFFSET(KPADBase3D, 0x0C, y);
WUT_CHECK_OFFSET(KPADBase3D, 0x18, z);
WUT_CHECK_SIZE(KPADBase3D, 0x24);

//! 2D rectangle.
struct KPADRect
{
   KPADVec2D topLeft;
   KPADVec2D bottomRight;
};
WUT_CHECK_OFFSET(KPADRect, 0x00, topLeft);
WUT_CHECK_OFFSET(KPADRect, 0x08, bottomRight);
WUT_CHECK_SIZE(KPADRect, 0x10);

//! A structure containing the Wii Remote data.
struct KPADStatus
{
   //! Indicates what KPADButtons are held down.
   uint32_t hold;

   //! Indicates what KPADButtons have been pressed since last sample.
   uint32_t trigger;

   //! Indicates what KPADButtons have been released since last sample.
   uint32_t release;

   //! Indicates the value of the acceleration sensor.
   KPADVec3D acc;

   //! Indicates the magnitude of acceleration.
   float accMagnitude;

   //! Indicates the variation in acceleration.
   float accVariation;

   //! Indicates the position where the Wii Remote is pointing; positive for right and down.
   KPADVec2D pos;

   //! Difference from previous `pos`.
   KPADVec2D posDiff;

   //! Magnitude of `posDiff`.
   float posDiffMagnitude;

   //! Angle: horizon vector (+x is right, +y is down.)
   KPADVec2D angle;

   //! Difference from previous `angle`.
   KPADVec2D angleDiff;

   //! Magnitude of `angleDiff`.
   float angleDiffMagnitude;

   //! Distance to the sensor bar, in meters.
   float dist;

   //! Difference from previous `dist`.
   float distDiff;

   //! Absolute value of `distDiff`.
   float distDiffMagnitude;

   //! The "down" vector from accelerometer: when `down.y` is negative, wiimote is facing down.
   KPADVec2D down;

   //! Value from KPADExtensionType.
   uint8_t extensionType;

   //! Value from WPADError.
   int8_t error;

   //! Validity of the `pos` field.
   int8_t posValid;

   //! Value from KPADDataFormat.
   uint8_t format;

   //! Extension data, check with extensionType to see what is valid to read.
   union
   {
      //! Structure to use when `extensionType` is set to \link WPAD_EXT_NUNCHUK \endlink.
      struct
      {
         //! Position of the analog stick.
         KPADVec2D stick;
         //! Indicates the value of the acceleration sensor.
         KPADVec3D acc;
         //! Indicates the magnitude of acceleration.
         float accMagnitude;
         //! Indicates the variation in acceleration.
         float accVariation;
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
      } nunchuk;

      //! Structure to use when `extensionType` is set to \link WPAD_EXT_CLASSIC \endlink.
      struct
      {
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
         //! Position of left analog stick.
         KPADVec2D leftStick;
         //! Position of right analog stick.
         KPADVec2D rightStick;
         //! Left trigger.
         float leftTrigger;
         //! Right trigger.
         float rightTrigger;
      } classic;

      //! Structure to use when `extensionType` is set to \link WPAD_EXT_PRO_CONTROLLER \endlink.
      struct
      {
         //! Indicates what buttons are held down.
         uint32_t hold;
         //! Indicates what buttons have been pressed since last sample.
         uint32_t trigger;
         //! Indicates what buttons have been released since last sample.
         uint32_t release;
         //! Position of left analog stick.
         KPADVec2D leftStick;
         //! Position of right analog stick.
         KPADVec2D rightStick;
         //! Is charging flag.
         int32_t charging;
         //! Is wired flag.
         int32_t wired;
      } pro;

      /**
       * Structure to use when `extensionType` is set to `WPAD_EXT_BALANCE_BOARD`.
       *
       * Note: Balance Board support in KPAD seems to be incomplete, only `weights` and
       * `error` members seem to hold useful data.
       */
      struct
      {
         //! Averaged corrected (total) weight, but it's always zero because calibration
         //! never completes.
         double avgTGCWeight;
         //! Instantaneous uncorrected weights.
         double weights[WPAD_MAX_PRESSURE_SENSORS];
         //! Time-smoothed uncorrected weights, very slow to stabilize.
         double avgWeights[WPAD_MAX_PRESSURE_SENSORS];
         //! Error generated from reading weights.
         WBCError error;
         //! Status of calibration: negative is error, otherwise is [0, 3], but KPAD never
         //! reaches level 3.
         int32_t calibration;
      } balance;
   };

   //! Structure to use when MotionPlus is enabled.
   struct
   {
      //! Angular acceleration.
      KPADVec3D acc;
      //! Computed angles integrated from acceleration.
      KPADVec3D angles;
      //! Computed directions.
      KPADBase3D dir;
   } mplus;

   WUT_PADDING_BYTES(4);
};
WUT_CHECK_OFFSET(KPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(KPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x08, release);
WUT_CHECK_OFFSET(KPADStatus, 0x0C, acc);
WUT_CHECK_OFFSET(KPADStatus, 0x18, accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x1C, accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x20, pos);
WUT_CHECK_OFFSET(KPADStatus, 0x28, posDiff);
WUT_CHECK_OFFSET(KPADStatus, 0x30, posDiffMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x34, angle);
WUT_CHECK_OFFSET(KPADStatus, 0x3C, angleDiff);
WUT_CHECK_OFFSET(KPADStatus, 0x44, angleDiffMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x48, dist);
WUT_CHECK_OFFSET(KPADStatus, 0x4C, distDiff);
WUT_CHECK_OFFSET(KPADStatus, 0x50, distDiffMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x54, down);
WUT_CHECK_OFFSET(KPADStatus, 0x5C, extensionType);
WUT_CHECK_OFFSET(KPADStatus, 0x5D, error);
WUT_CHECK_OFFSET(KPADStatus, 0x5E, posValid);
WUT_CHECK_OFFSET(KPADStatus, 0x5F, format);
// Nunchuk fields.
WUT_CHECK_OFFSET(KPADStatus, 0x60, nunchuk.stick);
WUT_CHECK_OFFSET(KPADStatus, 0x68, nunchuk.acc);
WUT_CHECK_OFFSET(KPADStatus, 0x74, nunchuk.accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x78, nunchuk.accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, nunchuk.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x80, nunchuk.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x84, nunchuk.release);
// Classic fields.
WUT_CHECK_OFFSET(KPADStatus, 0x60, classic.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, classic.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, classic.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, classic.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, classic.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, classic.leftTrigger);
WUT_CHECK_OFFSET(KPADStatus, 0x80, classic.rightTrigger);
// Pro fields.
WUT_CHECK_OFFSET(KPADStatus, 0x60, pro.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, pro.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, pro.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, pro.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, pro.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, pro.charging);
WUT_CHECK_OFFSET(KPADStatus, 0x80, pro.wired);
// Balance Board fields.
WUT_CHECK_OFFSET(KPADStatus, 0x60, balance.avgTGCWeight);
WUT_CHECK_OFFSET(KPADStatus, 0x68, balance.weights);
WUT_CHECK_OFFSET(KPADStatus, 0x88, balance.avgWeights);
WUT_CHECK_OFFSET(KPADStatus, 0xA8, balance.error);
WUT_CHECK_OFFSET(KPADStatus, 0xAC, balance.calibration);
// MotionPlus fields.
WUT_CHECK_OFFSET(KPADStatus, 0xB0, mplus.acc);
WUT_CHECK_OFFSET(KPADStatus, 0xBC, mplus.angles);
WUT_CHECK_OFFSET(KPADStatus, 0xC8, mplus.dir);
WUT_CHECK_SIZE(KPADStatus, 0xF0);

/**
 * Storage type for the internal KPAD ring buffer.
 *
 * \sa
 * - `KPADInitEx()`
 * - `KPADGetUnifiedWpadStatus()`
 */
struct KPADUnifiedWpadStatus
{
   union
   {
      WPADStatus core;
      WPADStatusNunchuk nunchuk;
      WPADStatusClassic classic;
      WPADStatusPro pro;
      WPADStatusBalanceBoard balance;
      WPADStatusTrain train;
   };
   //! One of `WPADDataFormat`.
   uint8_t format;
   WUT_PADDING_BYTES(3);
};
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, core);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, nunchuk);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, classic);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, pro);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, balance);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x00, train);
WUT_CHECK_OFFSET(KPADUnifiedWpadStatus, 0x40, format);
WUT_CHECK_SIZE(KPADUnifiedWpadStatus, 0x44);

typedef WPADConnectCallback KPADConnectCallback;
typedef WPADSamplingCallback KPADSamplingCallback;

/**
 * Callback for receiving notifications about IR state changes.
 *
 * \sa
 * - `KPADDisableDPD()`
 * - `KPADEnableDPD()`
 * - `KPADSetControlDpdCallback()`
 */
typedef void (*KPADControlDpdCallback)(KPADChan chan, KPADControlDpdStatus status);

//! Callback used for `KPADSetControlMplsCallback()`.
typedef void (*KPADControlMplsCallback)(KPADChan chan, KPADControlMplsStatus status);

/**
 * Initializes the KPAD library for use.
 *
 * \note This calls `KPADInitEx(NULL, 0)`.
 *
 * \sa
 * - `KPADInitEx()`
 */
void
KPADInit(void);

/**
 * Initializes the KPAD library with extra buffers.
 *
 * \param buffer Additional buffer to store data.
 * \param count How many entries exist in the buffer. Should be multiple of the maximum
 *              number of controllers.
 *
 * \sa
 * - `KPADInit()`
 * - `KPADSetMaxControllers()`
 */
void
KPADInitEx(KPADUnifiedWpadStatus *buffer,
           uint32_t count);

/**
 * Cleans up and frees the KPAD library.
 */
void
KPADShutdown(void);

/**
 * Read data from the desired controller.
 *
 * \note
 * When the button processing mode is `KPAD_BUTTON_PROC_MODE_LOOSE` (the default) all
 * samples have the same button data, corresponding to the most recent button
 * state. Button activity between `KPADRead()` calls are discarded.
 *
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill with samples, from newest to oldest.
 *
 * \param count
 * The maximum number of data samples to read.
 *
 * \return
 * The number of data samples read.
 *
 * \sa
 * - `KPADGetButtonProcMode()`
 * - `KPADReadEx()`
 * - `KPADSetButtonProcMode()`
 */
uint32_t
KPADRead(KPADChan chan,
         KPADStatus *data,
         uint32_t count);

/**
 * Read data from the desired controller, and retrieve error status.
 *
 * \note
 * When the button processing mode is `KPAD_BUTTON_PROC_MODE_LOOSE` (the default) all
 * samples have the same button data, corresponding to the most recent button
 * state. Button activity between `KPADReadEx()` calls are discarded.
 *
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill with samples, from newest to oldest.
 *
 * \param count
 * The maximum number of data samples to read.
 *
 * \param error
 * A pointer to store an error code.
 *
 * \return
 * The number of data samples read.
 *
 * \sa
 * - `KPADGetButtonProcMode()`
 * - `KPADRead()`
 * - `KPADSetButtonProcMode()`
 */
uint32_t
KPADReadEx(KPADChan chan,
           KPADStatus *data,
           uint32_t count,
           KPADError *error);

/**
 * Read a number of entries from the internal buffer.
 *
 * \param chan The target wiimote.
 * \param buffer The destination buffer.
 * \param count The number of entries that will be copied.
 *
 * \sa
 * - `KPADRead()`
 * - `KPADUnifiedWpadStatus`
 */
void
KPADGetUnifiedWpadStatus(KPADChan chan,
                         KPADUnifiedWpadStatus *buffer,
                         uint32_t count);

/**
 * Sets the maximum amount of controllers which can be connected to the system.
 *
 * \param maxControllers
 * The maximum amount of controllers. Must be `4` or `7`.
 *
 * \return
 * `0` on success.
 *
 * \sa
 * - `KPADGetGameMaxControllers()`
 * - `KPADGetMaxControllers()`
 */
int32_t
KPADSetMaxControllers(uint32_t maxControllers);

/**
 * Gets the maximum amount of controllers which can be connected to the system.
 *
 * \return
 * The maximum amount of controllers.
 *
 * \sa
 * - `KPADGetGameMaxControllers()`
 * - `KPADSetMaxControllers()`
 */
uint32_t
KPADGetMaxControllers(void);

/**
 * Gets the maximum amount of controllers which can be connected, as reported by IOS-PAD.
 *
 * \return
 * The maximum amount of controllers.
 *
 * \sa
 * - `KPADGetMaxControllers()`
 * - `KPADSetMaxControllers()`
 */
uint32_t
KPADGetGameMaxControllers(void);

/**
 * Sets a callback for when a controller connection status changes.
 *
 * \note Do not call `WPADSetConnectCallback()` if you call this.
 *
 * \param chan
 * The channel of the controller to set a callback for.
 *
 * \param callback
 * Pointer to a callback function.
 *
 * \return
 * The previous connect callback.
 */
KPADConnectCallback
KPADSetConnectCallback(KPADChan chan,
                       KPADConnectCallback callback);

/**
 * Sets a sampling callback.
 *
 * \note Same usage as `WPADSetSamplingCallback()`, except compatible with other KPAD
 *       functions.
 *
 * \param chan The target wiimote.
 *
 * \param callback The callback that will be called whenever the wiimote communicates, or
 *                 `NULL`.
 *
 * \return The old callback.
 */
KPADSamplingCallback
KPADSetSamplingCallback(KPADChan chan,
                        KPADSamplingCallback callback);

/**
 * Returns the amount of extra memory needed for MotionPlus handling.
 *
 * \return How many bytes need to be allocated and set with `KPADSetMplsWorkarea()`.
 *
 * \sa
 * - `KPADSetMplsWorkarea()`
 */
uint32_t
KPADGetMplsWorkSize(void);

/**
 * Sets the extra memory needed to process MotionPlus data.
 *
 * Without this work area, the `mplus` field in `KPADStatus` will be filled with zeros.
 *
 * \param buf A memory buffer with size obtained from `KPADGetMplsWorkSize()`.
 *
 * \sa
 * - `KPADGetMplsWorkSize()`
 */
void
KPADSetMplsWorkarea(void *buf);

/**
 * Sets a callback for when the MotionPlus extension is configured.
 *
 * \param chan Controller channel to set the callback for.
 * \param callback Pointer to callback function that will be invoked.
 *
 * \sa
 * - `KPADEnableMpls()`
 * - `KPADDisableMpls()`
 */
void
KPADSetControlMplsCallback(KPADChan chan,
                           KPADControlMplsCallback callback);

/**
 * Sets MotionPlus for the controller in specified mode
 *
 * \param mode
 * The MotionPlus mode which should be used, the mode may be ignored and a different mode used,
 * usually because the required extension is not connected. Make sure to check result with
 * \link KPADGetMplsStatus \endlink
 *
 * \sa
 * - `KPADDisableMpls()`
 * - `KPADGetMplsStatus()`
 * - `KPADSetConnectCallback()`
 * - `KPADSetControlMplsCallback()`
 */
void
KPADEnableMpls(KPADChan channel,
               KPADMplsMode mode);

/**
 * Disables MotionPlus for the controller
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableMpls()`
 */
void
KPADDisableMpls(KPADChan chan);

/**
 * Gets MotionPlus mode
 *
 * \param chan The target wiimote.
 *
 * \return One of the `WPAD_MPLS_MODE_*` values.
 *
 * \sa
 * - `WPADiGetMplsStatus()`
 */
KPADMplsMode
KPADGetMplsStatus(KPADChan chan);

/**
 * Resets some controller state, like rumble motor, button state, etc.
 *
 * \note Some of the reset happens on the next `KPADRead()`.
 */
void
KPADReset(void);

/**
 * Resets the MotionPlus state.
 *
 * \note If MotionPlus is enabled, this is called by `KPADReset()`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADReset()`
 */
void
KPADResetMpls(KPADChan chan);

/**
 * Enable IR pointing
 */
void
KPADEnableDPD(KPADChan chan);

/**
 * Disables IR pointing.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableDPD()`
 */
void
KPADDisableDPD(KPADChan chan);

/**
 * Resets the Balance Board's zero.
 *
 * \note This is called by `KPADResetWbcTgcWeight()`.
 */
void
KPADResetWbcZeroPoint(void);

/**
 * Recalculates the Balance Board's TGC coefficients and zero.
 *
 * \note This is called by `KPADInit()/KPADInitEx()`.
 *
 * \sa
 * - `KPADInit()`
 * - `KPADInitEx()`
 */
void
KPADResetWbcTgcWeight(void);

/**
 * Recalibrates horizontal position for wiimote.
 *
 * \param chan The target wiimote.
 *
 * \return The number of IR points detected: if `2`, the calibration was performed, any
 *         other value (including `-1`) indicates an error.
 */
int32_t
KPADCalibrateDPD(KPADChan chan);

/**
 * Disables TV aiming mode.
 *
 * Makes the origin `(0, 0)` the center of the sensor bar.
 *
 * \param chan The wiimote channel
 *
 * \sa
 * - `KPADEnableAimingMode()`
 * - `KPADGetProjectionPos()`
 * - `KPADGetSensorHeight()`
 * - `KPADIsEnableAimingMode()`
 */
void
KPADDisableAimingMode(KPADChan chan);

/**
 * Disables MotionPlus accelerometer correction.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableMplsAccRevise()`
 * - `KPADIsEnableMplsAccRevise()`
 */
void
KPADDisableMplsAccRevise(KPADChan chan);

/**
 * Disables MotionPlus direction correction.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableMplsDirRevise()`
 * - `KPADIsEnableMplsDirRevise()`
 */
void
KPADDisableMplsDirRevise(KPADChan chan);

/**
 * Disables MotionPlus IR pointing correction.
 *
 * This is enabled by default.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableMplsDpdRevise()`
 * - `KPADIsEnableMplsDpdRevise()`
 */
void
KPADDisableMplsDpdRevise(KPADChan chan);

/**
 * Disables the MotionPlus zero play tolerance.
 *
 * This is disabled by default.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADEnableMplsZeroPlay()`
 * - `KPADIsEnableMplsZeroPlay()`
 */
void
KPADDisableMplsZeroPlay(KPADChan chan);

/**
 * Disables cross clamping for sticks.
 *
 * This is disabled by default.
 *
 * \sa
 * - `KPADEnableStickCrossClamp()`
 */
void
KPADDisableStickCrossClamp();

/**
 * Enables TV aiming mode.
 *
 * Makes the origin `(0, 0)` the center of the TV. This is enabled by default.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADDisableAimingMode()`
 * - `KPADGetProjectionPos()`
 * - `KPADGetSensorHeight()`
 * - `KPADIsEnableAimingMode()`
 */
void
KPADEnableAimingMode(KPADChan chan);

/**
 * Enables MotionPlus accelerometer correction.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADDisableMplsAccRevise()`
 * - `KPADIsEnableMplsAccRevise()`
 */
void
KPADEnableMplsAccRevise(KPADChan chan);

/**
 * Enables MotionPlus direction correction.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADDisableMplsDirRevise()`
 * - `KPADIsEnableMplsDirRevise()`
 */
void
KPADEnableMplsDirRevise(KPADChan chan);

/**
 * Enables MotionPlus IR pointing correction.
 *
 * This is enabled by default.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADDisableMplsDpdRevise()`
 * - `KPADIsEnableMplsDpdRevise()`
 */
void
KPADEnableMplsDpdRevise(KPADChan chan);

/**
 * Enables MotionPlus zero play tolerance.
 *
 * This is disabled by default.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADDisableMplsZeroPlay()`
 * - `KPADIsEnableMplsZeroPlay()`
 */
void
KPADEnableMplsZeroPlay(KPADChan chan);

/**
 * Enables cross clamping or sticks.
 *
 * This is disabled by default.
 *
 * \sa
 * - `KPADDisableStickCrossClamp()`
 */
void
KPADEnableStickCrossClamp(void);

/**
 * Gets the accelerometer parameters (tolerance and sensitivity.)
 *
 * \param chan The target wiimote.
 * \param tolerance Pointer to store the tolerance.
 * \param sensitivity Pointer to store the sensitivity.
 *
 * \ sa
 * - `KPADSetAccParam()`
 */
void
KPADGetAccParam(KPADChan chan,
                float *tolerance,
                float *sensitivity);

/**
 * Gets the accelrometer play mode.
 *
 * \param chan The target wiimote.
 *
 * \return The accelerometer play mode.
 *
 * \sa
 * - `KPADSetAccPlayMode()`
 */
KPADPlayMode
KPADGetAccPlayMode(KPADChan chan);

/**
 * Gets the button processing mode.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADRead()`
 * - `KPADReadEx()`
 * - `KPADSetButtonProcMode()`
 */
KPADButtonProcMode
KPADGetButtonProcMode(KPADChan chan);

/**
 * Gets the cross stick emulation parameters for the left stick.
 *
 * \param chan The target wiimote.
 * \param rotation Pointer to store the rotation.
 * \param dirAngle Pointer to store direction angle.
 * \param neutral Pointer to store the neutral radius.
 *
 * \sa
 * - `KPADGetCrossStickEmulationParamsR()`
 * - `KPADSetCrossStickEmulationParamsL()`
 * - `KPADSetCrossStickEmulationParamsR()`
 */
void
KPADGetCrossStickEmulationParamsL(KPADChan chan,
                                  float *rotation,
                                  float *dirAngle,
                                  float *neutral);

/**
 * Gets the cross stick emulation parameters for the right stick.
 *
 * \param chan The target wiimote.
 * \param rotation Pointer to store the rotation.
 * \param dirAngle Pointer to store the direction angle.
 * \param neutral Pointer to store the neutral radius.
 *
 * \sa
 * - `KPADGetCrossStickEmulationParamsL()`
 * - `KPADSetCrossStickEmulationParamsL()`
 * - `KPADSetCrossStickEmulationParamsR()`
 */
void
KPADGetCrossStickEmulationParamsR(KPADChan chan,
                                  float *rotation,
                                  float *dirAngle,
                                  float *neutral);

/**
 * Gets the IR pointer's distance parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance Pointer to store the tolerance.
 * \param sensitivity Pointer to store the sensitivity.
 *
 * \sa
 * - `KPADSetDistParam()`
 */
void
KPADGetDistParam(KPADChan chan,
                 float *tolerance,
                 float *sensitivity);

/**
 * Gets the IR pointer's distance play mode.
 *
 * \param chan The target wiimote.
 *
 * \return The mode used by the distance tracking.
 *
 * \sa
 * - `KPADSetDistPlayMode()`
 */
KPADPlayMode
KPADGetDistPlayMode(KPADChan chan);

/**
 * Gets the current IR detection mode.
 *
 * \return The current mode.
 *
 * \sa
 * - `KPADSetDpdDetection()`
 */
uint8_t
KPADGetDpdDetection(void);

/**
 * Gets the IR pointer's horizon parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance Pointer to store the tolerance.
 * \param sensitivity Pointer to store the sensitivity.
 *
 * \sa
 * - `KPADSetHoriParam()`
 */
void
KPADGetHoriParam(KPADChan chan,
                 float *tolerance,
                 float *sensitivity);

/**
 * Gets the IR pointer's horizon play mode.
 *
 * \param chan The target wiimote.
 *
 * \return The mode used by the horizon tracking.
 *
 * \sa
 * - `KPADSetHoriPlayMode()`
 */
KPADPlayMode
KPADGetHoriPlayMode(KPADChan chan);

/**
 * Gets the MotionPlus acceleration correction parameters.
 *
 * \param chan The target wiimote.
 * \param weight Pointer to store the weight.
 * \param range Pointer to store the range.
 *
 * \sa
 * - `KPADInitMplsAccReviseParam()`
 * - `KPADSetMplsAccReviseParam()`
 */
void
KPADGetMplsAccReviseParam(KPADChan chan,
                          float *weight,
                          float *range);

/**
 * Gets the MotionPlus direction correction weight parameter.
 *
 * \param chan The target wiimote.
 * \param weight Pointer to store the weight.
 *
 * \sa
 * - `KPADInitMplsDirReviseParam()`
 * - `KPADSetMplsDirReviseParam()`
 */
void
KPADGetMplsDirReviseParam(KPADChan chan,
                          float *weight);

/**
 * Gets the MotionPlus IR pointer correction weight parameter.
 *
 * \param chan The target wiimote.
 * \param weight Pointer to store the weight.
 */
void
KPADGetMplsDpdReviseParam(KPADChan chan,
                          float *weight);

/**
 * Gets the MotionPlus zero drift mode.
 *
 * \param chan The target wiimote.
 * \param mode Pointer to store the zero drift mode.
 *
 * \sa
 * - `KPADSetMplsZeroDriftMode()`
 * - `KPADInitMplsZeroDriftMode()`
 */
void
KPADGetMplsZeroDriftMode(KPADChan chan,
                         KPADMplsZeroDriftMode *mode);

/**
 * Gets the MotionPlus zero play tolerance parameter.
 *
 * \param chan The target wiimote.
 * \param tolerance Pointer to store the tolerance.
 *
 * \sa
 * - `KPADSetMplsZeroPlayParam()`
 * - `KPADInitMplsZeroPlayParam()`
 */
void
KPADGetMplsZeroPlayParam(KPADChan chan,
                         float *tolerance);

/**
 * Gets the IR pointer's position parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance Pointer to store the tolerance.
 * \param sensitivity Pointer to store the sensitivity.
 *
 * \sa
 * - `KPADSetPosParam()`
 */
void
KPADGetPosParam(KPADChan chan,
                float *tolerance,
                float *sensitivity);

/**
 * Gets the IR pointer's position play mode.
 *
 * \param chan The target wiimote.
 *
 * \return The position play mode.
 *
 * \sa
 * - `KPADSetPosPlayMode()`
 */
KPADPlayMode
KPADGetPosPlayMode(KPADChan chan);

/**
 * Transforms a normalized point to pixel coordinates.
 *
 * \param dst Pointer to store the calculated position.
 * \param src Pointer to the normalized (between -1 and 1) source point.
 * \param screen Pointer to a rectangle representing the screen boundary.
 * \param pixelRatio Correction factor for pixel ratio (1.0f for square pixels).
 *
 * \sa
 * - `KPADDisableAimingMode()`
 * - `KPADEnableAimingMode()`
 * - `KPADGetSensorHeight()`
 * - `KPADGetSensorHeight()`
 */
void
KPADGetProjectionPos(KPADVec2D *dst,
                     const KPADVec2D *src,
                     const KPADRect *screen,
                     float pixelRatio);

/**
 * Gets the pitch angle offset for the Nunchuk's orientation.
 *
 * The angle is taken counter-clockwise around the X axis, in degrees.
 *
 * \return The offset pitch angle offset applied to the Nunchuk, in degrees.
 *
 * \sa
 * - `KPADReviseAcc()`
 * - `KPADSetReviseMode()`
 */
float
KPADGetReviseAngle(void);

/**
 * Gets the sensor bar height.
 *
 * \param chan The target wiimote.
 *
 * \result The sensor bar height.
 *
 * \sa
 * - `KPADDisableAimingMode()`
 * - `KPADEnableAimingMode()`
 * - `KPADGetProjectionPos()`
 * - `KPADSetSensorHeight()`
 */
float
KPADGetSensorHeight(KPADChan chan);

/**
 * Initializes the MotionPlus acceleration correction parameters.
 *
 * The parameters are initialized:
 * - `weight = 0.03f`
 * - `range = 0.4f`
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADGetMplsAccReviseParam()`
 * - `KPADSetMplsAccReviseParam()`
 */
void
KPADInitMplsAccReviseParam(KPADChan chan);

/**
 * Initializes the MotionPlus orientation correction weight parameter.
 *
 * The weight is initialized to `0.5f`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADGetMplsDirReviseParam()`
 * - `KPADSetMplsDirReviseParam()`
 */
void
KPADInitMplsDirReviseParam(KPADChan chan);

/**
 * Initializes the MotionPlus IR pointer correction weight parameter.
 *
 * The weight is initialized to `0.05f`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADGetMplsDpdReviseParam()`
 * - `KPADSetMplsDpdReviseParam()`
 */
void
KPADInitMplsDpdReviseParam(KPADChan chan);

/**
 * Initializes the MotionPlus zero drift mode.
 *
 * The mode is initialized to `KPAD_MPLS_ZERO_DRIFT_MODE_STANDARD`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADGetMplsZeroDriftMode()`
 * - `KPADSetMplsZeroDriftMode()`
 */
void
KPADInitMplsZeroDriftMode(KPADChan chan);

/**
 * Initializes the MotionPlus zero play tolerance.
 *
 * The tolerance is initialized to `0.005f`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADGetMplsZeroPlayParam()`
 * - `KPADSetMplsZeroPlayParam()`
 */
void
KPADInitMplsZeroPlayParam(KPADChan chan);

/**
 * Returns the state of aiming mode.
 *
 * \param chan The target wiimote.
 *
 * \return `TRUE` if aiming mode is enabled, `FALSE` otherwise.
 *
 * \sa
 * - `KPADDisableAimingMode()`
 * - `KPADEnableAimingMode()`
 */
BOOL
KPADIsEnableAimingMode(KPADChan chan);

/**
 * Returns the state of MotionPlus acceleration correction parameter.
 *
 * \param chan The target wiimote.
 *
 * \return `-1` if the correction is disabled, or the correction parameter when enabled.
 *
 * \sa
 * - `KPADDisableMplsAccRevise()`
 * - `KPADEnableMplsAccRevise()`
 */
float
KPADIsEnableMplsAccRevise(KPADChan chan);

/**
 * Returns the state of the MotionPlus direction correction parameter.
 *
 * \param chan The target wiimote.
 *
 * \return `-1` if the correction is disabled, or the correction parameter when enabled.
 *
 * \sa
 * - `KPADDisableMplsDirRevise()`
 * - `KPADEnableMplsDirRevise()`
 */
float
KPADIsEnableMplsDirRevise(KPADChan chan);

/**
 * Returns the state of the MotionPlus IR pointer correction parameter.
 *
 * \param chan The target wiimote.
 *
 * \return `-1` if the correction is disabled, or the correction parameter when enabled.
 *
 * \sa
 * - `KPADDisableMplsDpdRevise()`
 * - `KPADEnableMplsDpdRevise()`
 */
float
KPADIsEnableMplsDpdRevise(KPADChan chan);

/**
 * Returns the state of the MotionPlus zero drift correction.
 *
 * \param chan The target wiimote.
 *
 * \return `-1` if the correction is disabled, or the current correction value.
 */
float
KPADIsEnableMplsZeroDrift(KPADChan chan);

/**
 * Returns the state of the MotionPlus zero play correction.
 *
 * \param chan The target wiimote.
 *
 * \return `-1` if the correction is disabled, or the current correction value.
 *
 * \sa
 * - `KPADDisableMplsZeroPlay()`
 * - `KPADEnableMplsZeroPlay()`
 */
float
KPADIsEnableMplsZeroPlay(KPADChan chan);

/**
 * Transforms the argument by the Nunchuk's pitch correction angle.
 *
 * \param vec The 3D vector to be transformed by the correction angle, around the X axis.
 *
 * \return The angle that was used to rotate the argument, degrees.
 *
 * \sa
 * - `KPADGetReviseAngle()`
 * - `KPADSetReviseMode()`
 */
float
KPADReviseAcc(KPADVec3D *vec);

/**
 * Sets the accelerometer tolerance and sensitivity parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance The play tolerance, `>= 0`. Default value is `0`.
 * \param sensitivity The sensitivity, in `[0, 1]`. Default value is `1`.
 *
 * \sa
 * - `KPADGetAccParam()`
 */
void
KPADSetAccParam(KPADChan chan,
                float tolerance,
                float sensitivity);

/**
 * Sets the accelerometer play mode.
 *
 * \param chan The target wiimote.
 * \param mode The desired mode. `KPAD_PLAY_MODE_LOOSE` is the default.
 *
 * \sa
 * - `KPADGetAccPlayMode()`
 */
void
KPADSetAccPlayMode(KPADChan chan,
                   KPADPlayMode mode);

/**
 * Sets the button repeat parameters.
 *
 * This sets the `KPAD_BUTTON_REPEAT` bit in the `hold` field every `pulse` seconds, after
 * a button is held down for `delay` seconds.
 *
 * \note Wii U Menu uses `delay = 0.5f`, `pulse = 0.1f`.
 *
 * \param chan The target wiimote.
 * \param delay How long a button needs to be held down (in seconds) before the repeat action
 *              starts.
 * \param pulse Interval (in seconds) between repeat pulses.
 */
void
KPADSetBtnRepeat(KPADChan chan,
                 float delay,
                 float pulse);

/**
 * Sets the button processing mode.
 *
 * Use `KPAD_BUTTON_PROC_MODE_TIGHT` to track button presses in-between samples, with
 * `KPADRead()`/`KPADReadEx()`
 *
 * \param chan The target wiimote.
 * \param mode The desired processing mode. The default is `KPAD_BUTTON_PROC_MODE_LOOSE`.
 *
 * \sa
 * - `KPADGetButtonProcMode()`
 * - `KPADRead()`
 * - `KPADReadEx()`
 */
void
KPADSetButtonProcMode(KPADChan chan,
                      KPADButtonProcMode mode);

/**
 * Sets the notification callback for IR status changes.
 *
 * \param chan The target wiimote.
 * \param callback The callback that will be called when IR status changes, or `NULL`.
 *
 * \sa
 * - `KPADDisableDPD()`
 * - `KPADEnableDPD()`
 */
void
KPADSetControlDpdCallback(KPADChan chan,
                          KPADControlDpdCallback callback);

/**
 * Sets the cross stick emulation parameters for the left stick.
 *
 * \param chan The target wiimote.
 * \param rotation The rotation parameter, in degrees.
 * \param dirAngle The direction angle parameter, as degrees, in `[0, 90]`.
 * \param neutral The neutral radius parameter, in `[0, 1]`.
 *
 * \sa
 * - `KPADGetCrossStickEmulationParamsL()`
 * - `KPADGetCrossStickEmulationParamsR()`
 * - `KPADSetCrossStickEmulationParamsR()`
 */
void
KPADSetCrossStickEmulationParamsL(KPADChan chan,
                                  float rotation,
                                  float dirAngle,
                                  float neutral);

/**
 * Sets the cross stick emulation parameters for the right stick.
 *
 * \param chan The target wiimote.
 * \param rotation The rotation parameter, in degrees.
 * \param dirAngle The direction angle parameter, as degrees, in `[0, 90]`.
 * \param neutral The neutral radius parameter, in `[0, 1]`.
 *
 * \sa
 * - `KPADGetCrossStickEmulationParamsL()`
 * - `KPADGetCrossStickEmulationParamsR()`
 * - `KPADSetCrossStickEmulationParamsL()`
 */
void
KPADSetCrossStickEmulationParamsR(KPADChan chan,
                                  float rotation,
                                  float dirAngle,
                                  float neutral);

/**
 * Sets the IR distance parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance The amount of movement that is interpreted as stationary, default is `0`.
 * \param sensitivity The scale used for movement, default is `1`.
 *
 * \sa
 * - `KPADGetDistParam()`
 */
void
KPADSetDistParam(KPADChan chan,
                 float tolerance,
                 float sensitivity);

/**
 * Sets the IR distance play mode.
 *
 * \param chan The target wiimote.
 * \param mode The play mode used for the distance calculation. The default is
 *             `KPAD_PLAY_MODE_LOOSE`.
 *
 * \sa
 * - `KPADGetDistPlayMode()`
 */
void
KPADSetDistPlayMode(KPADChan chan,
                    KPADPlayMode mode);

/**
 * Sets IR point detection algorithm.
 *
 * \todo Find out exactly what changes; it is accessed during KPADRead() while processing angles.
 *
 * \sa
 * - `KPADGetDpdDetection()`
 */
void
KPADSetDpdDetection(uint8_t state);

/**
 * Sets the Nunchuk's stick clamp values.
 *
 * These values are used by KPAD to convert the `WPADStatusNunchuk` stick values to the
 * normalized `KPADStatus` values. Values smaller than `min` are mapped to `0`, and larger
 * than `max` to `1`.
 *
 * \param min Minimum absolute stick value.
 * \param max Maximum absolute stick value.
 */
void
KPADSetFSStickClamp(int8_t min,
                    int8_t max);

/**
 * Sets the IR pointer's horizon parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance The tolerance parameter. Default is `0`.
 * \param sensitivity The sensitivity parameter. Default is `1`.
 *
 * \sa
 * - `KPADGetHoriParam()`
 */
void
KPADSetHoriParam(KPADChan chan,
                 float tolerance,
                 float sensitivity);

/**
 * Sets the IR pointer's horizon play mode.
 *
 * \param chan The target wiimote.
 * \param mode The mode used by the horizon tracking.
 *
 * \sa
 * - `KPADGetHoriPlayMode()`
 */
void
KPADSetHoriPlayMode(KPADChan chan,
                    KPADPlayMode mode);

/**
 * Sets the MotionPlus acceleration correction parameters.
 *
 * \param chan The target wiimote.
 * \param weight The weight parameter, in `[0, 1]`.
 * \param range The range parameter, measured in g (Earth's gravity).
 *
 * \sa
 * - `KPADGetMplsAccReviseParam()`
 * - `KPADInitMplsAccReviseParam()`
 */
void
KPADSetMplsAccReviseParam(KPADChan chan,
                          float weight,
                          float range);

/**
 * Sets the MotionPlus angles to arbitrary values.
 *
 * \note Angles are in normalized units: `1.0f` = 360°.
 *
 * \param chan The target wiimote.
 * \param rx The pitch angle around the X axis.
 * \param ry The yaw angle around the Y axis.
 * \param rz The roll angle around the Z axis.
 */
void
KPADSetMplsAngle(KPADChan chan,
                 float rx,
                 float ry,
                 float rz);

/**
 * Sets the MotionPlus current computed directions.
 *
 * \param chan The target wiimote.
 * \param dir The reference frame to copy to `KPADStatus::mplus::dir`.
 */
void
KPADSetMplsDirection(KPADChan chan,
                     const KPADBase3D *dir);

/**
 * Sets the MotionPlus velocity scale for computing directions.
 *
 * \param chan The target wiimote.
 * \param scale The velocity scale used to integrate the directions. Default is `1`.
 */
void
KPADSetMplsDirectionMag(KPADChan chan,
                        float scale);

/**
 * Sets the MotionPlus reference frame that points at the TV.
 *
 * \param chan The target wiimote.
 * \param base The base of the coordinate system that corresponds to pointing at the TV.
 */
void
KPADSetMplsDirReviseBase(KPADChan chan,
                         const KPADBase3D *base);

/**
 * Sets the MotionPlus direction correction weight parameter.
 *
 * \param chan The target wiimote.
 * \param weight The weight parameter, in `[0, 1]`.
 *
 * - `KPADGetMplsDirReviseParam()`
 * - `KPADInitMplsDirReviseParam()`
 */
void
KPADSetMplsDirReviseParam(KPADChan chan,
                          float weight);

/**
 * Sets the MotionPlus IR pointer correction weight parameter.
 *
 * \param chan The target wiimote.
 * \param weight The weight parameter, in `[0, 1]`.
 *
 * \sa
 * - `KPADGetMplsDpdReviseParam()`
 * - `KPADInitMplsDpdReviseParam()`
 */
void
KPADSetMplsDpdReviseParam(KPADChan chan,
                          float weight);

/**
 * Sets the MotionPlus angular speed scales.
 *
 * \param chan The target wiimote.
 * \param scalePitch Scale applied to the pitch speed.
 * \param scaleYaw Scale applied to the yaw speed.
 * \param scaleRoll Scale applied to the roll speed.
 */
void
KPADSetMplsMagnification(KPADChan chan,
                         float scalePitch,
                         float scaleYaw,
                         float scaleRoll);

/**
 * Sets the MotionPlus zero drift mode.
 *
 * \param chan The target wiimote.
 * \param mode The zero drift mode.
 *
 * \sa
 * - `KPADGetMplsZeroDriftMode()`
 * - `KPADInitMplsZeroDriftMode()`
 */
void
KPADSetMplsZeroDriftMode(KPADChan chan,
                         KPADMplsZeroDriftMode mode);

/**
 * Sets the MotionPlus zero play tolerance.
 *
 * \param chan The target wiimote.
 * \param tolerance The tolerance.
 *
 * \sa
 * - `KPADGetMplsZeroPlayParam()`
 * - `KPADInitMplsZeroPlayParam()`
 */
void
KPADSetMplsZeroPlayParam(KPADChan chan,
                         float tolerance);

/**
 * This function is stubbed, it does nothing.
 */
void
KPADSetObjInterval(void);

/**
 * Sets the IR pointer's position parameters.
 *
 * \param chan The target wiimote.
 * \param tolerance The tolerance, `>= 0`.
 * \param sensitivity The sensitivity, in `[0, 1]`.
 *
 * \sa
 * - `KPADGetPosParam()`
 */
void
KPADSetPosParam(KPADChan chan,
                float tolerance,
                float sensitivity);

/**
 * Sets the IR pointer's position play mode.
 *
 * \note The default is `KPAD_PLAY_MODE_LOOSE`.
 *
 * \param chan The target wiimote.
 * \param mode The position play mode.
 *
 * \sa
 * - `KPADGetPosPlayMode()`
 */
void
KPADSetPosPlayMode(KPADChan chan,
                   KPADPlayMode mode);

/**
 * Sets the Nunchuk's pitch angle correction mode.
 *
 * \note
 * This changes what it means for the Nunchuk to be upright:
 * - Without correction, the neutral Nunchuk stick orientation is up.
 * - With correction, laying the bottom flat on a surface is considered up.
 *
 * \param chan The target wiimote.
 * \param correct Set to `TRUE` to apply angle correction.
 *
 * \sa
 * - `KPADGetReviseAngle()`
 * - `KPADReviseAcc()`
 */
void
KPADSetReviseMode(KPADChan chan,
                  BOOL correct);

/**
 * Sets the IR sensor bar's height.
 *
 * \param chan The target wiimote.
 * \param height The set height.
 *
 * \sa
 * - `KPADDisableAimingMode()`
 * - `KPADEnableAimingMode()`
 * - `KPADGetProjectionPos()`
 * - `KPADGetSensorHeight()`
 */
void
KPADSetSensorHeight(KPADChan chan,
                    float height);

/**
 * Queues MotionPlus zero calibration.
 *
 * \note Calibration is performed inside `KPADRead()`.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADRead()`
 * - `KPADStopMplsCalibration()`
 * - `KPADWorkMplsCalibration()`
 */
void
KPADStartMplsCalibration(KPADChan chan);

/**
 * Stops the MotionPlus calibration.
 *
 * \param chan The target wiimote.
 *
 * \sa
 * - `KPADStartMplsCalibration()`
 * - `KPADWorkMplsCalibration()`
 */
void
KPADStopMplsCalibration(KPADChan chan);

/**
 * Returns progress of MotionPlus calibration.
 *
 * \param chan The target wiimote.
 *
 * \return
 * Progress of calibration, that decreases from `1.0` to `0.0`, or `< 0` when calibration
 * is not active.
 *
 * \sa
 * - `KPADStartMplsCalibration()`
 * - `KPADStopMplsCalibration()`
 */
float
KPADWorkMplsCalibration(KPADChan chan);

#ifdef __cplusplus
}
#endif

/** @} */
