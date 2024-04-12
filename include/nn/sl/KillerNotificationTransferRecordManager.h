#pragma once

#include <nn/result.h>
#include <nn/sl/FileStream.h>
#include <nn/sl/details/IKillerNotificationTransferRecordManagerDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IKillerNotificationTransferRecordManager : public details::IKillerNotificationTransferRecordManagerBase {

    public:
        IKillerNotificationTransferRecordManager() {
            InitInternalVtable();
        }

        IKillerNotificationTransferRecordManager(IKillerNotificationTransferRecordManager &src) {
            InitInternalVtable();
        }

        IKillerNotificationTransferRecordManager &operator=(const IKillerNotificationTransferRecordManager &other) {
            InitInternalVtable();
            return *this;
        }

        IKillerNotificationTransferRecordManager &operator=(IKillerNotificationTransferRecordManager &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IKillerNotificationTransferRecordManager() override = default;

    private:
        static nn::Result LoadWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance, nn::sl::details::IStreamInternal *stream) {
            return instance->vtable->instance->Load(*stream->vtable->instance);
        }

        static nn::Result LoadInitialWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance) {
            return instance->vtable->instance->LoadInitial();
        }

        static nn::Result StoreWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance, nn::sl::details::IStreamInternal *stream) {
            return instance->vtable->instance->Store(*stream->vtable->instance);
        }

        static uint32_t GetRecordCountWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance) {
            return instance->vtable->instance->GetRecordCount();
        }

        static uint32_t GetRecordsWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance, KillerNotificationTransferRecord *u1, uint32_t u2) {
            return instance->vtable->instance->GetRecords(u1, u2);
        }

        static void RegisterRecordsWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance, const KillerNotificationTransferRecord *u1, uint32_t u2) {
            return instance->vtable->instance->RegisterRecords(u1, u2);
        }

        static nn::Result RegisterRecordsOtherWrapper(details::IKillerNotificationTransferRecordManagerInternal *instance, const uint32_t *u1, uint32_t u2) {
            return instance->vtable->instance->RegisterRecords(u1, u2);
        }

        details::IKillerNotificationTransferRecordManagerInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance               = this,
                                .LoadFn                 = &LoadWrapper,
                                .LoadInitialFn          = &LoadInitialWrapper,
                                .StoreFn                = &StoreWrapper,
                                .GetRecordsFn           = &GetRecordsWrapper,
                                .RegisterRecordsFn      = &RegisterRecordsWrapper,
                                .RegisterRecordsOtherFn = &RegisterRecordsOtherWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IKillerNotificationTransferRecordManagerInternal mInstance{};
        details::IKillerNotificationTransferRecordManagerInternalVTable mVTable{};
    };

    class KillerNotificationTransferRecordManager : public details::IKillerNotificationTransferRecordManagerBase {
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

        nn::Result Load(nn::sl::details::IStreamBase &stream) override {
            return Load__Q3_2nn2sl39KillerNotificationTransferRecordManagerFRQ3_2nn2sl7IStream(&mInstance, stream.GetInternal());
        }

        nn::Result LoadInitial() override {
            return LoadInitial__Q3_2nn2sl39KillerNotificationTransferRecordManagerFv(&mInstance);
        }

        nn::Result Store(nn::sl::details::IStreamBase &stream) override {
            return Store__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFRQ3_2nn2sl7IStream(&mInstance, stream.GetInternal());
        }

        uint32_t GetRecordCount() const override {
            return GetRecordCount__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFv((details::IKillerNotificationTransferRecordManagerInternal *) &mInstance);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) const override {
            return GetRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerCFPQ3_2nn2sl32KillerNotificationTransferRecordUi((details::IKillerNotificationTransferRecordManagerInternal *) &mInstance, u1, u2);
        }

        void RegisterRecords(const KillerNotificationTransferRecord *u1, uint32_t u2) override {
            RegisterRecords__Q3_2nn2sl39KillerNotificationTransferRecordManagerFPCQ3_2nn2sl32KillerNotificationTransferRecordUi(&mInstance, u1, u2);
        }

        nn::Result RegisterRecords(const uint32_t *u1, uint32_t u2) override {
            return mInstance.vtable->RegisterRecordsOtherFn(&mInstance, u1, u2);
        }

    private:
        details::IKillerNotificationTransferRecordManagerInternal *GetInternal() override {
            return &mInstance;
        }
        details::IKillerNotificationTransferRecordManagerInternal mInstance = {};
    };

    class KillerNotificationTransferRecordManagerInternal : public details::IKillerNotificationTransferRecordManagerBase {
    public:
        KillerNotificationTransferRecordManagerInternal() {
            __ct__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance);
        }

        ~KillerNotificationTransferRecordManagerInternal() override {
            __dt__Q3_2nn2sl47KillerNotificationTransferRecordManagerInternalFv(&mInstance, 2);
        }

        nn::Result Load(nn::sl::details::IStreamBase &stream) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->LoadFn(base, stream.GetInternal());
        }

        nn::Result LoadInitial() override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->LoadInitialFn(base);
        }

        nn::Result Store(nn::sl::details::IStreamBase &stream) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->StoreFn(base, stream.GetInternal());
        }

        void Finalize() override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->FinalizeFn(base);
        }

        uint32_t GetRecordCount() const override {
            auto *base = (details::IKillerNotificationTransferRecordManagerInternal *) (&mInstance);
            return mInstance.vtable->GetRecordCountFn(base);
        }

        uint32_t GetRecords(KillerNotificationTransferRecord *u1, uint32_t u2) const override {
            auto *base = (details::IKillerNotificationTransferRecordManagerInternal *) (&mInstance);
            return mInstance.vtable->GetRecordsFn(base, u1, u2);
        }

        void RegisterRecords(const KillerNotificationTransferRecord *u1, uint32_t u2) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->RegisterRecordsFn(base, u1, u2);
        }

        nn::Result RegisterRecords(const uint32_t *u1, uint32_t u2) override {
            auto *base = reinterpret_cast<details::IKillerNotificationTransferRecordManagerInternal *>(&mInstance);
            return mInstance.vtable->RegisterRecordsOtherFn(base, u1, u2);
        }

    private:
        details::KillerNotificationTransferRecordManagerInternalInternal mInstance = {};
    };

    details::IKillerNotificationTransferRecordManagerBase &GetDefaultKillerNotificationTransferRecordManager();
} // namespace nn::sl

#endif