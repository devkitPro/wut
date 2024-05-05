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
typedef struct CCRCDCWowlWakeDrcArg CCRCDCWowlWakeDrcArg;
typedef struct CCRCDCUicConfig CCRCDCUicConfig;
typedef struct CCRCDCFWInfo CCRCDCFWInfo;
typedef struct CCRCDCSoftwareVersion CCRCDCSoftwareVersion;
typedef struct CCRCDCDrhState CCRCDCDrhState;
typedef struct CCRCDCDrcState CCRCDCDrcState;
typedef uint8_t CCRCDCDestination;
typedef uint32_t CCRCDCWpsStatusType;
typedef uint8_t CCRCDCWakeState;
typedef uint8_t CCRCDCUicConfigId;

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
   CCR_CDC_DRC_STATE_UPDATE            = 2,
   CCR_CDC_DRC_STATE_UNK3              = 3,
   CCR_CDC_DRC_STATE_BACKGROUND        = 4,
   CCR_CDC_DRC_STATE_DISCONNECT        = 5,
   CCR_CDC_DRC_STATE_UNK12             = 12,
   CCR_CDC_DRC_STATE_QUICK_START_MENU  = 15,
} CCRCDCDrcStateEnum;

typedef enum CCRCDCWakeStateEnum
{
   //! Power on normally.
   CCR_CDC_WAKE_STATE_ACTIVE     = 1,
   //! Connect in \c CCR_CDC_DRC_STATE_BACKGROUND state.
   CCR_CDC_WAKE_STATE_BACKGROUND = 2,
} CCRCDCWakeStateEnum;

typedef enum CCRCDCUicConfigIdEnum
{
   //! EEPROM offset 0x200, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_UNK0                             = 0,
   //! EEPROM offset 0x20D, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_MIC_CONFIG                       = 2,
   //! EEPROM offset 0x213, Size 0xE
   CCR_CDC_UIC_CONFIG_ID_ACC_CALIBRATION_VALUE            = 3,
   //! EEPROM offset 0x244, Size 0x12
   CCR_CDC_UIC_CONFIG_ID_TP_CALIBRATION_VALUE             = 5,
   //! EEPROM offset 0x203, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_UNK7                             = 7,
   //! EEPROM offset 0x206, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_UNK8                             = 8,
   //! EEPROM offset 0x256, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_UNK9                             = 9,
   //! EEPROM offset 0x289, Size 0xC
   CCR_CDC_UIC_CONFIG_ID_TV_CONTROL_ID                    = 10,
   //! EEPROM offset 0x262, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_UNK11                            = 11,
   //! EEPROM offset 0x268, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_UNK12                            = 12,
   //! EEPROM offset 0x26E, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_UNK13                            = 13,
   //! EEPROM offset 0x274, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_INIT_BOOT_FLAG                   = 14,
   //! EEPROM offset 0x277, Size 0xF
   CCR_CDC_UIC_CONFIG_ID_UNK15                            = 15,
   //! EEPROM offset 0x286, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_LCD_MODE                         = 16,
   //! EEPROM offset 0x25C, Size 0x6
   CCR_CDC_UIC_CONFIG_ID_UNK17                            = 17,
   //! EEPROM offset 0x295, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_UNK18                            = 18,
   //! EEPROM offset 0x298, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_ENABLE_FLAG             = 19,
   //! EEPROM offset 0x29B, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_INITIAL_BOOT_FLAG       = 20,
   //! EEPROM offset 0x29E, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_CAFFEINE_SLOT           = 21,
   //! EEPROM offset 0x2A1, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_NOTIFICATION_SOUND_MODE = 22,
   //! EEPROM offset 0x2A4, Size 0x3
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_NOTIFICATION_INFO       = 23,
   //! EEPROM offset 0x2A7, Size 0x4
   CCR_CDC_UIC_CONFIG_ID_CAFFEINE_NOTIFICATION_READ_COUNT = 24,
} CCRCDCUicConfigIdEnum;

typedef enum CCRCDCExt
{
   //! Language data
   CCR_CDC_EXT_LANGUAGE    = 0,
   //! Remote Control Database
   CCR_CDC_EXT_RC_DATABASE = 1,
   CCR_CDC_EXT_UNK2        = 2,
   CCR_CDC_EXT_UNK3        = 3,
   CCR_CDC_EXT_UNK4        = 4,
} CCRCDCExt;

typedef enum CCRCDCDrhStateEnum
{
   CCR_CDC_SYS_DRH_STATE_UNK0   = 0x00,
   CCR_CDC_SYS_DRH_STATE_UNK1   = 0x01,
   CCR_CDC_SYS_DRH_STATE_UNK2   = 0x02,
   CCR_CDC_SYS_DRH_STATE_UNK3   = 0x03,
   CCR_CDC_SYS_DRH_STATE_ECO    = 0x04,
   CCR_CDC_SYS_DRH_STATE_UNK7F  = 0x7F,
   CCR_CDC_SYS_DRH_STATE_CAFE   = 0xFF,
} CCRCDCDrhStateEnum;

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

struct WUT_PACKED CCRCDCWowlWakeDrcArg
{
   WUT_PADDING_BYTES(0x6);
   //! Must be one of \link CCRCDCWakeStateEnum \endlink
   CCRCDCWakeState state;
};
WUT_CHECK_OFFSET(CCRCDCWowlWakeDrcArg, 0x6, state);
WUT_CHECK_SIZE(CCRCDCWowlWakeDrcArg, 0x7);

struct CCRCDCUicConfig
{
   //! Configuration ID (see \link CCRCDCUicConfigIdEnum \endlink)
   CCRCDCUicConfigId configId;
   //! Size of the configuration data (must match the size described in \link CCRCDCUicConfigIdEnum \endlink)
   uint8_t size;
   //! Configuration data
   uint8_t data[0x100];
};
WUT_CHECK_SIZE(CCRCDCUicConfig, 0x102);
WUT_CHECK_OFFSET(CCRCDCUicConfig, 0x00, configId);
WUT_CHECK_OFFSET(CCRCDCUicConfig, 0x01, size);
WUT_CHECK_OFFSET(CCRCDCUicConfig, 0x02, data);

struct CCRCDCFWInfo
{
   uint32_t imageSize;
   uint32_t blockSize;
   uint32_t imageVersion;
   uint32_t sequencePerSession;
   //! Progress from 0-100
   uint32_t updateProgress;
};
WUT_CHECK_OFFSET(CCRCDCFWInfo, 0x00, imageSize);
WUT_CHECK_OFFSET(CCRCDCFWInfo, 0x04, blockSize);
WUT_CHECK_OFFSET(CCRCDCFWInfo, 0x08, imageVersion);
WUT_CHECK_OFFSET(CCRCDCFWInfo, 0x0C, sequencePerSession);
WUT_CHECK_OFFSET(CCRCDCFWInfo, 0x10, updateProgress);
WUT_CHECK_SIZE(CCRCDCFWInfo, 0x14);

struct CCRCDCSoftwareVersion
{
   uint32_t runningVersion;
   uint32_t activeVersion;
};
WUT_CHECK_OFFSET(CCRCDCSoftwareVersion, 0x0, runningVersion);
WUT_CHECK_OFFSET(CCRCDCSoftwareVersion, 0x4, activeVersion);
WUT_CHECK_SIZE(CCRCDCSoftwareVersion, 0x8);

struct CCRCDCDrcState {
   //! Must be one of \link CCRCDCDrcStateEnum \endlink
   uint8_t state;
};
WUT_CHECK_OFFSET(CCRCDCDrcState, 0x0, state);
WUT_CHECK_SIZE(CCRCDCDrcState, 0x1);

struct CCRCDCDrhState {
   //! Must be one of \link CCRCDCDrhStateEnum \endlink
   uint8_t state;
};
WUT_CHECK_OFFSET(CCRCDCDrhState, 0x0, state);
WUT_CHECK_SIZE(CCRCDCDrhState, 0x1);

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
* Gets the Drh State
*
* \return
* 0 on success.
*/
int32_t
CCRCDCSysGetDrhState(CCRCDCDrhState *state);
/**
* Sets the Drh State
*
* \return
* 0 on success.
*/
int32_t
CCRCDCSysSetDrhState(CCRCDCDrhState *state);

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

/**
 * Wake on Wireless LAN (power on) the DRC(s).
 * 
 * \return
 * 0 on success or timeout (i.e. out of range/no battery).
 * 0xFFE31B5B if DRC already connected.
 */
int32_t
CCRCDCWowlWakeDrc(CCRCDCWowlWakeDrcArg *arg);

/**
 * This doesn't seem to be implemented on the latest DRC/DRH firmware,
 * and always returns an error.
 * 
 * \param dest
 * The destination to send the command to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCPerClearUicConfig(CCRCDCDestination dest);

/**
 * Set a configuration value in the DRC UIC EEPROM.
 * 
 * \param dest
 * The destination to send the command to.
 * 
 * \param config
 * Pointer to configuration data.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCPerSetUicConfig(CCRCDCDestination dest,
                      CCRCDCUicConfig *config);

/**
 * Calculate a CRC16 used for DRC UIC EEPROM values.
 * 
 * \param data
 * Pointer to the data to calculate the CRC from.
 * 
 * \param config
 * Size of the data.
 * 
 * \return
 * The CRC value or \c 0xffff on error.
 */
uint16_t
CCRCDCCalcCRC16(void *data,
                uint32_t dataSize);

/**
 * Get the firmware info during a pending update.
 * 
 * \param dest
 * The destination to get the firmware info from.
 * 
 * \param outInfo
 * Pointer to write the info to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCGetFWInfo(CCRCDCDestination dest,
                CCRCDCFWInfo *outInfo);

/**
 * Get software version information.
 * 
 * \param dest
 * The destination to get the version information from.
 * 
 * \param outVersion
 * Pointer to write the version info to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSoftwareGetVersion(CCRCDCDestination dest,
                         CCRCDCSoftwareVersion *outVersion);

/**
 * Perform a software update.
 * 
 * \param dest
 * The destination to start a software update.
 * 
 * \param path
 * Absolute path to read the update file from.
 * Note that this path needs to be accessible from IOS-PAD (e.g. on the MLC).
 * 
 * \param callback
 * Callback to call once the update completes or \c NULL for synchronous updating.
 * 
 * \param userContext
 * User provided value which is passed to the callback.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSoftwareUpdate(CCRCDCDestination dest,
                     const char *path,
                     IOSAsyncCallbackFn callback,
                     void *userContext);

/**
 * Abort a software update.
 * 
 * \param dest
 * The destination to send the command to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSoftwareAbort(CCRCDCDestination dest);

/**
 * Activate a performed software update.
 * 
 * \param dest
 * The destination to send the command to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSoftwareActivate(CCRCDCDestination dest);

/**
 * Get an ext id from the specified destination.
 * 
 * \param dest
 * The destination to get the ID from.
 * 
 * \param ext
 * The ext to get the ID for.
 * 
 * \param outId
 * Pointer to write the ID to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCSoftwareGetExtId(CCRCDCDestination dest,
                       CCRCDCExt ext,
                       uint32_t *outId);

#ifdef __cplusplus
}
#endif

/** @} */
