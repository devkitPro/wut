#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IIconInfoAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{
class IIconInfoAccessor : public details::IIconInfoAccessorBase
{

public:
   IIconInfoAccessor()
   {
      InitInternalVtable();
   }

   IIconInfoAccessor(IIconInfoAccessor &src)
   {
      InitInternalVtable();
   }

   IIconInfoAccessor &
   operator=(const IIconInfoAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IIconInfoAccessor &
   operator=(IIconInfoAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IIconInfoAccessor() override = default;

private:
   static nn::Result
   GetTitleIconInfoWrapper(details::IIconInfoAccessorInternal *instance, nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language)
   {
      return instance->vtable->instance->GetTitleIconInfo(outIconInfo, titleInfo, language);
   }
   static nn::Result
   GetMiiIconWrapper(details::IIconInfoAccessorInternal *instance, void *buffer, uint32_t buffer_size, uint32_t slot)
   {
      return instance->vtable->instance->GetMiiIcon(buffer, buffer_size, slot);
   }

   details::IIconInfoAccessorInternal *
   GetInternal() override
   {
      return &mInstance;
   }

   void
   InitInternalVtable()
   {
      mVTable          = {.instance           = this,
                          .GetTitleIconInfoFn = GetTitleIconInfoWrapper,
                          .GetMiiIconFn       = GetMiiIconWrapper};
      mInstance.vtable = &mVTable;
   }

   details::IIconInfoAccessorInternal mInstance{};
   details::IIconInfoAccessorInternalVTable mVTable{};
};

details::IIconInfoAccessorBase &
GetDefaultIconInfoAccessor();
} // namespace nn::sl

#endif