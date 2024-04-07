#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class TitleListCache;
    namespace details {
        class IInstalledTitleListAccessorBase;
        struct IInstalledTitleListAccessorInternal;

        typedef nn::Result (*IInstalledTitleListAccessor_GetFn)(IInstalledTitleListAccessorInternal *, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED IInstalledTitleListAccessorInternalVTable {
            IInstalledTitleListAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IInstalledTitleListAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IInstalledTitleListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IInstalledTitleListAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IInstalledTitleListAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IInstalledTitleListAccessorInternal {
            IInstalledTitleListAccessorInternalVTable *vtable;
        } IInstalledTitleListAccessorInternal;
        WUT_CHECK_SIZE(IInstalledTitleListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IInstalledTitleListAccessorInternal, 0x00, vtable);

        class IInstalledTitleListAccessorBase {
            friend class nn::sl::TitleListCache;

        public:
            IInstalledTitleListAccessorBase()          = default;
            virtual ~IInstalledTitleListAccessorBase() = default;

            virtual nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const = 0;

        private:
            virtual details::IInstalledTitleListAccessorInternal *GetInternal() = 0;
        };

        class InstalledTitleListAccessorFromPtr : public IInstalledTitleListAccessorBase {
        public:
            explicit InstalledTitleListAccessorFromPtr(details::IInstalledTitleListAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) const override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
            }

        private:
            nn::sl::details::IInstalledTitleListAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IInstalledTitleListAccessorInternal *mInstancePtr;
        };
    } // namespace details

} // namespace nn::sl

#endif