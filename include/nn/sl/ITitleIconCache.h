#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ITitleIconCacheDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class ITitleIconCache : public details::ITitleIconCacheBase {

    public:
        ITitleIconCache();

        ITitleIconCache(ITitleIconCache &src);

        ITitleIconCache &operator=(const ITitleIconCache &other);

        ITitleIconCache &operator=(ITitleIconCache &&src) noexcept;

        ~ITitleIconCache() override = default;

    private:
        static nn::Result LoadWrapper(details::ITitleIconCacheInternal *instance);

        static nn::Result UpdateWrapper(details::ITitleIconCacheInternal *instance, TitleInfo *titleInfos, int num);

        static nn::Result StoreWrapper(details::ITitleIconCacheInternal *instance);

        static void GetWrapper(details::ITitleIconCacheInternal *instance, IconInfo *iconInfos, int num);

        details::ITitleIconCacheInternal *GetInternal() override;

        void InitInternalVtable();

        details::ITitleIconCacheInternal mInstance{};
        details::ITitleIconCacheInternalVTable mVTable{};
    };

    details::ITitleIconCacheBase &GetDefaultTitleIconCache();
} // namespace nn::sl

#endif