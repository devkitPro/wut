#include <nn/sl/TitleListCache.h>

namespace nn::sl {
    namespace {
        extern "C" details::ITitleListCacheInternal *GetDefaultTitleListCache__Q2_2nn2slFv();
    }
    static TitleListCacheFromPtr sDefaultTitleListCache(GetDefaultTitleListCache__Q2_2nn2slFv());

    details::ITitleListCacheBase &GetDefaultTitleListCache() {
        return sDefaultTitleListCache;
    }

} // namespace nn::sl