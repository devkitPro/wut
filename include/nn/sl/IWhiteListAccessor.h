#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IWhiteListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class IWhiteListAccessor : public details::IWhiteListAccessorBase {

    public:
        IWhiteListAccessor();

        IWhiteListAccessor(IWhiteListAccessor &src);

        IWhiteListAccessor &operator=(const IWhiteListAccessor &other);

        IWhiteListAccessor &operator=(IWhiteListAccessor &&src) noexcept;

        ~IWhiteListAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IWhiteListAccessorInternal *instance, nn::sl::WhiteList *outWhiteList);

        details::IWhiteListAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IWhiteListAccessorInternal mInstance{};
        details::IWhiteListAccessorInternalVTable mVTable{};
    };

    details::IWhiteListAccessorBase &GetDefaultWhiteListAccessor();
} // namespace nn::sl

#endif