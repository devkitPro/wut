#pragma once
#include <wut.h>

/**
 * \defgroup nn_spm
 * \ingroup nn_spm
 * Functions for extended storage (see nn::spm)
 * @{
 */

#ifdef __cplusplus

#include <cstring>

namespace nn {
namespace spm {

enum StorageType : uint32_t
{
   STORAGE_TYPE_RAW,
   STORAGE_TYPE_WFS,
};

using StorageIndex = uint64_t;

struct VolumeId
{
   VolumeId() = default;

   VolumeId(char const* id){
      strncpy(this->id, id, sizeof(this->id));
   }

   /**
    * Compares this VolumeId with another one
    *
    * \return
    * 0 if equal
    */
   int32_t
   Compare(VolumeId const& other) const
       asm("Compare__Q3_2nn3spm8VolumeIdCFRCQ3_2nn3spm8VolumeId");

   char id[16];
};
WUT_CHECK_SIZE(VolumeId, 0x10);

struct StorageListItem
{
   StorageIndex index;
   WUT_UNKNOWN_BYTES(0x04);
   StorageType type;
};
WUT_CHECK_OFFSET(StorageListItem, 0x00, index);
WUT_CHECK_OFFSET(StorageListItem, 0x0c, type);
WUT_CHECK_SIZE(StorageListItem, 0x10);

struct StorageInfo
{
   //! The mount path (e.g. "/vol/storage_usb01")
   char path[0x280];
   //! The connection type (e.g. "usb")
   char connection_type_string[8];
   //! The drive format (e.g. "raw" / "wfs")
   char format_string[8];
   WUT_UNKNOWN_BYTES(4);
   StorageType type;
   VolumeId volumeId;
};
WUT_CHECK_OFFSET(StorageInfo, 0x000, path);
WUT_CHECK_OFFSET(StorageInfo, 0x280, connection_type_string);
WUT_CHECK_OFFSET(StorageInfo, 0x288, format_string);
WUT_CHECK_OFFSET(StorageInfo, 0x294, type);
WUT_CHECK_OFFSET(StorageInfo, 0x298, volumeId);
WUT_CHECK_SIZE(StorageInfo, 0x2a8);

void
Initialize()
   asm("Initialize__Q2_2nn3spmFv");

void
Finalize()
   asm("Finalize__Q2_2nn3spmFv");

void
SetAutoFatal(bool enabled)
   asm("SetAutoFatal__Q2_2nn3spmFb");

/**
 * Sets the storage drive which should be used for extended storage
 *
 * \return
 * 0 on success.
 */
int32_t
SetExtendedStorage(StorageIndex* index)
   asm("SetExtendedStorage__Q2_2nn3spmFQ3_2nn3spm12StorageIndex");

/**
 * Sets the id of the default extended storage drive
 */
void
SetDefaultExtendedStorageVolumeId(VolumeId const& id)
   asm("SetDefaultExtendedStorageVolumeId__Q2_2nn3spmFRCQ3_2nn3spm8VolumeId");

/**
 * Gets the id of the default extended storage drive
 */
void
GetDefaultExtendedStorageVolumeId(VolumeId* id)
   asm("GetDefaultExtendedStorageVolumeId__Q2_2nn3spmFv");

bool
GetPreviousExtendedStorageVolumeId(bool*, VolumeId* outVolumeId)
   asm("GetPreviousExtendedStorageVolumeId__Q2_2nn3spmFPbPQ3_2nn3spm8VolumeId");

bool
FindStorageByVolumeId(StorageIndex* outIndex, VolumeId const& volumeId)
   asm("FindStorageByVolumeId__Q2_2nn3spmFPQ3_2nn3spm12StorageIndexRCQ3_2nn3spm8VolumeId");

int32_t
GetExtendedStorageIndex(StorageIndex* outIndex)
   asm("GetExtendedStorageIndex__Q2_2nn3spmFPQ3_2nn3spm12StorageIndex");

int32_t
GetStorageList(StorageListItem* items, uint32_t maxNumItems)
   asm("GetStorageList__Q2_2nn3spmFPQ3_2nn3spm15StorageListItemUi");

int32_t
GetStorageInfo(StorageInfo* outInfo, StorageIndex* index)
   asm("GetStorageInfo__Q2_2nn3spmFPQ3_2nn3spm11StorageInfoQ3_2nn3spm12StorageIndex");

/**
 * Reads the first 512 bytes of the storage head into the buffer
 *
 * \return
 * 0 on success.
 */
int32_t
ReadRawStorageHead512(StorageIndex* index, char* outBuffer)
   asm("ReadRawStorageHead512__Q2_2nn3spmFQ3_2nn3spm12StorageIndexPc");

/**
 * 
 * \param isPcFormatted
 * True if the drive contains a valid MBR with at least one active partition
 *
 * \return
 * 0 on success.
 */
int32_t
IsStorageMaybePcFormatted(bool* isPcFormatted, StorageIndex* index)
   asm("IsStorageMaybePcFormatted__Q2_2nn3spmFPbQ3_2nn3spm12StorageIndex");

/**
 * 
 * \param isWfsFormatted
 * True if the drive does not contain a valid MBR
 *
 * \return
 * 0 on success.
 */
int32_t
IsStorageMaybeWfsFormatted(bool* isWfsFormatted, StorageIndex* index)
   asm("IsStorageMaybeWfsFormatted__Q2_2nn3spmFPbQ3_2nn3spm12StorageIndex");

};
};

#endif
