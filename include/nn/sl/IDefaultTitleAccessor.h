#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IDefaultTitleAccessorDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{

class IDefaultTitleAccessor : public details::IDefaultTitleAccessorBase
{

public:
   IDefaultTitleAccessor()
   {
      InitInternalVtable();
   }

   IDefaultTitleAccessor(IDefaultTitleAccessor &src)
   {
      InitInternalVtable();
   }

   IDefaultTitleAccessor &
   operator=(const IDefaultTitleAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IDefaultTitleAccessor &
   operator=(IDefaultTitleAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IDefaultTitleAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IDefaultTitleAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos)
   {
      return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
   }

   details::IDefaultTitleAccessorInternal *
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

   details::IDefaultTitleAccessorInternal mInstance{};
   details::IDefaultTitleAccessorInternalVTable mVTable{};
};

details::IDefaultTitleAccessorBase &
GetDefaultDefaultTitleAccessor();
} // namespace nn::sl

#endif