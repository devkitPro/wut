#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/uds/ScrambledLocalFriendCode.h>
#include <nn/cfg/CTR.h>

#ifdef __cplusplus

namespace nn {

namespace uds {

namespace Cafe {
   //! Stores information about a node
   struct WUT_PACKED NodeInformation {
      //! The scrambled local friend code of the node
      ScrambledLocalFriendCode scrambledLocalFriendCode;
      //! The node username
      nn::cfg::CTR::UserName username;
      //! The network node ID
      uint16_t networkNodeId;
      //! Unknown
      WUT_UNKNOWN_BYTES(0x2);
   };
   WUT_CHECK_SIZE(NodeInformation, 0x28);
   WUT_CHECK_OFFSET(NodeInformation, 0x00, scrambledLocalFriendCode);
   WUT_CHECK_OFFSET(NodeInformation, 0x0C, username);
   WUT_CHECK_OFFSET(NodeInformation, 0x24, networkNodeId);
} // namespace Cafe

} // namespace uds

} // namespace nn

#endif
