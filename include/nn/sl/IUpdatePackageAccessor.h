#pragma once

#include <nn/result.h>
#include <nn/sl/details/IUpdatePackageAccessorDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IUpdatePackageAccessor : public details::IUpdatePackageAccessorBase {

    public:
        IUpdatePackageAccessor();

        IUpdatePackageAccessor(IUpdatePackageAccessor &src);

        IUpdatePackageAccessor &operator=(const IUpdatePackageAccessor &other);

        IUpdatePackageAccessor &operator=(IUpdatePackageAccessor &&src) noexcept;

        ~IUpdatePackageAccessor() override = default;

    private:
        static bool PackageExistsWrapper(details::IUpdatePackageAccessorInternal *instance);
        static bool IsUpdatePackageDownloadedWrapper(details::IUpdatePackageAccessorInternal *instance);

        details::IUpdatePackageAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IUpdatePackageAccessorInternal mInstance{};
        details::IUpdatePackageAccessorInternalVTable mVTable{};
    };

    details::IUpdatePackageAccessorBase &GetDefaultUpdatePackageAccessor();
} // namespace nn::sl

#endif