#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ITimeAccessor;
    namespace details {
        struct ITimeAccessorInternal;

        typedef nn::Result (*ITimeAccessor_GetNetworkTimeFn)(ITimeAccessorInternal *, OSTime *, bool *);
        typedef nn::Result (*ITimeAccessor_GetLocalTimeFn)(ITimeAccessorInternal *, OSTime *, bool *);

        struct WUT_PACKED ITimeAccessorInternalVTable {
            ITimeAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ITimeAccessor_GetNetworkTimeFn GetNetworkTimeFn;
            WUT_PADDING_BYTES(4);
            ITimeAccessor_GetLocalTimeFn GetLocalTimeFn;
        };
        WUT_CHECK_SIZE(ITimeAccessorInternalVTable, 0x20);
        WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x14, GetNetworkTimeFn);
        WUT_CHECK_OFFSET(ITimeAccessorInternalVTable, 0x1C, GetLocalTimeFn);

        typedef struct WUT_PACKED ITimeAccessorInternal {
            ITimeAccessorInternalVTable *vtable;
        } ITimeAccessorInternal;
        WUT_CHECK_SIZE(ITimeAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(ITimeAccessorInternal, 0x00, vtable);

        extern "C" ITimeAccessorInternal *GetDefaultTimeAccessor__Q2_2nn2slFv();
    } // namespace details


    class ITimeAccessor {
        friend class Condition;

    public:
        ITimeAccessor() = default;

        virtual ~ITimeAccessor() = default;

        virtual nn::Result GetNetworkTime(OSTime *, bool *) = 0;
        virtual nn::Result GetLocalTime(OSTime *, bool *)   = 0;

    private:
        virtual details::ITimeAccessorInternal *GetInternal() = 0;
    };

    class ITimeAccessorBase : public ITimeAccessor {

    public:
        ITimeAccessorBase() {
            InitInternalVtable();
        }

        ITimeAccessorBase(ITimeAccessorBase &src) {
            InitInternalVtable();
        }

        ITimeAccessorBase &operator=(const ITimeAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        ITimeAccessorBase &operator=(ITimeAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ITimeAccessorBase() override = default;

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

    class TimeAccessorFromPtr : public ITimeAccessor {
    public:
        explicit TimeAccessorFromPtr(details::ITimeAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result GetNetworkTime(OSTime *outTime, bool *outSuccess) override {
            return mInstancePtr->vtable->GetNetworkTimeFn(mInstancePtr, outTime, outSuccess);
        }
        nn::Result GetLocalTime(OSTime *outTime, bool *outSuccess) override {
            return mInstancePtr->vtable->GetLocalTimeFn(mInstancePtr, outTime, outSuccess);
        }

    private:
        details::ITimeAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ITimeAccessorInternal *mInstancePtr;
    };

    TimeAccessorFromPtr GetDefaultTimeAccessor() {
        return TimeAccessorFromPtr(details::GetDefaultTimeAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif