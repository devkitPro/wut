#pragma once
#include <wut.h>
namespace nn::sl {
    struct WUT_PACKED IconInfo {
        WUT_UNKNOWN_BYTES(0x20);
    };
    WUT_CHECK_SIZE(IconInfo, 0x20);
} // namespace nn::sl