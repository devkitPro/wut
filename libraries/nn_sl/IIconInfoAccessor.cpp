#include <nn/sl/IIconInfoAccessor.h>

namespace nn::sl {
    IIconInfoAccessor::IIconInfoAccessor() {
        InitInternalVtable();
    }

    IIconInfoAccessor::IIconInfoAccessor(IIconInfoAccessor &src) {
        InitInternalVtable();
    }

    IIconInfoAccessor &IIconInfoAccessor::operator=(const IIconInfoAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    IIconInfoAccessor &IIconInfoAccessor::operator=(IIconInfoAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result IIconInfoAccessor::GetTitleIconInfoWrapper(details::IIconInfoAccessorInternal *instance, nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) {
        return instance->vtable->instance->GetTitleIconInfo(outIconInfo, titleInfo, language);
    }
    nn::Result IIconInfoAccessor::GetMiiIconWrapper(details::IIconInfoAccessorInternal *instance, void *buffer, uint32_t buffer_size, uint32_t slot) {
        return instance->vtable->instance->GetMiiIcon(buffer, buffer_size, slot);
    }

    details::IIconInfoAccessorInternal *IIconInfoAccessor::GetInternal() {
        return &mInstance;
    }

    void IIconInfoAccessor::InitInternalVtable() {
        mVTable          = {.instance           = this,
                            .getTitleIconInfoFn = GetTitleIconInfoWrapper,
                            .getMiiIconFn       = GetMiiIconWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::IconInfoAccessorFromPtr::GetTitleIconInfo(nn::sl::IconInfo *outIconInfo, const TitleInfo &titleInfo, nn::sl::Language language) {
        return mInstancePtr->vtable->getTitleIconInfoFn(mInstancePtr, outIconInfo, titleInfo, language);
    }

    nn::Result details::IconInfoAccessorFromPtr::GetMiiIcon(void *buffer, uint32_t buffer_size, uint32_t slot) {
        return mInstancePtr->vtable->getMiiIconFn(mInstancePtr, buffer, buffer_size, slot);
    }

    nn::sl::details::IIconInfoAccessorInternal *details::IconInfoAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::IIconInfoAccessorInternal *GetDefaultIconInfoAccessor__Q2_2nn2slFv();
    }

    static details::IconInfoAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultIconInfoAccessor__Q2_2nn2slFv());

    details::IIconInfoAccessorBase &GetDefaultIconInfoAccessor() {
        return sDefaultIconInfoAccessor;
    }

} // namespace nn::sl