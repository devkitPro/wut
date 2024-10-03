#pragma once
#include <wut.h>

/**
 * \defgroup tve_cec TVE HDMI CEC
 * \ingroup tve
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TVECECLogicalAddress
{
   TVE_CEC_DEVICE_TV                 = 0x0,
   TVE_CEC_DEVICE_RECORDING_DEVICE_1 = 0x1,
   TVE_CEC_DEVICE_RECORDING_DEVICE_2 = 0x2,
   TVE_CEC_DEVICE_TUNER_1            = 0x3,
   TVE_CEC_DEVICE_PLAYBACK_DEVICE_1  = 0x4,
   TVE_CEC_DEVICE_AUDIO_SYSTEM       = 0x5,
   TVE_CEC_DEVICE_TUNER_2            = 0x6,
   TVE_CEC_DEVICE_TUNER_3            = 0x7,
   TVE_CEC_DEVICE_PLAYBACK_DEVICE_2  = 0x8,
   TVE_CEC_DEVICE_RECORDING_DEVICE_3 = 0x9,
   TVE_CEC_DEVICE_TUNER_4            = 0xA,
   TVE_CEC_DEVICE_PLAYBACK_DEVICE_3  = 0xB,
   TVE_CEC_DEVICE_RESERVED_1         = 0xC,
   TVE_CEC_DEVICE_RESERVED_2         = 0xD,
   TVE_CEC_DEVICE_FREE_USE           = 0xE,
   TVE_CEC_DEVICE_UNREGISTERED       = 0xF,
   TVE_CEC_DEVICE_BROADCAST          = 0xF,
} TVECECLogicalAddress;

typedef enum TVECECOpCode
{
   TVE_CEC_OPCODE_FEATURE_ABORT                 = 0x00,
   TVE_CEC_OPCODE_IMAGE_VIEW_ON                 = 0x04,
   TVE_CEC_OPCODE_TUNER_STEP_INCREMENT          = 0x05,
   TVE_CEC_OPCODE_TUNER_STEP_DECREMENT          = 0x06,
   TVE_CEC_OPCODE_TUNER_DEVICE_STATUS           = 0x07,
   TVE_CEC_OPCODE_GIVE_TUNER_DEVICE_STATUS      = 0x08,
   TVE_CEC_OPCODE_RECORD_ON                     = 0x09,
   TVE_CEC_OPCODE_RECORD_STATUS                 = 0x0A,
   TVE_CEC_OPCODE_RECORD_OFF                    = 0x0B,
   TVE_CEC_OPCODE_TEXT_VIEW_ON                  = 0x0D,
   TVE_CEC_OPCODE_RECORD_TV_SCREEN              = 0x0F,
   TVE_CEC_OPCODE_GIVE_DECK_STATUS              = 0x1A,
   TVE_CEC_OPCODE_DECK_STATUS                   = 0x1B,
   TVE_CEC_OPCODE_SET_MENU_LANGUAGE             = 0x32,
   TVE_CEC_OPCODE_CLEAR_ANALOGUE_TIMER          = 0x33,
   TVE_CEC_OPCODE_SET_ANALOGUE_TIMER            = 0x34,
   TVE_CEC_OPCODE_TIMER_STATUS                  = 0x35,
   TVE_CEC_OPCODE_STANDBY                       = 0x36,
   TVE_CEC_OPCODE_PLAY                          = 0x41,
   TVE_CEC_OPCODE_DECK_CONTROL                  = 0x42,
   TVE_CEC_OPCODE_TIMER_CLEARED_STATUS          = 0x43,
   TVE_CEC_OPCODE_USER_CONTROL_PRESSED          = 0x44,
   TVE_CEC_OPCODE_USER_CONTROL_RELEASE          = 0x45,
   TVE_CEC_OPCODE_GIVE_OSD_NAME                 = 0x46,
   TVE_CEC_OPCODE_SET_OSD_NAME                  = 0x47,
   TVE_CEC_OPCODE_SET_OSD_STRING                = 0x64,
   TVE_CEC_OPCODE_SET_TIMER_PROGRAM_TITLE       = 0x67,
   TVE_CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST     = 0x70,
   TVE_CEC_OPCODE_GIVE_AUDIO_STATUS             = 0x71,
   TVE_CEC_OPCODE_SET_SYSTEM_AUDIO_MODE         = 0x72,
   TVE_CEC_OPCODE_REPORT_AUDIO_STATUS           = 0x7A,
   TVE_CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS = 0x7D,
   TVE_CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS      = 0x7E,
   TVE_CEC_OPCODE_ROUTING_CHANGE                = 0x80,
   TVE_CEC_OPCODE_ROUTING_INFORMATION           = 0x81,
   TVE_CEC_OPCODE_ACTIVE_SOURCE                 = 0x82,
   TVE_CEC_OPCODE_GIVE_PHYSICAL_ADDRESS         = 0x83,
   TVE_CEC_OPCODE_REPORT_PHYSICAL_ADDRESS       = 0x84,
   TVE_CEC_OPCODE_REQUEST_ACTIVE_SOURCE         = 0x85,
   TVE_CEC_OPCODE_SET_STREAM_PATH               = 0x86,
   TVE_CEC_OPCODE_DEVICE_VENDOR_ID              = 0x87,
   TVE_CEC_OPCODE_VENDOR_COMMAND                = 0x89,
   TVE_CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN     = 0x8A,
   TVE_CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP       = 0x8B,
   TVE_CEC_OPCODE_GIVE_DEVICE_VENDOR_ID         = 0x8C,
   TVE_CEC_OPCODE_MENU_REQUEST                  = 0x8D,
   TVE_CEC_OPCODE_MENU_STATUS                   = 0x8E,
   TVE_CEC_OPCODE_GIVE_DEVICE_POWER_STATUS      = 0x8F,
   TVE_CEC_OPCODE_REPORT_POWER_STATUS           = 0x90,
   TVE_CEC_OPCODE_GET_MENU_LANGUAGE             = 0x91,
   TVE_CEC_OPCODE_SELECT_ANALOGUE_SERVICE       = 0x92,
   TVE_CEC_OPCODE_SELECT_DIGITAL_SERVICE        = 0x93,
   TVE_CEC_OPCODE_SET_DIGITAL_TIMER             = 0x97,
   TVE_CEC_OPCODE_CLEAR_DIGITAL_TIMER           = 0x99,
   TVE_CEC_OPCODE_SET_AUDIO_RATE                = 0x9A,
   TVE_CEC_OPCODE_INACTIVE_SOURCE               = 0x9D,
   TVE_CEC_OPCODE_CEC_VERSION                   = 0x9E,
   TVE_CEC_OPCODE_GET_CEC_VERSION               = 0x9F,
   TVE_CEC_OPCODE_VENDOR_COMMAND_WITH_ID        = 0xA0,
   TVE_CEC_OPCODE_CLEAR_EXTERNAL_TIMER          = 0xA1,
   TVE_CEC_OPCODE_SET_EXTERNAL_TIMER            = 0xA2,
   TVE_CEC_OPCODE_ABORT                         = 0xFF,
} TVECECOpCode;

/**
 * Initializes CEC.
 * 
 * \return
 * \c TRUE on success.
 */
BOOL
TVECECInit(void);

/**
 * Sets the CEC enabled status.
 * 
 * \param enable
 * \c TRUE if CEC should be enabled.
 * 
 * \return
 * The new CEC enabled status.
 */
BOOL
TVESetCECEnable(BOOL enable);

/**
 * Checks if CEC is enabled.
 * 
 * \return
 * \c TRUE if CEC is enabled.
 */
BOOL
TVEIsCECEnable(void);

/**
 * Sends a CEC command.
 * 
 * \param destination
 * Logical address of the device where the command should be sent to.
 * 
 * \param opCode
 * The op code of the command to send.
 * 
 * \param parameters
 * Pointer to optional command parameters.
 * 
 * \param numParameters
 * The amount of additional parameters.
 * 
 * \return
 * \c TRUE on success.
 */
BOOL
TVECECSendCommand(TVECECLogicalAddress destination,
                  TVECECOpCode opCode,
                  uint8_t *parameters,
                  uint8_t numParameters);

/**
 * Get the last receieved CEC command.
 * 
 * \param outInitiator
 * Pointer to store the logical address of the initiator of the command to.
 * 
 * \param outOpCode
 * Pointer to store the op code of the command to.
 * 
 * \param outParameters
 * Pointer to store additional parameters to.
 * 
 * \param numParameters
 * Pointer to store the amount of additional parameters to.
 * 
 * \return
 * \c TRUE on success.
 * 
 * \warning
 * This will return success even if no new command has been receieved.
 * The caller should check that the parameters were actually written to.
 */
BOOL
TVECECReceiveCommand(TVECECLogicalAddress *outInitiator,
                     TVECECOpCode *outOpCode,
                     uint8_t *outParameters,
                     uint8_t *outNumParameters);

#ifdef __cplusplus
}
#endif

/** @} */
