#include <nn/sl/IWhiteListAccessor.h>

namespace nn::sl {
    IWhiteListAccessor::IWhiteListAccessor() {
        InitInternalVtable();
    }

    IWhiteListAccessor::IWhiteListAccessor(IWhiteListAccessor &src) {
        InitInternalVtable();
    }

    IWhiteListAccessor &IWhiteListAccessor::operator=(const IWhiteListAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IWhiteListAccessor &IWhiteListAccessor::operator=(IWhiteListAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result IWhiteListAccessor::GetWrapper(details::IWhiteListAccessorInternal *instance, nn::sl::WhiteList *outWhiteList) {
        return instance->vtable->instance->Get(outWhiteList);
    }

    details::IWhiteListAccessorInternal *IWhiteListAccessor::GetInternal() {
        return &mInstance;
    }

    void IWhiteListAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::WhiteListAccessorFromPtr::Get(nn::sl::WhiteList *outWhiteList) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outWhiteList);
    }

    nn::sl::details::IWhiteListAccessorInternal *details::WhiteListAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IWhiteListAccessorInternal *GetDefaultWhiteListAccessor__Q2_2nn2slFv();
    }

    static details::WhiteListAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultWhiteListAccessor__Q2_2nn2slFv());

    details::IWhiteListAccessorBase &GetDefaultWhiteListAccessor() {
        return sDefaultIconInfoAccessor;
    }

} // namespace nn::sl