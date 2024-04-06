#pragma once

#include "DrcManager.h"
#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ITransferrer;
    namespace details {
        struct ITransferrerInternal;

        typedef nn::Result (*ITransferrer_TransferDeprecatedFn)(ITransferrerInternal *, void *, uint32_t, bool, int);
        typedef nn::Result (*ITransferrer_TransferFn)(ITransferrerInternal *, void *, uint32_t, bool, TransferMode);
        typedef nn::Result (*ITransferrer_CancelTransferFn)(ITransferrerInternal *);
        typedef nn::Result (*ITransferrer_InvalidateNotificationFn)(ITransferrerInternal *, uint32_t);
        typedef nn::Result (*ITransferrer_DisplayNotificationFn)(ITransferrerInternal *, uint32_t, uint32_t, uint32_t);

        struct WUT_PACKED ITransferrerInternalVTable {
            ITransferrer *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ITransferrer_TransferDeprecatedFn TransferDeprecatedFn;
            WUT_PADDING_BYTES(4);
            ITransferrer_TransferFn TransferFn;
            WUT_PADDING_BYTES(4);
            ITransferrer_CancelTransferFn CancelTransferFn;
            WUT_PADDING_BYTES(4);
            ITransferrer_InvalidateNotificationFn InvalidateNotificationFn;
            WUT_PADDING_BYTES(4);
            ITransferrer_DisplayNotificationFn DisplayNotificationFn;
        };
        WUT_CHECK_SIZE(ITransferrerInternalVTable, 0x38);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x14, TransferDeprecatedFn);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x1C, TransferFn);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x24, CancelTransferFn);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x2C, InvalidateNotificationFn);
        WUT_CHECK_OFFSET(ITransferrerInternalVTable, 0x34, DisplayNotificationFn);

        typedef struct WUT_PACKED ITransferrerInternal {
            ITransferrerInternalVTable *vtable;
        } ITransferrerInternal;
        WUT_CHECK_SIZE(ITransferrerInternal, 0x04);
        WUT_CHECK_OFFSET(ITransferrerInternal, 0x00, vtable);

        extern "C" ITransferrerInternal *GetDrcTransferrer__Q2_2nn2slFv();
    } // namespace details


    class ITransferrer {
        friend class DrcManager;

    public:
        ITransferrer() = default;

        virtual ~ITransferrer() = default;

        virtual nn::Result TransferDeprecated(void *buffer, uint32_t size, bool setKillerNotification, int transferMode) = 0;
        virtual nn::Result Transfer(void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode)  = 0;
        virtual nn::Result CancelTransfer()                                                                              = 0;
        virtual nn::Result InvalidateNotification(uint32_t)                                                              = 0;
        virtual nn::Result DisplayNotification(uint32_t, uint32_t, uint32_t)                                             = 0;

    private:
        virtual details::ITransferrerInternal *GetInternal() = 0;
    };

    class ITransferrerBase : public ITransferrer {

    public:
        ITransferrerBase() {
            InitInternalVtable();
        }

        ITransferrerBase(ITransferrerBase &src) {
            InitInternalVtable();
        }

        ITransferrerBase &operator=(const ITransferrerBase &other) {
            InitInternalVtable();
            return *this;
        }

        ITransferrerBase &operator=(ITransferrerBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ITransferrerBase() override = default;

    private:
        static nn::Result TransferDeprecatedWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, int transferMode) {
            return instance->vtable->instance->TransferDeprecated(buffer, size, setKillerNotification, transferMode);
        }
        static nn::Result TransferWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode) {
            return instance->vtable->instance->Transfer(buffer, size, setKillerNotification, transferMode);
        }
        static nn::Result CancelTransferWrapper(details::ITransferrerInternal *instance) {
            return instance->vtable->instance->CancelTransfer();
        }
        static nn::Result InvalidateNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1) {
            return instance->vtable->instance->InvalidateNotification(u1);
        }
        static nn::Result DisplayNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1, uint32_t u2, uint32_t u3) {
            return instance->vtable->instance->DisplayNotification(u1, u2, u3);
        }

        details::ITransferrerInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance                 = this,
                                .TransferDeprecatedFn     = &TransferDeprecatedWrapper,
                                .TransferFn               = &TransferWrapper,
                                .CancelTransferFn         = &CancelTransferWrapper,
                                .InvalidateNotificationFn = &InvalidateNotificationWrapper,
                                .DisplayNotificationFn    = &DisplayNotificationWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ITransferrerInternal mInstance{};
        details::ITransferrerInternalVTable mVTable{};
    };

    class TransferrerFromPtr : public ITransferrer {
    public:
        explicit TransferrerFromPtr(details::ITransferrerInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result TransferDeprecated(void *buffer, uint32_t size, bool setKillerNotification, int transferMode) override {
            return mInstancePtr->vtable->TransferDeprecatedFn(mInstancePtr, buffer, size, setKillerNotification, transferMode);
        }
        nn::Result Transfer(void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode) override {
            return mInstancePtr->vtable->TransferFn(mInstancePtr, buffer, size, setKillerNotification, transferMode);
        }
        nn::Result CancelTransfer() override {
            return mInstancePtr->vtable->CancelTransferFn(mInstancePtr);
        }
        nn::Result InvalidateNotification(uint32_t u1) override {
            return mInstancePtr->vtable->InvalidateNotificationFn(mInstancePtr, u1);
        }
        nn::Result DisplayNotification(uint32_t u1, uint32_t u2, uint32_t u3) override {
            return mInstancePtr->vtable->DisplayNotificationFn(mInstancePtr, u1, u2, u3);
        }

    private:
        details::ITransferrerInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ITransferrerInternal *mInstancePtr;
    };

    TransferrerFromPtr GetDrcTransferrer() {
        return TransferrerFromPtr(details::GetDrcTransferrer__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif