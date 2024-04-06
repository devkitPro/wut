#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/IBlackListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class IBlackListAccessor : public details::IBlackListAccessorBase {

    public:
        IBlackListAccessor();

        IBlackListAccessor(IBlackListAccessor &src);

        IBlackListAccessor &operator=(const IBlackListAccessor &other);

        IBlackListAccessor &operator=(IBlackListAccessor &&src) noexcept;

        ~IBlackListAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IBlackListAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos);

        details::IBlackListAccessorInternal *GetInternal() override;

        void InitInternalVtable();

        details::IBlackListAccessorInternal mInstance{};
        details::IBlackListAccessorInternalVTable mVTable{};
    };

    details::IBlackListAccessorBase &GetDefaultBlackListAccessor();
} // namespace nn::sl

#endif