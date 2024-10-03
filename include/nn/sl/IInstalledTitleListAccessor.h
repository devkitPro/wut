#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IInstalledTitleListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class IInstalledTitleListAccessor : public details::IInstalledTitleListAccessorBase
{

public:
   IInstalledTitleListAccessor()
   {
      InitInternalVtable();
   }


   IInstalledTitleListAccessor(IInstalledTitleListAccessor &src)
   {
      InitInternalVtable();
   }

   IInstalledTitleListAccessor &
   operator=(const IInstalledTitleListAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IInstalledTitleListAccessor &
   operator=(IInstalledTitleListAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IInstalledTitleListAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IInstalledTitleListAccessorInternal *instance, nn::sl::TitleInfo *outInstalledTitleInfos, int *outInstalledTitleInfosSize, int maxInstalledTitleInfos)
   {
      return instance->vtable->instance->Get(outInstalledTitleInfos, outInstalledTitleInfosSize, maxInstalledTitleInfos);
   }

   details::IInstalledTitleListAccessorInternal *
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

   details::IInstalledTitleListAccessorInternal mInstance{};
   details::IInstalledTitleListAccessorInternalVTable mVTable{};
};

details::IInstalledTitleListAccessorBase &
GetDefaultInstalledTitleListAccessor();
} // namespace nn::sl

#endif