#include <nn/sl/IKillerNotificationAccessor.h>

namespace nn::sl {
    IKillerNotificationAccessor::IKillerNotificationAccessor() {
        InitInternalVtable();
    }

    IKillerNotificationAccessor::IKillerNotificationAccessor(IKillerNotificationAccessor &src) {
        InitInternalVtable();
    }

    IKillerNotificationAccessor &IKillerNotificationAccessor::operator=(const IKillerNotificationAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IKillerNotificationAccessor &IKillerNotificationAccessor::operator=(IKillerNotificationAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result IKillerNotificationAccessor::GetWrapper(details::IKillerNotificationAccessorInternal *instance, nn::sl::KillerNotification *outBuffer, int *outNum, int outBufferNum) {
        return instance->vtable->instance->Get(outBuffer, outNum, outBufferNum);
    }

    details::IKillerNotificationAccessorInternal *IKillerNotificationAccessor::GetInternal() {
        return &mInstance;
    }

    void IKillerNotificationAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::KillerNotificationAccessorFromPtr::Get(nn::sl::KillerNotification *outBuffer, int *outNum, int outBufferNum) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outBuffer, outNum, outBufferNum);
    }

    nn::sl::details::IKillerNotificationAccessorInternal *details::KillerNotificationAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IKillerNotificationAccessorInternal *GetDefaultKillerNotificationAccessor__Q2_2nn2slFv();
    }

    static details::KillerNotificationAccessorFromPtr sDefaultKillerNotificationAccessor(GetDefaultKillerNotificationAccessor__Q2_2nn2slFv());

    details::IKillerNotificationAccessorBase &GetDefaultKillerNotificationAccessor() {
        return sDefaultKillerNotificationAccessor;
    }
} // namespace nn::sl