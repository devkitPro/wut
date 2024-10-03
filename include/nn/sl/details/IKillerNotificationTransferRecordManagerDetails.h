#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/FileStream.h>

#ifdef __cplusplus

namespace nn::sl
{
class KillerNotificationSelector;
namespace details
{
class IKillerNotificationTransferRecordManagerBase;
struct IKillerNotificationTransferRecordManagerInternal;
typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_LoadFn)(IKillerNotificationTransferRecordManagerInternal *, nn::sl::details::IStreamInternal *);
typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_LoadInitialFn)(IKillerNotificationTransferRecordManagerInternal *);
typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_StoreFn)(IKillerNotificationTransferRecordManagerInternal *, nn::sl::details::IStreamInternal *);
typedef void (*IKillerNotificationTransferRecordManagerInternVTable_FinalizeFn)(IKillerNotificationTransferRecordManagerInternal *);
typedef uint32_t (*IKillerNotificationTransferRecordManagerInternVTable_GetRecordCountFn)(IKillerNotificationTransferRecordManagerInternal *);
typedef uint32_t (*IKillerNotificationTransferRecordManagerInternVTable_GetRecordsFn)(IKillerNotificationTransferRecordManagerInternal *, KillerNotificationTransferRecord *, uint32_t);
typedef void (*IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsFn)(IKillerNotificationTransferRecordManagerInternal *, const KillerNotificationTransferRecord *, uint32_t);
typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsOtherFn)(IKillerNotificationTransferRecordManagerInternal *, const uint32_t *, uint32_t);

typedef struct WUT_PACKED IKillerNotificationTransferRecordManagerInternalVTable
{
   IKillerNotificationTransferRecordManagerBase *instance; // Normally this is padding
   WUT_UNKNOWN_BYTES(0x10);
   IKillerNotificationTransferRecordManagerInternVTable_LoadFn LoadFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_LoadInitialFn LoadInitialFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_StoreFn StoreFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_FinalizeFn FinalizeFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_GetRecordCountFn GetRecordCountFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_GetRecordsFn GetRecordsFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsFn RegisterRecordsFn;
   WUT_UNKNOWN_BYTES(0x4);
   IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsOtherFn RegisterRecordsOtherFn;
} IKillerNotificationTransferRecordManagerInternalVTable;
WUT_CHECK_SIZE(IKillerNotificationTransferRecordManagerInternalVTable, 0x50);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x14, LoadFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x1C, LoadInitialFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x24, StoreFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x2C, FinalizeFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x34, GetRecordCountFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x3C, GetRecordsFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x44, RegisterRecordsFn);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternalVTable, 0x4C, RegisterRecordsOtherFn);

typedef struct WUT_PACKED IKillerNotificationTransferRecordManagerInternal
{
   IKillerNotificationTransferRecordManagerInternalVTable *vtable;
} IKillerNotificationTransferRecordManagerIntern;
WUT_CHECK_SIZE(IKillerNotificationTransferRecordManagerInternal, 0x4);
WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternal, 0x00, vtable);

typedef struct WUT_PACKED KillerNotificationTransferRecordManagerInternalInternal
{
   IKillerNotificationTransferRecordManagerInternalVTable *vtable;
   void *killerNotificationTransferRecordManagerImpl;
} KillerNotificationTransferRecordManagerInternalInternal;
WUT_CHECK_SIZE(KillerNotificationTransferRecordManagerInternalInternal, 0x8);
WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x00, vtable);
WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x04, killerNotificationTransferRecordManagerImpl);

extern "C" IKillerNotificationTransferRecordManagerIntern *
__ct__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
extern "C" void *
__dt__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *, int);
extern "C" void
Finalize__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
extern "C" nn::Result
Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(IKillerNotificationTransferRecordManagerInternal *, details::IStreamInternal *);
extern "C" nn::Result
LoadInitial__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
extern "C" uint32_t
GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv(IKillerNotificationTransferRecordManagerInternal *);
extern "C" uint32_t
GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi(IKillerNotificationTransferRecordManagerInternal *, KillerNotificationTransferRecord *, uint32_t);
extern "C" void
RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(IKillerNotificationTransferRecordManagerInternal *, const KillerNotificationTransferRecord *, uint32_t);
extern "C" nn::Result
Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(IKillerNotificationTransferRecordManagerInternal *, details::IStreamInternal *);


extern "C" KillerNotificationTransferRecordManagerInternalInternal *
__ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *);
extern "C" void *
__dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *, int);

class IKillerNotificationTransferRecordManagerBase
{
   friend class nn::sl::KillerNotificationSelector;

public:
   virtual ~IKillerNotificationTransferRecordManagerBase() = default;

   virtual nn::Result
   Load(nn::sl::details::IStreamBase &stream) = 0;

   virtual nn::Result
   LoadInitial() = 0;

   virtual nn::Result
   Store(nn::sl::details::IStreamBase &stream) = 0;

   virtual void
   Finalize() = 0;

   virtual uint32_t
   GetRecordCount() const = 0;

   virtual uint32_t
   GetRecords(KillerNotificationTransferRecord *outTransferRecords, uint32_t maxTransferRecords) const = 0;

   virtual void
   RegisterRecords(const KillerNotificationTransferRecord *transferRecords, uint32_t numTransferRecords) = 0;

   virtual nn::Result
   RegisterRecords(const uint32_t *u1, uint32_t u2) = 0;

private:
   virtual details::IKillerNotificationTransferRecordManagerInternal *
   GetInternal() = 0;
};

class KillerNotificationTransferRecordManagerFromPtr : public IKillerNotificationTransferRecordManagerBase
{
public:
   explicit KillerNotificationTransferRecordManagerFromPtr(details::IKillerNotificationTransferRecordManagerInternal *instance) :
      mInstancePtr(instance)
   {
   }

   ~KillerNotificationTransferRecordManagerFromPtr() override = default;

   void
   Finalize() override
   {
      if (!mInstancePtr) {
         return;
      }
      mInstancePtr->vtable->FinalizeFn(mInstancePtr);
   }

   nn::Result
   Load(nn::sl::details::IStreamBase &stream) override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->LoadFn(mInstancePtr, stream.GetInternal());
   }

   nn::Result
   LoadInitial() override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->LoadInitialFn(mInstancePtr);
   }

   nn::Result
   Store(nn::sl::details::IStreamBase &stream) override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->StoreFn(mInstancePtr, stream.GetInternal());
   }

   uint32_t
   GetRecordCount() const override
   {
      if (!mInstancePtr) {
         return 0;
      }
      return mInstancePtr->vtable->GetRecordCountFn(mInstancePtr);
   }

   uint32_t
   GetRecords(KillerNotificationTransferRecord *outTransferRecords, uint32_t maxTransferRecords) const override
   {
      if (!mInstancePtr) {
         return 0;
      }
      return mInstancePtr->vtable->GetRecordsFn(mInstancePtr, outTransferRecords, maxTransferRecords);
   }

   void
   RegisterRecords(const KillerNotificationTransferRecord *transferRecords, uint32_t numTransferRecords) override
   {
      if (!mInstancePtr) {
         return;
      }
      mInstancePtr->vtable->RegisterRecordsFn(mInstancePtr, transferRecords, numTransferRecords);
   }

   nn::Result
   RegisterRecords(const uint32_t *u1, uint32_t u2) override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->RegisterRecordsOtherFn(mInstancePtr, u1, u2);
   }

private:
   details::IKillerNotificationTransferRecordManagerInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }
   details::IKillerNotificationTransferRecordManagerInternal *mInstancePtr = {};
};
} // namespace details
} // namespace nn::sl

#endif