#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IKillerNotificationAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class IKillerNotificationAccessor : public details::IKillerNotificationAccessorBase
{

public:
   IKillerNotificationAccessor()
   {
      InitInternalVtable();
   }

   IKillerNotificationAccessor(IKillerNotificationAccessor &src)
   {
      InitInternalVtable();
   }

   IKillerNotificationAccessor &
   operator=(const IKillerNotificationAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IKillerNotificationAccessor &
   operator=(IKillerNotificationAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IKillerNotificationAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IKillerNotificationAccessorInternal *instance, KillerNotification *outBuffer, int *outNum, int outBufferNum)
   {
      return instance->vtable->instance->Get(outBuffer, outNum, outBufferNum);
   }

   details::IKillerNotificationAccessorInternal *
   GetInternal() override
   {
      return &mInstance;
   }

   void
   InitInternalVtable()
   {
      mVTable          = {.instance = this,
                          .GetFn    = &GetWrapper};
      mInstance.vtable = &mVTable;
   }

   details::IKillerNotificationAccessorInternal mInstance{};
   details::IKillerNotificationAccessorInternalVTable mVTable{};
};

details::IKillerNotificationAccessorBase &
GetDefaultKillerNotificationAccessor();
} // namespace nn::sl

#endif