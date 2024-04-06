#include <nn/sl/IPreferentialTitleAccessor.h>

namespace nn::sl {
    IPreferentialTitleAccessor::IPreferentialTitleAccessor() {
        InitInternalVtable();
    }
    IPreferentialTitleAccessor::IPreferentialTitleAccessor(IPreferentialTitleAccessor &src) {
        InitInternalVtable();
    }
    IPreferentialTitleAccessor &IPreferentialTitleAccessor::operator=(const IPreferentialTitleAccessor &other) {
        InitInternalVtable();
        return *this;
    }
    IPreferentialTitleAccessor &IPreferentialTitleAccessor::operator=(IPreferentialTitleAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result IPreferentialTitleAccessor::GetWrapper(details::IPreferentialTitleAccessorInternal *instance, TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) {
        return instance->vtable->instance->Get(outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
    }
    details::IPreferentialTitleAccessorInternal *IPreferentialTitleAccessor::GetInternal() {
        return &mInstance;
    }
    void IPreferentialTitleAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::PreferentialTitleAccessorFromPtr::Get(TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
    }

    details::IPreferentialTitleAccessorInternal *details::PreferentialTitleAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }
    namespace {
        extern "C" details::IPreferentialTitleAccessorInternal *GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv();
    }

    static details::PreferentialTitleAccessorFromPtr sDefaultPreferentialTitleAccessor(GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv());

    details::IPreferentialTitleAccessorBase &GetDefaultPreferentialTitleAccessor() {
        return sDefaultPreferentialTitleAccessor;
    }

} // namespace nn::sl
