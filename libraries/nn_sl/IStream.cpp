#include <nn/sl/IStream.h>

namespace nn::sl {
    IStream::IStream() {
        InitInternalVtable();
    }

    IStream::IStream(IStream &src) {
        InitInternalVtable();
    }

    IStream &IStream::operator=(const IStream &other) {
        InitInternalVtable();
        return *this;
    }

    IStream &IStream::operator=(IStream &&src) noexcept {
        InitInternalVtable();
        return *this;
    }

    nn::Result IStream::ReadWrapper(details::IStreamInternal *instance, uint32_t *bytesRead, void *buffer, uint32_t readSize) {
        return instance->vtable->instance->Read(bytesRead, buffer, readSize);
    }

    nn::Result IStream::WriteWrapper(details::IStreamInternal *instance, uint32_t *bytesWritten, void *buffer, uint32_t readSize) {
        return instance->vtable->instance->Write(bytesWritten, buffer, readSize);
    }
    nn::Result IStream::GetSizeWrapper(details::IStreamInternal *instance, uint32_t *fileSize) {
        return instance->vtable->instance->GetSize(fileSize);
    }
    nn::Result IStream::SeekWrapper(details::IStreamInternal *instance, int32_t offset, nn::sl::SeekOrigin seekOrigin) {
        return instance->vtable->instance->Seek(offset, seekOrigin);
    }

    details::IStreamInternal *IStream::GetInternal() {
        return &mInstance;
    }

    void IStream::InitInternalVtable() {
        mVTable          = {.instance  = this,
                            .ReadFn    = &ReadWrapper,
                            .WriteFn   = &WriteWrapper,
                            .GetSizeFn = &GetSizeWrapper,
                            .SeekFn    = &SeekWrapper};
        mInstance.vtable = &mVTable;
    } // namespace nn::sl


} // namespace nn::sl