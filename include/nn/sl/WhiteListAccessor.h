#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IWhiteListAccessor;
    namespace details {
        struct IWhiteListAccessorInternal;

        typedef nn::Result (*IWhiteListAccessor_GetFn)(IWhiteListAccessorInternal *, WhiteList *);

        struct WUT_PACKED IWhiteListAccessorInternalVTable {
            IWhiteListAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            IWhiteListAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(IWhiteListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(IWhiteListAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(IWhiteListAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED IWhiteListAccessorInternal {
            IWhiteListAccessorInternalVTable *vtable;
        } IWhiteListAccessorInternal;
        WUT_CHECK_SIZE(IWhiteListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(IWhiteListAccessorInternal, 0x00, vtable);

        extern "C" IWhiteListAccessorInternal *GetDefaultWhiteListAccessor__Q2_2nn2slFv();
    } // namespace details


    class IWhiteListAccessor {
        friend class QuickStartApplicationSelector;

    public:
        IWhiteListAccessor() = default;

        virtual ~IWhiteListAccessor() = default;

        virtual nn::Result Get(WhiteList *) = 0;

    private:
        virtual details::IWhiteListAccessorInternal *GetInternal() = 0;
    };

    class IWhiteListAccessorBase : public IWhiteListAccessor {

    public:
        IWhiteListAccessorBase() {
            InitInternalVtable();
        }

        IWhiteListAccessorBase(IWhiteListAccessorBase &src) {
            InitInternalVtable();
        }

        IWhiteListAccessorBase &operator=(const IWhiteListAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        IWhiteListAccessorBase &operator=(IWhiteListAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~IWhiteListAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::IWhiteListAccessorInternal *instance, WhiteList *outWhiteList) {
            return instance->vtable->instance->Get(outWhiteList);
        }

        details::IWhiteListAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IWhiteListAccessorInternal mInstance{};
        details::IWhiteListAccessorInternalVTable mVTable{};
    };

    class WhiteListAccessorFromPtr : public IWhiteListAccessor {
    public:
        explicit WhiteListAccessorFromPtr(details::IWhiteListAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(WhiteList *outWhiteList) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outWhiteList);
        }

    private:
        details::IWhiteListAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::IWhiteListAccessorInternal *mInstancePtr;
    };

    WhiteListAccessorFromPtr GetDefaultWhiteListAccessor() {
        return WhiteListAccessorFromPtr(details::GetDefaultWhiteListAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif