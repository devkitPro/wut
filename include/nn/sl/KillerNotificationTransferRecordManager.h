#pragma once

#include "FileStream.h"
#include "KillerNotificationTransferRecordManagerInternal.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    namespace details {
        typedef struct WUT_PACKED KillerNotificationTransferRecordManagerRealIntern {
            void *vtable;
            void *killerNotificationTransferRecordManagerImpl;
        } KillerNotificationTransferRecordManagerRealIntern;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordManagerRealIntern, 0x8);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerRealIntern, 0x00, vtable);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerRealIntern, 0x04, killerNotificationTransferRecordManagerImpl);

        extern "C" KillerNotificationTransferRecordManagerRealIntern *__ct__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(KillerNotificationTransferRecordManagerRealIntern *);
        extern "C" void *__dt__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(KillerNotificationTransferRecordManagerRealIntern *, int);
        extern "C" void Finalize__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(KillerNotificationTransferRecordManagerRealIntern *);
        extern "C" nn::Result Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(KillerNotificationTransferRecordManagerRealIntern *, details::IStreamInternal *);
        extern "C" uint32_t GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv(KillerNotificationTransferRecordManagerRealIntern *);
        extern "C" uint32_t GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi(KillerNotificationTransferRecordManagerRealIntern *, KillerNotificationTransferRecord *, uint32_t);
        extern "C" void RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(KillerNotificationTransferRecordManagerRealIntern *, KillerNotificationTransferRecord *, uint32_t);
        extern "C" nn::Result Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(KillerNotificationTransferRecordManagerRealIntern *, details::IStreamInternal *);
    } // namespace details

    class KillerNotificationTransferRecordManager {
    public:
        KillerNotificationTransferRecordManager() {
            __ct__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        ~KillerNotificationTransferRecordManager() {
            __dt__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance, 2);
        }

        void Finalize() {
            Finalize__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        nn::Result Load(IStream *stream) {
            return Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(&mInstance, stream->getStream());
        }

        nn::Result Store(IStream *stream) {
            return Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(&mInstance, stream->getStream());
        }

        uint32_t GetRecordCount() {
            return GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv(&mInstance);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) {
            return GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi(&mInstance, u1, u2);
        }

        void RegisterRecords(KillerNotificationTransferRecord *u1, uint32_t u2) {
            RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(&mInstance, u1, u2);
        }

    private:
        details::KillerNotificationTransferRecordManagerRealIntern mInstance = {};
    };
} // namespace nn::sl

#endif