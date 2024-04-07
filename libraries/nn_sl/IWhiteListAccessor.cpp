#include <nn/sl/IWhiteListAccessor.h>

namespace nn::sl {
    namespace {
        extern "C" details::IWhiteListAccessorInternal *GetDefaultWhiteListAccessor__Q2_2nn2slFv();
    }

    static details::WhiteListAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultWhiteListAccessor__Q2_2nn2slFv());

    details::IWhiteListAccessorBase &GetDefaultWhiteListAccessor() {
        return sDefaultIconInfoAccessor;
    }

} // namespace nn::sl