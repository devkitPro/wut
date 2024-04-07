#pragma once

#include <nn/result.h>
#include <nn/sl/details/IDiscCachedTitleAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class DiscCachedTitleAccessor : public details::IDiscCachedTitleAccessorBase {

    public:
        DiscCachedTitleAccessor() {
            InitInternalVtable();
        }

        DiscCachedTitleAccessor(DiscCachedTitleAccessor &src) {
            InitInternalVtable();
        }

        DiscCachedTitleAccessor &operator=(const DiscCachedTitleAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        DiscCachedTitleAccessor &operator=(DiscCachedTitleAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~DiscCachedTitleAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::IDiscCachedTitleAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
            return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

        details::IDiscCachedTitleAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::IDiscCachedTitleAccessorInternal mInstance{};
        details::IDiscCachedTitleAccessorInternalVTable mVTable{};
    };

    details::IDiscCachedTitleAccessorBase &GetDefaultCachedTitleAccessor();
} // namespace nn::sl

#endif