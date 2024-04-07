#pragma once

#include <nn/result.h>
#include <nn/sl/details/ISettingAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ISettingAccessor : public details::ISettingAccessorBase {

    public:
        ISettingAccessor() {
            InitInternalVtable();
        }

        ISettingAccessor(ISettingAccessor &src) {
            InitInternalVtable();
        }

        ISettingAccessor &operator=(const ISettingAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        ISettingAccessor &operator=(ISettingAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ISettingAccessor() override = default;

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

    details::ISettingAccessorBase &GetDefaultSettingAccessor();
} // namespace nn::sl

#endif