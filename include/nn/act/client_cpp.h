#pragma once
#include <wut.h>
#include <nn/result.h>
#include <nn/ffl/miidata.h>

/**
 * \defgroup nn_act_client Accounts Client API
 * \ingroup nn_act
 * Personal information and accounts service client managment (see nn::act)
 * @{
 */

#ifdef __cplusplus

namespace nn {

namespace act {

//https://github.com/decaf-emu/decaf-emu/blob/master/src/libdecaf/src/nn/act/nn_act_types.h

using SlotNo = uint8_t;
using LocalFriendCode = uint64_t;
using PersistentId = uint32_t;
using PrincipalId = uint32_t;
using SimpleAddressId = uint32_t;
using TransferrableId = uint64_t;

static constexpr size_t AccountIdSize = 17;
static constexpr size_t DeviceHashSize = 8;
static constexpr size_t NfsPasswordSize = 17;
static constexpr size_t MiiNameSize = 11;
static constexpr size_t UuidSize = 16;

//https://github.com/decaf-emu/decaf-emu/blob/master/src/libdecaf/src/cafe/libraries/nn_act/nn_act_client.cpp

nn::Result
Initialize(void)
   asm("Initialize__Q2_2nn3actFv");

nn::Result
Finalize(void)
   asm("Finalize__Q2_2nn3actFv");

//https://github.com/decaf-emu/decaf-emu/blob/master/src/libdecaf/src/cafe/libraries/nn_act/nn_act_clientstandardservice.cpp

nn::Result
GetAccountId(char outAccountId[AccountIdSize])
   asm("GetAccountId__Q2_2nn3actFPc");

nn::Result
GetAccountIdEx(char outAccountId[AccountIdSize], SlotNo slot)
   asm("GetAccountIdEx__Q2_2nn3actFPcUc");

nn::Result
GetBirthday(uint16_t* outYear, uint8_t* outMonth, uint8_t* outDay)
   asm("GetBirthday__Q2_2nn3actFPUsPUcT2");

nn::Result
GetBirthdayEx(uint16_t* outYear, uint8_t* outMonth, uint8_t* outDay, SlotNo slot)
   asm("GetBirthdayEx__Q2_2nn3actFPUsPUcT2Uc");

SlotNo
GetDefaultAccount(void)
   asm("GetDefaultAccount__Q2_2nn3actFv");

nn::Result
GetDeviceHash(char outHash[DeviceHashSize])
   asm("GetDeviceHash__Q2_2nn3actFPUL");

nn::Result
GetMii(FFLStoreData* mii)
   asm("GetMii__Q2_2nn3actFP12FFLStoreData");

nn::Result
GetMiiEx(FFLStoreData* mii, SlotNo slot)
   asm("GetMiiEx__Q2_2nn3actFP12FFLStoreDataUc");

nn::Result
GetMiiImageEx(size_t* outImageSize, void* buffer, size_t bufferSize, int unk, SlotNo slot)
   asm("GetMiiImageEx__Q2_2nn3actFPUiPvUi15ACTMiiImageTypeUc");

nn::Result
GetMiiName(int16_t outName[MiiNameSize])
   asm("GetMiiName__Q2_2nn3actFPw");

nn::Result
GetMiiNameEx(int16_t outName[MiiNameSize], SlotNo slot)
   asm("GetMiiNameEx__Q2_2nn3actFPwUc");

nn::Result
GetNfsPassword(char outPassword[NfsPasswordSize])
   asm("GetNfsPassword__Q2_2nn3actFPc");

nn::Result
GetNfsPasswordEx(char outPassword[NfsPasswordSize], SlotNo slot)
   asm("GetNfsPasswordEx__Q2_2nn3actFPcUc");

uint8_t
GetNumOfAccounts(void)
   asm("GetNumOfAccounts__Q2_2nn3actFv");

SlotNo
GetParentalControlsSlotNo(void)
   asm("GetParentalControlSlotNo__Q2_2nn3actFv");

nn::Result
GetParentalControlsSlotNoEx(void)
   asm("GetParentalControlSlotNoEx__Q2_2nn3actFPUcUc");

PersistentId
GetPersistentId(void)
   asm("GetPersistentId__Q2_2nn3actFv");

PersistentId
GetPersistentIdEx(SlotNo slot)
   asm("GetPersistentIdEx__Q2_2nn3actFUc");

PrincipalId
GetPrincipalId(void)
   asm("GetPrincipalId__Q2_2nn3actFv");

nn::Result
GetPrincipalIdEx(PrincipalId* outId, SlotNo slot)
   asm("GetPrincipalIdEx__Q2_2nn3actFPUiUc");

SimpleAddressId
GetSimpleAddressId(void)
   asm("GetSimpleAddressId__Q2_2nn3actFv");

nn::Result
GetSimpleAddressId(SimpleAddressId* outId, SlotNo slot)
   asm("GetSimpleAddressIdEx__Q2_2nn3actFPUiUc");

SlotNo
GetSlotNo(void)
   asm("GetSlotNo__Q2_2nn3actFv");

TransferrableId
GetTransferableId(uint32_t unk1)
   asm("GetTransferableId__Q2_2nn3actFUi");

nn::Result
GetTransferableIdEx(TransferrableId* outId, uint32_t unk1, SlotNo slot)
   asm("GetTransferableIdEx__Q2_2nn3actFPULUiUc");

nn::Result
GetUuidEx(char outUuid[UuidSize], SlotNo slot, int32_t unk1)
   asm("GetUuidEx__Q2_2nn3actFP7ACTUuidUcUi");

nn::Result
GetUuidEx(char outUuid[UuidSize], SlotNo slot)
   asm("GetUuidEx__Q2_2nn3actFP7ACTUuidUc");

nn::Result
GetUuid(char outUuid[UuidSize], int32_t unk1)
   asm("GetUuid__Q2_2nn3actFP7ACTUuidUi");

nn::Result
GetUuid(char outUuid[UuidSize])
   asm("GetUuid__Q2_2nn3actFP7ACTUuid");

BOOL
HasNfsAccount(void)
   asm("HasNfsAccount__Q2_2nn3actFv");

BOOL
IsCommitted(void)
   asm("IsCommitted__Q2_2nn3actFv");

BOOL
IsCommittedEx(SlotNo slot)
   asm("IsCommittedEx__Q2_2nn3actFUc");

BOOL
IsPasswordCacheEnabled(void)
   asm("IsPasswordCacheEnabled__Q2_2nn3actFv");

BOOL
IsPasswordCacheEnabledEx(SlotNo slot)
   asm("IsPasswordCacheEnabledEx__Q2_2nn3actFUc");

BOOL
IsNetworkAccount(void)
   asm("IsNetworkAccount__Q2_2nn3actFv");

BOOL
IsNetworkAccountEx(SlotNo slot)
   asm("IsNetworkAccountEx__Q2_2nn3actFUc");

BOOL
IsServerAccountActive(void)
   asm("IsServerAccountActive__Q2_2nn3actFv");

BOOL
IsServerAccountActiveEx(SlotNo slot)
   asm("IsServerAccountActiveEx__Q2_2nn3actFUc");

BOOL
IsServerAccountDeleted(void)
   asm("IsServerAccountDeleted__Q2_2nn3actFv");

BOOL
IsServerAccountDeletedEx(SlotNo slot)
   asm("IsServerAccountDeletedEx__Q2_2nn3actFUc");

BOOL
IsSlotOccupied(SlotNo slot)
   asm("IsSlotOccupied__Q2_2nn3actFUc");

} //namespace act

} //namespace nn

#endif //__cplusplus

/** @} */
