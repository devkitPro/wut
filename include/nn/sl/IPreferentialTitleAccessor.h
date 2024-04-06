#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IPreferentialTitleAccessorDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class IPreferentialTitleAccessor : public details::IPreferentialTitleAccessorBase {

    public:
        IPreferentialTitleAccessor();

        IPreferentialTitleAccessor(IPreferentialTitleAccessor &src);

        IPreferentialTitleAccessor &operator=(const IPreferentialTitleAccessor &other);

        IPreferentialTitleAccessor &operator=(IPreferentialTitleAccessor &&src) noexcept;

        ~IPreferentialTitleAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IPreferentialTitleAccessorInternal *instance, TitleInfo *outTitleInfo, uint32_t *outTitleInfoSize, int maxTitleInfo, uint32_t u1);

        details::IPreferentialTitleAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IPreferentialTitleAccessorInternal mInstance{};
        details::IPreferentialTitleAccessorInternalVTable mVTable{};
    };

    details::IPreferentialTitleAccessorBase &GetDefaultPreferentialTitleAccessor();
} // namespace nn::sl

#endif