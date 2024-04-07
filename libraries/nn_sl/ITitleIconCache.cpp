#include <nn/sl/ITitleIconCache.h>

namespace nn::sl {

    namespace {
        extern "C" details::ITitleIconCacheInternal *GetDefaultTitleIconCache__Q2_2nn2slFv();
    }

    static details::TitleIconCacheFromPtr sDefaultTitleIconCache(GetDefaultTitleIconCache__Q2_2nn2slFv());

    details::ITitleIconCacheBase &GetDefaultTitleIconCache() {
        return sDefaultTitleIconCache;
    }
} // namespace nn::sl