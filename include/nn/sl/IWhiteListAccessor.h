#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IWhiteListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{

class IWhiteListAccessor : public details::IWhiteListAccessorBase
{

public:
   IWhiteListAccessor()
   {
      InitInternalVtable();
   }

   IWhiteListAccessor(IWhiteListAccessor &src)
   {
      InitInternalVtable();
   }

   IWhiteListAccessor &
   operator=(const IWhiteListAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IWhiteListAccessor &
   operator=(IWhiteListAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IWhiteListAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IWhiteListAccessorInternal *instance, nn::sl::WhiteList *outWhiteList)
   {
      return instance->vtable->instance->Get(outWhiteList);
   }

   details::IWhiteListAccessorInternal *
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

   details::IWhiteListAccessorInternal mInstance{};
   details::IWhiteListAccessorInternalVTable mVTable{};
};

details::IWhiteListAccessorBase &
GetDefaultWhiteListAccessor();
} // namespace nn::sl

#endif