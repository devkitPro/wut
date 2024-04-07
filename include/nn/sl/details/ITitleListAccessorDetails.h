#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class TitleListCache;
    namespace details {
        class ITitleListAccessorBase;
        struct ITitleListAccessorInternal;

        typedef nn::Result (*ITitleListAccessor_GetFn)(ITitleListAccessorInternal *, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED ITitleListAccessorInternalVTable {
            ITitleListAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ITitleListAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(ITitleListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(ITitleListAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ITitleListAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED ITitleListAccessorInternal {
            ITitleListAccessorInternalVTable *vtable;
        } ITitleListAccessorInternal;
        WUT_CHECK_SIZE(ITitleListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(ITitleListAccessorInternal, 0x00, vtable);

        class ITitleListAccessorBase {
            friend class nn::sl::TitleListCache;

        public:
            ITitleListAccessorBase()          = default;
            virtual ~ITitleListAccessorBase() = default;

            virtual nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const = 0;

        private:
            virtual details::ITitleListAccessorInternal *GetInternal() = 0;
        };

        class TitleListAccessorFromPtr : public ITitleListAccessorBase {
        public:
            explicit TitleListAccessorFromPtr(details::ITitleListAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
            }

        private:
            nn::sl::details::ITitleListAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::ITitleListAccessorInternal *mInstancePtr;
        };
    } // namespace details

} // namespace nn::sl

#endif