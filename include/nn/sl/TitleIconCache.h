#pragma once

#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ITitleIconCache;
    namespace details {
        struct ITitleIconCacheInternal;

        struct WUT_PACKED ITitleIconCacheInternal;

        typedef nn::Result (*TitleIconCache_LoadFn)(ITitleIconCacheInternal *);
        typedef nn::Result (*TitleIconCache_UpdateFn)(ITitleIconCacheInternal *, TitleInfo *, int);
        typedef nn::Result (*TitleIconCache_StoreFn)(ITitleIconCacheInternal *);
        typedef void (*TitleIconCache_GetFn)(ITitleIconCacheInternal *, IconInfo *, int);

        typedef struct WUT_PACKED ITitleIconCacheInternalVTable {
            ITitleIconCache *instance; // this is normally padding
            WUT_UNKNOWN_BYTES(0x4);
            WUT_UNKNOWN_BYTES(0x4);
            void *destructor;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_LoadFn LoadFn;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_UpdateFn UpdateFn;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_StoreFn StoreFn;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_GetFn GetFn;
        } ITitleIconCacheInternalVTable;
        WUT_CHECK_SIZE(ITitleIconCacheInternalVTable, 0x30);
        WUT_CHECK_OFFSET(ITitleIconCacheInternalVTable, 0x14, LoadFn);
        WUT_CHECK_OFFSET(ITitleIconCacheInternalVTable, 0x1c, UpdateFn);
        WUT_CHECK_OFFSET(ITitleIconCacheInternalVTable, 0x24, StoreFn);
        WUT_CHECK_OFFSET(ITitleIconCacheInternalVTable, 0x2C, GetFn);

        typedef struct WUT_PACKED ITitleIconCacheInternal {
            ITitleIconCacheInternalVTable *vtable;
        } ITitleIconCacheInternal;
        WUT_CHECK_SIZE(ITitleIconCacheInternal, 0x04);
        WUT_CHECK_OFFSET(ITitleIconCacheInternal, 0x00, vtable);

        extern "C" ITitleIconCacheInternal *GetDefaultTitleIconCache__Q2_2nn2slFv();
    } // namespace details


    class ITitleIconCache {
        friend class DataCreator;

    public:
        ITitleIconCache() = default;

        virtual ~ITitleIconCache() = default;

        virtual nn::Result Load() = 0;

        virtual nn::Result Update(nn::sl::TitleInfo *titleInfos, int num) = 0;

        virtual nn::Result Store() = 0;

        virtual void Get(nn::sl::IconInfo *iconInfos, int num) = 0;

    private:
        virtual details::ITitleIconCacheInternal *GetInternal() = 0;
    };

    class TitleIconCacheBase : public ITitleIconCache {

    public:
        TitleIconCacheBase() {
            InitInternalVtable();
        }

        TitleIconCacheBase(TitleIconCacheBase &src) {
            InitInternalVtable();
        }

        TitleIconCacheBase &operator=(const TitleIconCacheBase &other) {
            InitInternalVtable();
            return *this;
        }

        TitleIconCacheBase &operator=(TitleIconCacheBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~TitleIconCacheBase() override = default;

    private:
        static nn::Result LoadWrapper(details::ITitleIconCacheInternal *instance) {
            return instance->vtable->instance->Load();
        }

        static nn::Result UpdateWrapper(details::ITitleIconCacheInternal *instance, TitleInfo *titleInfos, int num) {
            return instance->vtable->instance->Update(titleInfos, num);
        }

        static nn::Result StoreWrapper(details::ITitleIconCacheInternal *instance) {
            return instance->vtable->instance->Store();
        }
        static void GetWrapper(details::ITitleIconCacheInternal *instance, IconInfo *iconInfos, int num) {
            return instance->vtable->instance->Get(iconInfos, num);
        }

        details::ITitleIconCacheInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .LoadFn   = &LoadWrapper,
                                .UpdateFn = &UpdateWrapper,
                                .StoreFn  = &StoreWrapper,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ITitleIconCacheInternal mInstance{};
        details::ITitleIconCacheInternalVTable mVTable{};
    };

    class TitleIconCacheFromPtr : public ITitleIconCache {
    public:
        explicit TitleIconCacheFromPtr(details::ITitleIconCacheInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Load() override {
            return mInstancePtr->vtable->LoadFn(mInstancePtr);
        }

        nn::Result Update(nn::sl::TitleInfo *titleInfos, int num) override {
            return mInstancePtr->vtable->UpdateFn(mInstancePtr, titleInfos, num);
        }

        nn::Result Store() override {
            return mInstancePtr->vtable->StoreFn(mInstancePtr);
        }

        void Get(nn::sl::IconInfo *iconInfos, int num) override {
            mInstancePtr->vtable->GetFn(mInstancePtr, iconInfos, num);
        }

    private:
        details::ITitleIconCacheInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ITitleIconCacheInternal *mInstancePtr;
    };

    TitleIconCacheFromPtr GetDefaultTitleIconCache() {
        return TitleIconCacheFromPtr(details::GetDefaultTitleIconCache__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif