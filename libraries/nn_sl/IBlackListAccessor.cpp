#include <nn/sl/IBlackListAccessor.h>

namespace nn::sl {
    IBlackListAccessor::IBlackListAccessor() {
        InitInternalVtable();
    }

    IBlackListAccessor::IBlackListAccessor(IBlackListAccessor &src) {
        InitInternalVtable();
    }

    IBlackListAccessor &IBlackListAccessor::operator=(const IBlackListAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IBlackListAccessor &IBlackListAccessor::operator=(IBlackListAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result IBlackListAccessor::GetWrapper(details::IBlackListAccessorInternal *instance, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
        return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
    }

    details::IBlackListAccessorInternal *IBlackListAccessor::GetInternal() {
        return &mInstance;
    }

    void IBlackListAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::BlackListAccessorFromPtr::Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
    }

    nn::sl::details::IBlackListAccessorInternal *details::BlackListAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IBlackListAccessorInternal *GetDefaultBlackListAccessor__Q2_2nn2slFv();
    }

    static details::BlackListAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultBlackListAccessor__Q2_2nn2slFv());

    details::IBlackListAccessorBase &GetDefaultBlackListAccessor() {
        return sDefaultIconInfoAccessor;
    }

} // namespace nn::sl