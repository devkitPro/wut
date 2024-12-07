#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class DrcManager;
namespace details
{
class ITransferrerBase;
struct ITransferrerInternal;

typedef nn::Result (*ITransferrer_TransferDeprecatedFn)(ITransferrerInternal *, void *, uint32_t, bool, int);
typedef nn::Result (*ITransferrer_TransferFn)(ITransferrerInternal *, void *, uint32_t, bool, TransferMode);
typedef nn::Result (*ITransferrer_CancelTransferFn)(ITransferrerInternal *);
typedef nn::Result (*ITransferrer_InvalidateNotificationFn)(ITransferrerInternal *, uint32_t);
typedef nn::Result (*ITransferrer_DisplayNotificationFn)(ITransferrerInternal *, uint32_t, uint32_t, uint32_t);

struct WUT_PACKED ITransferrerInternalVTable
{
   ITransferrerBase *instance; // Is normally padding
   uint32_t info;
   WUT_PADDING_BYTES(4);
   uint32_t destructor;
   WUT_PADDING_BYTES(4);
   ITransferrer_TransferDeprecatedFn TransferDeprecatedFn;
   WUT_PADDING_BYTES(4);
   ITransferrer_TransferFn TransferFn;
   WUT_PADDING_BYTES(4);
   ITransferrer_CancelTransferFn CancelTransferFn;
   WUT_PADDING_BYTES(4);
   ITransferrer_InvalidateNotificationFn InvalidateNotificationFn;
   WUT_PADDING_BYTES(4);
   ITransferrer_DisplayNotificationFn DisplayNotificationFn;
};
WUT_CHECK_SIZE(ITransferrerInternalVTable, 0x38);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x00, instance);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x14, TransferDeprecatedFn);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x1C, TransferFn);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x24, CancelTransferFn);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x2C, InvalidateNotificationFn);
WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x34, DisplayNotificationFn);

typedef struct WUT_PACKED ITransferrerInternal
{
   ITransferrerInternalVTable *vtable;
} ITransferrerInternal;
WUT_CHECK_SIZE(ITransferrerInternal, 0x04);
WUT_CHECK_OFFSET(ITransferrerInternal, 0x00, vtable);

class ITransferrerBase
{
   friend class nn::sl::DrcManager;

public:
   ITransferrerBase()          = default;

   virtual ~ITransferrerBase() = default;

   virtual nn::Result
   TransferDeprecated(void *buffer, uint32_t size, bool setKillerNotification, int transferMode) const = 0;
   virtual nn::Result
   Transfer(void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode) const = 0;
   virtual nn::Result
   CancelTransfer() const                                                     = 0;
   virtual nn::Result InvalidateNotification(uint32_t) const                  = 0;
   virtual nn::Result DisplayNotification(uint32_t, uint32_t, uint32_t) const = 0;

private:
   virtual details::ITransferrerInternal *
   GetInternal() = 0;
};

class TransferrerFromPtr : public ITransferrerBase
{
public:
   explicit TransferrerFromPtr(details::ITransferrerInternal *ptr) :
      mInstancePtr(ptr)
   {
   }
   nn::Result
   TransferDeprecated(void *buffer, uint32_t size, bool setKillerNotification, int transferMode) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->TransferDeprecatedFn(mInstancePtr, buffer, size, setKillerNotification, transferMode);
   }
   nn::Result
   Transfer(void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->TransferFn(mInstancePtr, buffer, size, setKillerNotification, transferMode);
   }
   nn::Result
   CancelTransfer() const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->CancelTransferFn(mInstancePtr);
   }
   nn::Result
   InvalidateNotification(uint32_t u1) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->InvalidateNotificationFn(mInstancePtr, u1);
   }
   nn::Result
   DisplayNotification(uint32_t u1, uint32_t u2, uint32_t u3) const override
   {
      if (!mInstancePtr) {
         return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
      }
      return mInstancePtr->vtable->DisplayNotificationFn(mInstancePtr, u1, u2, u3);
   }

private:
   details::ITransferrerInternal *
   GetInternal() override
   {
      return mInstancePtr;
   }

   details::ITransferrerInternal *mInstancePtr;
};
} // namespace details

} // namespace nn::sl

#endif