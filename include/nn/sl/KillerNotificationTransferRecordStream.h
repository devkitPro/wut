#pragma once
#include "nn/sl/FileStream.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus
namespace nn::sl {
    namespace {
        typedef struct WUT_PACKED KillerNotificationTransferRecordStreamInternal {
            void *vtable;
            FileStreamInternal *fileStream;
            WUT_UNKNOWN_BYTES(0x0C);
            uint32_t unkn1;
            WUT_UNKNOWN_BYTES(0x84);
        } KillerNotificationTransferRecordStreamInternal;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordStreamInternal, 0x9C);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x00, vtable);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x04, fileStream);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x14, unkn1);

        extern "C" KillerNotificationTransferRecordStreamInternal *GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv();
    } // namespace

    class KillerNotificationTransferRecordStream {
        friend class KillerNotificationTransferRecordManagerInternal;

    public:
        KillerNotificationTransferRecordStream(KillerNotificationTransferRecordStreamInternal *instance) : mInstance(instance) {
        }

        ~KillerNotificationTransferRecordStream() = default;

    private:
        KillerNotificationTransferRecordStreamInternal mInstance = {};
    };

    KillerNotificationTransferRecordStream GetDefaultKillerNotificationTransferRecordStream() {
        return {GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv()};
    }
} // namespace nn::sl
#endif