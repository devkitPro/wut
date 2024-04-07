#pragma once

#include <memory>
#include <nn/result.h>
#include <nn/sl/details/ITitleListAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    class ITitleListAccessor : public details::ITitleListAccessorBase {

    public:
        ITitleListAccessor() {
            InitInternalVtable();
        }


        ITitleListAccessor(ITitleListAccessor &src) {
            InitInternalVtable();
        }

        ITitleListAccessor &operator=(const ITitleListAccessor &other) {
            InitInternalVtable();
            return *this;
        }

        ITitleListAccessor &operator=(ITitleListAccessor &&src) noexcept {
            InitInternalVtable();
            return *this;
        }

        ~ITitleListAccessor() override = default;

    private:
        static nn::Result GetWrapper(details::ITitleListAccessorInternal *instance, nn::sl::TitleInfo *outTitleInfos, int *outTitleInfosSize, int maxTitleInfos) {
            return instance->vtable->instance->Get(outTitleInfos, outTitleInfosSize, maxTitleInfos);
        }

        details::ITitleListAccessorInternal *GetInternal() override {
            return &mInstance;
        }

        void InitInternalVtable() {
            mVTable          = {.instance = this,
                                .GetFn    = &GetWrapper};
            mInstance.vtable = &mVTable;
        }

        details::ITitleListAccessorInternal mInstance{};
        details::ITitleListAccessorInternalVTable mVTable{};
    };

    details::ITitleListAccessorBase &GetDefaultTitleListAccessor();
} // namespace nn::sl

#endif