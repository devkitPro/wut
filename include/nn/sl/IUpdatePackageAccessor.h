#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/details/IUpdatePackageAccessorDetails.h>

#ifdef __cplusplus

namespace nn::sl
{
class IUpdatePackageAccessor : public details::IUpdatePackageAccessorBase
{

public:
   IUpdatePackageAccessor()
   {
      InitInternalVtable();
   }

   IUpdatePackageAccessor(IUpdatePackageAccessor &src)
   {
      InitInternalVtable();
   }

   IUpdatePackageAccessor &
   operator=(const IUpdatePackageAccessor &other)
   {
      InitInternalVtable();
      return *this;
   }

   IUpdatePackageAccessor &
   operator=(IUpdatePackageAccessor &&src) noexcept
   {
      InitInternalVtable();
      return *this;
   }

   ~IUpdatePackageAccessor() override = default;

private:
   static bool
   PackageExistsWrapper(details::IUpdatePackageAccessorInternal *instance)
   {
      return instance->vtable->instance->PackageExists();
   }
   static bool
   IsUpdatePackageDownloadedWrapper(details::IUpdatePackageAccessorInternal *instance)
   {
      return instance->vtable->instance->IsUpdatePackageDownloaded();
   }

   details::IUpdatePackageAccessorInternal *
   GetInternal() override
   {
      return &mInstance;
   }

   void
   InitInternalVtable()
   {
      mVTable          = {.instance                    = this,
                          .PackageExistsFn             = PackageExistsWrapper,
                          .IsUpdatePackageDownloadedFn = IsUpdatePackageDownloadedWrapper};
      mInstance.vtable = &mVTable;
   }

   details::IUpdatePackageAccessorInternal mInstance{};
   details::IUpdatePackageAccessorInternalVTable mVTable{};
};

details::IUpdatePackageAccessorBase &
GetDefaultUpdatePackageAccessor();
} // namespace nn::sl

#endif