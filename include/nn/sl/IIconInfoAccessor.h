#pragma once

#include <nn/result.h>
#include <nn/sl/details/IIconInfoAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IIconInfoAccessor : public details::IIconInfoAccessorBase {

    public:
        IIconInfoAccessor();

        IIconInfoAccessor(IIconInfoAccessor &src);

        IIconInfoAccessor &operator=(const IIconInfoAccessor &other);

        IIconInfoAccessor &operator=(IIconInfoAccessor &&src) noexcept;

        ~IIconInfoAccessor() override = default;

    private:
        static nn::Result GetTitleIconInfoWrapper(details::IIconInfoAccessorInternal *instance, nn::sl::IconInfo *outIconInfo, const nn::sl::TitleInfo &titleInfo, nn::sl::Language language);
        static nn::Result GetMiiIconWrapper(details::IIconInfoAccessorInternal *instance, void *buffer, uint32_t buffer_size, uint32_t slot);

        details::IIconInfoAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IIconInfoAccessorInternal mInstance{};
        details::IIconInfoAccessorInternalVTable mVTable{};
    };

    details::IIconInfoAccessorBase &GetDefaultIconInfoAccessor();
} // namespace nn::sl

#endif