#include <nn/sl/IDefaultTitleAccessor.h>

namespace nn::sl {
    IDefaultTitleAccessor::IDefaultTitleAccessor() {
        InitInternalVtable();
    }

    IDefaultTitleAccessor::IDefaultTitleAccessor(IDefaultTitleAccessor &src) {
        InitInternalVtable();
    }

    IDefaultTitleAccessor &IDefaultTitleAccessor::operator=(const IDefaultTitleAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IDefaultTitleAccessor &IDefaultTitleAccessor::operator=(IDefaultTitleAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }
    nn::Result IDefaultTitleAccessor::GetWrapper(details::IDefaultTitleAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
        return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
    }

    details::IDefaultTitleAccessorInternal *IDefaultTitleAccessor::GetInternal() {
        return &mInstance;
    }

    void IDefaultTitleAccessor::InitInternalVtable() {
        mVTable          = {.instance = this,
                            .GetFn    = &GetWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::DefaultTitleAccessorFromPtr::Get(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
        return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
    }

    nn::sl::details::IDefaultTitleAccessorInternal *details::DefaultTitleAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IDefaultTitleAccessorInternal *GetDefaultDefaultTitleAccessor__Q2_2nn2slFv();
    }

    static details::DefaultTitleAccessorFromPtr sDefaultDefaultTitleAccessor(GetDefaultDefaultTitleAccessor__Q2_2nn2slFv());

    details::IDefaultTitleAccessorBase &GetDefaultDefaultTitleAccessor() {
        return sDefaultDefaultTitleAccessor;
    }

} // namespace nn::sl