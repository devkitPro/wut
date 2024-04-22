#include <nn/sl/IUpdatePackageAccessor.h>

namespace nn::sl {
    namespace {
        extern "C" details::IUpdatePackageAccessorInternal *GetDefaultUpdatePackageAccessor__Q2_2nn2slFv();
    }

    static details::UpdatePackageAccessorFromPtr sDefaultUpdatePackageAccessor(GetDefaultUpdatePackageAccessor__Q2_2nn2slFv());

    details::IUpdatePackageAccessorBase &GetDefaultUpdatePackageAccessor() {
        return sDefaultUpdatePackageAccessor;
    }

} // namespace nn::sl