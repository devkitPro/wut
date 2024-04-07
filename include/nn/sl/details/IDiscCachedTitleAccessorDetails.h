#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class TitleListCache;
    namespace details {
        class IDiscCachedTitleAccessorBase;
        struct IDiscCachedTitleAccessorInternal;

        typedef nn::Result (*IDiscCachedTitleAccessor_GetFn)(IDiscCachedTitleAccessorInternal *, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED IDiscCachedTitleAccessorInternalVTable {
            IDiscCachedTitleAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IDiscCachedTitleAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IDiscCachedTitleAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IDiscCachedTitleAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IDiscCachedTitleAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IDiscCachedTitleAccessorInternal {
            IDiscCachedTitleAccessorInternalVTable *vtable;
        } IDiscCachedTitleAccessorInternal;
        WUT_CHECK_SIZE(IDiscCachedTitleAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IDiscCachedTitleAccessorInternal, 0x00, vtable);

        class IDiscCachedTitleAccessorBase {
            friend class nn::sl::TitleListCache;

        public:
            IDiscCachedTitleAccessorBase()          = default;
            virtual ~IDiscCachedTitleAccessorBase() = default;

            virtual nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const = 0;

        private:
            virtual details::IDiscCachedTitleAccessorInternal *GetInternal() = 0;
        };

        class DiscCachedTitleAccessorFromPtr : public IDiscCachedTitleAccessorBase {
        public:
            explicit DiscCachedTitleAccessorFromPtr(details::IDiscCachedTitleAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
            }

        private:
            nn::sl::details::IDiscCachedTitleAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IDiscCachedTitleAccessorInternal *mInstancePtr;
        };
    } // namespace details

} // namespace nn::sl

#endif