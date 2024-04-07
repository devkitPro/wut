#pragma once

#include <coreinit/time.h>
#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ITimeAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class ITimeAccessor : public details::ITimeAccessorBase {

    public:
        ITimeAccessor() {
            InitInternalVtable();
        }

        ITimeAccessor(ITimeAccessor &src) {
            InitInternalVtable();
        }

        ITimeAccessor &operator=(const ITimeAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        ITimeAccessor &operator=(ITimeAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ITimeAccessor() override = default;

    private:
        static nn::Result GetNetworkTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut) {
            return instance->vtable->instance->GetNetworkTime(timeOut, successOut);
        }
        static nn::Result GetLocalTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut) {
            return instance->vtable->instance->GetLocalTime(timeOut, successOut);
        }

        details::ITimeAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance         = this,
                                .GetNetworkTimeFn = &GetNetworkTimeWrapper,
                                .GetLocalTimeFn   = &GetLocalTimeWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ITimeAccessorInternal mInstance{};
        details::ITimeAccessorInternalVTable mVTable{};
    };

    details::ITimeAccessorBase &GetDefaultTimeAccessor();
} // namespace nn::sl

#endif