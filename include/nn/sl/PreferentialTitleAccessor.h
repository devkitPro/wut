#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IPreferentialTitleAccessor;
    namespace details {
        struct IPreferentialTitleAccessorInternal;

        typedef nn::Result (*IPreferentialTitleAccessor_GetFn)(IPreferentialTitleAccessorInternal *, TitleInfo *, uint32_t *, int, uint32_t);

        struct WUT_PACKED IPreferentialTitleAccessorInternalVTable {
            IPreferentialTitleAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IPreferentialTitleAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IPreferentialTitleAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IPreferentialTitleAccessorInternal {
            IPreferentialTitleAccessorInternalVTable *vtable;
        } IPreferentialTitleAccessorInternal;
        WUT_CHECK_SIZE(IPreferentialTitleAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IPreferentialTitleAccessorInternal, 0x00, vtable);

        extern "C" IPreferentialTitleAccessorInternal *GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv();
    } // namespace details


    class IPreferentialTitleAccessor {
        friend class QuickStartApplicationSelector;

    public:
        IPreferentialTitleAccessor() = default;

        virtual ~IPreferentialTitleAccessor() = default;

        virtual nn::Result Get(TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) = 0;

    private:
        virtual details::IPreferentialTitleAccessorInternal *GetInternal() = 0;
    };

    class IPreferentialTitleAccessorBase : public IPreferentialTitleAccessor {

    public:
        IPreferentialTitleAccessorBase() {
            InitInternalVtable();
        }

        IPreferentialTitleAccessorBase(IPreferentialTitleAccessorBase &src) {
            InitInternalVtable();
        }

        IPreferentialTitleAccessorBase &operator=(const IPreferentialTitleAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IPreferentialTitleAccessorBase &operator=(IPreferentialTitleAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IPreferentialTitleAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IPreferentialTitleAccessorInternal *instance, TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) {
            return instance->vtable->instance->Get(outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
        }

        details::IPreferentialTitleAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IPreferentialTitleAccessorInternal mInstance{};
        details::IPreferentialTitleAccessorInternalVTable mVTable{};
    };

    class PreferentialTitleAccessorFromPtr : public IPreferentialTitleAccessor {
    public:
        explicit PreferentialTitleAccessorFromPtr(details::IPreferentialTitleAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outTitleInfo, outTitleInfoSize, maxTitleInfo, u1);
        }

    private:
        details::IPreferentialTitleAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IPreferentialTitleAccessorInternal *mInstancePtr;
    };

    PreferentialTitleAccessorFromPtr GetDefaultPreferentialTitleAccessor() {
        return PreferentialTitleAccessorFromPtr(details::GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif