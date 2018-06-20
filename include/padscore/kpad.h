#pragma once
#include <wut.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_kpad KPAD
 * \ingroup padscore
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef enum WPADChan KPADChan;
typedef enum WPADDataFormat KPADDataFormat;
typedef enum WPADExtensionType KPADExtensionType;

typedef struct KPADStatus KPADStatus;
typedef struct KPADVec2D KPADVec2D;

typedef enum KPADError
{
   KPAD_ERROR_OK              = 0,
} KPADError;

struct KPADVec2D
{
    float x;
    float y;
};
WUT_CHECK_OFFSET(KPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(KPADVec2D, 0x04, y);
WUT_CHECK_SIZE(KPADVec2D, 0x08);

struct KPADStatus
{
   //! Indicates what KPADButtons are held down
   uint32_t hold;

   //! Indicates what KPADButtons have been pressed since last sample
   uint32_t trigger;

   //! Indicates what KPADButtons have been released since last sample
   uint32_t release;

   WUT_UNKNOWN_BYTES(5 * 4);

   KPADVec2D pos;

   WUT_UNKNOWN_BYTES(3 * 4);

   KPADVec2D angle;

   WUT_UNKNOWN_BYTES(8 * 4);

   //! Value from KPADExtensionType
   uint8_t extensionType;

   //! Value from KPADError
   int8_t error;

   uint8_t posValid;

   //! Value from KPADDataFormat
   uint8_t format;

   // Extension data, check with extensionType to see what is valid to read
   union
   {
      // For WPAD_EXT_NUNCHUK
      struct
      {
         KPADVec2D stick;
      } nunchuck;

      // For WPAD_EXT_CLASSIC
      struct
      {
         uint32_t hold;
         uint32_t trigger;
         uint32_t release;
         KPADVec2D leftStick;
         KPADVec2D rightStick;
         float leftTrigger;
         float rightTrigger;
      } classic;

      // For WPAD_EXT_PRO_CONTROLLER
      struct
      {
         uint32_t hold;
         uint32_t trigger;
         uint32_t release;
         KPADVec2D leftStick;
         KPADVec2D rightStick;
         int32_t charging;
         int32_t wired;
      } pro;

      WUT_UNKNOWN_BYTES(20 * 4);
   };

   WUT_UNKNOWN_BYTES(16 * 4);
};
WUT_CHECK_OFFSET(KPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(KPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(KPADStatus, 0x08, release);
WUT_CHECK_OFFSET(KPADStatus, 0x20, pos);
WUT_CHECK_OFFSET(KPADStatus, 0x34, angle);
WUT_CHECK_OFFSET(KPADStatus, 0x5C, extensionType);
WUT_CHECK_OFFSET(KPADStatus, 0x5D, error);
WUT_CHECK_OFFSET(KPADStatus, 0x5E, posValid);
WUT_CHECK_OFFSET(KPADStatus, 0x5F, format);
// For WPAD_EXT_NUNCHUK
WUT_CHECK_OFFSET(KPADStatus, 0x60, nunchuck.stick);
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

void
KPADInit();

int32_t
KPADRead(KPADChan chan,
         KPADStatus *data,
         uint32_t size);

int32_t
KPADReadEx(KPADChan chan,
           KPADStatus *data,
           uint32_t size,
           int32_t *error);

#ifdef __cplusplus
}
#endif

/** @} */
