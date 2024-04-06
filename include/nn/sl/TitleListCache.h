#pragma once

#include <nn/result.h>
#include <nn/sl/ILaunchedTitleListAccessor.h>
#include <nn/sl/ITimeAccessor.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED ITitleListCacheInternal {
            void *titleListAccessor;
            ILaunchedTitleListAccessorInternal *launchedTitleListAccessor;
            void *installedTitleListAccessor;
            void *discCachedTitleAccessor;
            void *titleInfoSerializer;
            ITimeAccessorInternal *timeAccessor;
            void *metaInfoAccessor;
            WUT_UNKNOWN_BYTES(0x18);
            void *vtable;
        } TitleListCacheInternal;
        WUT_CHECK_SIZE(ITitleListCacheInternal, 0x38);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x00, titleListAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x04, launchedTitleListAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x08, installedTitleListAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x0C, discCachedTitleAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x10, titleInfoSerializer);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x14, timeAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x18, metaInfoAccessor);
        WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x34, vtable);

        extern "C" ITitleListCacheInternal *__ct__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" void Finalize__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" nn::Result Update__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" nn::Result UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" nn::Result Store__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
        extern "C" nn::Result Initialize__Q3_2nn2sl14TitleListCacheFiT1(ITitleListCacheInternal *, int, int);
        extern "C" void Finalize__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
    } // namespace details

    class ITitleListCache {
        friend class QuickStartApplicationSelector;
        friend class KillerNotificationSelector;

    public:
        virtual ~ITitleListCache()                    = default;
        virtual nn::Result Initialize(int u1, int u2) = 0;
        virtual void Finalize()                       = 0;
        virtual nn::Result Load()                     = 0;
        virtual nn::Result Update()                   = 0;
        virtual nn::Result UpdateIfNeeded()           = 0;
        virtual nn::Result Store()                    = 0;

    private:
        virtual details::ITitleListCacheInternal *GetInternal() = 0;
    };

    class TitleListCache : public ITitleListCache {

    public:
        TitleListCache() {
            __ct__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        ~TitleListCache() override {
            Finalize__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        nn::Result Initialize(int u1, int u2) override {
            return Initialize__Q3_2nn2sl14TitleListCacheFiT1(&mInstance, u1, u2);
        }

        void Finalize() override {
            return Finalize__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        nn::Result Load() override {
            return Load__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        nn::Result Update() override {
            return Update__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        nn::Result UpdateIfNeeded() override {
            return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

        nn::Result Store() override {
            return Store__Q3_2nn2sl14TitleListCacheFv(&mInstance);
        }

    private:
        details::ITitleListCacheInternal *GetInternal() override {
            return &mInstance;
        }
        details::ITitleListCacheInternal mInstance = {};
    };

    class TitleListCacheFromPtr : public ITitleListCache {
    public:
        explicit TitleListCacheFromPtr(details::ITitleListCacheInternal *ptr) : mPtrInstance(ptr) {
        }
        ~TitleListCacheFromPtr() = default;

        nn::Result Initialize(int u1, int u2) override {
            return Initialize__Q3_2nn2sl14TitleListCacheFiT1(mPtrInstance, u1, u2);
        }

        void Finalize() override {
            return Finalize__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
        }

        nn::Result Load() override {
            return Load__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
        }

        nn::Result Update() override {
            return Update__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
        }

        nn::Result UpdateIfNeeded() override {
            return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
        }

        nn::Result Store() override {
            return Store__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
        }

    private:
        details::ITitleListCacheInternal *GetInternal() override {
            return mPtrInstance;
        }

        details::ITitleListCacheInternal *mPtrInstance = {};
    };

    ITitleListCache &GetDefaultTitleListCache();
} // namespace nn::sl

#endif