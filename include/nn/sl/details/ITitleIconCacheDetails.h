#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class DataCreator;
    namespace details {
        class ITitleIconCacheBase;
        struct ITitleIconCacheInternal;

        struct WUT_PACKED ITitleIconCacheInternal;

        typedef nn::Result (*TitleIconCache_LoadFn)(ITitleIconCacheInternal *);
        typedef nn::Result (*TitleIconCache_UpdateFn)(ITitleIconCacheInternal *, TitleInfo *, int);
        typedef nn::Result (*TitleIconCache_StoreFn)(ITitleIconCacheInternal *);
        typedef void (*TitleIconCache_GetFn)(ITitleIconCacheInternal *, IconInfo *, int);

        typedef struct WUT_PACKED ITitleIconCacheInternalVTable {
            ITitleIconCacheBase *instance; // this is normally padding
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

        class ITitleIconCacheBase {
            friend class nn::sl::DataCreator;

        public:
            ITitleIconCacheBase() = default;

            virtual ~ITitleIconCacheBase() = default;

            virtual nn::Result Load() = 0;

            virtual nn::Result Update(nn::sl::TitleInfo *titleInfos, int num) = 0;

            virtual nn::Result Store() = 0;

            virtual void Get(nn::sl::IconInfo *iconInfos, int num) = 0;

        private:
            virtual details::ITitleIconCacheInternal *GetInternal() = 0;
        };

        class TitleIconCacheFromPtr : public ITitleIconCacheBase {
        public:
            explicit TitleIconCacheFromPtr(details::ITitleIconCacheInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Load() override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->LoadFn(mInstancePtr);
            }

            nn::Result Update(nn::sl::TitleInfo *titleInfos, int num) override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->UpdateFn(mInstancePtr, titleInfos, num);
            }

            nn::Result Store() override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->StoreFn(mInstancePtr);
            }

            void Get(nn::sl::IconInfo *iconInfos, int num) override {
                if (!mInstancePtr) {
                    return;
                }
                mInstancePtr->vtable->GetFn(mInstancePtr, iconInfos, num);
            }

        private:
            details::ITitleIconCacheInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::ITitleIconCacheInternal *mInstancePtr;
        };
    } // namespace details


} // namespace nn::sl

#endif