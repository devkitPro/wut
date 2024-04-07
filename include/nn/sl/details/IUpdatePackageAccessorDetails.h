#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class Condition;
    namespace details {
        class IUpdatePackageAccessorBase;
        struct IUpdatePackageAccessorInternal;

        typedef bool (*IUpdatePackageAccessor_PackageExistsFn)(IUpdatePackageAccessorInternal *);
        typedef bool (*IUpdatePackageAccessor_IsUpdatePackageDownloadedFn)(IUpdatePackageAccessorInternal *);

        struct WUT_PACKED IUpdatePackageAccessorInternalVTable {
            IUpdatePackageAccessorBase *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IUpdatePackageAccessor_PackageExistsFn PackageExistsFn;
            WUT_PADDING_BYTES(4);
            IUpdatePackageAccessor_IsUpdatePackageDownloadedFn IsUpdatePackageDownloadedFn;
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

        class IUpdatePackageAccessorBase {
            friend class nn::sl::Condition;

        public:
            IUpdatePackageAccessorBase()          = default;
            virtual ~IUpdatePackageAccessorBase() = default;

            virtual bool PackageExists() = 0;

            virtual bool IsUpdatePackageDownloaded() = 0;

        private:
            virtual details::IUpdatePackageAccessorInternal *GetInternal() = 0;
        };

        class UpdatePackageAccessorFromPtr : public IUpdatePackageAccessorBase {
        public:
            explicit UpdatePackageAccessorFromPtr(details::IUpdatePackageAccessorInternal *ptr) : mInstancePtr(ptr) {
            }
            bool PackageExists() override {
                if (!mInstancePtr) {
                    return false;
                }
                return mInstancePtr->vtable->PackageExistsFn(mInstancePtr);
            }

            bool IsUpdatePackageDownloaded() override {
                if (!mInstancePtr) {
                    return false;
                }
                return mInstancePtr->vtable->IsUpdatePackageDownloadedFn(mInstancePtr);
            }

            details::IUpdatePackageAccessorInternal *GetInternal() override {
                return mInstancePtr;
            }

        private:
            details::IUpdatePackageAccessorInternal *mInstancePtr;
        };
    } // namespace details
} // namespace nn::sl

#endif