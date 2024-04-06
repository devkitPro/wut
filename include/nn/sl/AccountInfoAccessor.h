#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IAccountInfoAccessor;
    namespace details {
        struct IAccountInfoAccessorInternal;

        typedef nn::Result (*IAccountInfoAccessor_GetFn)(IAccountInfoAccessorInternal *, AccountInfo *);

        struct WUT_PACKED IAccountInfoAccessorInternalVTable {
            IAccountInfoAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IAccountInfoAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IAccountInfoAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IAccountInfoAccessorInternal {
            IAccountInfoAccessorInternalVTable *vtable;
        } IAccountInfoAccessorInternal;
        WUT_CHECK_SIZE(IAccountInfoAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IAccountInfoAccessorInternal, 0x00, vtable);

        extern "C" IAccountInfoAccessorInternal *GetDefaultAccountInfoAccessor__Q2_2nn2slFv();
    } // namespace details


    class IAccountInfoAccessor {
        friend class DataCreator;
        friend class KillerNotificationSelector;

    public:
        IAccountInfoAccessor() = default;

        virtual ~IAccountInfoAccessor() = default;

        virtual nn::Result Get(nn::sl::AccountInfo *) = 0;

    private:
        virtual details::IAccountInfoAccessorInternal *GetInternal() = 0;
    };

    class IAccountInfoAccessorBase : public IAccountInfoAccessor {

    public:
        IAccountInfoAccessorBase() {
            InitInternalVtable();
        }

        IAccountInfoAccessorBase(IAccountInfoAccessorBase &src) {
            InitInternalVtable();
        }

        IAccountInfoAccessorBase &operator=(const IAccountInfoAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IAccountInfoAccessorBase &operator=(IAccountInfoAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IAccountInfoAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IAccountInfoAccessorInternal *instance, AccountInfo *outAccountInfo) {
            return instance->vtable->instance->Get(outAccountInfo);
        }

        details::IAccountInfoAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IAccountInfoAccessorInternal mInstance{};
        details::IAccountInfoAccessorInternalVTable mVTable{};
    };

    class AccountInfoAccessorFromPtr : public IAccountInfoAccessor {
    public:
        explicit AccountInfoAccessorFromPtr(details::IAccountInfoAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(nn::sl::AccountInfo *outAccountInfo) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outAccountInfo);
        }

    private:
        details::IAccountInfoAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IAccountInfoAccessorInternal *mInstancePtr;
    };

    AccountInfoAccessorFromPtr GetDefaultAccountInfoAccessor() {
        return AccountInfoAccessorFromPtr(details::GetDefaultAccountInfoAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif