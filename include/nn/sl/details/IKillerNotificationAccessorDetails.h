#pragma once

#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class KillerNotificationSelector;
    namespace details {
        class IKillerNotificationAccessorBase;
        struct IKillerNotificationAccessorInternal;

        typedef nn::Result (*IKillerNotificationAccessor_GetFn)(IKillerNotificationAccessorInternal *, KillerNotification *outBuffer, int *outNum, int outBufferNum);

        struct WUT_PACKED IKillerNotificationAccessorInternalVTable {
            IKillerNotificationAccessorBase *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IKillerNotificationAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IKillerNotificationAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IKillerNotificationAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IKillerNotificationAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IKillerNotificationAccessorInternal {
            IKillerNotificationAccessorInternalVTable *vtable;
        } IKillerNotificationAccessorInternal;
        WUT_CHECK_SIZE(IKillerNotificationAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IKillerNotificationAccessorInternal, 0x00, vtable);

        class IKillerNotificationAccessorBase {
            friend class nn::sl::KillerNotificationSelector;

        public:
            IKillerNotificationAccessorBase()          = default;
            virtual ~IKillerNotificationAccessorBase() = default;

            virtual nn::Result Get(KillerNotification *outBuffer, int *outNum, int outBufferNum) = 0;

        private:
            virtual details::IKillerNotificationAccessorInternal *GetInternal() = 0;
        };

        class KillerNotificationAccessorFromPtr : public IKillerNotificationAccessorBase {
        public:
            explicit KillerNotificationAccessorFromPtr(details::IKillerNotificationAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            nn::Result Get(KillerNotification *outBuffer, int *outNum, int outBufferNum) override {
                return mInstancePtr->vtable->GetFn(mInstancePtr, outBuffer, outNum, outBufferNum);
            }

        private:
            nn::sl::details::IKillerNotificationAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

            details::IKillerNotificationAccessorInternal *mInstancePtr;
        };

    } // namespace details

} // namespace nn::sl

#endif