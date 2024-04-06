#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IKillerNotificationAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IKillerNotificationAccessor : public details::IKillerNotificationAccessorBase {

    public:
        IKillerNotificationAccessor();

        IKillerNotificationAccessor(IKillerNotificationAccessor &src);

        IKillerNotificationAccessor &operator=(const IKillerNotificationAccessor &other);

        IKillerNotificationAccessor &operator=(IKillerNotificationAccessor &&src) noexcept;

        ~IKillerNotificationAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IKillerNotificationAccessorInternal *instance, KillerNotification *outBuffer, int *outNum, int outBufferNum);

        details::IKillerNotificationAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IKillerNotificationAccessorInternal mInstance{};
        details::IKillerNotificationAccessorInternalVTable mVTable{};
    };


    details::IKillerNotificationAccessorBase &GetDefaultKillerNotificationAccessor();
} // namespace nn::sl

#endif