#pragma once
#include <wut.h>
#include <coreinit/time.h>

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
typedef struct WPADInfo WPADInfo;
typedef struct WPADiQueueElement WPADiQueueElement;
typedef struct WPADiQueue WPADiQueue;

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
   //! Channel 4.
   WPAD_CHAN_4                         = 4,
   //! Channel 5.
   WPAD_CHAN_5                         = 5,
   //! Channel 6.
   WPAD_CHAN_6                         = 6,
} WPADChan;

//! Data format.
typedef enum WPADDataFormat
{
   //! Wii Remote buttons
   WPAD_FMT_CORE                       = 0,
   //! Wii Remote buttons and accelerometer
   WPAD_FMT_CORE_ACC                   = 1,
   //! Wii Remote buttons, accelerometer and IR pos
   WPAD_FMT_CORE_ACC_DPD               = 2,
   //! Wii Remote buttons, Nunchuk
   WPAD_FMT_NUNCHUK                    = 3,
   //! Wii Remote buttons, accelerometer, Nunchuk
   WPAD_FMT_NUNCHUK_ACC                = 4,
   //! Wii Remote buttons, accelerometer, IR pos, Nunchuk
   WPAD_FMT_NUNCHUK_ACC_DPD            = 5,
   //! Wii Remote buttons, Classic Controller
   WPAD_FMT_CLASSIC                    = 6,
   //! Wii Remote buttons, accelerometer, Classic Controller
   WPAD_FMT_CLASSIC_ACC                = 7,
   //! Wii Remote buttons, accelerometer, IR pos, Classic Controller
   WPAD_FMT_CLASSIC_ACC_DPD            = 8,
   //! Wii Remote buttons, accelerometer and IR pos with bounds
   WPAD_FMT_CORE_ACC_DPD_FULL          = 9,
   //! Wii Remote, Densha De GO! Shinkansen Controller
   WPAD_FMT_TRAIN                      = 10,
   //! Guitar Hero Guitar
   WPAD_FMT_GUITAR                     = 11,
   //! Wii Balance Board
   WPAD_FMT_BALANCE_BOARD              = 12,
   //! Guitar Hero World Tour Drums
   WPAD_FMT_DRUM                       = 15,
   //! Wii Remote buttons, accelerometer, IR pos, Motion Plus gyroscope
   WPAD_FMT_MPLUS                      = 16,
   //! Wii Remote, Taiko no Testsujin TaTaCon
   WPAD_FMT_TAIKO                      = 17,
   //! Wii U Pro Controller
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

typedef enum WPADLed
{
  WPAD_LED_ONE = 0x01,
  WPAD_LED_TWO = 0x02,
  WPAD_LED_THREE = 0x4,
  WPAD_LED_FOUR = 0x8
} WPADLed;

//!  WPAD Infrared Mode. For more information see <a href="https://wiibrew.org/wiki/Wiimote#Data_Formats">IR Data Formats</a>
typedef enum WPADDpdMode
{
    WPAD_DPD_DISABLE = 0,
    WPAD_DPD_ENABLE_BASIC = 1,
    WPAD_DPD_ENABLE_EXTENDED = 3,
    WPAD_DPD_ENABLE_FULL = 5
} WPADDpdMode;

//! WPAD Speaker Mode.
typedef enum WPADSpeakerMode
{
    //! Deinitializes and turns off speaker
    WPAD_SPEAKER_OFF            = 0,
    //! Turns on, initializes and mutes speaker
    WPAD_SPEAKER_ON             = 1,
    //! Mutes speaker
    WPAD_SPEAKER_MUTE           = 2,
    //! Unmutes speaker
    WPAD_SPEAKER_UNMUTE         = 3,
    //! Allows audio to play, use after setting WPAD_SPEAKER_ON and before playing sound
    WPAD_SPEAKER_FINISH_INIT    = 4,
    //! Does the same as WPAD_SPEAKER_ON
    WPAD_SPEAKER_ON_ALT         = 5
} WPADSpeakerMode;

//! MotionPlus Mode.
typedef enum WPADMplsMode
{
    WPAD_MPLS_MODE_DISABLE  = 0,
    WPAD_MPLS_MODE_ENABLE   = 4,
} WPADMplsMode;


//! WPAD Peripheral Memory Space Prefixes
typedef enum WPADPeripheralSpace
{
    WPAD_PERIPHERAL_SPACE_SPEAKER     = 0xA2,
    //! Any extension other than Motion Plus
    WPAD_PERIPHERAL_SPACE_EXTENSION   = 0xA4,
    WPAD_PERIPHERAL_SPACE_MOTIONPLUS  = 0xA6,
    //! Infrared
    WPAD_PERIPHERAL_SPACE_DPD         = 0xB0
} WPADPeripheralSpace;

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

struct WPADInfo
{
    uint32_t irEnabled;
    uint32_t speakerEnabled;
    uint32_t extensionAttached;
    uint32_t batteryLow;
    uint32_t batteryNearEmpty;
    uint8_t batteryLevel;
    uint8_t led;
    uint8_t protocol;
    uint8_t firmware;
};
WUT_CHECK_OFFSET(WPADInfo, 0x00, irEnabled);
WUT_CHECK_OFFSET(WPADInfo, 0x04, speakerEnabled);
WUT_CHECK_OFFSET(WPADInfo, 0x08, extensionAttached);
WUT_CHECK_OFFSET(WPADInfo, 0x0c, batteryLow);
WUT_CHECK_OFFSET(WPADInfo, 0x10, batteryNearEmpty);
WUT_CHECK_OFFSET(WPADInfo, 0x14, batteryLevel);
WUT_CHECK_OFFSET(WPADInfo, 0x15, led);
WUT_CHECK_OFFSET(WPADInfo, 0x16, protocol);
WUT_CHECK_OFFSET(WPADInfo, 0x17, firmware);
WUT_CHECK_SIZE(WPADInfo, 0x18);


struct WPADiQueueElement
{
    uint8_t data[0x30];
};
WUT_CHECK_OFFSET(WPADiQueueElement, 0x00, data);
WUT_CHECK_SIZE(WPADiQueueElement, 0x30);

struct WPADiQueue
{
    uint8_t frontIndex;
    uint8_t backIndex;
    WUT_PADDING_BYTES(2);
    WPADiQueueElement* elements;
    uint32_t capacity;
};
WUT_CHECK_OFFSET(WPADiQueue, 0x00, frontIndex);
WUT_CHECK_OFFSET(WPADiQueue, 0x01, backIndex);
WUT_CHECK_OFFSET(WPADiQueue, 0x04, elements);
WUT_CHECK_OFFSET(WPADiQueue, 0x08, capacity);
WUT_CHECK_SIZE(WPADiQueue, 0xc);

typedef void (*WPADIsMplsAttachedCallback)(WPADChan chan, int32_t status);
typedef void (*WPADControlLedCallback)(WPADChan chan, int32_t status);
typedef void (*WPADControlDpdCallback)(WPADChan chan, int32_t status);
typedef void (*WPADControlSpeakerCallback)(WPADChan chan, int32_t status);
typedef void (*WPADGetInfoCallback)(WPADChan chan, int32_t status);

typedef void (*WPADReadMemoryCallback)(WPADChan chan, int32_t status);
typedef void (*WPADWriteMemoryCallback)(WPADChan chan, int32_t status);

typedef void (*WPADSamplingCallback)(WPADChan chan);
typedef void (*WPADExtensionCallback)(WPADChan chan, int32_t status);
typedef void (*WPADConnectCallback)(WPADChan chan, int32_t status);

typedef void (*WPADiSendCallback)(WPADChan chan, int32_t status);

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

void
WPADDisconnect(WPADChan chan);

int32_t
WPADProbe(WPADChan chan,
          WPADExtensionType *outExtensionType);

int32_t
WPADSetDataFormat(WPADChan chan,
                  WPADDataFormat format);

WPADDataFormat 
WPADGetDataFormat(WPADChan chan);

void
WPADRead(WPADChan chan,
         void *data);

/**
* Controls the associated WPADChan's LEDs
*/
void
WPADControlLed(WPADChan channel, 
               WPADLed led, 
               WPADControlLedCallback callback);

/**
 * Controls the WPADChan's IR sensor
*/
int32_t 
WPADControlDpd(WPADChan channel,
               WPADDpdMode mode,
               WPADControlDpdCallback callback);

/**
 * Controls the associated WPADChan's rumble motor.
 */
void
WPADControlMotor(WPADChan chan,
                 BOOL motorEnabled);

/**
 * Sets the wiimote speaker mode
 */
int32_t
WPADControlSpeakerMode(WPADChan chan,
                       WPADSpeakerMode mode,
                       WPADControlSpeakerCallback);

/**
 * Returns whether the wiimote's speaker is enabled
 */
BOOL
WPADIsSpeakerEnabled(WPADChan chan);

/**
 * Returns whether it is possible to send data to the wiimote's speaker
 */
BOOL
WPADCanSendStreamData(WPADChan chan);

/**
 * Sends data to be played by wiimote speaker
 */
int32_t
WPADSendStreamData(WPADChan chan,
                   void* data,
                   uint32_t size);

/**
 * Returns the global Wii Remote speaker volume
 */
uint8_t
WPADGetSpeakerVolume();

/**
 * Sets the global Wii Remote speaker volume
 * only applies to later initialized Wii Remote speakers
 */
void
WPADSetSpeakerVolume(uint8_t volume);

/**
 * Gets whether MotionPlus is enabled for the WPAD
 * \param enabled is set if MotionPlus is enabled
 */
int32_t 
WPADIsMplsAttached(WPADChan channel, 
                  BOOL *enabled,
                  WPADIsMplsAttachedCallback callback);

/**
 * Returns whether the WPADChan has MotionPlus integrated
 * \return -1 if controller is not connected, 1 if MotionPlus integrated, 0 if not
 */
int32_t
WPADIsMplsIntegrated(WPADChan channel);

/**
 * Retrieves status info from the controller
 */
int32_t
WPADGetInfo(WPADChan channel,
            WPADInfo* outInfo);
/**
 * Retrieves status info from the controller asynchronously
 */
int32_t
WPADGetInfoAsync(WPADChan channel,
            WPADInfo* outInfo,
            WPADGetInfoCallback);

/**
 * Reads from the device's memory
 * \param destination where the received data will be stored
 * \param size number of bytes to read
 * \param address
 * device memory address, see
 * <a href="https://wiibrew.org/wiki/Wiimote#EEPROM_Memory">EEPROM Memory</a> and
 * <a href="https://wiibrew.org/wiki/Wiimote#Control_Registers">Control Registers</a>
 * \param completionCallback function to be called upon completion
 * - WPADWriteMemoryAsync()
 * - WPADReadExtReg()
 */
int32_t
WPADReadMemoryAsync(WPADChan channel,
                    void *destination,
                    uint16_t size,
                    uint32_t address,
                    WPADReadMemoryCallback callback);

/**
 * Writes to the device's memory
 * \param source data to be written to the controller
 * \param size number of bytes to write
 * \param address
 * device memory address, see
 * <a href="https://wiibrew.org/wiki/Wiimote#EEPROM_Memory">EEPROM Memory</a> and
 * <a href="https://wiibrew.org/wiki/Wiimote#Control_Registers">Control Registers</a>
 * \param callback function to be called upon completion
 * \sa
 * - WPADReadMemoryAsync()
 * - WPADWriteExtReg()
 */
int32_t
WPADWriteMemoryAsync(WPADChan channel,
                     void *source,
                     uint32_t size,
                     uint32_t address,
                     WPADWriteMemoryCallback callback);

/**
 * Reads from the registers of the Wii Remote's peripherals
 * \param address address within the peripheral's memory space
 * \sa
 * - WPADReadMemoryAsync()
 * - WPADWriteExtReg()
 */
int32_t
WPADReadExtReg(WPADChan channel,
               void *destination,
               uint16_t size,
               WPADPeripheralSpace peripheral,
               uint32_t address,
               WPADReadMemoryCallback callback);

/**
 * Writes to the registers of the Wii Remote's peripherals
 * \param address address within the peripheral's memory space
 * \sa
 * - WPADWriteMemoryAsync()
 * - WPADReadExtReg()
 */
int32_t
WPADWriteExtReg(WPADChan channel,
                void *source,
                uint32_t size,
                WPADPeripheralSpace peripheral,
                uint32_t address,
                WPADWriteMemoryCallback callback);

/**
 * Read Balance Board calibration
 * \param address may only be in the ranges [0x24,0x40) and [0x50, 0x70)
 * \sa
 * - WPADReadExtReg()
 */
int32_t
WPADGetBLCalibration(WPADChan channel,
                     void *destination,
                     uint32_t address,
                     uint32_t size,
                     WPADReadMemoryCallback callback);

/**
 * Enables/disables motors globally
 */
void 
WPADEnableMotor(BOOL enable);

/**
 * Returns whether motors are disabled globally
 */
BOOL 
WPADIsMotorEnabled();

void
WPADEnableURCC(BOOL enable);

void
WPADEnableWiiRemote(BOOL enable);

void
WPADSetAutoSleepTime(uint8_t time);


WPADConnectCallback
WPADSetConnectCallback(WPADChan chan,
                       WPADConnectCallback callback);

WPADExtensionCallback
WPADSetExtensionCallback(WPADChan chan,
                         WPADExtensionCallback callback);

WPADSamplingCallback
WPADSetSamplingCallback(WPADChan chan,
                        WPADSamplingCallback callback);

void
WPADiShutdown();

/**
 * Clears all elements from queue
 */
void
WPADiClearQueue(WPADiQueue* queue);

/**
 * Checks if there is enough space in the queue
 */
bool
WPADiIsAvailableCmdQueue(WPADiQueue* queue,
                         uint32_t count);

/**
 * Parses incoming HID report data for a controller
 * \return -1 if first byte is outside the valid input report range (0x20 to 0x3f)
 */
uint32_t
WPADiHIDParser(WPADChan channel,
               uint8_t* hidData);


/**
 * Queues HID Report for Rumble Update
 *
 * Rumble must be set before this
 */
BOOL
WPADiSendSetVibrator(WPADiQueue* cmdQueue);

/**
 * Queues HID Report for setting LEDs
 * used internally by \ref WPADControlLed
 */
BOOL
WPADiSendSetPort(WPADiQueue* cmdQueue,
                 WPADLed led,
                 WPADiSendCallback callback);

/**
 * Queues HID Report for setting data reporting mode
 */
BOOL
WPADiSendSetReportType(WPADiQueue* cmdQueue,
                       WPADDataFormat dataFormat,
                       BOOL noRepeat,
                       WPADiSendCallback callback);

/**
 * Queues HID report for a controller status request
 */
BOOL
WPADiSendGetContStat(WPADiQueue* cmdQueue,
                     WPADInfo* outInfo,
                     WPADiSendCallback callback);

/**
 * Queues HID Report for enabling the IR Camera clock
 */
BOOL
WPADiSendEnableDPD(WPADiQueue* cmdQueue,
               BOOL enable,
               WPADiSendCallback callback);

/**
 * Queues HID Report for enabling IR Camera
 */
BOOL
WPADiSendEnableDPDCSB(WPADiQueue* cmdQueue,
                  BOOL enable,
                  WPADiSendCallback callback);

/**
 * Queues HID Report for enabling speakers
 */
BOOL
WPADiSendEnableSpeaker(WPADiQueue* cmdQueue,
                       BOOL enable,
                       WPADiSendCallback callback);

/**
 * Queues HID Report for muting speakers
 */
BOOL
WPADiSendMuteSpeaker(WPADiQueue* cmdQueue,
                     BOOL mute,
                     WPADiSendCallback callback);

/**
 * Queues HID Report for sending speaker stream data
 * used internally by \ref WPADSendStreamData
 */
BOOL
WPADiSendStreamData(WPADiQueue* cmdQueue,
                    void* source,
                    uint32_t size);

/**
 * Queues HID Report for a single-byte memory write
 */
BOOL
WPADiSendWriteDataCmd(WPADiQueue* cmdQueue,
                      uint8_t byte,
                      uint32_t address,
                      WPADiSendCallback callback);

/**
 * Queues HID Report for a multi-byte memory write
 * used internally by \ref WPADWriteMemory
 */
BOOL
WPADiSendWriteData(WPADiQueue* cmdQueue,
                   void* source,
                   uint32_t size,
                   uint32_t address,
                   WPADiSendCallback callback);

/**
 * Queues HID Report for a memory read
 * used internally by \ref WPADReadMemory
 */
BOOL
WPADiSendReadData(WPADiQueue* cmdQueue,
                  void* destination,
                  uint16_t size,
                  uint32_t address,
                  WPADiSendCallback callback);

uint32_t*
WPADiGetGameCode();

uint8_t
WPADiGetGameType();

/**
 * Sets game title for all connected controllers
 * \param title up to 17 characters including null terminator
 * title will be copied onto the controller EEPROM
 */
void
WPADSetGameTitleUtf16(char16_t* title);

/**
 * Gets game title stored on specified controller
 * \returns -4, if game data previously failed to write
 */
int32_t
WPADGetGameTitleUtf16(WPADChan chan,
                      char16_t** outTitle);

/**
 * Get the time that game data was written
 * \returns -4, if game data previously failed to write
 */
int32_t
WPADGetGameDataTimestamp(WPADChan chan,
                         OSTime* timestamp);

/**
 * Write custom game data to the controller's EEPROM
 *
 * \param offset start address within custom data region
 *
 * also commits game title set by \ref WPADSetGameTitleUtf16
 */
int32_t
WPADiWriteGameData(WPADChan channel,
                   void* source,
                   uint16_t size,
                   uint32_t offset,
                   WPADWriteMemoryCallback callback);

/**
 * Read custom game data from the controller's EEPROM
 * \param offset start address within custom data region
 * \returns -6, if game data previously failed to write,
 * \returns -2, if the controller
 */
int32_t
WPADiReadGameData(WPADChan channel,
                  void* destination,
                  uint16_t size,
                  uint32_t offset,
                  WPADReadMemoryCallback callback);

/**
 * Get MotionPlus mode
 *
 * identical to \ref KPADGetMplsStatus
 */
WPADMplsMode
WPADiGetMplsStatus();

#ifdef __cplusplus
}
#endif

/** @} */
