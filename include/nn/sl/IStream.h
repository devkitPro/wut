#pragma once

#include <nn/result.h>
#include <nn/sl/details/IStreamDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IStream : public details::IStreamBase {

    public:
        IStream() {
            InitInternalVtable();
        }

        IStream(IStream &src) {
            InitInternalVtable();
        }

        IStream &operator=(const IStream &other) {
            InitInternalVtable();
            return *this;
        }

        IStream &operator=(IStream &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IStream() override = default;

    private:
        static nn::Result ReadWrapper(details::IStreamInternal *instance, uint32_t *bytesRead, void *buffer, uint32_t readSize) {
            return instance->vtable->instance->Read(bytesRead, buffer, readSize);
        }

        static nn::Result WriteWrapper(details::IStreamInternal *instance, uint32_t *bytesWritten, void *buffer, uint32_t readSize) {
            return instance->vtable->instance->Write(bytesWritten, buffer, readSize);
        }

        static nn::Result GetSizeWrapper(details::IStreamInternal *instance, uint32_t *fileSize) {
            return instance->vtable->instance->GetSize(fileSize);
        }

        static nn::Result SeekWrapper(details::IStreamInternal *instance, int32_t offset, nn::sl::SeekOrigin seekOrigin) {
            return instance->vtable->instance->Seek(offset, seekOrigin);
        }

        details::IStreamInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance  = this,
                                .ReadFn    = &ReadWrapper,
                                .WriteFn   = &WriteWrapper,
                                .GetSizeFn = &GetSizeWrapper,
                                .SeekFn    = &SeekWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IStreamInternal mInstance{};
        details::IStreamInternalVTable mVTable{};
    };
} // namespace nn::sl

#endif