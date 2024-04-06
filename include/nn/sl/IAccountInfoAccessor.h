#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IAccountInfoAccessorDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IAccountInfoAccessor : public details::IAccountInfoAccessorBase {

    public:
        IAccountInfoAccessor();

        IAccountInfoAccessor(IAccountInfoAccessor &src);

        IAccountInfoAccessor &operator=(const IAccountInfoAccessor &other);

        IAccountInfoAccessor &operator=(IAccountInfoAccessor &&src) noexcept;

        ~IAccountInfoAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IAccountInfoAccessorInternal *instance, AccountInfo *outAccountInfo);

        details::IAccountInfoAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IAccountInfoAccessorInternal mInstance{};
        details::IAccountInfoAccessorInternalVTable mVTable{};
    };

    details::IAccountInfoAccessorBase &GetDefaultAccountInfoAccessor();
} // namespace nn::sl

#endif