#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class DataCreator;
    class QuickStartApplicationSelector;
    namespace details {
        class IBlackListAccessorBase;
        struct IBlackListAccessorInternal;

        typedef nn::Result (*IBlackListAccessor_GetFn)(IBlackListAccessorInternal *, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED IBlackListAccessorInternalVTable {
            IBlackListAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IBlackListAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IBlackListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IBlackListAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IBlackListAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IBlackListAccessorInternal {
            IBlackListAccessorInternalVTable *vtable;
        } IBlackListAccessorInternal;
        WUT_CHECK_SIZE(IBlackListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IBlackListAccessorInternal, 0x00, vtable);

        class IBlackListAccessorBase {
            friend class nn::sl::DataCreator;
            friend class nn::sl::QuickStartApplicationSelector;

        public:
            IBlackListAccessorBase()          = default;
            virtual ~IBlackListAccessorBase() = default;

            virtual nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) = 0;

        private:
            virtual details::IBlackListAccessorInternal *GetInternal() = 0;
        };

        class BlackListAccessorFromPtr : public IBlackListAccessorBase {
        public:
            explicit BlackListAccessorFromPtr(details::IBlackListAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
            }

        private:
            nn::sl::details::IBlackListAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IBlackListAccessorInternal *mInstancePtr;
        };
    } // namespace details

} // namespace nn::sl

#endif