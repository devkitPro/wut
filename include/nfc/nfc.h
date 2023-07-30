#pragma once
#include <wut.h>
#include <vpadbase/base.h>

/**
 * \defgroup nfc_nfc
 * \ingroup nfc
 * Near Field Communication (NFC).
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t NFCError;
typedef uint8_t NFCProtocol;
typedef uint8_t NFCTechnology;
typedef uint8_t NFCTechnologyMask;
typedef uint8_t NFCNDEFFlags;
typedef struct NFCUid NFCUid;
typedef struct NFCTagInfo NFCTagInfo;
typedef struct NFCNTAGVersion NFCNTAGVersion;
typedef struct NFCReadT2TResult NFCReadT2TResult;

typedef enum NFCMode
{
   NFC_MODE_INVALID     = -1,
   //! NFC is idle
   NFC_MODE_IDLE        = 0,
   //! NFC is discovering / has an active tag
   NFC_MODE_ACTIVE      = 1,
} NFCMode;

typedef enum NFCProtocolEnum
{
   NFC_PROTOCOL_UNKNOWN         = 0x00,
   NFC_PROTOCOL_T1T             = 0x01,
   NFC_PROTOCOL_T2T             = 0x02,
   NFC_PROTOCOL_T3T             = 0x03,
   NFC_PROTOCOL_ISO_DEP         = 0x04,
   NFC_PROTOCOL_15693           = 0x83,
} NFCProtocolEnum;

typedef enum NFCTechnologyEnum
{
   NFC_TECHNOLOGY_A             = 0x00,
   NFC_TECHNOLOGY_B             = 0x01,
   NFC_TECHNOLOGY_F             = 0x02,
   NFC_TECHNOLOGY_ISO15693      = 0x06,
} NFCTechnologyEnum;

typedef enum NFCTechnologyMaskEnum
{
   NFC_TECHNOLOGY_MASK_ALL      = 0,
   NFC_TECHNOLOGY_MASK_A        = (1 << 0),
   NFC_TECHNOLOGY_MASK_B        = (1 << 1),
   NFC_TECHNOLOGY_MASK_F        = (1 << 2),
   NFC_TECHNOLOGY_MASK_ISO15693 = (1 << 3),
} NFCTechnologyMaskEnum;

typedef enum NFCNDEFFlagsEnum
{
   //! Tag is read only
   NFC_NDEF_FLAG_READ_ONLY     = (1 << 0),
   //! Tag formated for NDEF
   NFC_NDEF_FLAG_FORMATED      = (1 << 1),
   //! NDEF supported by the tag
   NFC_NDEF_FLAG_SUPPORTED     = (1 << 2),
   //! Unable to find if tag is ndef capable/formated/read only
   NFC_NDEF_FLAG_UNKNOWN       = (1 << 3),
   //! Tag supports format operation
   NFC_NDEF_FLAG_FORMATABLE    = (1 << 4),
   //! Tag can be soft locked
   NFC_NDEF_FLAG_SOFT_LOCKABLE = (1 << 5),
   //! Tag can be hard locked
   NFC_NDEF_FLAG_HARD_LOCKABLE = (1 << 6),
   //! Tag is one time programmable
   NFC_NDEF_FLAG_OTP           = (1 << 7),
} NFCNDEFFlagsEnum;

struct NFCUid
{
   uint8_t uid[7];
};
WUT_CHECK_OFFSET(NFCUid, 0x00, uid);
WUT_CHECK_SIZE(NFCUid, 0x07);

struct NFCTagInfo
{
   uint8_t uidSize;
   uint8_t uid[10];
   NFCTechnology technology;
   NFCProtocol protocol;
   WUT_PADDING_BYTES(0x20); // reserved
};
WUT_CHECK_OFFSET(NFCTagInfo, 0x00, uidSize);
WUT_CHECK_OFFSET(NFCTagInfo, 0x01, uid);
WUT_CHECK_OFFSET(NFCTagInfo, 0x0B, technology);
WUT_CHECK_OFFSET(NFCTagInfo, 0x0C, protocol);
WUT_CHECK_SIZE(NFCTagInfo, 0x2D);

// GET_VERSION response for NTAG213, NTAG215 and NTAG216
struct NFCNTAGVersion
{
   uint8_t header;
   uint8_t vendorId;
   uint8_t productType;
   uint8_t productSubtype;
   uint8_t majorProductVersion;
   uint8_t minorProductversion;
   uint8_t storageSize;
   uint8_t protocolType;
};
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x00, header);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x01, vendorId);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x02, productType);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x03, productSubtype);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x04, majorProductVersion);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x05, minorProductversion);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x06, storageSize);
WUT_CHECK_OFFSET(NFCNTAGVersion, 0x07, protocolType);
WUT_CHECK_SIZE(NFCNTAGVersion, 0x08);

struct NFCReadT2TResult
{
   //! The amount of reads which have been performed
   uint8_t numReads;
   uint8_t read0Start;
   uint8_t read0End;
   uint8_t read1Start;
   uint8_t read1End;
   uint8_t read2Start;
   uint8_t read2End;
   uint8_t read3Start;
   uint8_t read3End;
   //! The data which has been read
   uint8_t data[0x3A0];
};
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x00, numReads);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x01, read0Start);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x02, read0End);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x03, read1Start);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x04, read1End);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x05, read2Start);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x06, read2End);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x07, read3Start);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x08, read3End);
WUT_CHECK_OFFSET(NFCReadT2TResult, 0x09, data);
WUT_CHECK_SIZE(NFCReadT2TResult, 0x3A9);

/**
 * Generic callback function.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCCallbackFn)(VPADChan chan,
                 NFCError error,
                 void *userContext);

/**
 * Callback function for \link NFCSetTagDetectCallback \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param hasTag
 * \c TRUE if a tag has been attached. \c FALSE if a tag has been removed.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCTagDetectCallbackFn)(VPADChan chan,
                          BOOL hasTag,
                          void *userContext);

/**
 * Callback function for \link NFCDetect \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param uid
 * The UID of the tag.
 * 
 * \param readOnly
 * \c TRUE if the tag is read only.
 * 
 * \param hasLockedData
 * \c TRUE if the tag has a locked area.
 * 
 * \param flags
 * A combination of \link NFCNDEFFlagsEnum \endlink flags.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCDetectCallbackFn)(VPADChan chan,
                       NFCError error,
                       NFCUid *uid,
                       BOOL readOnly,
                       BOOL hasLockedData,
                       NFCNDEFFlags flags,
                       void *userContext);

/**
 * Callback function for \link NFCSendRawData \endlink and variations.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param responseSize
 * The size of the responseData.
 * 
 * \param responseData
 * The data received from the tag.
 *
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCRawDataCallbackFn)(VPADChan chan,
                        NFCError error,
                        uint32_t responseSize,
                        void *responseData,
                        void *userContext);

/**
 * Callback function for \link NFCSendRawDataTwice \endlink and variations.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param numCompleted
 * The amount of commands which have been sent to the tag.
 * 
 * \param response0Size,response1Size
 * The size of the response data.
 * 
 * \param response0Data,response1Data
 * The data received from each of the commands.
 *
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCRawDataTwiceCallbackFn)(VPADChan chan,
                             NFCError error,
                             uint8_t numCompleted,
                             uint32_t response0Size,
                             void *response0Data,
                             uint32_t response1Size,
                             void *response1Data,
                             void *userContext);

/**
 * Callback function for \link NFCRead \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param uid
 * The UID of the tag.
 * 
 * \param readOnly
 * \c TRUE if the tag is read only.
 * 
 * \param dataSize
 * The size of the read data.
 * 
 * \param data
 * The data payload of the first tnf 5 NDEF record.
 * 
 * \param lockedDataSize
 * The size of the locked data.
 * 
 * \param lockedData
 * The data of the locked area (see \link NFCSetLockBitsForT1T \endlink).
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCReadCallbackFn)(VPADChan chan,
                     NFCError error,
                     NFCUid *uid,
                     BOOL readOnly,
                     uint32_t dataSize,
                     void *data,
                     uint32_t lockedDataSize,
                     void *lockedData,
                     void *userContext);

/**
 * Callback function for \link NFCReadT2T \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param rfDiscId
 * RF Discovery ID.
 * 
 * \param protocol
 * The tag protocol.
 * 
 * \param technology
 * Discovery type / Detected technology.
 * 
 * \param uidSize
 * The size of the UID.
 * 
 * \param uid
 * The UID of the tag.
 * 
 * \param version
 * The response of the NTAG GET_VERSION command.
 * 
 * \param result
 * The read result.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCReadT2TCallbackFn)(VPADChan chan,
                        NFCError error,
                        uint8_t rfDiscId,
                        NFCProtocol protocol,
                        NFCTechnology technology,
                        uint8_t uidSize,
                        uint8_t *uid,
                        NFCNTAGVersion *version,
                        NFCReadT2TResult *result,
                        void *userContext);

/**
 * Callback function for \link NFCGetTagInfo \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param tagInfo
 * The tag info.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCGetTagInfoCallbackFn)(VPADChan chan,
                           NFCError error,
                           NFCTagInfo *tagInfo,
                           void *userContext);

/**
 * Callback function for \link NFCGetTagInfoMulti \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param numTagInfos
 * The amount of tag infos which have been obtained.
 * 
 * \param tagInfo0,tagInfo1,tagInfo2
 * The obtained tag infos.
 * 
 * \param userContext
 * User provided value.
 */
typedef void
(*NFCGetTagInfoMultiCallbackFn)(VPADChan chan,
                                NFCError error,
                                uint8_t numTagInfos,
                                NFCTagInfo *tagInfo0,
                                NFCTagInfo *tagInfo1,
                                NFCTagInfo *tagInfo2,
                                void *userContext);

/**
 * Initializes the NFC library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCInit(VPADChan chan);

/**
 * Initializes the NFC library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param powerMode
 * Unknown.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCInitEx(VPADChan chan,
          uint32_t powerMode);

/**
 * Shutdown the NFC library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCShutdown(VPADChan chan);

/**
 * Check if NFC is initialized.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * \c TRUE if initialized, \c FALSE otherwise.
 */
BOOL
NFCIsInit(VPADChan chan);

/**
 * Process NFC.
 * This needs to be called periodically and will call pending callbacks.
 * 
 * \param chan
 * The DRC channel to use.
 */
void
NFCProc(VPADChan chan);

/**
 * Set a callback which will be called once a tag is attached / removed.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 */
void
NFCSetTagDetectCallback(VPADChan chan,
                        NFCTagDetectCallbackFn callback,
                        void *userContext);

/**
 * Get the current NFC mode.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * The current NFC mode.
 */
NFCMode
NFCGetMode(VPADChan chan);

/**
 * Set the current NFC mode.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param mode
 * The NFC mode to set.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSetMode(VPADChan chan,
           NFCMode mode);

/**
 * Abort pending NFC operations.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCAbort(VPADChan chan,
         NFCCallbackFn callback,
         void *userContext);

/**
 * Check the NFC antenna.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCAntennaCheck(VPADChan chan,
                NFCCallbackFn callback,
                void *userContext);

/**
 * Start tag discovery and provide info about the first detected tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCDetect(VPADChan chan,
          uint32_t discoveryTimeout,
          NFCDetectCallbackFn callback,
          void *userContext);

/**
 * This will lock an area of blocks at the end of a 512-byte Type 1 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param numBlocks
 * The amount of blocks which should be locked.
 * Setting this to 16 would lock the last 16 blocks of the tag.
 * The maximum value is 48 which would lock blocks 16 to 63.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSetLockBitsForT1T(VPADChan chan,
                     uint8_t numBlocks,
                     NFCRawDataCallbackFn callback,
                     void *userContext);

/**
 * Read from a tag.
 * This will start by reading the locked pages from a Type 1 Tag (aka. lockedData).
 * Then it reads the NDEF tag data and returns the payload data from the first tnf 5 record.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCRead(VPADChan chan,
        uint32_t discoveryTimeout,
        NFCUid *uid,
        NFCUid *uidMask,
        NFCReadCallbackFn callback,
        void *userContext);

/**
 * Write to a tag.
 * This will create a NDEF structure and add the data to a TNF 5 record, then writes it to the tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param size
 * The size of the data.
 * 
 * \param data
 * A pointer to the data which will be copied to the NDEF payload.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCWrite(VPADChan chan,
         uint32_t discoveryTimeout,
         NFCUid *uid,
         NFCUid *uidMask,
         uint32_t size,
         void *data,
         NFCCallbackFn callback,
         void *userContext);

/**
 * Send a raw NFC command to a tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param startDiscovery
 * If \c TRUE, start tag discovery and activate the tag if found.
 * This will ignore any command data and receives the activation event data in the callback (see \link NFCGetUIDFromActivationEventData \endlink).
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param commandSize
 * Size of the command data.
 * 
 * \param responseSize
 * Size of the response data from the tag.
 * 
 * \param commandData
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawData(VPADChan chan,
               BOOL startDiscovery,
               uint32_t discoveryTimeout,
               uint32_t commandTimeout,
               uint32_t commandSize,
               uint32_t responseSize,
               void *commandData,
               NFCRawDataCallbackFn callback,
               void *userContext);

/**
 * Send a raw NFC command to a tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param startDiscovery
 * If \c TRUE, start tag discovery and activate the tag if found.
 * This will ignore any command data and receives the activation event data in the callback (see \link NFCGetUIDFromActivationEventData \endlink).
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param commandSize
 * Size of the command data.
 * 
 * \param responseSize
 * Size of the response data from the tag.
 * 
 * \param commandData
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param disableCRC
 * \c TRUE if the CRC check should be disabled.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawDataEx(VPADChan chan,
                 BOOL startDiscovery,
                 uint32_t discoveryTimeout,
                 uint32_t commandTimeout,
                 uint32_t commandSize,
                 uint32_t responseSize,
                 void *commandData,
                 BOOL disableCRC,
                 NFCRawDataCallbackFn callback,
                 void *userContext);

/**
 * Send a raw NFC command to a tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param startDiscovery
 * If \c TRUE, start tag discovery and activate the tag if found.
 * This will ignore any command data and receives the activation event data in the callback (see \link NFCGetUIDFromActivationEventData \endlink).
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param commandSize
 * Size of the command data.
 * 
 * \param responseSize
 * Size of the response data from the tag.
 * 
 * \param commandData
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param disableCRC
 * \c TRUE if the CRC check should be disabled.
 * 
 * \param techMask
 * One or more technology masks which should be used OR'd together.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawDataEx2(VPADChan chan,
                  BOOL startDiscovery,
                  uint32_t discoveryTimeout,
                  uint32_t commandTimeout,
                  uint32_t commandSize,
                  uint32_t responseSize,
                  void *commandData,
                  BOOL disableCRC,
                  NFCTechnologyMask techMask,
                  NFCRawDataCallbackFn callback,
                  void *userContext);

/**
 * Send a raw NFC command to a tag.
 * Starts tag discovery and activation before sending the command data.
 * Note: This forces \link NFC_TECHNOLOGY_MASK_F \endlink, see \link NFCSendRawDataWithPrePollingEx \endlink for a generic version.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param startDiscovery
 * If \c TRUE, start tag discovery and activate the tag if found, before sending the command data.
 * If \c FALSE this will behave exactly like \link NFCSendRawData \endlink.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param commandSize
 * Size of the command data.
 * 
 * \param responseSize
 * Size of the response data from the tag.
 * 
 * \param commandData
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawDataWithPrePolling(VPADChan chan,
                             BOOL startDiscovery,
                             uint32_t discoveryTimeout,
                             uint32_t commandTimeout,
                             uint32_t commandSize,
                             uint32_t responseSize,
                             void *commandData,
                             NFCRawDataCallbackFn callback,
                             void *userContext);

/**
 * Send a raw NFC command to a tag.
 * Starts tag discovery and activation before sending the command data.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param startDiscovery
 * If \c TRUE, start tag discovery and activate the tag if found, before sending the command data.
 * If \c FALSE this will behave exactly like \link NFCSendRawData \endlink.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param commandSize
 * Size of the command data.
 * 
 * \param responseSize
 * Size of the response data from the tag.
 * 
 * \param commandData
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawDataWithPrePollingEx(VPADChan chan,
                               BOOL startDiscovery,
                               uint32_t discoveryTimeout,
                               uint32_t commandTimeout,
                               uint32_t commandSize,
                               uint32_t responseSize,
                               void *commandData,
                               NFCRawDataCallbackFn callback,
                               void *userContext);

/**
 * Send two raw NFC commands to an activated tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param command0Timeout,command1Timeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param command0Size,command1Size
 * Size of the command data.
 * 
 * \param response0Size,response1Size
 * Size of the response data from the tag.
 * 
 * \param command0Data,command1Size
 * Pointer to the command data.
 * Note: The crc should not be included in the command and will be appended automatically.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSendRawDataTwice(VPADChan chan,
                    uint32_t command0Timeout,
                    uint32_t command0Size,
                    uint32_t response0Size,
                    void *command0Data,
                    uint32_t command1Timeout,
                    uint32_t command1Size,
                    uint32_t response1Size,
                    void *command1Data,
                    NFCRawDataTwiceCallbackFn callback,
                    void *userContext);

/**
 * Check if the tag is NDEF Formatable. If yes, format the tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCFormat(VPADChan chan,
          uint32_t discoveryTimeout,
          NFCUid *uid,
          NFCUid *uidMask,
          NFCCallbackFn callback,
          void *userContext);

/**
 * Obtain info about tags.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCGetTagInfo(VPADChan chan,
              uint32_t discoveryTimeout,
              NFCGetTagInfoCallbackFn callback,
              void *userContext);

/**
 * Obtain info about multiple tags.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCGetTagInfoMulti(VPADChan chan,
                   uint32_t discoveryTimeout,
                   NFCGetTagInfoMultiCallbackFn callback,
                   void *userContext);

/**
 * Check if a tag is still present.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCIsTagPresent(VPADChan chan,
                uint32_t discoveryTimeout,
                NFCUid *uid,
                NFCUid *uidMask,
                NFCCallbackFn callback,
                void *userContext);

/**
 * Make a Type 1 Tag read only by setting the RWA byte.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param readOnly
 * \c TRUE if read only, \c FALSE otherwise.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCSetReadOnly(VPADChan chan,
               uint32_t discoveryTimeout,
               NFCUid *uid,
               NFCUid *uidMask,
               BOOL readOnly,
               NFCCallbackFn callback,
               void *userContext);

/**
 * Read data from a Type 2 NTAG.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param version
 * A pointer to the expected response data from the NTAG GET_VERSION command.
 * The contents of this data is ignored for reads.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param numReads
 * The amount of read commands which should be peformed.
 * 
 * \param read0Start,read1Start,read2Start,read3Start
 * The start page address.
 * 
 * \param read0End,read1End,read2End,read3End
 * The end page address.
 * 
 * \param authenticate
 * \c TRUE if authentification using PWD_AUTH should be done.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCReadT2T(VPADChan chan,
           uint32_t discoveryTimeout,
           NFCUid *uid,
           NFCUid *uidMask,
           NFCNTAGVersion *version,
           uint32_t commandTimeout,
           uint8_t numReads,
           uint8_t read0Start, uint8_t read0End,
           uint8_t read1Start, uint8_t read1End,
           uint8_t read2Start, uint8_t read2End,
           uint8_t read3Start, uint8_t read3End,
           uint8_t authenticate,
           NFCReadT2TCallbackFn callback,
           void *userContext);

/**
 * Write data to a Type 2 NTAG.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param discoveryTimeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID.
 * 
 * \param version
 * A pointer to the expected response data from the NTAG GET_VERSION command.
 * 
 * \param commandTimeout
 * Timeout in ms after a command has been sent to the tag.
 * 
 * \param numWrites
 * The amount of write commands which should be peformed.
 * 
 * \param write0Start,write1Start,write2Start,write3Start
 * The start page address.
 * 
 * \param write0Size,write1Size,write2Size,write3Size
 * The size of the data to write in bytes.
 * 
 * \param write0Data,write1Data,write2Data,write3Data
 * The data which should be written (max. \c 0xF0 bytes per write).
 * 
 * \param activationStart
 * Page address where activation/deactivation should be performed
 * 
 * \param deactivationData
 * Pointer to the deactivation data
 * 
 * \param activationData
 * Pointer to the activation data
 * 
 * \param authenticate
 * \c TRUE if (custom?) authentification using PWD_AUTH should be done.
 * 
 * \param activate
 * \c TRUE if activation should be done.
 * This will write the deactivation data to the activation start before performing any writes.
 * After writing is completed the activation data will be written to the activation start.
 * If writing fails at any point the activation data can be checked to ensure writing has completed.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \return
 * 0 on success.
 */
NFCError
NFCWriteT2T(VPADChan chan,
            uint16_t discoveryTimeout,
            NFCUid *uid,
            NFCUid *uidMask,
            NFCNTAGVersion *version,
            uint32_t commandTimeout,
            uint8_t numWrites,
            uint8_t write0Start, uint8_t write0Size, void *write0Data,
            uint8_t write1Start, uint8_t write1Size, void *write1Data,
            uint8_t write2Start, uint8_t write2Size, void *write2Data,
            uint8_t write3Start, uint8_t write3Size, void *write3Data,
            uint8_t activationStart, uint32_t *deactivationData, uint32_t *activationData,
            uint8_t authenticate, uint8_t activate,
            NFCCallbackFn callback,
            void *userContext);

/**
 * Get the UID and other parameters from activation event data.
 * 
 * \param data
 * Pointer to the activation event data returned by \link NFCRawDataCallbackFn \endlink if \c startDiscovery is true.
 * 
 * \param outProtocol
 * Pointer to write the protocol to.
 * 
 * \param outTechnology
 * Pointer to write the technology to.
 * 
 * \param outUidSize
 * Pointer to write the UID size to.
 * 
 * \param outUid
 * Pointer to write the UID to (max. 10 bytes).
 */
void
NFCGetUIDFromActivationEventData(void *data,
                                 NFCProtocol *outProtocol,
                                 NFCTechnology *outTechnology,
                                 uint8_t *outUidSize,
                                 uint8_t *outUid);

/**
 * Abort and call pending callbacks.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NFCError
__NFCSystemAbort(VPADChan chan);

#ifdef __cplusplus
}
#endif

/** @} */
