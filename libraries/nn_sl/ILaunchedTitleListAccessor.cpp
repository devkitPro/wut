#include <coreinit/debug.h>
#include <nn/sl/ILaunchedTitleListAccessor.h>
#include <nn/sl/sl_cpp.h>

namespace nn::sl {
    ILaunchedTitleListAccessor::ILaunchedTitleListAccessor() {
        InitInternalVtable();
    }

    ILaunchedTitleListAccessor::ILaunchedTitleListAccessor(ILaunchedTitleListAccessor &src) {
        InitInternalVtable();
    }

    ILaunchedTitleListAccessor &ILaunchedTitleListAccessor::operator=(const ILaunchedTitleListAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    ILaunchedTitleListAccessor &ILaunchedTitleListAccessor::operator=(ILaunchedTitleListAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result ILaunchedTitleListAccessor::GetByAccountWrapper(details::ILaunchedTitleListAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) {
        return instance->vtable->instance->GetByAccount(outTitleInfos, outTitleInfoSize, inTitleInfosSize, userId);
    }

    details::ILaunchedTitleListAccessorInternal *ILaunchedTitleListAccessor::GetInternal() {
        return &mInstance;
    }

    void ILaunchedTitleListAccessor::InitInternalVtable() {
        mVTable          = {.instance       = this,
                            .GetByAccountFn = &GetByAccountWrapper};
        mInstance.vtable = &mVTable;
    }

    nn::Result details::LaunchedTitleListAccessorFromPtr::GetByAccount(nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) {
        return mInstancePtr->vtable->GetByAccountFn(mInstancePtr, outTitleInfos, outTitleInfoSize, inTitleInfosSize, userId);
    }

    details::ILaunchedTitleListAccessorInternal *details::LaunchedTitleListAccessorFromPtr::GetInternal() {
        return mInstancePtr;
    }

    namespace {
        extern "C" details::ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(LaunchedTitleListAccessorType type);
        extern "C" details::ILaunchedTitleListAccessorInternal *GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFv();
    } // namespace
    static details::LaunchedTitleListAccessorFromPtr sDefaultLaunchedTitleListAccessorType0(GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(TITLE_LIST_ACCESSOR_LAUNCHED_TITLES));
    static details::LaunchedTitleListAccessorFromPtr sDefaultLaunchedTitleListAccessorType1(GetDefaultLaunchedTitleListAccessor__Q2_2nn2slFQ3_2nn2sl29LaunchedTitleListAccessorType(TITLE_LIST_ACCESSOR_PLAY_STATS));

    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor(LaunchedTitleListAccessorType type) {
        if (type == TITLE_LIST_ACCESSOR_LAUNCHED_TITLES) {
            return sDefaultLaunchedTitleListAccessorType0;
        } else if (type == TITLE_LIST_ACCESSOR_PLAY_STATS) {
            return sDefaultLaunchedTitleListAccessorType1;
        }
        OSFatal("Called GetDefaultLaunchedTitleListAccessor with invalid type");
        // not reached
        return sDefaultLaunchedTitleListAccessorType1;
    }
    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor() {
        return sDefaultLaunchedTitleListAccessorType0;
    }
} // namespace nn::sl