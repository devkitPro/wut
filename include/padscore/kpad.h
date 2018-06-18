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
CHECK_OFFSET(KPADVec2D, 0x00, x);
CHECK_OFFSET(KPADVec2D, 0x04, y);
CHECK_SIZE(KPADVec2D, 0x08);

struct KPADStatus
{
   //! Indicates what KPADButtons are held down
   uint32_t hold;

   //! Indicates what KPADButtons have been pressed since last sample
   uint32_t trigger;

   //! Indicates what KPADButtons have been released since last sample
   uint32_t release;

   UNKNOWN(5 * 4);

   KPADVec2D pos;

   UNKNOWN(3 * 4);

   KPADVec2D angle;

   UNKNOWN(8 * 4);

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

      UNKNOWN(20 * 4);
   };

   UNKNOWN(16 * 4);
};
CHECK_OFFSET(KPADStatus, 0x00, hold);
CHECK_OFFSET(KPADStatus, 0x04, trigger);
CHECK_OFFSET(KPADStatus, 0x08, release);
CHECK_OFFSET(KPADStatus, 0x20, pos);
CHECK_OFFSET(KPADStatus, 0x34, angle);
CHECK_OFFSET(KPADStatus, 0x5C, extensionType);
CHECK_OFFSET(KPADStatus, 0x5D, error);
CHECK_OFFSET(KPADStatus, 0x5E, posValid);
CHECK_OFFSET(KPADStatus, 0x5F, format);
// For WPAD_EXT_NUNCHUK
CHECK_OFFSET(KPADStatus, 0x60, nunchuck.stick);
// For WPAD_EXT_CLASSIC
CHECK_OFFSET(KPADStatus, 0x60, classic.hold);
CHECK_OFFSET(KPADStatus, 0x64, classic.trigger);
CHECK_OFFSET(KPADStatus, 0x68, classic.release);
CHECK_OFFSET(KPADStatus, 0x6C, classic.leftStick);
CHECK_OFFSET(KPADStatus, 0x74, classic.rightStick);
CHECK_OFFSET(KPADStatus, 0x7C, classic.leftTrigger);
CHECK_OFFSET(KPADStatus, 0x80, classic.rightTrigger);
// For WPAD_EXT_PRO_CONTROLLER
CHECK_OFFSET(KPADStatus, 0x60, pro.hold);
CHECK_OFFSET(KPADStatus, 0x64, pro.trigger);
CHECK_OFFSET(KPADStatus, 0x68, pro.release);
CHECK_OFFSET(KPADStatus, 0x6C, pro.leftStick);
CHECK_OFFSET(KPADStatus, 0x74, pro.rightStick);
CHECK_OFFSET(KPADStatus, 0x7C, pro.charging);
CHECK_OFFSET(KPADStatus, 0x80, pro.wired);
CHECK_SIZE(KPADStatus, 0xF0);

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
