#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ISettingAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ISettingAccessor : public details::ISettingAccessorBase {

    public:
        ISettingAccessor();

        ISettingAccessor(ISettingAccessor &src);

        ISettingAccessor &operator=(const ISettingAccessor &other);

        ISettingAccessor &operator=(ISettingAccessor &&src) noexcept;

        ~ISettingAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::ISettingAccessorInternal *instance, Setting *outSetting);

        details::ISettingAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::ISettingAccessorInternal mInstance{};
        details::ISettingAccessorInternalVTable mVTable{};
    };

    details::ISettingAccessorBase &GetDefaultSettingAccessor();
} // namespace nn::sl

#endif