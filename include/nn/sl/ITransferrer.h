#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ITransferrerDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ITransferrer : public details::ITransferrerBase {

    public:
        ITransferrer();

        ITransferrer(ITransferrer &src);

        ITransferrer &operator=(const ITransferrer &other);

        ITransferrer &operator=(ITransferrer &&src) noexcept;

        ~ITransferrer() override = default;

    private:
        static nn::Result TransferDeprecatedWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, int transferMode);
        static nn::Result TransferWrapper(details::ITransferrerInternal *instance, void *buffer, uint32_t size, bool setKillerNotification, TransferMode transferMode);
        static nn::Result CancelTransferWrapper(details::ITransferrerInternal *instance);
        static nn::Result InvalidateNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1);
        static nn::Result DisplayNotificationWrapper(details::ITransferrerInternal *instance, uint32_t u1, uint32_t u2, uint32_t u3);

        details::ITransferrerInternal *GetInternal() override;

        void InitInternalVtable();

        details::ITransferrerInternal mInstance{};
        details::ITransferrerInternalVTable mVTable{};
    };

    details::ITransferrerBase &GetDrcTransferrer();
} // namespace nn::sl

#endif