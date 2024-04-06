#pragma once

#include "FileStream.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED KillerNotificationTransferRecordStreamInternal {
            void *vtable;
            FileStreamInternal fileStream;
            uint32_t unkn1;
            WUT_UNKNOWN_BYTES(0x84);
        } KillerNotificationTransferRecordStreamInternal;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordStreamInternal, 0x9C);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x00, vtable);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x04, fileStream);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordStreamInternal, 0x14, unkn1);

        extern "C" KillerNotificationTransferRecordStreamInternal *GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv();
    } // namespace details

    class KillerNotificationTransferRecordStream : public IStream {
    public:
        explicit KillerNotificationTransferRecordStream(details::KillerNotificationTransferRecordStreamInternal *instance) : mInstance(instance) {
        }

        ~KillerNotificationTransferRecordStream() override = default;

        details::IStreamInternal *getStream() override {
            return reinterpret_cast<details::IStreamInternal *>(mInstance);
        }

    private:
        details::KillerNotificationTransferRecordStreamInternal *mInstance = {};
    };

    KillerNotificationTransferRecordStream GetDefaultKillerNotificationTransferRecordStream() {
        return KillerNotificationTransferRecordStream(details::GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif