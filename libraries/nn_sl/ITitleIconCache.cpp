#include <nn/sl/ITitleIconCache.h>

namespace nn::sl {
    ITitleIconCache::ITitleIconCache() {
        InitInternalVtable();
    }
    ITitleIconCache::ITitleIconCache(ITitleIconCache &src) {
        InitInternalVtable();
    }
    ITitleIconCache &ITitleIconCache::operator=(const ITitleIconCache &other) {
        InitInternalVtable();
        return *this;
    }
    ITitleIconCache &ITitleIconCache::operator=(ITitleIconCache &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result ITitleIconCache::LoadWrapper(details::ITitleIconCacheInternal *instance) {
        return instance->vtable->instance->Load();
    }
    nn::Result ITitleIconCache::UpdateWrapper(details::ITitleIconCacheInternal *instance, TitleInfo *titleInfos, int num) {
        return instance->vtable->instance->Update(titleInfos, num);
    }
    nn::Result ITitleIconCache::StoreWrapper(details::ITitleIconCacheInternal *instance) {
        return instance->vtable->instance->Store();
    }
    void ITitleIconCache::GetWrapper(details::ITitleIconCacheInternal *instance, IconInfo *iconInfos, int num) {
        return instance->vtable->instance->Get(iconInfos, num);
    }
    details::ITitleIconCacheInternal *ITitleIconCache::GetInternal() {
        return &mInstance;
    }
    void ITitleIconCache::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .LoadFn   = &LoadWrapper,
                            .UpdateFn = &UpdateWrapper,
                            .StoreFn  = &StoreWrapper,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    namespace {
        extern "C" details::ITitleIconCacheInternal *GetDefaultTitleIconCache__Q2_2nn2slFv();
    }

    static details::TitleIconCacheFromPtr sDefaultTitleIconCache(GetDefaultTitleIconCache__Q2_2nn2slFv());

    details::ITitleIconCacheBase &GetDefaultTitleIconCache() {
        return sDefaultTitleIconCache;
    }
} // namespace nn::sl