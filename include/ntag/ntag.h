#pragma once
#include <wut.h>
#include <nfc/nfc.h>
#include <nn/ffl/miidata.h>

/**
 * \defgroup ntag_ntag
 * \ingroup ntag
 * Nintendo? Tag (NTAG).
 * NFC library for Amiibo and Pokemon Rumble U.
 * For a high-level Amiibo library see nn::nfp.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t NTAGError;
typedef struct NTAGFormatSettings NTAGFormatSettings;
typedef struct NTAGNoftHeader NTAGNoftHeader;
typedef struct NTAGInfoHeader NTAGInfoHeader;
typedef struct NTAGAreaHeader NTAGAreaHeader;
typedef struct NTAGAreaInfo NTAGAreaInfo;
typedef struct NTAGData NTAGData;
typedef struct NTAGInfoT2T NTAGInfoT2T;
typedef struct NTAGApplicationDataT2T NTAGApplicationDataT2T;
typedef struct NTAGRawDataT2T NTAGRawDataT2T;
typedef struct NTAGRawDataContainerT2T NTAGRawDataContainerT2T;
typedef struct NTAGDataT2T NTAGDataT2T;

struct NTAGFormatSettings
{
   uint8_t version;
   WUT_PADDING_BYTES(0x3);
   uint32_t makerCode;
   uint32_t identifyCode;
   WUT_PADDING_BYTES(0x1C);
};
WUT_CHECK_OFFSET(NTAGFormatSettings, 0x0, version);
WUT_CHECK_OFFSET(NTAGFormatSettings, 0x4, makerCode);
WUT_CHECK_OFFSET(NTAGFormatSettings, 0x8, identifyCode);
WUT_CHECK_SIZE(NTAGFormatSettings, 0x28);

struct WUT_PACKED NTAGNoftHeader
{
   uint32_t magic;
   uint8_t version;
   uint16_t writeCount;
   uint8_t unknown;
};
WUT_CHECK_OFFSET(NTAGNoftHeader, 0x0, magic);
WUT_CHECK_OFFSET(NTAGNoftHeader, 0x4, version);
WUT_CHECK_OFFSET(NTAGNoftHeader, 0x5, writeCount);
WUT_CHECK_OFFSET(NTAGNoftHeader, 0x7, unknown);
WUT_CHECK_SIZE(NTAGNoftHeader, 0x8);

struct NTAGInfoHeader
{
   uint16_t rwHeaderOffset;
   uint16_t rwSize;
   uint16_t roHeaderOffset;
   uint16_t roSize;
   NFCUid uid;
   uint8_t formatVersion;
};
WUT_CHECK_OFFSET(NTAGInfoHeader, 0x0, rwHeaderOffset);
WUT_CHECK_OFFSET(NTAGInfoHeader, 0x2, rwSize);
WUT_CHECK_OFFSET(NTAGInfoHeader, 0x4, roHeaderOffset);
WUT_CHECK_OFFSET(NTAGInfoHeader, 0x6, roSize);
WUT_CHECK_OFFSET(NTAGInfoHeader, 0x8, uid);
WUT_CHECK_OFFSET(NTAGInfoHeader, 0xF, formatVersion);
WUT_CHECK_SIZE(NTAGInfoHeader, 0x10);

struct NTAGAreaHeader
{
   uint16_t magic;
   uint16_t offset;
   uint16_t size;
   WUT_PADDING_BYTES(0x2);
   uint32_t makerCode;
   uint32_t identifyCode;
};
WUT_CHECK_OFFSET(NTAGAreaHeader, 0x0, magic);
WUT_CHECK_OFFSET(NTAGAreaHeader, 0x2, offset);
WUT_CHECK_OFFSET(NTAGAreaHeader, 0x4, size);
WUT_CHECK_OFFSET(NTAGAreaHeader, 0x8, makerCode);
WUT_CHECK_OFFSET(NTAGAreaHeader, 0xC, identifyCode);
WUT_CHECK_SIZE(NTAGAreaHeader, 0x10);

struct NTAGAreaInfo
{
   void *data;
   uint16_t size;
   WUT_PADDING_BYTES(0x2);
   uint32_t makerCode;
   uint32_t identifyCode;
   WUT_PADDING_BYTES(0x20);
};
WUT_CHECK_OFFSET(NTAGAreaInfo, 0x0, data);
WUT_CHECK_OFFSET(NTAGAreaInfo, 0x4, size);
WUT_CHECK_OFFSET(NTAGAreaInfo, 0x8, makerCode);
WUT_CHECK_OFFSET(NTAGAreaInfo, 0xC, identifyCode);
WUT_CHECK_SIZE(NTAGAreaInfo, 0x30);

struct NTAGData
{
   NFCUid uid;
   uint8_t readOnly;
   uint8_t formatVersion;
   WUT_PADDING_BYTES(0x3);
   NTAGAreaInfo rwInfo;
   NTAGAreaInfo roInfo;
   WUT_PADDING_BYTES(0x20);
};
WUT_CHECK_OFFSET(NTAGData, 0x00, uid);
WUT_CHECK_OFFSET(NTAGData, 0x07, readOnly);
WUT_CHECK_OFFSET(NTAGData, 0x08, formatVersion);
WUT_CHECK_OFFSET(NTAGData, 0x0C, rwInfo);
WUT_CHECK_OFFSET(NTAGData, 0x3C, roInfo);
WUT_CHECK_SIZE(NTAGData, 0x8C);

struct WUT_PACKED NTAGInfoT2T
{
   uint8_t magic;
   uint16_t writes;
   uint8_t figureVersion;
   uint8_t flags;
   uint8_t characterID[3];
   uint16_t numberingID;
   uint8_t figureType;
   uint8_t seriesID;
   uint32_t unknown;
   uint16_t applicationAreaWrites;
   uint16_t crcCounter;
   uint32_t crc;
   uint8_t fontRegion;
   uint16_t name[10];
   FFLStoreData mii;
   uint8_t country;
   uint16_t setupDate;
   uint16_t lastWriteDate;
   uint32_t accessID;
   uint64_t titleID;
   //! First 0x22 bytes contain NX specific extensions
   uint8_t reserved[0x1FC];
};
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x00, magic);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x01, writes);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x03, figureVersion);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x04, flags);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x05, characterID);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x08, numberingID);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x0A, figureType);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x0B, seriesID);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x0C, unknown);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x10, applicationAreaWrites);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x12, crcCounter);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x14, crc);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x18, fontRegion);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x19, name);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x2D, mii);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x8D, country);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x8E, setupDate);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x90, lastWriteDate);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x92, accessID);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x96, titleID);
WUT_CHECK_OFFSET(NTAGInfoT2T, 0x9E, reserved);
WUT_CHECK_SIZE(NTAGInfoT2T, 0x29a);

struct NTAGApplicationDataT2T
{
   uint16_t size;
   uint8_t data[0xD8];
};
WUT_CHECK_OFFSET(NTAGApplicationDataT2T, 0x00, size);
WUT_CHECK_OFFSET(NTAGApplicationDataT2T, 0x02, data);
WUT_CHECK_SIZE(NTAGApplicationDataT2T, 0xDA);

struct NTAGRawDataT2T
{
   uint8_t uid[9];
   uint8_t internal;
   uint8_t lockBytes[2];
   uint8_t capabilityContainer[4];
   struct WUT_PACKED
   {
      uint8_t magic;
      uint16_t writes;
      uint8_t figureVersion;
      uint8_t flags;
      uint8_t country;
      uint16_t crcCounter;
      uint16_t setupDate;
      uint16_t lastWriteDate;
      uint32_t crc;
      uint16_t name[10];
   } section0;
   struct WUT_PACKED
   {
      uint8_t tagHmac[0x20];
      uint8_t characterID[3];
      uint8_t figureType;
      uint16_t numberingID;
      uint8_t seriesID;
      uint8_t formatVersion;
      uint32_t unknown;
      uint8_t keygenSalt[0x20];
      uint8_t dataHmac[0x20];
   } section1;
   struct WUT_PACKED
   {
      FFLStoreData mii;
      uint64_t titleID;
      uint16_t applicationAreaWrites;
      uint32_t accessID;
      uint8_t reserved[0x22];
   } section2;
   uint8_t applicationData[0xD8];
   uint8_t dynamicLock[3];
   uint8_t reserved0;
   uint8_t cfg0[4];
   uint8_t cfg1[4];
   uint8_t pwd[4];
   uint8_t pack[2];
   uint8_t reserved1[2];
};
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x000, uid);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x009, internal);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x00A, lockBytes);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x00C, capabilityContainer);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x010, section0.magic);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x011, section0.writes);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x013, section0.figureVersion);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x014, section0.flags);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x015, section0.country);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x016, section0.crcCounter);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x018, section0.setupDate);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x01A, section0.lastWriteDate);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x01C, section0.crc);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x020, section0.name);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x034, section1.tagHmac);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x054, section1.characterID);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x057, section1.figureType);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x058, section1.numberingID);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x05A, section1.seriesID);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x05B, section1.formatVersion);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x05C, section1.unknown);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x060, section1.keygenSalt);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x080, section1.dataHmac);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x0A0, section2.mii);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x100, section2.titleID);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x108, section2.applicationAreaWrites);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x10A, section2.accessID);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x10E, section2.reserved);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x130, applicationData);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x208, dynamicLock);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x20B, reserved0);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x20C, cfg0);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x210, cfg1);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x214, pwd);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x218, pack);
WUT_CHECK_OFFSET(NTAGRawDataT2T, 0x21A, reserved1);
WUT_CHECK_SIZE(NTAGRawDataT2T, 0x21C);

struct NTAGRawDataContainerT2T
{
   uint16_t size;
   NTAGRawDataT2T data;
};
WUT_CHECK_OFFSET(NTAGRawDataContainerT2T, 0x00, size);
WUT_CHECK_OFFSET(NTAGRawDataContainerT2T, 0x02, data);
WUT_CHECK_SIZE(NTAGRawDataContainerT2T, 0x21E);

struct NTAGDataT2T
{
   NFCTagInfo tagInfo;
   uint8_t formatVersion;
   NTAGInfoT2T info;
   NTAGApplicationDataT2T appData;
   NTAGRawDataContainerT2T raw;
   WUT_PADDING_BYTES(0x20);
};
WUT_CHECK_OFFSET(NTAGDataT2T, 0x000, tagInfo);
WUT_CHECK_OFFSET(NTAGDataT2T, 0x02D, formatVersion);
WUT_CHECK_OFFSET(NTAGDataT2T, 0x02E, info);
WUT_CHECK_OFFSET(NTAGDataT2T, 0x2C8, appData);
WUT_CHECK_OFFSET(NTAGDataT2T, 0x3A2, raw);
WUT_CHECK_SIZE(NTAGDataT2T, 0x5E0);

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
typedef void (*NTAGCallbackFn)(VPADChan chan,
                               NTAGError error,
                               void *userContext);

/**
 * Callback function for \link NTAGRead \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param data
 * The result of the data read.
 * 
 * \param userContext
 * User provided value.
 */
typedef void (*NTAGReadCallbackFn)(VPADChan chan,
                                   NTAGError error,
                                   NTAGData *data,
                                   void *userContext);

/**
 * Callback function for \link NTAGReadT2T \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param data
 * The result of the data read.
 * 
 * \param userContext
 * User provided value.
 */
typedef void (*NTAGReadT2TCallbackFn)(VPADChan chan,
                                      NTAGError error,
                                      NTAGDataT2T *data,
                                      void *userContext);

/**
 * Callback function for \link NTAGReadT2TRawData \endlink.
 * 
 * \param chan
 * The channel this callback is coming from.
 * 
 * \param error
 * 0 on success.
 * 
 * \param tagInfo
 * The tag info of the read tag.
 * 
 * \param data
 * The result of the data read.
 * 
 * \param userContext
 * User provided value.
 */
typedef void (*NTAGReadT2TRawDataCallbackFn)(VPADChan chan,
                                             NTAGError error,
                                             NFCTagInfo *tagInfo,
                                             NTAGRawDataContainerT2T *rawData,
                                             void *userContext);

/**
 * Initializes the NTAG library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGInit(VPADChan chan);

/**
 * Initializes the NTAG library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGInitEx(VPADChan chan);

/**
 * Check if NTAG is initialized.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * \c TRUE if initialized, \c FALSE otherwise.
 */
BOOL
NTAGIsInit(VPADChan chan);

/**
 * Process NTAG.
 * This needs to be called periodically and will call pending callbacks.
 * 
 * \param chan
 * The DRC channel to use.
 */
void
NTAGProc(VPADChan chan);

/**
 * Shutdown the NTAG library.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGShutdown(VPADChan chan);

/**
 * Abort pending NTAG operations.
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
NTAGError
NTAGAbort(VPADChan chan,
          NTAGCallbackFn callback,
          void *userContext);

/**
 * Start tag discovery and provide info about the first detected tag.
 * 
 * \note
 * The original function contains an error and calls itself recursively.
 * This inline version uses \link NFCDetect \endlink instead.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
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
static inline NFCError
NTAGDetect(VPADChan chan,
           uint32_t timeout,
           NFCDetectCallbackFn callback,
           void *userContext)
{
   return NFCDetect(chan, timeout, callback, userContext);
}
// NTAGError
// NTAGDetect(VPADChan chan,
//            uint32_t timeout,
//            NTAGDetectCallbackFn callback,
//            void *userContext);

/**
 * Format a Type 1 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param rwSize
 * The size of the data which should be written to initialize the RW area.
 * 
 * \param rwData
 * A pointer to the data which should be written to initialize the RW area.
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
NTAGError
NTAGFormat(VPADChan chan,
           uint32_t timeout,
           NFCUid *uid,
           uint32_t rwSize,
           void *rwData,
           NTAGCallbackFn callback,
           void *userContext);

/**
 * Make a Type 1 Tag read only by setting the RWA byte.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag (can be \c NULL).
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID (can be \c NULL).
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
NTAGError
NTAGSetReadOnly(VPADChan chan,
                uint32_t timeout,
                NFCUid *uid,
                NFCUid *uidMask,
                BOOL readOnly,
                NTAGCallbackFn callback,
                void *userContext);

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
NTAGSetTagDetectCallback(VPADChan chan,
                         NFCTagDetectCallbackFn callback,
                         void *userContext);

/**
 * Set the format settings which should be checked against while reading from Type 1 tags.
 * 
 * \param settings
 * A pointer from which the settings should be copied from.
 */
void
NTAGSetFormatSettings(NTAGFormatSettings *settings);

/**
 * Read from a Type 1 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag (can be \c NULL).
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID (can be \c NULL).
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
NTAGError
NTAGRead(VPADChan chan,
         uint32_t timeout,
         NFCUid *uid,
         NFCUid *uidMask,
         NTAGReadCallbackFn callback,
         void *userContext);

/**
 * Read from a Type 2 Tag and decrypt & convert the data.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag (can be \c NULL).
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID (can be \c NULL).
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
NTAGError
NTAGReadT2T(VPADChan chan,
            uint32_t timeout,
            NFCUid *uid,
            NFCUid *uidMask,
            NTAGReadT2TCallbackFn callback,
            void *userContext);

/**
 * Read raw data from a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag (can be \c NULL).
 * 
 * \param uidMask
 * The UID of the tag will be masked with this mask before compared to the expected UID (can be \c NULL).
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
NTAGError
NTAGReadT2TRawData(VPADChan chan,
                   uint32_t timeout,
                   NFCUid *uid,
                   NFCUid *uidMask,
                   NTAGReadT2TRawDataCallbackFn callback,
                   void *userContext);

/**
 * Write to the RW area of a Type 1 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param rwSize
 * The size of the data which should be written to the RW area.
 * 
 * \param rwData
 * A pointer to the data which should be written to the RW area.
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
NTAGError
NTAGWrite(VPADChan chan,
          uint32_t timeout,
          NFCUid *uid,
          uint32_t rwSize,
          void *rwData,
          NTAGCallbackFn callback,
          void *userContext);

/**
 * Write to a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param dataContainer
 * A pointer to the container which contains the data which should be written to the tag.
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
NTAGError
NTAGWriteT2T(VPADChan chan,
             uint32_t timeout,
             NFCUid *uid,
             NTAGRawDataContainerT2T *dataContainer,
             NTAGCallbackFn callback,
             void *userContext);

/**
 * Write to the configuration fields of a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param cfg0
 * A pointer to the data which should be written to the CFG0 field.
 * 
 * \param cfg1
 * A pointer to the data which should be written to the CFG1 field.
 * 
 * \param pwd
 * A pointer to the data which should be written to the PWD field.
 * 
 * \param pack
 * A pointer to the data which should be written to the PACK field.
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
NTAGError
NTAGWriteT2TConfigArea(VPADChan chan,
                       uint32_t timeout,
                       NFCUid *uid,
                       uint32_t *cfg0,
                       uint32_t *cfg1,
                       uint32_t *pwd,
                       uint16_t *pack,
                       NTAGCallbackFn callback,
                       void *userContext);

/**
 * Write to the lock bytes of a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param lockBytes
 * A pointer to the data which should be written to the lock bytes.
 * 
 * \param dynamicLock
 * A pointer to the data which should be written to the dynamic lock bytes.
 * 
 * \param cc
 * A pointer to the data which should be written to the capability container.
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
NTAGError
NTAGWriteT2TLockArea(VPADChan chan,
                     uint32_t timeout,
                     NFCUid *uid,
                     uint32_t *lockBytes,
                     uint32_t *dynamicLock,
                     uint32_t *cc,
                     NTAGCallbackFn callback,
                     void *userContext);

/**
 * Write raw data to a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param data
 * A pointer to the data which should be written to the tag.
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
NTAGError
NTAGWriteT2TRawData(VPADChan chan,
                    uint32_t timeout,
                    NFCUid *uid,
                    NTAGRawDataT2T *data,
                    NTAGCallbackFn callback,
                    void *userContext);

/**
 * Write raw data to a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param data
 * A pointer to the data which should be written to the tag.
 * 
 * \param callback
 * A pointer to the callback function.
 * 
 * \param userContext
 * User provided value which will be passed to the callback.
 * 
 * \param authenticate
 * \c TRUE if authentification using PWD_AUTH should be done.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGWriteT2TRawDataEx(VPADChan chan,
                      uint32_t timeout,
                      NFCUid *uid,
                      NTAGRawDataT2T *data,
                      NTAGCallbackFn callback,
                      void *userContext,
                      uint8_t authenticate);

/**
 * Convert & encrypt data and write it to a Type 2 Tag.
 * 
 * \param chan
 * The DRC channel to use.
 * 
 * \param timeout
 * Timeout in ms until tag discovery is cancelled.
 * 
 * \param uid
 * The UID of the expected tag.
 * 
 * \param data
 * A pointer to the data which should be written to the tag.
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
NTAGError
NTAGWriteT2TWithConvert(VPADChan chan,
                        uint32_t timeout,
                        NFCUid *uid,
                        NTAGDataT2T *data,
                        NTAGCallbackFn callback,
                        void *userContext);

/**
 * Convert and encrypt data.
 * 
 * \param out
 * A pointer to write the encrypted data to the raw field. This can be the same as \param in.
 * 
 * \param in
 * A pointer to read the data from. This can be the same as \param out.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGConvertT2T(NTAGDataT2T *out,
               NTAGDataT2T *in);

/**
 * Parse the headers from Type 1 Tag data.
 * 
 * \param data
 * The data from which the headers should be parsed from.
 * 
 * \param outNoftHeader
 * A pointer to which the NOFT header should be copied to.
 * 
 * \param outInfoHeader
 * A pointer to which the info header should be copied to.
 * 
 * \param outRwHeader
 * A pointer to which the RW header should be copied to.
 * 
 * \param outRoHeader
 * A pointer to which the RO header should be copied to.
 * 
 * \return
 * 0 on success.
 */
NTAGError
NTAGParseHeader(void *data,
                NTAGNoftHeader *outNoftHeader,
                NTAGInfoHeader *outInfoHeader,
                NTAGAreaHeader *outRwHeader,
                NTAGAreaHeader *outRoHeader);

#ifdef __cplusplus
}
#endif

/** @} */
