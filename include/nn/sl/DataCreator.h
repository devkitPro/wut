#pragma once

#include "IconInfo.h"
#include "TitleInfo.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn ::sl {
    namespace {
        struct WUT_PACKED TitleIconCacheInternal;

        typedef nn::Result (*TitleIconCache_LoadFn)(TitleIconCacheInternal *);
        typedef nn::Result (*TitleIconCache_UpdateFn)(TitleIconCacheInternal *, TitleInfo *, int);
        typedef nn::Result (*TitleIconCache_StoreFn)(TitleIconCacheInternal *);
        typedef void (*TitleIconCache_GetFn)(TitleIconCacheInternal *, IconInfo *, int);

        typedef struct WUT_PACKED TitleIconCacheVTable {
            WUT_UNKNOWN_BYTES(0x4);
            WUT_UNKNOWN_BYTES(0x4);
            WUT_UNKNOWN_BYTES(0x4);
            void *destructor;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_LoadFn LoadFunc;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_UpdateFn UpdateFunc;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_StoreFn StoreFunc;
            WUT_UNKNOWN_BYTES(0x4);
            TitleIconCache_GetFn GetFunc;
        } TitleIconCacheVTable;
        WUT_CHECK_SIZE(TitleIconCacheVTable, 0x30);

        WUT_CHECK_OFFSET(TitleIconCacheVTable, 0x14, LoadFunc);
        WUT_CHECK_OFFSET(TitleIconCacheVTable, 0x1c, UpdateFunc);
        WUT_CHECK_OFFSET(TitleIconCacheVTable, 0x24, StoreFunc);
        WUT_CHECK_OFFSET(TitleIconCacheVTable, 0x2C, GetFunc);

        typedef struct WUT_PACKED TitleIconCacheInternal {
            TitleIconCacheVTable *vtable;
            uint32_t count;
            BOOL isDataLoaded;
            void *iconInfoAccessor;
            void *iconInfoSerializer;
            void *settingsAccessor;
        } TitleIconCacheInternal;
        WUT_CHECK_SIZE(TitleIconCacheInternal, 0x18);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x00, vtable);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x04, count);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x08, isDataLoaded);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x0C, iconInfoAccessor);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x10, iconInfoSerializer);
        WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x14, settingsAccessor);


        typedef struct WUT_PACKED DataCreatorInternal {
            void *iconInfoAccesor;
            void *accountInfoAccesor;
            void *settingInfoAccesor;
            TitleIconCacheInternal *titleIconCache;
            WUT_UNKNOWN_BYTES(0x4);
        } DataCreatorInternal;
        WUT_CHECK_SIZE(DataCreatorInternal, 0x14);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x00, iconInfoAccesor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x04, accountInfoAccesor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x08, settingInfoAccesor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x0c, titleIconCache);


        extern "C" DataCreatorInternal *__ct__Q3_2nn2sl11DataCreatorFv(DataCreatorInternal *);

    } // namespace


    class TitleIconCache {
    public:
        explicit TitleIconCache(TitleIconCacheInternal *instance) : mInstance(instance) {
        }

        nn::Result Load() {
            if (!mInstance) {
                return {nn::Result::LEVEL_FATAL, nn::Result::RESULT_MODULE_NN_SL, 1};
            }
            return mInstance->vtable->LoadFunc(mInstance);
        }

        nn::Result Update(TitleInfo *title_info, int max) {
            if (!mInstance) {
                return {nn::Result::LEVEL_FATAL, nn::Result::RESULT_MODULE_NN_SL, 1};
            }
            return mInstance->vtable->UpdateFunc(mInstance, title_info, max);
        }

        nn::Result Store() {
            if (!mInstance) {
                return {nn::Result::LEVEL_FATAL, nn::Result::RESULT_MODULE_NN_SL, 1};
            }
            return mInstance->vtable->StoreFunc(mInstance);
        }

        void Get(nn::sl::IconInfo *icon_info, int max) {
            if (!mInstance) {
                return;
            }
            return mInstance->vtable->GetFunc(mInstance, icon_info, max);
        }

    private:
        TitleIconCacheInternal *mInstance;
    };

    class DataCreator {
    public:
        DataCreator() : mIconCache(nullptr) {
            if (__ct__Q3_2nn2sl11DataCreatorFv(&mInstance) != nullptr) {
                mIconCache = TitleIconCache(mInstance.titleIconCache);
            }
        }

        [[nodiscard]] TitleIconCache *getTitleIconCache() {
            return &mIconCache;
        }

        ~DataCreator() = default;

    private:
        DataCreatorInternal mInstance = {};
        TitleIconCache mIconCache;
    };
}; // namespace nn::sl

#endif