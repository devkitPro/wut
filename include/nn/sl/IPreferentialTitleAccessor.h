#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IPreferentialTitleAccessorDetails.h>

#ifdef __cplusplus

namespace nn::sl
{
class IPreferentialTitleAccessor : public details::IPreferentialTitleAccessorBase
{

public:
   IPreferentialTitleAccessor()
   {
      InitInternalVtable();
   }

   IPreferentialTitleAccessor(IPreferentialTitleAccessor &src)
   {
      InitInternalVtable();
   }

   IPreferentialTitleAccessor &
   operator=(const IPreferentialTitleAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IPreferentialTitleAccessor &
   operator=(IPreferentialTitleAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IPreferentialTitleAccessor() override = default;

private:
   static nn::Result
   GetWrapper(details::IPreferentialTitleAccessorInternal *instance, TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1)
   {
      return instance->vtable->instance->Get(outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
   }

   details::IPreferentialTitleAccessorInternal *
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

   details::IPreferentialTitleAccessorInternal mInstance{};
   details::IPreferentialTitleAccessorInternalVTable mVTable{};
};

details::IPreferentialTitleAccessorBase &
GetDefaultPreferentialTitleAccessor();
} // namespace nn::sl

#endif