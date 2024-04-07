#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class DataCreator;
    class KillerNotificationSelector;
    namespace details {
        class IAccountInfoAccessorBase;
        struct IAccountInfoAccessorInternal;
        typedef nn::Result (*IAccountInfoAccessor_GetFn)(IAccountInfoAccessorInternal *, nn::sl::AccountInfo *);

        struct WUT_PACKED IAccountInfoAccessorInternalVTable {
            IAccountInfoAccessorBase *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IAccountInfoAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IAccountInfoAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IAccountInfoAccessorInternal {
            IAccountInfoAccessorInternalVTable *vtable;
        } IAccountInfoAccessorInternal;
        WUT_CHECK_SIZE(IAccountInfoAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternal, 0x00, vtable);

        class IAccountInfoAccessorBase {
            friend class nn::sl::DataCreator;
            friend class nn::sl::KillerNotificationSelector;

        public:
            IAccountInfoAccessorBase() = default;

            virtual ~IAccountInfoAccessorBase() = default;

            virtual nn::Result Get(nn::sl::AccountInfo *) = 0;

        private:
            virtual details::IAccountInfoAccessorInternal *GetInternal() = 0;
        };

        class AccountInfoAccessorFromPtr : public IAccountInfoAccessorBase {
        public:
            explicit AccountInfoAccessorFromPtr(details::IAccountInfoAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(nn::sl::AccountInfo *outAccountInfo) override {
                if (!mInstancePtr) {
                    return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 1};
                }
                return mInstancePtr->vtable->GetFn(mInstancePtr, outAccountInfo);
            }

        private:
            details::IAccountInfoAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IAccountInfoAccessorInternal *mInstancePtr;
        };
    } // namespace details
} // namespace nn::sl

#endif