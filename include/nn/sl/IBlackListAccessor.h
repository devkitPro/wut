#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IBlackListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{

class IBlackListAccessor : public details::IBlackListAccessorBase
{

public:
   IBlackListAccessor()
   {
      InitInternalVtable();
   }


   IBlackListAccessor(IBlackListAccessor &src)
   {
      InitInternalVtable();
   }

   IBlackListAccessor &
   operator=(const IBlackListAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IBlackListAccessor &
   operator=(IBlackListAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IBlackListAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IBlackListAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos)
   {
      return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
   }

   details::IBlackListAccessorInternal *
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

   details::IBlackListAccessorInternal mInstance{};
   details::IBlackListAccessorInternalVTable mVTable{};
};

details::IBlackListAccessorBase &
GetDefaultBlackListAccessor();
} // namespace nn::sl

#endif