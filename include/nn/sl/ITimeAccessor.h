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
        ITimeAccessor();

        ITimeAccessor(ITimeAccessor &src);

        ITimeAccessor &operator=(const ITimeAccessor &other);

        ITimeAccessor &operator=(ITimeAccessor &&src) noexcept;

        ~ITimeAccessor() override = default;

    private:
        static nn::Result GetNetworkTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut);
        static nn::Result GetLocalTimeWrapper(details::ITimeAccessorInternal *instance, OSTime *timeOut, bool *successOut);

        details::ITimeAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::ITimeAccessorInternal mInstance{};
        details::ITimeAccessorInternalVTable mVTable{};
    };

    details::ITimeAccessorBase &GetDefaultTimeAccessor();
} // namespace nn::sl

#endif