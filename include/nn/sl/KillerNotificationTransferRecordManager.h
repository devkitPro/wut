#pragma once

#include "FileStream.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    namespace details {
        struct IKillerNotificationTransferRecordManagerInternal;
        typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_LoadFn)(IKillerNotificationTransferRecordManagerInternal *, nn::sl::details::IStreamInternal *);
        typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_LoadInitialFn)(IKillerNotificationTransferRecordManagerInternal *);
        typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_StoreFn)(IKillerNotificationTransferRecordManagerInternal *, nn::sl::details::IStreamInternal *);
        typedef void (*IKillerNotificationTransferRecordManagerInternVTable_FinalizeFn)(IKillerNotificationTransferRecordManagerInternal *);
        typedef uint32_t (*IKillerNotificationTransferRecordManagerInternVTable_GetRecordCountFn)(IKillerNotificationTransferRecordManagerInternal *);
        typedef uint32_t (*IKillerNotificationTransferRecordManagerInternVTable_GetRecordsFn)(IKillerNotificationTransferRecordManagerInternal *, KillerNotificationTransferRecord *, uint32_t);
        typedef void (*IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsFn)(IKillerNotificationTransferRecordManagerInternal *, const KillerNotificationTransferRecord *, uint32_t);
        typedef nn::Result (*IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsOtherFn)(IKillerNotificationTransferRecordManagerInternal *, const uint32_t *, uint32_t);

        typedef struct WUT_PACKED IKillerNotificationTransferRecordManagerInternVTable {
            WUT_UNKNOWN_BYTES(0x14);
            IKillerNotificationTransferRecordManagerInternVTable_LoadFn LoadFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_LoadInitialFn LoadInitialFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_StoreFn StoreFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_FinalizeFn FinalizeFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_GetRecordCountFn GetRecordCountFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_GetRecordsFn GetRecordsFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsFn RegisterRecordsFn;
            WUT_UNKNOWN_BYTES(0x4);
            IKillerNotificationTransferRecordManagerInternVTable_RegisterRecordsOtherFn RegisterRecordsOtherFn;
        } IKillerNotificationTransferRecordManagerInternVTable;
        WUT_CHECK_SIZE(IKillerNotificationTransferRecordManagerInternVTable, 0x50);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x14, LoadFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x1C, LoadInitialFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x24, StoreFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x2C, FinalizeFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x34, GetRecordCountFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x3C, GetRecordsFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x44, RegisterRecordsFn);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternVTable, 0x4C, RegisterRecordsOtherFn);

        typedef struct WUT_PACKED IKillerNotificationTransferRecordManagerInternal {
            IKillerNotificationTransferRecordManagerInternVTable *vtable;
        } IKillerNotificationTransferRecordManagerIntern;
        WUT_CHECK_SIZE(IKillerNotificationTransferRecordManagerInternal, 0x4);
        WUT_CHECK_OFFSET(IKillerNotificationTransferRecordManagerInternal, 0x00, vtable);


        typedef struct WUT_PACKED KillerNotificationTransferRecordManagerInternalInternal {
            IKillerNotificationTransferRecordManagerInternVTable *vtable;
            void *killerNotificationTransferRecordManagerImpl;
        } KillerNotificationTransferRecordManagerInternalInternal;
        WUT_CHECK_SIZE(KillerNotificationTransferRecordManagerInternalInternal, 0x8);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x00, vtable);
        WUT_CHECK_OFFSET(KillerNotificationTransferRecordManagerInternalInternal, 0x04, killerNotificationTransferRecordManagerImpl);

        extern "C" IKillerNotificationTransferRecordManagerIntern *__ct__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
        extern "C" void *__dt__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *, int);
        extern "C" void Finalize__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(IKillerNotificationTransferRecordManagerInternal *, details::IStreamInternal *);
        extern "C" nn::Result LoadInitial__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(IKillerNotificationTransferRecordManagerInternal *);
        extern "C" uint32_t GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv(IKillerNotificationTransferRecordManagerInternal *);
        extern "C" uint32_t GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi(IKillerNotificationTransferRecordManagerInternal *, KillerNotificationTransferRecord *, uint32_t);
        extern "C" void RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(IKillerNotificationTransferRecordManagerInternal *, KillerNotificationTransferRecord *, uint32_t);
        extern "C" nn::Result Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(IKillerNotificationTransferRecordManagerInternal *, details::IStreamInternal *);
        extern "C" IKillerNotificationTransferRecordManagerInternal *GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv();

        extern "C" KillerNotificationTransferRecordManagerInternalInternal *__ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *);
        extern "C" void *__dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(KillerNotificationTransferRecordManagerInternalInternal *, int);
    } // namespace details

    class IKillerNotificationTransferRecordManager {
        friend class KillerNotificationSelector;

    public:
        virtual ~IKillerNotificationTransferRecordManager() = default;

        virtual nn::Result Load(IStream &stream) = 0;

        virtual nn::Result LoadInitial() = 0;

        virtual nn::Result Store(IStream &stream) = 0;

        virtual void Finalize() = 0;

        virtual uint32_t GetRecordCount() = 0;

        virtual uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) = 0;

        virtual void RegisterRecords(KillerNotificationTransferRecord *u1, uint32_t u2) = 0;

        virtual nn::Result RegisterRecords(uint32_t *u1, uint32_t u2) = 0;

    private:
        virtual details::IKillerNotificationTransferRecordManagerInternal *GetInternal() = 0;
    };

    class KillerNotificationTransferRecordManager : public IKillerNotificationTransferRecordManager {
    public:
        KillerNotificationTransferRecordManager() {
            __ct__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        ~KillerNotificationTransferRecordManager() override {
            __dt__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance, 2);
        }

        void Finalize() override {
            Finalize__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        nn::Result Load(IStream &stream) override {
            return Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(&mInstance, stream.getStream());
        }

        nn::Result LoadInitial() override {
            return LoadInitial__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        nn::Result Store(IStream &stream) override {
            return Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(&mInstance, stream.getStream());
        }

        uint32_t GetRecordCount() override {
            return GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv(&mInstance);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            return GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi(&mInstance, u1, u2);
        }

        void RegisterRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(&mInstance, u1, u2);
        }

        nn::Result RegisterRecords(uint32_t *u1, uint32_t u2) override {
            return mInstance.vtable->RegisterRecordsOtherFn(&mInstance, u1, u2);
        }

    private:
        details::IKillerNotificationTransferRecordManagerInternal *GetInternal() override {
            return &mInstance;
        }
        details::IKillerNotificationTransferRecordManagerInternal mInstance = {};
    };


    class KillerNotificationTransferRecordManagerInternal : public IKillerNotificationTransferRecordManager {
    public:
        KillerNotificationTransferRecordManagerInternal() {
            __ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance);
        }

        ~KillerNotificationTransferRecordManagerInternal() override {
            __dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance, 2);
        }

        nn::Result Load(IStream &stream) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->LoadFn(base, stream.getStream());
        }

        nn::Result LoadInitial() override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->LoadInitialFn(base);
        }

        nn::Result Store(IStream &stream) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->StoreFn(base, stream.getStream());
        }

        void Finalize() override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->FinalizeFn(base);
        }

        uint32_t GetRecordCount() override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->GetRecordCountFn(base);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->GetRecordsFn(base, u1, u2);
        }

        void RegisterRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->RegisterRecordsFn(base, u1, u2);
        }

        nn::Result RegisterRecords(uint32_t *u1, uint32_t u2) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->RegisterRecordsOtherFn(base, u1, u2);
        }

    private:
        details::KillerNotificationTransferRecordManagerInternalInternal mInstance = {};
    };


    class KillerNotificationTransferRecordManagerFromPtr : public IKillerNotificationTransferRecordManager {
    public:
        explicit KillerNotificationTransferRecordManagerFromPtr(details::IKillerNotificationTransferRecordManagerInternal *instance) : mInstancePtr(instance) {
        }

        ~KillerNotificationTransferRecordManagerFromPtr() override = default;

        void Finalize() override {
            mInstancePtr->vtable->FinalizeFn(mInstancePtr);
        }

        nn::Result Load(IStream &stream) override {
            return mInstancePtr->vtable->LoadFn(mInstancePtr, stream.getStream());
        }

        nn::Result LoadInitial() override {
            return mInstancePtr->vtable->LoadInitialFn(mInstancePtr);
        }

        nn::Result Store(IStream &stream) override {
            return mInstancePtr->vtable->StoreFn(mInstancePtr, stream.getStream());
        }

        uint32_t GetRecordCount() override {
            return mInstancePtr->vtable->GetRecordCountFn(mInstancePtr);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            return mInstancePtr->vtable->GetRecordsFn(mInstancePtr, u1, u2);
        }

        void RegisterRecords(KillerNotificationTransferRecord *u1, uint32_t u2) override {
            mInstancePtr->vtable->RegisterRecordsFn(mInstancePtr, u1, u2);
        }

        nn::Result RegisterRecords(uint32_t *u1, uint32_t u2) override {
            return mInstancePtr->vtable->RegisterRecordsOtherFn(mInstancePtr, u1, u2);
        }

    private:
        details::IKillerNotificationTransferRecordManagerInternal *GetInternal() override {
            return mInstancePtr;
        }
        details::IKillerNotificationTransferRecordManagerInternal *mInstancePtr = {};
    };

    KillerNotificationTransferRecordManagerFromPtr GetDefaultKillerNotificationTransferRecordManager() {
        return KillerNotificationTransferRecordManagerFromPtr(details::GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif