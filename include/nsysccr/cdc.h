#pragma once
#include <wut.h>
#include <coreinit/ios.h>

/**
 * \defgroup nsysccr_cdc
 * \ingroup nsysccr
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CCRCDCMacAddress CCRCDCMacAddress;
typedef struct CCRCDCWpsArgs CCRCDCWpsArgs;
typedef struct CCRCDCSysMessage CCRCDCSysMessage;
typedef struct CCRCDCEepromData CCRCDCEepromData;
typedef uint8_t CCRCDCDestination;
typedef uint32_t CCRCDCWpsStatusType;
typedef uint8_t CCRCDCDrcState;

typedef enum CCRCDCDestinationEnum
{
   CCR_CDC_DESTINATION_DRH  = 1,
   CCR_CDC_DESTINATION_DRC0 = 2,
   CCR_CDC_DESTINATION_DRC1 = 3,
} CCRCDCDestinationEnum;

typedef enum CCRCDCWpsStatusEnum
{
   CCR_CDC_WPS_STATUS_PAIRED     = 0,
   CCR_CDC_WPS_STATUS_SEARCHING  = 1,
   CCR_CDC_WPS_STATUS_PAIRING    = 2,
} CCRCDCWpsStatusEnum;

typedef enum CCRCDCDrcStateEnum
{
   CCR_CDC_DRC_STATE_ACTIVE            = 0,
   CCR_CDC_DRC_STATE_UNK1              = 1,
   CCR_CDC_DRC_STATE_UNK2              = 2,
   CCR_CDC_DRC_STATE_UNK3              = 3,
   CCR_CDC_DRC_STATE_BACKGROUND        = 4,
   CCR_CDC_DRC_STATE_DISCONNECT        = 5,
   CCR_CDC_DRC_STATE_UNK12             = 12,
   CCR_CDC_DRC_STATE_UNK15             = 15,
} CCRCDCDrcStateEnum;

struct WUT_PACKED CCRCDCMacAddress
{
   //! The device this mac address belongs to
   CCRCDCDestination device;
   uint8_t address[6];
};
WUT_CHECK_OFFSET(CCRCDCMacAddress, 0x0, device);
WUT_CHECK_OFFSET(CCRCDCMacAddress, 0x1, address);
WUT_CHECK_SIZE(CCRCDCMacAddress, 0x7);

struct WUT_PACKED CCRCDCWpsArgs
{
   //! Should be set to 1
   uint8_t hasArgs;
   //! The pin code used for WPS
   char pin[8];
   //! Timeout in seconds
   uint16_t timeout;
   // \c CCR_CDC_DESTINATION_DRC0 or \c CCR_CDC_DESTINATION_DRC1 depending on where the device should be paired to
   CCRCDCDestination pairDestination;
};
WUT_CHECK_OFFSET(CCRCDCWpsArgs, 0x0, hasArgs);
WUT_CHECK_OFFSET(CCRCDCWpsArgs, 0x1, pin);
WUT_CHECK_OFFSET(CCRCDCWpsArgs, 0x9, timeout);
WUT_CHECK_OFFSET(CCRCDCWpsArgs, 0xb, pairDestination);
WUT_CHECK_SIZE(CCRCDCWpsArgs, 0xc);

struct WUT_PACKED CCRCDCSysMessage
{
   uint16_t message;
   //! Timeout in seconds
   uint16_t timeout;
};
WUT_CHECK_OFFSET(CCRCDCSysMessage, 0x0, message);
WUT_CHECK_OFFSET(CCRCDCSysMessage, 0x2, timeout);
WUT_CHECK_SIZE(CCRCDCSysMessage, 0x4);

struct WUT_PACKED CCRCDCEepromData
{
   uint32_t version;
   WUT_UNKNOWN_BYTES(0x300);
};
WUT_CHECK_OFFSET(CCRCDCEepromData, 0x0, version);
WUT_CHECK_SIZE(CCRCDCEepromData, 0x304);

/**
 * Send a command directly to the specified destination.
 * 
 * \param dest
 * The device to send the command to.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCCommand(uint8_t unk,
              uint8_t fragment,
              CCRCDCDestination dest,
              uint8_t flags0,
              uint8_t flags1,
              uint8_t service,
              uint8_t method,
              void *payload,
              uint32_t payloadSize,
              void *reply,
              uint32_t replySize);

/**
 * Send a ping to the specified destination.
 * 
 * \param dest
 * The device to ping.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCDevicePing(CCRCDCDestination dest);

int32_t
CCRCDCSetStationId(CCRCDCMacAddress *id);

/**
 * Gets the mac address of the specified destination.
 * 
 * \param dest
 * The device to get the mac address from.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param mac
 * A pointer to write the mac address to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCGetMacAddress(CCRCDCDestination dest,
                    CCRCDCMacAddress *mac);

/**
 * Gets the amount of DRCs which can be connected to the system.
 * 
 * \param numDrcs
 * A pointer to write the amount to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCGetMultiDrc(uint8_t *numDrcs);

/**
 * Sets the amount of DRCs which can be connected to the system.
 * 
 * \param numDrcs
 * The amount of DRCs (must be 1 or 2).
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSetMultiDrc(uint8_t numDrcs);

/**
 * Gets the state of the specified DRC.
 * 
 * \param dest
 * The device to get the state from.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param state
 * A pointer to write the state to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSysGetDrcState(CCRCDCDestination dest,
                     CCRCDCDrcState *state);

/**
 * Sets the state of the specified DRC.
 * 
 * \param dest
 * The device to set the state.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param state
 * A pointer to read the state from.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSysSetDrcState(CCRCDCDestination dest,
                     CCRCDCDrcState *state);

/**
 * Start WPS (WiFi Protected Setup) on the DRH.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCWpsStart(void);

/**
 * Start WPS (WiFi Protected Setup) on the DRH.
 * 
 * \param args
 * Additional arguments.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCWpsStartEx(CCRCDCWpsArgs *args);

/**
 * Get the WPS status.
 * 
 * \param status
 * A pointer to write the status to.
 * See \link CCRCDCWpsStatusEnum \endlink.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCWpsStatus(CCRCDCWpsStatusType *status);

/**
 * Stop WPS.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCWpsStop(void);

/**
 * Display a message on the specified DRC.
 * 
 * \param dest
 * The device to display the message on.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param message
 * The message struct.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSysDrcDisplayMessage(CCRCDCDestination dest,
                           CCRCDCSysMessage *message);

/**
 * Read the Eeprom of the specified device.
 * 
 * \param dest
 * The device to read the eeprom of.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param eeprom
 * Pointer to write the the eeprom data to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCPerGetUicEeprom(CCRCDCDestination dest,
                      CCRCDCEepromData *eeprom);

/**
 * Read the Eeprom of the specified device (async version).
 * 
 * \param dest
 * The device to read the eeprom of.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param eeprom
 * Pointer to write the the eeprom data to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCPerGetUicEepromEx(CCRCDCDestination dest,
                        CCRCDCEepromData *eeprom,
                        IOSAsyncCallbackFn callback,
                        void* arg);

/**
 * Notify the specified device that the console is about to shut down,
 * and the device should shut down as well.
 * 
 * \param dest
 * The device to notify.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSysConsoleShutdownInd(CCRCDCDestination dest);

#ifdef __cplusplus
}
#endif

/** @} */
