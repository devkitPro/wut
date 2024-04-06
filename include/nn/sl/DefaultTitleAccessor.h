#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IDefaultTitleAccessor;
    namespace details {
        struct IDefaultTitleAccessorInternal;

        typedef nn::Result (*IDefaultTitleAccessor_GetFn)(IDefaultTitleAccessorInternal *, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED IDefaultTitleAccessorInternalVTable {
            IDefaultTitleAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IDefaultTitleAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IDefaultTitleAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IDefaultTitleAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IDefaultTitleAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IDefaultTitleAccessorInternal {
            IDefaultTitleAccessorInternalVTable *vtable;
        } IDefaultTitleAccessorInternal;
        WUT_CHECK_SIZE(IDefaultTitleAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IDefaultTitleAccessorInternal, 0x00, vtable);

        extern "C" IDefaultTitleAccessorInternal *GetDefaultDefaultTitleAccessor__Q2_2nn2slFv();
    } // namespace details


    class IDefaultTitleAccessor {
        friend class QuickStartApplicationSelector;

    public:
        IDefaultTitleAccessor() = default;

        virtual ~IDefaultTitleAccessor() = default;

        virtual nn::Result Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) = 0;

    private:
        virtual details::IDefaultTitleAccessorInternal *GetInternal() = 0;
    };

    class IDefaultTitleAccessorBase : public IDefaultTitleAccessor {

    public:
        IDefaultTitleAccessorBase() {
            InitInternalVtable();
        }

        IDefaultTitleAccessorBase(IDefaultTitleAccessorBase &src) {
            InitInternalVtable();
        }

        IDefaultTitleAccessorBase &operator=(const IDefaultTitleAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IDefaultTitleAccessorBase &operator=(IDefaultTitleAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IDefaultTitleAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IDefaultTitleAccessorInternal *instance, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
            return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

        details::IDefaultTitleAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IDefaultTitleAccessorInternal mInstance{};
        details::IDefaultTitleAccessorInternalVTable mVTable{};
    };

    class DefaultTitleAccessorFromPtr : public IDefaultTitleAccessor {
    public:
        explicit DefaultTitleAccessorFromPtr(details::IDefaultTitleAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

    private:
        details::IDefaultTitleAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IDefaultTitleAccessorInternal *mInstancePtr;
    };

    DefaultTitleAccessorFromPtr GetDefaultDefaultTitleAccessor() {
        return DefaultTitleAccessorFromPtr(details::GetDefaultDefaultTitleAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif