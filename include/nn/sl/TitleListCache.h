#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace {
        typedef struct WUT_PACKED TitleListCacheInternal {
            void *titleListAccessor;
            void *launchedTitleListAccessor;
            void *installedTitleListAccessor;
            void *discCachedTitleAccessor;
            void *titleInfoSerializer;
            void *timeAccessor;
            void *metaInfoAccessor;
            WUT_UNKNOWN_BYTES(0x18);
            void *vtable;
        } TitleListCacheInternal;
        WUT_CHECK_SIZE(TitleListCacheInternal, 0x38);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x00, titleListAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x04, launchedTitleListAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x08, installedTitleListAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x0C, discCachedTitleAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x10, titleInfoSerializer);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x14, timeAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x18, metaInfoAccessor);
        WUT_CHECK_OFFSET(TitleListCacheInternal, 0x34, vtable);

        extern "C" TitleListCacheInternal *__ct__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
        extern "C" void Finalize__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
        extern "C" nn::Result Update__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
        extern "C" nn::Result UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
        extern "C" nn::Result Store__Q3_2nn2sl14TitleListCacheFv(TitleListCacheInternal *);
    } // namespace

    class TitleListCache {
    public:
        TitleListCache() {
            __ct__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }
        ~TitleListCache() {
            // if the ptr is set, we are using this class as wrapper
            if (!mPtrInstance) {
                Finalize__Q3_2nn2sl14TitleListCacheFv(&mInstance);
            }
        }

        static TitleListCache FromExistingPtr(TitleListCacheInternal *instance) {
            return TitleListCache(instance);
        }

        nn::Result Load() {
            if (mPtrInstance) {
                return Load__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
            }
            return Load__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }
        nn::Result Update() {
            if (mPtrInstance) {
                return Update__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
            }
            return Update__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }
        nn::Result UpdateIfNeeded() {
            if (mPtrInstance) {
                return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
            }
            return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }
        nn::Result Store() {
            if (mPtrInstance) {
                return Store__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
            }
            return Store__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

    private:
        explicit TitleListCache(TitleListCacheInternal *instance) : mPtrInstance(instance) {
        }

        TitleListCacheInternal *mPtrInstance = {};
        TitleListCacheInternal mInstance     = {};
    };

} // namespace nn::sl

#endif