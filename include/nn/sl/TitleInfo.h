#pragma once
#include <wut.h>
namespace nn::sl {
    struct WUT_PACKED TitleInfo {
        WUT_UNKNOWN_BYTES(0x20);
    };
    WUT_CHECK_SIZE(TitleInfo, 0x20);
} // namespace nn::sl