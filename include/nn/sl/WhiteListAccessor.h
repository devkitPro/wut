#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    struct WUT_PACKED WhiteList {
        uint32_t titleTypes[50];
        uint32_t titleTypeCount;
        WUT_PADDING_BYTES(4);
        uint64_t titleIds[50];
        uint32_t titleIdCount;
    };
    WUT_CHECK_SIZE(WhiteList, 0x264);
    WUT_CHECK_OFFSET(WhiteList, 0x00, titleTypes);
    WUT_CHECK_OFFSET(WhiteList, 0xC8, titleTypeCount);
    WUT_CHECK_OFFSET(WhiteList, 0xD0, titleIds);
    WUT_CHECK_OFFSET(WhiteList, 0x260, titleIdCount);

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