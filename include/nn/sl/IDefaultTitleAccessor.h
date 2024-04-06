#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IDefaultTitleAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class IDefaultTitleAccessor : public details::IDefaultTitleAccessorBase {

    public:
        IDefaultTitleAccessor();

        IDefaultTitleAccessor(IDefaultTitleAccessor &src);

        IDefaultTitleAccessor &operator=(const IDefaultTitleAccessor &other);

        IDefaultTitleAccessor &operator=(IDefaultTitleAccessor &&src) noexcept;

        ~IDefaultTitleAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IDefaultTitleAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        details::IDefaultTitleAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IDefaultTitleAccessorInternal mInstance{};
        details::IDefaultTitleAccessorInternalVTable mVTable{};
    };

    details::IDefaultTitleAccessorBase &GetDefaultDefaultTitleAccessor();
} // namespace nn::sl

#endif