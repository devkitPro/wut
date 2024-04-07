#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IAccountInfoAccessorDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IAccountInfoAccessor : public details::IAccountInfoAccessorBase {

    public:
        IAccountInfoAccessor() {
            InitInternalVtable();
        }

        IAccountInfoAccessor(IAccountInfoAccessor &src) {
            InitInternalVtable();
        }

        IAccountInfoAccessor &operator=(const IAccountInfoAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        IAccountInfoAccessor &operator=(IAccountInfoAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IAccountInfoAccessor() override = default;

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

    details::IAccountInfoAccessorBase &GetDefaultAccountInfoAccessor();
} // namespace nn::sl

#endif