#include <nn/sl/ISettingAccessor.h>

namespace nn::sl {
    ISettingAccessor::ISettingAccessor() {
        InitInternalVtable();
    }

    ISettingAccessor::ISettingAccessor(ISettingAccessor &src) {
        InitInternalVtable();
    }

    ISettingAccessor &ISettingAccessor::operator=(const ISettingAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    ISettingAccessor &ISettingAccessor::operator=(ISettingAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result ISettingAccessor::GetWrapper(details::ISettingAccessorInternal *instance, Setting *outSetting) {
        return instance->vtable->instance->Get(outSetting);
    }

    details::ISettingAccessorInternal *ISettingAccessor::GetInternal() {
        return &mInstance;
    }

    void ISettingAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::SettingAccessorFromPtr::Get(nn::sl::Setting *outSetting) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outSetting);
    }

    details::ISettingAccessorInternal *details::SettingAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::ISettingAccessorInternal *GetDefaultSettingAccessor__Q2_2nn2slFv();
    }

    static details::SettingAccessorFromPtr sDefaultSettingAccessor(GetDefaultSettingAccessor__Q2_2nn2slFv());

    details::ISettingAccessorBase &GetDefaultSettingAccessor() {
        return sDefaultSettingAccessor;
    }
} // namespace nn::sl