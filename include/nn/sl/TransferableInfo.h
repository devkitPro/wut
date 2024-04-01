#pragma once
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    typedef struct WUT_PACKED TransferableInfo {
        WUT_UNKNOWN_BYTES(0xc1934);
    } TransferableInfo;
    WUT_CHECK_SIZE(TransferableInfo, 0xc1934);

} // namespace nn::sl

#endif
