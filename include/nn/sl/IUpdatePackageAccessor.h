#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IUpdatePackageAccessor;
    namespace details {
        struct IUpdatePackageAccessorInternal;

        typedef bool (*UpdatePackageAccessor_PackageExistsFn)(IUpdatePackageAccessorInternal *);
        typedef bool (*UpdatePackageAccessor_IsUpdatePackageDownloadedFn)(IUpdatePackageAccessorInternal *);

        struct WUT_PACKED IUpdatePackageAccessorInternalVTable {
            IUpdatePackageAccessor *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            UpdatePackageAccessor_PackageExistsFn PackageExistsFn;
            WUT_PADDING_BYTES(4);
            UpdatePackageAccessor_IsUpdatePackageDownloadedFn IsUpdatePackageDownloadedFn;
            WUT_PADDING_BYTES(4);
        };
        WUT_CHECK_SIZE(IUpdatePackageAccessorInternalVTable, 0x24);
        WUT_CHECK_OFFSET(IUpdatePackageAccessorInternalVTable, 0x14, PackageExistsFn);
        WUT_CHECK_OFFSET(IUpdatePackageAccessorInternalVTable, 0x1C, IsUpdatePackageDownloadedFn);

        typedef struct WUT_PACKED IUpdatePackageAccessorInternal {
            IUpdatePackageAccessorInternalVTable *vtable;
        } IUpdatePackageAccessorInternal;
        WUT_CHECK_SIZE(IUpdatePackageAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IUpdatePackageAccessorInternal, 0x00, vtable);

        extern "C" IUpdatePackageAccessorInternal *GetDefaultUpdatePackageAccessor__Q2_2nn2slFv();
    } // namespace details

    class IUpdatePackageAccessor {
        friend class Condition;

    public:
        IUpdatePackageAccessor()          = default;
        virtual ~IUpdatePackageAccessor() = default;

        virtual bool PackageExists() = 0;

        virtual bool IsUpdatePackageDownloaded() = 0;

    private:
        virtual details::IUpdatePackageAccessorInternal *GetInternal() = 0;
    };

    class IUpdatePackageAccessorBase : public IUpdatePackageAccessor {

    public:
        IUpdatePackageAccessorBase() {
            InitInternalVtable();
        }

        IUpdatePackageAccessorBase(IUpdatePackageAccessorBase &src) {
            InitInternalVtable();
        }

        IUpdatePackageAccessorBase &operator=(const IUpdatePackageAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IUpdatePackageAccessorBase &operator=(IUpdatePackageAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IUpdatePackageAccessorBase() override = default;

    private:
        static bool PackageExistsWrapper(details::IUpdatePackageAccessorInternal *instance) {
            return instance->vtable->instance->PackageExists();
        }
        static bool IsUpdatePackageDownloadedWrapper(details::IUpdatePackageAccessorInternal *instance) {
            return instance->vtable->instance->IsUpdatePackageDownloaded();
        }

        details::IUpdatePackageAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance                    = this,
                                .PackageExistsFn             = PackageExistsWrapper,
                                .IsUpdatePackageDownloadedFn = IsUpdatePackageDownloadedWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IUpdatePackageAccessorInternal mInstance{};
        details::IUpdatePackageAccessorInternalVTable mVTable{};
    };


    class UpdatePackageAccessorFromPtr : public IUpdatePackageAccessor {
    public:
        explicit UpdatePackageAccessorFromPtr(details::IUpdatePackageAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        bool PackageExists() override {
            return mInstancePtr->vtable->PackageExistsFn(mInstancePtr);
        }

        bool IsUpdatePackageDownloaded() override {
            return mInstancePtr->vtable->IsUpdatePackageDownloadedFn(mInstancePtr);
        }

        details::IUpdatePackageAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

    private:
        details::IUpdatePackageAccessorInternal *mInstancePtr;
    };

    UpdatePackageAccessorFromPtr GetDefaultUpdatePackageAccessor() {
        return UpdatePackageAccessorFromPtr(details::GetDefaultUpdatePackageAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif