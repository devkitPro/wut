#include <nn/sl/IAccountInfoAccessor.h>

namespace nn::sl {
    IAccountInfoAccessor::IAccountInfoAccessor() {
        InitInternalVtable();
    }

    IAccountInfoAccessor::IAccountInfoAccessor(IAccountInfoAccessor &src) {
        InitInternalVtable();
    }

    IAccountInfoAccessor &IAccountInfoAccessor::operator=(const IAccountInfoAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IAccountInfoAccessor &IAccountInfoAccessor::operator=(IAccountInfoAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result IAccountInfoAccessor::GetWrapper(details::IAccountInfoAccessorInternal *instance, AccountInfo *outAccountInfo) {
        return instance->vtable->instance->Get(outAccountInfo);
    }

    details::IAccountInfoAccessorInternal *IAccountInfoAccessor::GetInternal() {
        return &mInstance;
    }

    void IAccountInfoAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::AccountInfoAccessorFromPtr::Get(nn::sl::AccountInfo *outAccountInfo) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outAccountInfo);
    }

    details::IAccountInfoAccessorInternal *details::AccountInfoAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IAccountInfoAccessorInternal *GetDefaultAccountInfoAccessor__Q2_2nn2slFv();
    }

    static details::AccountInfoAccessorFromPtr gAccountInfoAccessor(GetDefaultAccountInfoAccessor__Q2_2nn2slFv());

    details::IAccountInfoAccessorBase &GetDefaultAccountInfoAccessor() {
        return gAccountInfoAccessor;
    }
} // namespace nn::sl