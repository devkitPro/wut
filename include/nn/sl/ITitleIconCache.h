#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/ITitleIconCacheDetails.h>
#include <nn/sl/sl_cpp.h>

#ifdef __cplusplus

namespace nn::sl
{

class ITitleIconCache : public details::ITitleIconCacheBase
{

public:
   ITitleIconCache()
   {
      InitInternalVtable();
   }

   ITitleIconCache(ITitleIconCache &src)
   {
      InitInternalVtable();
   }

   ITitleIconCache &
   operator=(const ITitleIconCache &other)
   {
      InitInternalVtable();
      return *this;
   }

   ITitleIconCache &
   operator=(ITitleIconCache &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~ITitleIconCache() override = default;

private:
   static nn::Result
   LoadWrapper(details::ITitleIconCacheInternal *instance)
   {
      return instance->vtable->instance->Load();
   }

   static nn::Result
   UpdateWrapper(details::ITitleIconCacheInternal *instance, TitleInfo *titleInfos, int num)
   {
      return instance->vtable->instance->Update(titleInfos, num);
   }

   static nn::Result
   StoreWrapper(details::ITitleIconCacheInternal *instance)
   {
      return instance->vtable->instance->Store();
   }

   static void
   GetWrapper(details::ITitleIconCacheInternal *instance, IconInfo *iconInfos, int num)
   {
      return instance->vtable->instance->Get(iconInfos, num);
   }

   details::ITitleIconCacheInternal *
   GetInternal() override
   {
      return &mInstance;
   }

   void
   InitInternalVtable()
   {
      mVTable          = {.instance = this,
                          .LoadFn   = &LoadWrapper,
                          .UpdateFn = &UpdateWrapper,
                          .StoreFn  = &StoreWrapper,
                          .GetFn    = &GetWrapper};
      mInstance.vtable = &mVTable;
   }

   details::ITitleIconCacheInternal mInstance{};
   details::ITitleIconCacheInternalVTable mVTable{};
};

details::ITitleIconCacheBase &
GetDefaultTitleIconCache();
} // namespace nn::sl

#endif