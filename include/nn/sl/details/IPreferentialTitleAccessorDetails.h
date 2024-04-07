#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class QuickStartApplicationSelector;
    namespace details {
        class IPreferentialTitleAccessorBase;
        struct IPreferentialTitleAccessorInternal;

        typedef nn::Result (*IPreferentialTitleAccessorBase_GetFn)(IPreferentialTitleAccessorInternal *, TitleInfo *, uint32_t *, int, uint32_t);

        struct WUT_PACKED IPreferentialTitleAccessorInternalVTable {
            IPreferentialTitleAccessorBase *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IPreferentialTitleAccessorBase_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IPreferentialTitleAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IPreferentialTitleAccessorInternal {
            IPreferentialTitleAccessorInternalVTable *vtable;
        } IPreferentialTitleAccessorInternal;
        WUT_CHECK_SIZE(IPreferentialTitleAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternal, 0x00, vtable);

        class IPreferentialTitleAccessorBase {
            friend class nn::sl::QuickStartApplicationSelector;

        public:
            IPreferentialTitleAccessorBase() = default;

            virtual ~IPreferentialTitleAccessorBase() = default;

            virtual nn::Result Get(TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) = 0;

        private:
            virtual details::IPreferentialTitleAccessorInternal *GetInternal() = 0;
        };

        class PreferentialTitleAccessorFromPtr : public IPreferentialTitleAccessorBase {
        public:
            explicit PreferentialTitleAccessorFromPtr(details::IPreferentialTitleAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
            }

        private:
            details::IPreferentialTitleAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IPreferentialTitleAccessorInternal *mInstancePtr;
        };
    } // namespace details
} // namespace nn::sl

#endif