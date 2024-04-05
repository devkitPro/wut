#pragma once

#include "sl_cpp.h"
#include <memory>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ISettingAccessor;
    namespace details {
        struct ISettingAccessorInternal;

        typedef nn::Result (*ISettingAccessor_GetFn)(ISettingAccessorInternal *, Setting *);

        struct WUT_PACKED ISettingAccessorInternalVTable {
            ISettingAccessor *instance; // Is normally padding
            uint32_t info;
            WUT_PADDING_BYTES(4);
            uint32_t destructor;
            WUT_PADDING_BYTES(4);
            ISettingAccessor_GetFn GetFn;
        };
        WUT_CHECK_SIZE(ISettingAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(ISettingAccessorInternalVTable, 0x00, instance);
        WUT_CHECK_OFFSET(ISettingAccessorInternalVTable, 0x14, GetFn);

        typedef struct WUT_PACKED ISettingAccessorInternal {
            ISettingAccessorInternalVTable *vtable;
        } ISettingAccessorInternal;
        WUT_CHECK_SIZE(ISettingAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(ISettingAccessorInternal, 0x00, vtable);

        extern "C" ISettingAccessorInternal *GetDefaultSettingAccessor__Q2_2nn2slFv();
    } // namespace details


    class ISettingAccessor {
        friend class DataCreator;
        friend class Condition;

    public:
        ISettingAccessor() = default;

        virtual ~ISettingAccessor() = default;

        virtual nn::Result Get(Setting *) = 0;

    private:
        virtual details::ISettingAccessorInternal *GetInternal() = 0;
    };

    class ISettingAccessorBase : public ISettingAccessor {

    public:
        ISettingAccessorBase() {
            InitInternalVtable();
        }

        ISettingAccessorBase(ISettingAccessorBase &src) {
            InitInternalVtable();
        }

        ISettingAccessorBase &operator=(const ISettingAccessorBase &other) {
            InitInternalVtable();
            return *this;
        }

        ISettingAccessorBase &operator=(ISettingAccessorBase &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ISettingAccessorBase() override = default;

    private:
        static nn::Result GetWrapper(details::ISettingAccessorInternal *instance, Setting *outSetting) {
            return instance->vtable->instance->Get(outSetting);
        }

        details::ISettingAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ISettingAccessorInternal mInstance{};
        details::ISettingAccessorInternalVTable mVTable{};
    };

    class SettingAccessorFromPtr : public ISettingAccessor {
    public:
        explicit SettingAccessorFromPtr(details::ISettingAccessorInternal *ptr) : mInstancePtr(ptr) {
        }
        nn::Result Get(Setting *outSetting) override {
            return mInstancePtr->vtable->GetFn(mInstancePtr, outSetting);
        }

    private:
        details::ISettingAccessorInternal *GetInternal() override {
            return mInstancePtr;
        }

        details::ISettingAccessorInternal *mInstancePtr;
    };

    SettingAccessorFromPtr GetDefaultSettingAccessor() {
        return SettingAccessorFromPtr(details::GetDefaultSettingAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif