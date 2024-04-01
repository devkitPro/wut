#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    namespace details {
        struct WhiteListAccessorInternal;

        typedef nn::Result (*WhiteListAccessorInternal_LoadFn)(WhiteListAccessorInternal *, WhiteList *);

        typedef struct WUT_PACKED WhiteListAccessorInternalVTable {
            WUT_UNKNOWN_BYTES(0x14);
            WhiteListAccessorInternal_LoadFn getFn;
        } WhiteListAccessorInternalVTable;
        WUT_CHECK_SIZE(WhiteListAccessorInternalVTable, 0x18);
        WUT_CHECK_OFFSET(WhiteListAccessorInternalVTable, 0x14, getFn);

        typedef struct WUT_PACKED WhiteListAccessorInternal {
            WhiteListAccessorInternalVTable *vtable;
        } WhiteListAccessorInternal;
        WUT_CHECK_SIZE(WhiteListAccessorInternal, 0x04);
        WUT_CHECK_OFFSET(WhiteListAccessorInternal, 0x00, vtable);

        extern "C" WhiteListAccessorInternal *GetDefaultWhiteListAccessor__Q2_2nn2slFv();
    } // namespace details

    class WhiteListAccessor {
    public:
        explicit WhiteListAccessor(details::WhiteListAccessorInternal *instance) : mInstance(instance) {
        }

        ~WhiteListAccessor() = default;

        nn::Result Get(WhiteList *whiteList) {
            return mInstance->vtable->getFn(mInstance, whiteList);
        }

    private:
        details::WhiteListAccessorInternal *mInstance = {};
    };

    WhiteListAccessor GetDefaultWhiteListAccessor() {
        return WhiteListAccessor(details::GetDefaultWhiteListAccessor__Q2_2nn2slFv());
    }
} // namespace nn::sl

#endif