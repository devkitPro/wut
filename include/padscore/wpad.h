#pragma once
#include <wut.h>

/**
 * \defgroup padscore_wpad WPAD
 * \ingroup padscore
 * 
 * WPAD is a low-level library under KPAD.
 * 
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct WPADStatusProController WPADStatusProController;
typedef struct WPADVec2D WPADVec2D;

//! Wii Remote channel.
typedef enum WPADChan
{
   //! Channel 0.
   WPAD_CHAN_0                         = 0,
   //! Channel 1.
   WPAD_CHAN_1                         = 1,
   //! Channel 2.
   WPAD_CHAN_2                         = 2,
   //! Channel 3.
   WPAD_CHAN_3                         = 3,
} WPADChan;

//! Data format.
typedef enum WPADDataFormat
{
   WPAD_FMT_PRO_CONTROLLER             = 22,
} WPADDataFormat;

//! Extension type.
typedef enum WPADExtensionType
{
   //! Wii Remote with no extension.
   WPAD_EXT_CORE                    = 0,
   //! Nunchuk.
   WPAD_EXT_NUNCHUK                 = 1,
   //! Classic Controller.
   WPAD_EXT_CLASSIC                 = 2,
   //! Motion Plus.
   WPAD_EXT_MPLUS                   = 5,
   //! Motion Plus with Nunchuk.
   WPAD_EXT_MPLUS_NUNCHUK           = 6,
   //! Motion Plus with Classic Controller.
   WPAD_EXT_MPLUS_CLASSIC           = 7,
   //! Pro Controller.
   WPAD_EXT_PRO_CONTROLLER          = 31,
} WPADExtensionType;

//! Wii Remote buttons.
typedef enum WPADButton
{
   //! The left button of the D-pad.
   WPAD_BUTTON_LEFT                    = 0x0001,
   //! The right button of the D-pad.
   WPAD_BUTTON_RIGHT                   = 0x0002,
   //! The down button of the D-pad.
   WPAD_BUTTON_DOWN                    = 0x0004,
   //! The up button of the D-pad.
   WPAD_BUTTON_UP                      = 0x0008,
   //! The + button.
   WPAD_BUTTON_PLUS                    = 0x0010,
   //! The 2 button.
   WPAD_BUTTON_2                       = 0x0100,
   //! The 1 button.
   WPAD_BUTTON_1                       = 0x0200,
   //! The B button.
   WPAD_BUTTON_B                       = 0x0400,
   //! The A button.
   WPAD_BUTTON_A                       = 0x0800,
   //! The - button.
   WPAD_BUTTON_MINUS                   = 0x1000,
   //! The Z button on the Nunchuk extension.
   WPAD_BUTTON_Z                       = 0x2000,
   //! The C button on the Nunchuk extension.
   WPAD_BUTTON_C                       = 0x4000,
   //! The HOME button.
   WPAD_BUTTON_HOME                    = 0x8000,
} WPADButton;

//! Nunchuk buttons.
typedef enum WPADNunchukButton
{
   //! The emulated left button on the Nunchuk stick or the left button of the D-pad on the Wii Remote.
   WPAD_NUNCHUK_STICK_EMULATION_LEFT  = 0x0001,
   //! The emulated right button on the Nunchuk stick or the right button of the D-pad on the Wii Remote.
   WPAD_NUNCHUK_STICK_EMULATION_RIGHT = 0x0002,
   //! The emulated down button on the Nunchuk stick or the down button of the D-pad on the Wii Remote.
   WPAD_NUNCHUK_STICK_EMULATION_DOWN  = 0x0004,
   //! The emulated up button on the Nunchuk stick or the up button of the D-pad on the Wii Remote.
   WPAD_NUNCHUK_STICK_EMULATION_UP    = 0x0008,
   //! The Z button.
   WPAD_NUNCHUK_BUTTON_Z              = 0x2000,
   //! The C button.
   WPAD_NUNCHUK_BUTTON_C              = 0x4000,
} WPADNunchukButton;

//! Classic Controller buttons.
typedef enum WPADClassicButton
{
   //! The up button of the D-pad.
   WPAD_CLASSIC_BUTTON_UP               = 0x00000001,
   //! The left button of the D-pad.
   WPAD_CLASSIC_BUTTON_LEFT             = 0x00000002,
   //! The ZR button.
   WPAD_CLASSIC_BUTTON_ZR               = 0x00000004,
   //! The X button.
   WPAD_CLASSIC_BUTTON_X                = 0x00000008,
   //! The A button.
   WPAD_CLASSIC_BUTTON_A                = 0x00000010,
   //! The Y button.
   WPAD_CLASSIC_BUTTON_Y                = 0x00000020,
   //! The B button.
   WPAD_CLASSIC_BUTTON_B                = 0x00000040,
   //! The ZL button.
   WPAD_CLASSIC_BUTTON_ZL               = 0x00000080,
   //! The R button.
   WPAD_CLASSIC_BUTTON_R                = 0x00000200,
   //! The + button.
   WPAD_CLASSIC_BUTTON_PLUS             = 0x00000400,
   //! The HOME button.
   WPAD_CLASSIC_BUTTON_HOME             = 0x00000800,
   //! The - button.
   WPAD_CLASSIC_BUTTON_MINUS            = 0x00001000,
   //! The L button.
   WPAD_CLASSIC_BUTTON_L                = 0x00002000,
   //! The down button of the D-pad.
   WPAD_CLASSIC_BUTTON_DOWN             = 0x00004000,
   //! The right button of the D-pad.
   WPAD_CLASSIC_BUTTON_RIGHT            = 0x00008000,
   //! The emulated left button on the left stick.
   WPAD_CLASSIC_STICK_L_EMULATION_LEFT  = 0x00010000,
   //! The emulated right button on the left stick.
   WPAD_CLASSIC_STICK_L_EMULATION_RIGHT = 0x00020000,
   //! The emulated down button on the left stick.
   WPAD_CLASSIC_STICK_L_EMULATION_DOWN  = 0x00040000,
   //! The emulated up button on the left stick.
   WPAD_CLASSIC_STICK_L_EMULATION_UP    = 0x00080000,
   //! The emulated left button on the right stick.
   WPAD_CLASSIC_STICK_R_EMULATION_LEFT  = 0x00100000,
   //! The emulated right button on the right stick.
   WPAD_CLASSIC_STICK_R_EMULATION_RIGHT = 0x00200000,
   //! The emulated down button on the right stick.
   WPAD_CLASSIC_STICK_R_EMULATION_DOWN  = 0x00400000,
   //! The emulated up button on the right stick.
   WPAD_CLASSIC_STICK_R_EMULATION_UP    = 0x00800000,
} WPADClassicButton;

//! Pro Controller buttons.
typedef enum WPADProButton
{
   //! The up button of the D-pad.
   WPAD_PRO_BUTTON_UP                  = 0x00000001,
   //! The left button of the D-pad.
   WPAD_PRO_BUTTON_LEFT                = 0x00000002,
   //! The ZR button.
   WPAD_PRO_TRIGGER_ZR                 = 0x00000004,
   //! The X button.
   WPAD_PRO_BUTTON_X                   = 0x00000008,
   //! The A button.
   WPAD_PRO_BUTTON_A                   = 0x00000010,
   //! The Y button.
   WPAD_PRO_BUTTON_Y                   = 0x00000020,
   //! The B button.
   WPAD_PRO_BUTTON_B                   = 0x00000040,
   //! The ZL button.
   WPAD_PRO_TRIGGER_ZL                 = 0x00000080,
   //! Reserved.
   WPAD_PRO_RESERVED                   = 0x00000100,
   //! The right trigger button.
   WPAD_PRO_TRIGGER_R                  = 0x00000200,
   //! The + button.
   WPAD_PRO_BUTTON_PLUS                = 0x00000400,
   //! The HOME button.
   WPAD_PRO_BUTTON_HOME                = 0x00000800,
   //! The - button.
   WPAD_PRO_BUTTON_MINUS               = 0x00001000,
   //! The left trigger button.
   WPAD_PRO_TRIGGER_L                  = 0x00002000,
   //! The down button of the D-pad.
   WPAD_PRO_BUTTON_DOWN                = 0x00004000,
   //! The right button of the D-pad.
   WPAD_PRO_BUTTON_RIGHT               = 0x00008000,
   //! The right stick button.
   WPAD_PRO_BUTTON_STICK_R             = 0x00010000,
   //! The left stick button.
   WPAD_PRO_BUTTON_STICK_L             = 0x00020000,
   //! The emulated up button on the left stick.
   WPAD_PRO_STICK_L_EMULATION_UP       = 0x00200000,
   //! The emulated down button on the left stick.
   WPAD_PRO_STICK_L_EMULATION_DOWN     = 0x00100000,
   //! The emulated left button on the left stick.
   WPAD_PRO_STICK_L_EMULATION_LEFT     = 0x00040000,
   //! The emulated right button on the left stick.
   WPAD_PRO_STICK_L_EMULATION_RIGHT    = 0x00080000,
   //! The emulated up button on the right stick.
   WPAD_PRO_STICK_R_EMULATION_UP       = 0x02000000,
   //! The emulated down button on the right stick.
   WPAD_PRO_STICK_R_EMULATION_DOWN     = 0x01000000,
   //! The emulated left button on the right stick.
   WPAD_PRO_STICK_R_EMULATION_LEFT     = 0x00400000,
   //! The emulated right button on the right stick.
   WPAD_PRO_STICK_R_EMULATION_RIGHT    = 0x00800000,
} WPADProButton;

//! 2D vector.
struct WPADVec2D
{
   //! x.
   int16_t x;
   //! y.
   int16_t y;
};
WUT_CHECK_OFFSET(WPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(WPADVec2D, 0x02, y);
WUT_CHECK_SIZE(WPADVec2D, 0x04);

struct WPADStatusProController
{
   WUT_UNKNOWN_BYTES(0x28);

   //! A value from WPADExtensionType.
   uint8_t extensionType;

   uint8_t err;
   WUT_PADDING_BYTES(2);
   uint32_t buttons;
   WPADVec2D leftStick;
   WPADVec2D rightStick;
   WUT_UNKNOWN_BYTES(8);
   WPADDataFormat dataFormat;
};
WUT_CHECK_OFFSET(WPADStatusProController, 0x28, extensionType);
WUT_CHECK_OFFSET(WPADStatusProController, 0x29, err);
WUT_CHECK_OFFSET(WPADStatusProController, 0x2C, buttons);
WUT_CHECK_OFFSET(WPADStatusProController, 0x30, leftStick);
WUT_CHECK_OFFSET(WPADStatusProController, 0x34, rightStick);
WUT_CHECK_OFFSET(WPADStatusProController, 0x40, dataFormat);
WUT_CHECK_SIZE(WPADStatusProController, 0x44);

typedef void (*WPADSamplingCallback)(WPADChan chan);
typedef void (*WPADExtensionCallback)(WPADChan chan, int32_t status);
typedef void (*WPADConnectCallback)(WPADChan chan, int32_t status);

/**
 * Initialises the WPAD library for use.
 */
void
WPADInit();

/**
 * Cleans up and frees the WPAD library.
 */
void
WPADShutdown();

int32_t
WPADProbe(WPADChan chan,
          WPADExtensionType *outExtensionType);

int32_t
WPADSetDataFormat(WPADChan chan,
                  WPADDataFormat format);

void
WPADEnableURCC(int32_t enable);

void
WPADEnableWiiRemote(int32_t enable);

void
WPADRead(WPADChan chan,
         void *data);

void
WPADSetAutoSleepTime(uint8_t time);

void
WPADDisconnect(WPADChan chan);

WPADConnectCallback
WPADSetConnectCallback(WPADChan chan,
                       WPADConnectCallback callback);

WPADExtensionCallback
WPADSetExtensionCallback(WPADChan chan,
                         WPADExtensionCallback callback);

WPADSamplingCallback
WPADSetSamplingCallback(WPADChan chan,
                        WPADSamplingCallback callback);

#ifdef __cplusplus
}
#endif

/** @} */
