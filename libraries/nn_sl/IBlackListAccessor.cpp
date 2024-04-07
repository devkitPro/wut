#include <nn/sl/IBlackListAccessor.h>

namespace nn::sl {
    namespace {
        extern "C" details::IBlackListAccessorInternal *GetDefaultBlackListAccessor__Q2_2nn2slFv();
    }

    static details::BlackListAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultBlackListAccessor__Q2_2nn2slFv());

    details::IBlackListAccessorBase &GetDefaultBlackListAccessor() {
        return sDefaultIconInfoAccessor;
    }

} // namespace nn::sl