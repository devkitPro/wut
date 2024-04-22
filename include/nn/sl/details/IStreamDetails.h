#pragma once

#include <coreinit/filesystem.h>
#include <nn/result.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class LaunchInfoDatabase;
    class KillerNotificationTransferRecordManager;
    class KillerNotificationTransferRecordManagerInternal;

    namespace details {
        class KillerNotificationTransferRecordManagerFromPtr;
        class IStreamBase;
        struct IStreamInternal;

        typedef nn::Result (*IStream_ReadFn)(IStreamInternal *, uint32_t *bytesRead, void *buffer, uint32_t readSize);
        typedef nn::Result (*IStream_WriteFn)(IStreamInternal *, uint32_t *bytesWritten, void *buffer, uint32_t writeSize);
        typedef nn::Result (*IStream_GetSizeFn)(IStreamInternal *, uint32_t *fileSize);
        typedef nn::Result (*IStream_SeekFn)(IStreamInternal *, int32_t offset, nn::sl::SeekOrigin seekOrigin);

        struct WUT_PACKED IStreamInternalVTable {
            IStreamBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IStream_ReadFn ReadFn;
            WUT_PADDING_BYTES(4);
            IStream_WriteFn WriteFn;
            WUT_PADDING_BYTES(4);
            IStream_GetSizeFn GetSizeFn;
            WUT_PADDING_BYTES(4);
            IStream_SeekFn SeekFn;
        };
        WUT_CHECK_SIZE(IStreamInternalVTable, 0x30);
        WUT_CHECK_OFFSET(IStreamInternalVTable, 0x14, ReadFn);
        WUT_CHECK_OFFSET(IStreamInternalVTable, 0x1C, WriteFn);
        WUT_CHECK_OFFSET(IStreamInternalVTable, 0x24, GetSizeFn);
        WUT_CHECK_OFFSET(IStreamInternalVTable, 0x2C, SeekFn);

        typedef struct WUT_PACKED IStreamInternal {
            IStreamInternalVTable *vtable;
        } IStreamInternal;
        WUT_CHECK_SIZE(IStreamInternal, 0x04);

        class IStreamBase {
            friend class nn::sl::LaunchInfoDatabase;
            friend class nn::sl::KillerNotificationTransferRecordManager;
            friend class nn::sl::KillerNotificationTransferRecordManagerInternal;
            friend class nn::sl::details::KillerNotificationTransferRecordManagerFromPtr;

        public:
            IStreamBase() = default;

            virtual ~IStreamBase() = default;

            virtual nn::Result Read(uint32_t *bytesRead, void *buffer, uint32_t readSize)      = 0;
            virtual nn::Result Write(uint32_t *bytesWritten, void *buffer, uint32_t writeSize) = 0;
            virtual nn::Result GetSize(uint32_t *fileSize)                                     = 0;
            virtual nn::Result Seek(int32_t offset, nn::sl::SeekOrigin seekOrigin)             = 0;

        private:
            virtual details::IStreamInternal *GetInternal() = 0;
        };


    } // namespace details


} // namespace nn::sl

#endif