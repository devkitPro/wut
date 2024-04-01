#pragma once
#include "KillerNotificationTransferRecordStream.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    struct KillerNotificationTransferRecord {
        WUT_UNKNOWN_BYTES(0x18);
    };
    WUT_CHECK_SIZE(KillerNotificationTransferRecord, 0x18);

    namespace {
        struct KillerNotificationTransferRecordManagerInternalInternal;

        typedef nn::Result (*KillerNotificationTransferRecordManagerInternal_LoadFn)(KillerNotificationTransferRecordManagerInternalInternal *, KillerNotificationTransferRecordStreamInternal * /* IStream*/);
        typedef nn::Result (*KillerNotificationTransferRecordManagerInternal_LoadInitialFn)(KillerNotificationTransferRecordManagerInternalInternal *);
        typedef nn::Result (*KillerNotificationTransferRecordManagerInternal_StoreFn)(KillerNotificationTransferRecordManagerInternalInternal *, KillerNotificationTransferRecordStreamInternal * /* IStream*/);
        typedef void (*KillerNotificationTransferRecordManagerInternal_FinalizeFn)(KillerNotificationTransferRecordManagerInternalInternal *);
        typedef uint32_t (*KillerNotificationTransferRecordManagerInternal_GetRecordCountFn)(KillerNotificationTransferRecordManagerInternalInternal *);
        typedef uint32_t (*KillerNotificationTransferRecordManagerInternal_GetRecordsFn)(KillerNotificationTransferRecordManagerInternalInternal *, KillerNotificationTransferRecord *, uint32_t);
        typedef nn::Result (*KillerNotificationTransferRecordManagerInternal_RegisterRecordsFn)(KillerNotificationTransferRecordManagerInternalInternal *, const KillerNotificationTransferRecord *, uint32_t);
        typedef nn::Result (*KillerNotificationTransferRecordManagerInternal_RegisterRecordsOtherFn)(KillerNotificationTransferRecordManagerInternalInternal *, const uint32_t *, uint32_t);

        typedef struct WUT_PACKED KillerNotificationTransferRecordManagerInternalVTable {
            WUT_UNKNOWN_BYTES(0x14);
            KillerNotificationTransferRecordManagerInternal_LoadFn loadFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_LoadInitialFn loadInitialFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_StoreFn storeFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_FinalizeFn finalizeFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_GetRecordCountFn getRecordCountFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_GetRecordsFn getRecordsFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_RegisterRecordsFn registerRecordsFn;
            WUT_UNKNOWN_BYTES(0x4);
            KillerNotificationTransferRecordManagerInternal_RegisterRecordsOtherFn registerRecordsOtherFn;
        } KillerNotificationTransferRecordManagerInternalVTable;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordManagerInternalVTable, 0x50);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x14, loadFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x1C, loadInitialFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x24, storeFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x2C, finalizeFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x34, getRecordCountFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x3C, getRecordsFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x44, registerRecordsFn);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalVTable, 0x4C, registerRecordsOtherFn);

        typedef struct WUT_PACKED KillerNotificationTransferRecordManagerInternalInternal {
            KillerNotificationTransferRecordManagerInternalVTable *vtable;
            void *killerNotificationTransferRecordManagerImpl;
        } KillerNotificationTransferRecordManagerInternalInternal;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordManagerInternalInternal, 0x8);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x00, vtable);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x04, killerNotificationTransferRecordManagerImpl);

        extern "C" KillerNotificationTransferRecordManagerInternalInternal *__ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *);
        extern "C" void *__dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *, int);
    } // namespace

    class KillerNotificationTransferRecordManagerInternal {
    public:
        KillerNotificationTransferRecordManagerInternal() {
            __ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance);
        }

        ~KillerNotificationTransferRecordManagerInternal() {
            __dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance, 2);
        }

        nn::Result Load(KillerNotificationTransferRecordStream *stream) {
            return mInstance.vtable->loadFn(&mInstance, &stream->mInstance);
        }

        nn::Result LoadInitial() {
            return mInstance.vtable->loadInitialFn(&mInstance);
        }

        nn::Result Store(KillerNotificationTransferRecordStream *stream) {
            return mInstance.vtable->storeFn(&mInstance, &stream->mInstance);
        }

        void Finalize(void *stream) {
            return mInstance.vtable->finalizeFn(&mInstance);
        }

        uint32_t GetRecordCount() {
            return mInstance.vtable->getRecordCountFn(&mInstance);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) {
            return mInstance.vtable->getRecordsFn(&mInstance, u1, u2);
        }

        nn::Result RegisterRecords(const KillerNotificationTransferRecord *u1, uint32_t u2) {
            return mInstance.vtable->registerRecordsFn(&mInstance, u1, u2);
        }

        nn::Result RegisterRecords(const uint32_t *u1, uint32_t u2) {
            return mInstance.vtable->registerRecordsOtherFn(&mInstance, u1, u2);
        }

    private:
        KillerNotificationTransferRecordManagerInternalInternal mInstance = {};
    };
} // namespace nn::sl
#endif