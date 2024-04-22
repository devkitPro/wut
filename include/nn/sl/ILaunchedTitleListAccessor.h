#pragma once

#include <nn/result.h>
#include <nn/sl/details/ILaunchedTitleListAccessoDetails.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    class ILaunchedTitleListAccessor : public details::ILaunchedTitleListAccessorBase {

    public:
        ILaunchedTitleListAccessor() {
            InitInternalVtable();
        }

        ILaunchedTitleListAccessor(ILaunchedTitleListAccessor &src) {
            InitInternalVtable();
        }

        ILaunchedTitleListAccessor &operator=(const ILaunchedTitleListAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        ILaunchedTitleListAccessor &operator=(ILaunchedTitleListAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ILaunchedTitleListAccessor() override = default;

    private:
        static nn::Result GetByAccountWrapper(details::ILaunchedTitleListAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfoSize, int inTitleInfosSize, int userId) {
            return instance->vtable->instance->GetByAccount(outTitleInfos, outTitleInfoSize, inTitleInfosSize, userId);
        }

        details::ILaunchedTitleListAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance       = this,
                                .GetByAccountFn = &GetByAccountWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ILaunchedTitleListAccessorInternal mInstance{};
        details::ILaunchedTitleListAccessorInternalVTable mVTable{};
    };

    enum LaunchedTitleListAccessorType {
        TITLE_LIST_ACCESSOR_LAUNCHED_TITLES = 0,
        TITLE_LIST_ACCESSOR_PLAY_STATS      = 1,
    };

    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor(LaunchedTitleListAccessorType type);
    details::ILaunchedTitleListAccessorBase &GetDefaultLaunchedTitleListAccessor();
} // namespace nn::sl

#endif