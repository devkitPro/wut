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

typedef struct KPADStatus KPADStatus;
typedef struct KPADVec2D KPADVec2D;
typedef struct KPADVec3D KPADVec3D;

//! Error.
typedef enum KPADError
{
   //! No errors.
   KPAD_ERROR_OK              = 0,
} KPADError;

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

//! A structure conataining the Wii Remote data.
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

   //! Indicates the position where the Wii Remote is pointing.
   KPADVec2D pos;

   WUT_UNKNOWN_BYTES(3 * 4);

   //! Angle.
   KPADVec2D angle;

   WUT_UNKNOWN_BYTES(8 * 4);

   //! Value from KPADExtensionType.
   uint8_t extensionType;

   //! Value from KPADError.
   int8_t error;

   //! Validity of the result.
   int8_t posValid;

   //! Value from KPADDataFormat.
   uint8_t format;

   //! Extension data, check with extensionType to see what is valid to read.
   union
   {
      //! Structure to use when extension type is set to \link WPAD_EXT_NUNCHUK \endlink.
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
      } nunchuck;

      //! Structure to use when extension type is set to \link WPAD_EXT_CLASSIC \endlink.
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

      //! Structure to use when extension type is set to \link WPAD_EXT_PRO_CONTROLLER \endlink.
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

      WUT_UNKNOWN_BYTES(20 * 4);
   };

   WUT_UNKNOWN_BYTES(16 * 4);
};
WUT_CHECK_OFFSET(KPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(KPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x08, release);
WUT_CHECK_OFFSET(KPADStatus, 0x0C, acc);
WUT_CHECK_OFFSET(KPADStatus, 0x18, accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x1C, accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x20, pos);
WUT_CHECK_OFFSET(KPADStatus, 0x34, angle);
WUT_CHECK_OFFSET(KPADStatus, 0x5C, extensionType);
WUT_CHECK_OFFSET(KPADStatus, 0x5D, error);
WUT_CHECK_OFFSET(KPADStatus, 0x5E, posValid);
WUT_CHECK_OFFSET(KPADStatus, 0x5F, format);
// For WPAD_EXT_NUNCHUK
WUT_CHECK_OFFSET(KPADStatus, 0x60, nunchuck.stick);
WUT_CHECK_OFFSET(KPADStatus, 0x68, nunchuck.acc);
WUT_CHECK_OFFSET(KPADStatus, 0x74, nunchuck.accMagnitude);
WUT_CHECK_OFFSET(KPADStatus, 0x78, nunchuck.accVariation);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, nunchuck.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x80, nunchuck.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x84, nunchuck.release);
// For WPAD_EXT_CLASSIC
WUT_CHECK_OFFSET(KPADStatus, 0x60, classic.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, classic.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, classic.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, classic.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, classic.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, classic.leftTrigger);
WUT_CHECK_OFFSET(KPADStatus, 0x80, classic.rightTrigger);
// For WPAD_EXT_PRO_CONTROLLER
WUT_CHECK_OFFSET(KPADStatus, 0x60, pro.hold);
WUT_CHECK_OFFSET(KPADStatus, 0x64, pro.trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x68, pro.release);
WUT_CHECK_OFFSET(KPADStatus, 0x6C, pro.leftStick);
WUT_CHECK_OFFSET(KPADStatus, 0x74, pro.rightStick);
WUT_CHECK_OFFSET(KPADStatus, 0x7C, pro.charging);
WUT_CHECK_OFFSET(KPADStatus, 0x80, pro.wired);
WUT_CHECK_SIZE(KPADStatus, 0xF0);

/**
 * Initialises the KPAD library for use.
 */
void
KPADInit();

/**
 * Read data from the desired Wii Remote.
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
int32_t
KPADRead(KPADChan chan,
         KPADStatus *data,
         uint32_t size);

/**
 * Read data from the desired Wii Remote.
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
int32_t
KPADReadEx(KPADChan chan,
           KPADStatus *data,
           uint32_t size,
           int32_t *error);

#ifdef __cplusplus
}
#endif

/** @} */
