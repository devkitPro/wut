#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IIconInfoAccessor;
    namespace details {
        struct IIconInfoAccessorInternal;

        typedef nn::Result (*IconInfoAccessor_GetTitleIconInfoFn)(IIconInfoAccessorInternal *, IconInfo *, const TitleInfo &, nn::sl::Language);
        typedef nn::Result (*IconInfoAccessor_GetMiiIconFn)(IIconInfoAccessorInternal *, void *buffer, uint32_t buffer_size, uint slot);

        struct WUT_PACKED IIconInfoAccessorInternalVTable {
            IIconInfoAccessor *instance; // normally this is padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IconInfoAccessor_GetTitleIconInfoFn getTitleIconInfoFn;
            WUT_PADDING_BYTES(4);
            IconInfoAccessor_GetMiiIconFn getMiiIconFn;
            WUT_PADDING_BYTES(4);
        };
        WUT_CHECK_SIZE(IIconInfoAccessorInternalVTable, 0x24);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternalVTable, 0x14, getTitleIconInfoFn);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternalVTable, 0x1C, getMiiIconFn);

        typedef struct WUT_PACKED IIconInfoAccessorInternal {
            IIconInfoAccessorInternalVTable *vtable;
        } IIconInfoAccessorInternal;
        WUT_CHECK_SIZE(IIconInfoAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IIconInfoAccessorInternal, 0x00, vtable);

        extern "C" IIconInfoAccessorInternal *GetDefaultIconInfoAccessor__Q2_2nn2slFv();
    } // namespace details

    class IIconInfoAccessor {
        friend class DataCreator;

    public:
        IIconInfoAccessor()          = default;
        virtual ~IIconInfoAccessor() = default;

        virtual nn::Result GetTitleIconInfo(nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) = 0;

        virtual nn::Result GetMiiIcon(void *buffer, uint32_t buffer_size, uint slot) = 0;

    private:
        virtual details::IIconInfoAccessorInternal *GetInternal() = 0;
    };

    class IIconInfoAccessorBase : public IIconInfoAccessor {

    public:
        IIconInfoAccessorBase() {
            InitInternalVtable();
        }

        IIconInfoAccessorBase(IIconInfoAccessorBase &src) {
            InitInternalVtable();
        }

        IIconInfoAccessorBase &operator=(const IIconInfoAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IIconInfoAccessorBase &operator=(IIconInfoAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IIconInfoAccessorBase() override = default;

    private:
        static nn::Result GetTitleIconInfoWrapper(details::IIconInfoAccessorInternal *instance, nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) {
            return instance->vtable->instance->GetTitleIconInfo(outIconInfo, titleInfo, language);
        }
        static nn::Result GetMiiIconWrapper(details::IIconInfoAccessorInternal *instance, void *buffer, uint32_t buffer_size, uint slot) {
            return instance->vtable->instance->GetMiiIcon(buffer, buffer_size, slot);
        }

        details::IIconInfoAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance           = this,
                                .getTitleIconInfoFn = GetTitleIconInfoWrapper,
                                .getMiiIconFn       = GetMiiIconWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IIconInfoAccessorInternal mInstance{};
        details::IIconInfoAccessorInternalVTable mVTable{};
    };


    class IconInfoAccessorFromPtr : public IIconInfoAccessor {
    public:
        explicit IconInfoAccessorFromPtr(details::IIconInfoAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result GetTitleIconInfo(nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language) override {
            return mInstancePtr->vtable->getTitleIconInfoFn(mInstancePtr, outIconInfo, titleInfo, language);
        }

        nn::Result GetMiiIcon(void *buffer, uint32_t buffer_size, uint slot) override {
            return mInstancePtr->vtable->getMiiIconFn(mInstancePtr, buffer, buffer_size, slot);
        }

    private:
        nn::sl::details::IIconInfoAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }
        details::IIconInfoAccessorInternal *mInstancePtr;
    };

    IconInfoAccessorFromPtr GetDefaultIconInfoAccessor() {
        return IconInfoAccessorFromPtr(details::GetDefaultIconInfoAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif