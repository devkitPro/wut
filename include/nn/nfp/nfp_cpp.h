#pragma once
#include <wut.h>
#include <nn/result.h>
#include <nn/ffl/miidata.h>
#include <coreinit/event.h>
#include <nfc/nfc.h>

/**
 * \defgroup nn_nfp
 * \ingroup nn_nfp
 * Nintendo Figurine (amiibo) Platform library (see nn::nfp)
 * @{
 */

#ifdef __cplusplus

namespace nn {

namespace nfp {

//! NN_NFP result descriptions for \link nn::Result::GetDescription \endlink.
enum ResultDescription 
{
   // Usage results
   RESULT_OUT_OF_RANGE                 = 0x03700,
   RESULT_INVALID_PARAM                = 0x03780,
   RESULT_INVALID_ALIGNMENT            = 0x03800,

   // Status results
   RESULT_INVALID_STATE                = 0x06400,
   RESULT_INVALID_TAG                  = 0x0c800,
   RESULT_INVALID_TAG_INFO             = 0x0ca80,
   RESULT_NO_BACKUPENTRY               = 0x0e580,
   RESULT_NO_REGISTER_INFO             = 0x10900,
   RESULT_APP_AREA_MISSING             = 0x10400,
   RESULT_APP_AREA_TAGID_MISMATCH      = 0x11d00,
   RESULT_APP_AREA_ALREADY_EXISTS      = 0x10e00,
   RESULT_APP_AREA_ACCESS_ID_MISMATCH  = 0x11300,
   RESULT_NO_BACKUP_SAVEDATA           = 0x38880,
   RESULT_SYSTEM_ERROR                 = 0x3e880,

   // Fatal results
   RESULT_FATAL                        = 0x5db00,
};

enum class NfpState : uint32_t
{
   //! nn_nfp is uninitialized
   Uninitialized  = 0,
   //! nn_nfp has been initialized
   Initialized    = 1,
   //! Searching for a tag
   Searching      = 2,
   //! A tag has been found
   Found          = 3,
   //! Tag was removed
   Removed        = 4,
   //! The tag is mounted
   Mounted        = 5,
   Unknown6       = 6,
   //! The tag was mounted in ROM mode
   MountedROM     = 7,
};
WUT_CHECK_SIZE(NfpState, 0x4);

enum class AdminFlags : uint8_t
{
   //! The tag was registered and contains register info 
   IsRegistered        = 1 << 0,
   //! The tag contains an application area
   HasApplicationData  = 1 << 1,
};
WUT_CHECK_SIZE(AdminFlags, 0x1);

enum class TagType : uint8_t
{
   Unknown  = 0,
   Type1Tag = 1 << 0,
   Type2Tag = 1 << 1,
   Type3Tag = 1 << 2,
   Iso15693 = 1 << 5,
};
WUT_CHECK_SIZE(TagType, 0x1);

struct Date
{
   //! Year (Starting at 0)
   uint16_t year;
   //! Month (0 - 11)
   uint8_t month;
   //! Day (0 - 30)
   uint8_t day;
};
WUT_CHECK_OFFSET(Date, 0x0, year);
WUT_CHECK_OFFSET(Date, 0x2, month);
WUT_CHECK_OFFSET(Date, 0x3, day);
WUT_CHECK_SIZE(Date, 0x4);

struct ApplicationAreaCreateInfo
{
   //! The access ID with which the area should be created
   uint32_t accessID;
   //! The initial data to write to the area
   void* data;
   //! The size of the data
   uint32_t size;
   //! reserved bytes, must be set to 0
   uint8_t reserved[0x30];
};
WUT_CHECK_OFFSET(ApplicationAreaCreateInfo, 0x0, accessID);
WUT_CHECK_OFFSET(ApplicationAreaCreateInfo, 0x4, data);
WUT_CHECK_OFFSET(ApplicationAreaCreateInfo, 0x8, size);
WUT_CHECK_OFFSET(ApplicationAreaCreateInfo, 0xC, reserved);
WUT_CHECK_SIZE(ApplicationAreaCreateInfo, 0x3C);

struct TagId
{
   //! The size of the id
   uint8_t size;
   //! The uid of the tag
   uint8_t uid[10];
};
WUT_CHECK_OFFSET(TagId, 0x0, size);
WUT_CHECK_OFFSET(TagId, 0x1, uid);
WUT_CHECK_SIZE(TagId, 0xB);

struct TagInfo
{
   //! The id of the tag
   TagId id;
   //! reserved bytes
   uint8_t reserved0[0x15];
   //! Technology (always \link NFC_TECHNOLOGY_A \endlink)
   NFCTechnology technology;
   //! Tag type (always \link TagType::Type2Tag \endlink)
   TagType tag_type;
   //! reserved bytes
   uint8_t reserved1[0x32];
};
WUT_CHECK_OFFSET(TagInfo, 0x0, id);
WUT_CHECK_OFFSET(TagInfo, 0xB, reserved0);
WUT_CHECK_OFFSET(TagInfo, 0x20, technology);
WUT_CHECK_OFFSET(TagInfo, 0x21, tag_type);
WUT_CHECK_OFFSET(TagInfo, 0x22, reserved1);
WUT_CHECK_SIZE(TagInfo, 0x54);

struct CommonInfo
{
   //! The date when the tag was last written to
   Date lastWriteDate;
   //! The amount of times this tag was written to
   uint16_t writes;
   //! The character id of the amiibo
   uint8_t characterID[3];
   //! The series this amiibo is from
   uint8_t seriesID;
   //! Numbering ID of the amiibo
   uint16_t numberingID;
   //! The type of this figure
   uint8_t figureType;
   //! The version of this figure (always 0x00)
   uint8_t figureVersion;
   //! The size of the application area
   uint16_t applicationAreaSize;
   //! reserved bytes
   uint8_t reserved[0x30];
};
WUT_CHECK_OFFSET(CommonInfo, 0x0, lastWriteDate);
WUT_CHECK_OFFSET(CommonInfo, 0x4, writes);
WUT_CHECK_OFFSET(CommonInfo, 0x6, characterID);
WUT_CHECK_OFFSET(CommonInfo, 0x9, seriesID);
WUT_CHECK_OFFSET(CommonInfo, 0xA, numberingID);
WUT_CHECK_OFFSET(CommonInfo, 0xC, figureType);
WUT_CHECK_OFFSET(CommonInfo, 0xD, figureVersion);
WUT_CHECK_OFFSET(CommonInfo, 0xE, applicationAreaSize);
WUT_CHECK_OFFSET(CommonInfo, 0x10, reserved);
WUT_CHECK_SIZE(CommonInfo, 0x40);

struct WUT_PACKED RegisterInfo
{
   //! The mii this figure was registered with
   FFLStoreData mii;
   //! The name of this amiibo
   uint16_t name[11];
   //! Font region
   uint8_t fontRegion;
   //! Country code
   uint8_t country;
   //! The date when the amiibo was registered
   Date registerDate;
   //! reserved bytes
   uint8_t reserved[0x2c];
};
WUT_CHECK_OFFSET(RegisterInfo, 0x0, mii);
WUT_CHECK_OFFSET(RegisterInfo, 0x60, name);
WUT_CHECK_OFFSET(RegisterInfo, 0x76, fontRegion);
WUT_CHECK_OFFSET(RegisterInfo, 0x77, country);
WUT_CHECK_OFFSET(RegisterInfo, 0x78, registerDate);
WUT_CHECK_OFFSET(RegisterInfo, 0x7C, reserved);
WUT_CHECK_SIZE(RegisterInfo, 0xA8);

struct WUT_PACKED ReadOnlyInfo
{
   //! The character id of the amiibo
   uint8_t characterID[3];
   //! The series this amiibo is from
   uint8_t seriesID;
   //! Numbering ID of the amiibo
   uint16_t numberingID;
   //! The type of this figure
   uint8_t figureType;
   //! reserved bytes
   uint8_t reserved[0x2f];
};
WUT_CHECK_OFFSET(ReadOnlyInfo, 0x0, characterID);
WUT_CHECK_OFFSET(ReadOnlyInfo, 0x3, seriesID);
WUT_CHECK_OFFSET(ReadOnlyInfo, 0x4, numberingID);
WUT_CHECK_OFFSET(ReadOnlyInfo, 0x6, figureType);
WUT_CHECK_OFFSET(ReadOnlyInfo, 0x7, reserved);
WUT_CHECK_SIZE(ReadOnlyInfo, 0x36);

// seems to be the same as ReadOnlyInfo
// maybe left over from an older library version?
using RomInfo = ReadOnlyInfo;
WUT_CHECK_SIZE(RomInfo, 0x36);

struct WUT_PACKED RegisterInfoSet
{
   //! The mii this figure will be registered to
   FFLStoreData mii;
   //! The name of this amiibo
   uint16_t name[11];
   //! Font region
   uint8_t fontRegion;
   //! reserved bytes, must be 0
   uint8_t reserved[0x2d];
};
WUT_CHECK_OFFSET(RegisterInfoSet, 0x0, mii);
WUT_CHECK_OFFSET(RegisterInfoSet, 0x60, name);
WUT_CHECK_OFFSET(RegisterInfoSet, 0x76, fontRegion);
WUT_CHECK_OFFSET(RegisterInfoSet, 0x77, reserved);
WUT_CHECK_SIZE(RegisterInfoSet, 0xA4);

struct WUT_PACKED AdminInfo
{
   //! The titleID of the application which wrote to the application data
   uint64_t titleID;
   //! The accessID of the current application area
   uint32_t accessID;
   //! The amount of times the application area was written to
   uint16_t applicationAreaWrites;
   //! Flags
   AdminFlags flags;
   //! The version of the amiibo format (always 0x02)
   uint8_t formatVersion;
   //! The platform which wrote to the amiibo (0x01 if Wii U)
   uint8_t platform;
   //! reserved bytes
   uint8_t reserved[0x2f];
};
WUT_CHECK_OFFSET(AdminInfo, 0x0, titleID);
WUT_CHECK_OFFSET(AdminInfo, 0x8, accessID);
WUT_CHECK_OFFSET(AdminInfo, 0xC, applicationAreaWrites);
WUT_CHECK_OFFSET(AdminInfo, 0xE, flags);
WUT_CHECK_OFFSET(AdminInfo, 0xF, formatVersion);
WUT_CHECK_OFFSET(AdminInfo, 0x10, platform);
WUT_CHECK_OFFSET(AdminInfo, 0x11, reserved);
WUT_CHECK_SIZE(AdminInfo, 0x40);

/**
 * Gets the state nfp is currently in.
 *
 * \return
 * The current NfpState.
 */
NfpState
GetNfpState()
   asm("GetNfpState__Q2_2nn3nfpFv");

/**
 * Initializes NFP.
 */
nn::Result
Initialize()
   asm("Initialize__Q2_2nn3nfpFv");

/**
 * Finalizes NFP.
 */
nn::Result
Finalize()
   asm("Finalize__Q2_2nn3nfpFv");

/**
 * Checks if the NFC Antenna can be used.
 * Note: This will re-initialize the library.
 * 
 * \return
 * Successful result if available.
 */
nn::Result
AntennaCheck()
   asm("AntennaCheck__Q2_2nn3nfpFv");

/**
 * Sets an event which will be signalled once a tag has been found.
 * Setting an event is not necessary and polling the NfpState can be done instead.
 * 
 * \param event
 * A pointer to an event which will be initialized by the library.
 */
nn::Result
SetActivateEvent(OSEvent *event)
   asm("SetActivateEvent__Q2_2nn3nfpFP7OSEvent");

/**
 * Sets an event which will be signalled once a tag has been lost.
 * Setting an event is not necessary and polling the NfpState can be done instead.
 * 
 * \param event
 * A pointer to an event which will be initialized by the library.
 */
nn::Result
SetDeactivateEvent(OSEvent *event)
   asm("SetDeactivateEvent__Q2_2nn3nfpFP7OSEvent");

/**
 * Starts searching for tags. 
 * Once a tag has been found the \c ActivateEvent will be signalled and the NfpState changes to \c Found .
 */
nn::Result
StartDetection()
   asm("StartDetection__Q2_2nn3nfpFv");

/**
 * Stops searching for tags. 
 * Any currently mounted tag will be unmounted and the \c DeactivateEvent will be signaled.
 */
nn::Result
StopDetection()
   asm("StopDetection__Q2_2nn3nfpFv");

/**
 * Mounts a found tag. 
 * 
 * The current NfpState must be \c Found before calling this function.
 */
nn::Result
Mount()
   asm("Mount__Q2_2nn3nfpFv");

/**
 * Mounts a found tag as read-only. 
 * 
 * The current NfpState must be \c Found before calling this function.
 */
nn::Result
MountReadOnly()
   asm("MountReadOnly__Q2_2nn3nfpFv");

/**
 * Mounts a found tag in ROM mode. 
 * 
 * The current NfpState must be \c Found before calling this function.
 */
nn::Result
MountRom()
   asm("MountRom__Q2_2nn3nfpFv");

/**
 * Writes any changes done while mounted to the tag.
 * 
 * The current state must be \c Mounted and not read-only.
 */
nn::Result
Flush()
   asm("Flush__Q2_2nn3nfpFv");

/**
 * Unmounts a currently mounted tag.
 * 
 * The current state must be \c Mounted or \c MountedROM .
 * If the tag was not removed the state changes to \c Found .
 * 
 * Note: This does not write any changes to the tag,
 * call \link Flush \endlink before unmounting to write changes.
 */
nn::Result
Unmount()
   asm("Unmount__Q2_2nn3nfpFv");

/**
 * Checks if the tag contains application data.
 * 
 * The current state must be \c Mounted.
 * 
 * \return
 * \c true if the tag contains an application area.
 */
bool
IsExistApplicationArea()
   asm("IsExistApplicationArea__Q2_2nn3nfpFv");

/**
 * Initializes a \c ApplicationAreaCreateInfo struct.
 * 
 * \param info
 * The struct which should be initialized.
 */
nn::Result
InitializeCreateInfo(ApplicationAreaCreateInfo *info)
   asm("InitializeCreateInfo__Q2_2nn3nfpFPQ3_2nn3nfp25ApplicationAreaCreateInfo");

/**
 * Initializes the application area of the tag.
 * 
 * The tag can not be read-only and the application area can not already exist.
 * The current state must be \c Mounted.
 * 
 * \param createInfo
 * The info with which the application area will be created.
 */
nn::Result
CreateApplicationArea(const ApplicationAreaCreateInfo &createInfo)
   asm("CreateApplicationArea__Q2_2nn3nfpFRCQ3_2nn3nfp25ApplicationAreaCreateInfo");

/**
 * Opens the application area for reading and writing.
 * 
 * The application area must exist.
 * The current state must be \c Mounted.
 * 
 * \param accessID
 * The accessID with which the application area was created.
 */
nn::Result
OpenApplicationArea(uint32_t accessID)
   asm("OpenApplicationArea__Q2_2nn3nfpFUi");

/**
 * Deletes the application area.
 * 
 * The application area must exist and the tag must not be read-only.
 * The current state must be \c Mounted.
 */
nn::Result
DeleteApplicationArea()
   asm("DeleteApplicationArea__Q2_2nn3nfpFv");

/**
 * Writes data to the opened application area.
 * 
 * The application area must be opened and the tag must not be read-only.
 * The current state must be \c Mounted.
 * 
 * \param data
 * A pointer to the data which will be written to the application area.
 * 
 * \param size
 * The size of the data which should be written
 * 
 * \param id
 * The tag id of the tag which the data should be written to.
 */
nn::Result
WriteApplicationArea(const void *data, uint32_t size, const TagId &id)
   asm("WriteApplicationArea__Q2_2nn3nfpFPCvUiRCQ3_2nn3nfp5TagId");

/**
 * Reads data from the opened application area.
 * 
 * The application area must be opened.
 * The current state must be \c Mounted.
 * 
 * \param data
 * A pointer to store the read data.
 * 
 * \param size
 * The size of the data which should be read.
 */
nn::Result
ReadApplicationArea(void *outData, uint32_t size)
   asm("ReadApplicationArea__Q2_2nn3nfpFPvUi");

/**
 * Initializes a \c RegisterInfoSet struct.
 * 
 * \param infoSet
 * The set which should be initialized.
 */
nn::Result
InitializeRegisterInfoSet(RegisterInfoSet *infoSet)
   asm("InitializeRegisterInfoSet__Q2_2nn3nfpFPQ3_2nn3nfp15RegisterInfoSet");

/**
 * Sets the register info of the mounted tag.
 * 
 * The current state must be \c Mounted and not read-only.
 * 
 * \param info
 * The register info which should be set.
 */
nn::Result
SetNfpRegisterInfo(const RegisterInfoSet &info)
   asm("SetNfpRegisterInfo__Q2_2nn3nfpFRCQ3_2nn3nfp15RegisterInfoSet");

/**
 * Gets the register info of the mounted tag.
 * 
 * The current state must be \c Mounted.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetNfpRegisterInfo(RegisterInfo *outInfo)
   asm("GetNfpRegisterInfo__Q2_2nn3nfpFPQ3_2nn3nfp12RegisterInfo");

/**
 * Deletes the register info of the mounted tag.
 * 
 * The current state must be \c Mounted and not read-only.
 */
nn::Result
DeleteNfpRegisterInfo()
   asm("DeleteNfpRegisterInfo__Q2_2nn3nfpFv");

/**
 * Gets the common info of the mounted tag.
 * 
 * The current state must be \c Mounted.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetNfpCommonInfo(CommonInfo *outInfo)
   asm("GetNfpCommonInfo__Q2_2nn3nfpFPQ3_2nn3nfp10CommonInfo");

/**
 * Gets the read only info of the mounted tag.
 * 
 * The current state must be \c Mounted.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetNfpReadOnlyInfo(ReadOnlyInfo *outInfo)
   asm("GetNfpReadOnlyInfo__Q2_2nn3nfpFPQ3_2nn3nfp12ReadOnlyInfo");

/**
 * Gets the admin info of the mounted tag.
 * 
 * The current state must be \c Mounted.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetNfpAdminInfo(AdminInfo *outInfo)
   asm("GetNfpAdminInfo__Q2_2nn3nfpFPQ3_2nn3nfp9AdminInfo");

/**
 * Gets the rom info of the mounted tag.
 * 
 * The current state must be \c Mounted or \c MountedROM.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetNfpRomInfo(RomInfo *outInfo)
   asm("GetNfpRomInfo__Q2_2nn3nfpFPQ3_2nn3nfp7RomInfo");

/**
 * Gets the tag info.
 * 
 * The current state must be \c Found, \c Mounted or \c MountedROM.
 * 
 * \param outInfo
 * A pointer to write the info to.
 */
nn::Result
GetTagInfo(TagInfo *outInfo)
   asm("GetTagInfo__Q2_2nn3nfpFPQ3_2nn3nfp7TagInfo");

/**
 * Formats a found tag.
 * Formatting will wipe the register info and application data.
 * 
 * The current state must be \c Found.
 * 
 * \param data
 * A pointer to data which gets written over the application area (can be \c NULL).
 * 
 * \param size
 * The size of the data (can be \c 0).
 */
nn::Result
Format(const uint8_t *data, int32_t size)
   asm("Format__Q2_2nn3nfpFPCUci");

nn::Result
Restore()
   asm("Restore__Q2_2nn3nfpFv");

/**
 * Converts a \link nn::Result \endlink to an error code.
 * 
 * \return
 * The error code.
 */
uint32_t
GetErrorCode(const nn::Result &res)
   asm("GetErrorCode__Q2_2nn3nfpFRCQ2_2nn6Result");

} //namespace nfp

} //namespace nn

#endif

/** @} */
