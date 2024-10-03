#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IMetaInfoAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{

class MetaInfoAccessor : public details::IMetaInfoAccessorBase
{

public:
   MetaInfoAccessor()
   {
      InitInternalVtable();
   }


   MetaInfoAccessor(MetaInfoAccessor &src)
   {
      InitInternalVtable();
   }

   MetaInfoAccessor &
   operator=(const MetaInfoAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   MetaInfoAccessor &
   operator=(MetaInfoAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~MetaInfoAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IMetaInfoAccessorInternal *instance, nn::sl::TitleMetaInfo *outMetaInfo, const nn::sl::TitleInfo &titleInfo)
   {
      return instance->vtable->instance->Get(outMetaInfo, titleInfo);
   }

   details::IMetaInfoAccessorInternal *
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

   details::IMetaInfoAccessorInternal mInstance{};
   details::IMetaInfoAccessorInternalVTable mVTable{};
};

details::IMetaInfoAccessorBase &
GetDefaultMetaInfoAccessor();
} // namespace nn::sl

#endif