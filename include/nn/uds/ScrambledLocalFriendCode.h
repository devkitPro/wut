#pragma once

#include <wut.h>
#include <nn/result.h>

#ifdef __cplusplus

namespace nn {

namespace uds {

namespace Cafe {
   //! Stores data about the scrambled local friend code of a node
   struct WUT_PACKED ScrambledLocalFriendCode {
      //! The scrambled local friend code. On the Wii U this is always descrambled
      uint64_t localFriendCode;
      //! The node ID that the local friend code belongs to
      uint16_t networkNodeId;
      //! The XOR key used for descrambling the local friend code
      uint16_t xorKey;
   };
   WUT_CHECK_SIZE(ScrambledLocalFriendCode, 0x0C);
   WUT_CHECK_OFFSET(ScrambledLocalFriendCode, 0x00, localFriendCode);
   WUT_CHECK_OFFSET(ScrambledLocalFriendCode, 0x08, networkNodeId);
   WUT_CHECK_OFFSET(ScrambledLocalFriendCode, 0x0A, xorKey);
} // namespace Cafe

} // namespace uds

} // namespace nn

#endif
