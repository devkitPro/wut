#include <nn/sl/ITimeAccessor.h>

namespace nn::sl {
    ITimeAccessor::ITimeAccessor() {
        InitInternalVtable();
    }

    ITimeAccessor::ITimeAccessor(ITimeAccessor &src) {
        InitInternalVtable();
    }

    ITimeAccessor &ITimeAccessor::operator=(const ITimeAccessor &other) {
        InitInternalVtable();
        return *this;
    }

    ITimeAccessor &ITimeAccessor::operator=(ITimeAccessor &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result ITimeAccessor::GetNetworkTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut) {
        return instance->vtable->instance->GetNetworkTime(timeOut, successOut);
    }

    nn::Result ITimeAccessor::GetLocalTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut) {
        return instance->vtable->instance->GetLocalTime(timeOut, successOut);
    }

    details::ITimeAccessorInternal *ITimeAccessor::GetInternal() {
        return &mInstance;
    }

    void ITimeAccessor::InitInternalVtable() {
        mVTable          = {.instance         = this,
                            .GetNetworkTimeFn = &GetNetworkTimeWrapper,
                            .GetLocalTimeFn   = &GetLocalTimeWrapper};
        mInstance.vtable = &mVTable;
    }

    namespace {
        extern "C" details::ITimeAccessorInternal *GetDefaultTimeAccessor__Q2_2nn2slFv();
    }

    static details::TimeAccessorFromPtr sDefaultTimeAccessor(GetDefaultTimeAccessor__Q2_2nn2slFv());

    details::ITimeAccessorBase &GetDefaultTimeAccessor() {
        return sDefaultTimeAccessor;
    }
} // namespace nn::sl