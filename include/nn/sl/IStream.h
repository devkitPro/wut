#pragma once

#include <nn/result.h>
#include <nn/sl/details/IStreamDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IStream : public details::IStreamBase {

    public:
        IStream();

        IStream(IStream &src);

        IStream &operator=(const IStream &other);

        IStream &operator=(IStream &&src) noexcept;

        ~IStream() override = default;

    private:
        static nn::Result ReadWrapper(details::IStreamInternal *instance, uint32_t *bytesRead, void *buffer, uint32_t readSize);
        static nn::Result WriteWrapper(details::IStreamInternal *instance, uint32_t *bytesWritten, void *buffer, uint32_t readSize);
        static nn::Result GetSizeWrapper(details::IStreamInternal *instance, uint32_t *fileSize);
        static nn::Result SeekWrapper(details::IStreamInternal *instance, int32_t offset, nn::sl::SeekOrigin seekOrigin);

        details::IStreamInternal *GetInternal() override;

        void InitInternalVtable();

        details::IStreamInternal mInstance{};
        details::IStreamInternalVTable mVTable{};
    };
} // namespace nn::sl

#endif