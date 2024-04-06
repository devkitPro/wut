#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IKillerNotificationAccessor;
    namespace details {
        struct IKillerNotificationAccessorInternal;

        typedef nn::Result (*IKillerNotificationAccessor_GetFn)(IKillerNotificationAccessorInternal *, KillerNotification *outBuffer, int *outNum, int outBufferNum);

        struct WUT_PACKED IKillerNotificationAccessorInternalVTable {
            IKillerNotificationAccessor *instance; // Is normally padding
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

        extern "C" IKillerNotificationAccessorInternal *GetDefaultKillerNotificationAccessor__Q2_2nn2slFv();
    } // namespace details

    class IKillerNotificationAccessor {
        friend class KillerNotificationSelector;

    public:
        IKillerNotificationAccessor() = default;

        virtual ~IKillerNotificationAccessor() = default;

        virtual nn::Result Get(KillerNotification *outBuffer, int *outNum, int outBufferNum) = 0;

    private:
        virtual details::IKillerNotificationAccessorInternal *GetInternal() = 0;
    };

    class IKillerNotificationAccessorBase : public IKillerNotificationAccessor {

    public:
        IKillerNotificationAccessorBase() {
            InitInternalVtable();
        }

        IKillerNotificationAccessorBase(IKillerNotificationAccessorBase &src) {
            InitInternalVtable();
        }

        IKillerNotificationAccessorBase &operator=(const IKillerNotificationAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IKillerNotificationAccessorBase &operator=(IKillerNotificationAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IKillerNotificationAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IKillerNotificationAccessorInternal *instance, KillerNotification *outBuffer, int *outNum, int outBufferNum) {
            return instance->vtable->instance->Get(outBuffer, outNum, outBufferNum);
        }

        details::IKillerNotificationAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IKillerNotificationAccessorInternal mInstance{};
        details::IKillerNotificationAccessorInternalVTable mVTable{};
    };

    class KillerNotificationAccessorFromPtr : public IKillerNotificationAccessor {
    public:
        explicit KillerNotificationAccessorFromPtr(details::IKillerNotificationAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(KillerNotification *outBuffer, int *outNum, int outBufferNum) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outBuffer, outNum, outBufferNum);
        }

    private:
        details::IKillerNotificationAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IKillerNotificationAccessorInternal *mInstancePtr;
    };

    KillerNotificationAccessorFromPtr GetDefaultKillerNotificationAccessor() {
        return KillerNotificationAccessorFromPtr(details::GetDefaultKillerNotificationAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif