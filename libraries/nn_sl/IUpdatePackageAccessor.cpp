#include <nn/sl/IUpdatePackageAccessor.h>

namespace nn::sl {
    IUpdatePackageAccessor::IUpdatePackageAccessor() {
        InitInternalVtable();
    }

    IUpdatePackageAccessor::IUpdatePackageAccessor(IUpdatePackageAccessor &src) {
        InitInternalVtable();
    }

    IUpdatePackageAccessor &IUpdatePackageAccessor::operator=(const IUpdatePackageAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IUpdatePackageAccessor &IUpdatePackageAccessor::operator=(IUpdatePackageAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    bool nn::sl::IUpdatePackageAccessor::PackageExistsWrapper(nn::sl::details::IUpdatePackageAccessorInternal *instance) {

        return instance->vtable->instance->PackageExists();
    }

    bool nn::sl::IUpdatePackageAccessor::IsUpdatePackageDownloadedWrapper(nn::sl::details::IUpdatePackageAccessorInternal *instance) {
        return instance->vtable->instance->IsUpdatePackageDownloaded();
    }

    details::IUpdatePackageAccessorInternal *IUpdatePackageAccessor::GetInternal() {
        return &mInstance;
    }

    void IUpdatePackageAccessor::InitInternalVtable() {
        mVTable          = {.instance                    = this,
                            .PackageExistsFn             = PackageExistsWrapper,
                            .IsUpdatePackageDownloadedFn = IsUpdatePackageDownloadedWrapper};
        mInstance.vtable = &mVTable;
    }

    namespace {
        extern "C" details::IUpdatePackageAccessorInternal *GetDefaultUpdatePackageAccessor__Q2_2nn2slFv();
    }

    static details::UpdatePackageAccessorFromPtr sDefaultUpdatePackageAccessor(GetDefaultUpdatePackageAccessor__Q2_2nn2slFv());

    details::IUpdatePackageAccessorBase &GetDefaultUpdatePackageAccessor() {
        return sDefaultUpdatePackageAccessor;
    }

} // namespace nn::sl