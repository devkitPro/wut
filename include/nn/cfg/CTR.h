#pragma once

#include <wut.h>

#ifdef __cplusplus

namespace nn {

namespace cfg {

namespace CTR {

//! Represents a console username, used in UDS and DLP
struct UserName {
   char16_t name[12];
};
WUT_CHECK_SIZE(UserName, 0x18);

} // namespace CTR

} // namespace cfg

} // namespace nn

#endif
