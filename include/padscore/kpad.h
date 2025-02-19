#pragma once
#include <wut.h>
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

//! Wii Remote channel.
typedef enum WPADChan KPADChan;
//! Data format.
typedef enum WPADDataFormat KPADDataFormat;
//! Extension type.
typedef enum WPADExtensionType KPADExtensionType;
//! MotionPlus Mode.
typedef enum WPADMplsMode KPADMplsMode;

typedef struct KPADStatus KPADStatus;
typedef struct KPADUnifiedWpadStatus KPADUnifiedWpadStatus;
typedef struct KPADVec2D KPADVec2D;
typedef struct KPADVec3D KPADVec3D;

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
   KPAD_CONTROL_MPLS_STATUS_STARTED = 0,
   //! When MotionPlus mode was set correctly, or wiimote disconnected prematurely.
   KPAD_CONTROL_MPLS_STATUS_FINISHED = 1,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_ONLY)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_ONLY = -1,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_NUNCHUK)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_NUNCHUK = -2,
   //! When `KPADEnableMpls(chan, WPAD_MPLS_MODE_MPLS_CLASSIC)` failed.
   KPAD_CONTROL_MPLS_STATUS_FAILED_MPLS_CLASSIC = -3,
} KPADControlMplsStatus;

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

   //! Value from KPADError.
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
         double  avgTGCWeight;
         //! Instantaneous uncorrected weights.
         double  weights[WPAD_MAX_PRESSURE_SENSORS];
         //! Time-smoothed uncorrected weights, very slow to stabilize.
         double  avgWeights[WPAD_MAX_PRESSURE_SENSORS];
         //! Error generated from reading weights.
         int32_t error;
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
      //! Computed X direction vector.
      KPADVec3D dirX;
      //! Computed Y direction vector.
      KPADVec3D dirY;
      //! Computed Z direction vector.
      KPADVec3D dirZ;
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
WUT_CHECK_OFFSET(KPADStatus, 0xC8, mplus.dirX);
WUT_CHECK_OFFSET(KPADStatus, 0xD4, mplus.dirY);
WUT_CHECK_OFFSET(KPADStatus, 0xE0, mplus.dirZ);
WUT_CHECK_SIZE(KPADStatus, 0xF0);

/**
 * Storage type for the internal KPAD ring buffer.
 *
 * \sa
 * - `KPADInitEx()`
 * - `KPADGetUnifiedWpadStatus()`
 */
struct KPADUnifiedWpadStatus {
   union {
      WPADStatus             core;
      WPADStatusNunchuk      nunchuk;
      WPADStatusClassic      classic;
      WPADStatusPro          pro;
      WPADStatusBalanceBoard balance;
      WPADStatusTrain        train;
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

//! Callback used for `KPADSetControlMplsCallback()`.
typedef void (*KPADControlMplsCallback)(KPADChan chan, KPADControlMplsStatus status);

/**
 * Initialises the KPAD library for use.
 *
 * Note: this calls `KPADInitEx(NULL, 0)`.
 */
void
KPADInit(void);

/**
 * Initializes the KPAD library with extra buffers.
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
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill.
 *
 * \param size
 * The maximum number of data to read.
 *
 * \return
 * The number of data read.
 */
uint32_t
KPADRead(KPADChan chan,
         KPADStatus *data,
         uint32_t size);

/**
 * Read data from the desired controller.
 *
 * \param chan
 * The channel of the controller to read from.
 *
 * \param data
 * The KPADStatus to fill.
 *
 * \param size
 * The maximum number of data to read.
 *
 * \param error
 * A pointer to an error code.
 *
 * \return
 * The number of data read.
 */
uint32_t
KPADReadEx(KPADChan chan,
           KPADStatus *data,
           uint32_t size,
           KPADError *error);

/**
 * Read a number of entries from the internal buffer.
 */
void
KPADGetUnifiedWpadStatus(KPADChan chan,
                         KPADUnifiedWpadStatus *buffer,
                         uint32_t count);

/**
 * Set the maximum amount of controllers which can be connected to the system.
 *
 * \param maxControllers
 * The maximum amount of controllers. Must be \c 4 or \c 7.
 *
 * \return
 * 0 on success.
 */
int32_t
KPADSetMaxControllers(uint32_t maxControllers);

/**
 * Get the maximum amount of controllers which can be connected to the system.
 *
 * \return
 * The maximum amount of controllers.
 */
uint32_t
KPADGetMaxControllers(void);

/**
 * Get the maximum amount of controllers which can be connected, as reported by IOS-PAD.
 *
 * \return
 * The maximum amount of controllers.
 */
uint32_t
KPADGetGameMaxControllers(void);

/**
 * Set a callback for when a controller connection status changes.
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
 * Same usage as \link WPADSetSamplingCallback\endlink, except compatible with other KPAD functions
 */
KPADSamplingCallback
KPADSetSamplingCallback(KPADChan channel,
                        KPADSamplingCallback callback);

/**
 * Returns the amount of memory needed for `KPADSetMplsWorkarea()`.
 */
uint32_t
KPADGetMplsWorkSize(void);

/**
 * Sets the extra memory KPAD will use to process MotionPlus data.
 *
 * Without this work area, the `mplus` field in `KPADStatus` will be filled with zeros.
 *
 * \param buf A memory buffer with size obtained from `KPADGetMplsWorkSize()`.
 */
void
KPADSetMplsWorkarea(void *buf);

/**
 * Set a callback for when the MotionPlus extension is configured.
 *
 * \param chan Controller channel to set the callback for.
 * \param callback Pointer to callback functio that will be invoked.
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
 * - `KPADSetControlMplsCallback()`
 */
void
KPADEnableMpls(KPADChan channel,
               KPADMplsMode mode);

/**
 * Disables MotionPlus for the controller
 */
void
KPADDisableMpls(KPADChan channel);

/**
 * Get MotionPlus mode
 *
 * identical to \ref WPADiGetMplsStatus
 */
KPADMplsMode
KPADGetMplsStatus(KPADChan chan);

/**
 * Resets the MotionPlus state.
 */
void
KPADResetMpls(KPADChan chan);

/**
 * Enable IR pointing
 */
void
KPADEnableDPD(KPADChan chan);

/**
 * Disable IR pointing
 */
void
KPADDisableDPD(KPADChan chan);

/**
 * Resets the Balance Board's zero.
 */
void
KPADResetWbcZeroPoint(void);

/**
 * Recalculate the Balance Board's TGC coefficients and zero.
 */
void
KPADResetWbcTgcWeight(void);

#ifdef __cplusplus
}
#endif

/** @} */
