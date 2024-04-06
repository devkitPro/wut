#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IBlackListAccessor;
    namespace details {
        struct IBlackListAccessorInternal;

        typedef nn::Result (*IBlackListAccessor_GetFn)(IBlackListAccessorInternal *, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        struct WUT_PACKED IBlackListAccessorInternalVTable {
            IBlackListAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IBlackListAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IBlackListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IBlackListAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IBlackListAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IBlackListAccessorInternal {
            IBlackListAccessorInternalVTable *vtable;
        } IBlackListAccessorInternal;
        WUT_CHECK_SIZE(IBlackListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IBlackListAccessorInternal, 0x00, vtable);

        extern "C" IBlackListAccessorInternal *GetDefaultBlackListAccessor__Q2_2nn2slFv();
    } // namespace details


    class IBlackListAccessor {
        friend class QuickStartApplicationSelector;

    public:
        IBlackListAccessor() = default;

        virtual ~IBlackListAccessor() = default;

        virtual nn::Result Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) = 0;

    private:
        virtual details::IBlackListAccessorInternal *GetInternal() = 0;
    };

    class IBlackListAccessorBase : public IBlackListAccessor {

    public:
        IBlackListAccessorBase() {
            InitInternalVtable();
        }

        IBlackListAccessorBase(IBlackListAccessorBase &src) {
            InitInternalVtable();
        }

        IBlackListAccessorBase &operator=(const IBlackListAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IBlackListAccessorBase &operator=(IBlackListAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IBlackListAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IBlackListAccessorInternal *instance, TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
            return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

        details::IBlackListAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IBlackListAccessorInternal mInstance{};
        details::IBlackListAccessorInternalVTable mVTable{};
    };

    class BlackListAccessorFromPtr : public IBlackListAccessor {
    public:
        explicit BlackListAccessorFromPtr(details::IBlackListAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

    private:
        details::IBlackListAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IBlackListAccessorInternal *mInstancePtr;
    };

    BlackListAccessorFromPtr GetDefaultBlackListAccessor() {
        return BlackListAccessorFromPtr(details::GetDefaultBlackListAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif