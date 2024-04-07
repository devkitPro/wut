#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ITransferrerDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ITransferrer : public details::ITransferrerBase {

    public:
        ITransferrer() {
            InitInternalVtable();
        }

        ITransferrer(ITransferrer &src) {
            InitInternalVtable();
        }

        ITransferrer &operator=(const ITransferrer &other) {
            InitInternalVtable();
            return *this;
        }

        ITransferrer &operator=(ITransferrer &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ITransferrer() override = default;

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

    details::ITransferrerBase &GetDrcTransferrer();
} // namespace nn::sl

#endif