#include <nn/sl/ITransferrer.h>

namespace nn::sl {
    ITransferrer::ITransferrer() {
        InitInternalVtable();
    }

    ITransferrer::ITransferrer(ITransferrer &src) {
        InitInternalVtable();
    }

    ITransferrer &ITransferrer::operator=(const ITransferrer &other) {
        InitInternalVtable();
        return *this;
    }

    ITransferrer &ITransferrer::operator=(ITransferrer &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result ITransferrer::TransferDeprecatedWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, int transferMode) {
        return instance->vtable->instance->TransferDeprecated(buffer, size, setKillerNotification, transferMode);
    }

    nn::Result ITransferrer::TransferWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode) {
        return instance->vtable->instance->Transfer(buffer, size, setKillerNotification, transferMode);
    }

    nn::Result ITransferrer::CancelTransferWrapper(details::ITransferrerInternal *instance) {
        return instance->vtable->instance->CancelTransfer();
    }

    nn::Result ITransferrer::InvalidateNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1) {
        return instance->vtable->instance->InvalidateNotification(u1);
    }

    nn::Result ITransferrer::DisplayNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1, uint32_t u2, uint32_t u3) {
        return instance->vtable->instance->DisplayNotification(u1, u2, u3);
    }

    details::ITransferrerInternal *ITransferrer::GetInternal() {
        return &mInstance;
    }

    void ITransferrer::InitInternalVtable() {
        mVTable          = {.instance                 = this,
                            .TransferDeprecatedFn     = &TransferDeprecatedWrapper,
                            .TransferFn               = &TransferWrapper,
                            .CancelTransferFn         = &CancelTransferWrapper,
                            .InvalidateNotificationFn = &InvalidateNotificationWrapper,
                            .DisplayNotificationFn    = &DisplayNotificationWrapper};
        mInstance.vtable = &mVTable;
    }

    namespace {
        extern "C" details::ITransferrerInternal *GetDrcTransferrer__Q2_2nn2slFv();
    }

    static details::TransferrerFromPtr sDrcTransferrer(GetDrcTransferrer__Q2_2nn2slFv());

    details::ITransferrerBase &GetDrcTransferrer() {
        return sDrcTransferrer;
    }
} // namespace nn::sl