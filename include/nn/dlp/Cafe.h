#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/cfg/CTR.h>
#include <nn/uds/NodeInformation.h>

/**
 * \defgroup nn_dlp nn_dlp
 * \ingroup nn_dlp
 * Download Play functions (see \link nn::dlp \endlink)
 * @{
 */

#ifdef __cplusplus

namespace nn {

namespace dlp {

namespace Cafe {
   enum PollStateChangeFlags : uint8_t {
      //! Prevents \c PollStateChange from blocking if no new data is available
      DLP_POLL_NONBLOCK  = 1 << 0,
   };
   WUT_CHECK_SIZE(PollStateChangeFlags, 0x1);

   //! Represents the client state
   enum class ClientState : uint32_t {
      //! The client is accepted for the DLP child distribution
      Accepted    = 5,
      //! The client is receiving the distributed DLP child
      Receiving   = 6,
      //! The client has received the distribution and is ready to boot the DLP child
      Ready       = 7,
      //! The client is connected to the session and pending to be accepted
      Connecting  = 64
   };
   WUT_CHECK_SIZE(ClientState, 0x4);

   //! Represents the server state. All values between 3 and 7 are considered internal state
   enum class ServerState : uint32_t {
      //! The server is not initialized
      Uninitialized         = 0,
      //! The server is initialized but there is no active network
      Idle                  = 1,
      //! The server is open to new connections
      Open                  = 2,
      //! The server is distributing the DLP child to the clients
      DistributingInternal  = 7,
      //! The server has distributed the DLP child
      Distributed           = 8,
      //! The server has finished distribution and clients are booted into the DLP child
      Finished              = 9,
      //! The server failed to distribute the DLP child to the clients
      Failed                = 10,
      //! Public value for internal states
      Distributing          = 11
   };
   WUT_CHECK_SIZE(ServerState, 0x4);

   class Server {
   public:
      /**
       * Accepts a client into the DLP child distribution.
       *
       * \param nodeId
       * The node ID of the client.
       */
      static nn::Result
      AcceptClient(uint16_t nodeId) asm("AcceptClient__Q4_2nn3dlp4Cafe6ServerSFUs");

      /**
       * Closes the DLP session.
       */
      static nn::Result
      CloseSessions() asm("CloseSessions__Q4_2nn3dlp4Cafe6ServerSFv");

      /**
       * Disconnects a client from the DLP session. This cannot be done after starting distribution.
       *
       * \param nodeId
       * The node ID of the client.
       */
      static nn::Result
      DisconnectClient(uint16_t nodeId) asm("DisconnectClient__Q4_2nn3dlp4Cafe6ServerSFUs");

      /**
       * Finalizes DLP.
       */
      static nn::Result
      Finalize() asm("Finalize__Q4_2nn3dlp4Cafe6ServerSFv");

      /**
       * Gets information about a client.
       *
       * \param clientInfo
       * Pointer where the client information is written.
       *
       * \param nodeId
       * Node ID of the client.
       */
      static nn::Result
      GetClientInfo(nn::uds::Cafe::NodeInformation *clientInfo, uint16_t nodeId) asm("GetClientInfo__Q4_2nn3dlp4Cafe6ServerSFPQ4_2nn3uds4Cafe15NodeInformationUs");

      /**
       * Gets a client state.
       *
       * \param state
       * Pointer where the client state is filled in.
       *
       * \param nodeId
       * Node ID of the client.
       */
      static nn::Result
      GetClientState(ClientState *state, uint16_t nodeId) asm("GetClientState__Q4_2nn3dlp4Cafe6ServerSFPQ4_2nn3dlp4Cafe11ClientStateUs");

      /**
       * Gets a client state.
       *
       * \param state
       * Pointer where the client state is filled in.
       *
       * \param unitsTotal
       * Pointer filled with the total number of units being distributed.
       * Only filled when starting distribution and the DLP child isn't cached.
       *
       * \param unitsReceived
       * Pointer filled with the number of units that the client has received.
       * Only filled when starting distribution and the DLP child isn't cached.
       *
       * \param nodeId
       * Node ID of the client.
       */
      static nn::Result
      GetClientState(ClientState *state,
                     uint32_t *unitsTotal,
                     uint32_t *unitsReceived,
                     uint16_t nodeId) asm("GetClientState__Q4_2nn3dlp4Cafe6ServerSFPQ4_2nn3dlp4Cafe11ClientStatePUiT2Us");

      /**
       * Gets the clients that are connected to the DLP session.
       *
       * \param receivedLength
       * Pointer where the number of clients written to the array is stored.
       *
       * \param connectingClients
       * Array where the node IDs of the clients are written.
       *
       * \param length
       * Number of nodes that the \c connectingClients array can hold.
       */
      static nn::Result
      GetConnectingClients(uint16_t *receivedLength,
                           uint16_t *connectingClients,
                           uint16_t length) asm("GetConnectingClients__Q4_2nn3dlp4Cafe6ServerSFPUsT1Us");

      /**
       * Gets the server state. Internal states are filtered as \link Distributing \endlink .
       *
       * \param state
       * Pointer where the server state is written.
       */
      static nn::Result
      GetState(ServerState *state) asm("GetState__Q4_2nn3dlp4Cafe6ServerSFPQ4_2nn3dlp4Cafe11ServerState");

      /**
       * Initializes DLP.
       *
       * \param maxClientNum
       * Maximum number of clients allowed for distribution. Must be between 1 and 8 inclusively.
       *
       * \param uniqueId
       * Unique ID of the DLP child to be distributed.
       *
       * \param childIndex
       * Index of the DLP child to be distributed.
       *
       * \param userName
       * Username that will be displayed to the clients. If \c NULL, the Mii name will be used.
       */
      static nn::Result
      Initialize(uint8_t maxClientNum,
               uint32_t uniqueId,
               uint8_t childIndex,
               nn::cfg::CTR::UserName *userName) asm("Initialize__Q4_2nn3dlp4Cafe6ServerSFUcUiT1PQ4_2nn3cfg3CTR8UserName");

      /**
       * Initializes DLP.
       *
       * \param dupNoticeNeed
       * Unknown output bool, always false on the Wii U.
       *
       * \param maxClientNum
       * Maximum number of clients allowed for distribution. Must be between 1 and 8 inclusively.
       *
       * \param uniqueId
       * Unique ID of the DLP child to be distributed.
       *
       * \param childIndex
       * Index of the DLP child to be distributed.
       *
       * \param userName
       * Username that will be displayed to the clients. If \c NULL, the Mii name will be used.
       */
      static nn::Result
      Initialize(bool *dupNoticeNeed,
               uint8_t maxClientNum,
               uint32_t uniqueId,
               uint8_t childIndex,
               nn::cfg::CTR::UserName *userName) asm("Initialize__Q4_2nn3dlp4Cafe6ServerSFPbUcUiT2PQ4_2nn3cfg3CTR8UserName");

      /**
       * Opens the DLP session.
       *
       * \param isManualAccept
       * If set, all clients must be accepted to allow them to join the session.
       *
       * \param channel
       * The channel to be used for hosting the session. Use 0 to choose a channel automatically.
       * Must be either 0, 1, 6 or 11.
       */
      static nn::Result
      OpenSessions(bool isManualAccept, uint8_t channel) asm("OpenSessions__Q4_2nn3dlp4Cafe6ServerSFbUc");

      /**
       * Checks if the server state chas changed, and waits until it changes if specified.
       *
       * \param flags
       * Flags, see \link PollStateChangeFlags \endlink for all flags.
       */
      static nn::Result
      PollStateChange(uint8_t flags) asm("PollStateChange__Q4_2nn3dlp4Cafe6ServerSFUc");

      /**
       * Reboots all clients into the Download Play child.
       *
       * \param passPhrase
       * Passphrase to be used by the client when connecting to the main UDS network.
       * If \c NULL, it will be set to an empty string.
       */
      static nn::Result
      RebootAllClients(const char *passPhrase) asm("RebootAllClients__Q4_2nn3dlp4Cafe6ServerSFPCc");

      /**
       * Starts distribution of the Download Play child.
       */
      static nn::Result
      StartDistribution() asm("StartDistribute__Q4_2nn3dlp4Cafe6ServerSFv");
   };

   class ServerPrivate {
   public:
      /**
       * Gets the server state. Internal states are not filtered.
       *
       * \param state
       * Pointer where the server state is written.
       */
      static nn::Result
      GetInternalState(ServerState *state) asm("GetInternalState__Q4_2nn3dlp4Cafe13ServerPrivateSFPQ4_2nn3dlp4Cafe11ServerState");

      /**
       * Initializes DLP.
       *
       * \param maxClientNum
       * Maximum number of clients allowed for distribution. Must be between 1 and 8 inclusively.
       *
       * \param uniqueId
       * Unique ID of the DLP child to be distributed.
       *
       * \param childIndex
       * Index of the DLP child to be distributed.
       *
       * \param blockBufferSize
       * Unknown parameter (default: 0xC000). Must be bigger than 0x4000 and smaller than 0x80000 inclusively.
       *
       * \param blockBufferNum
       * Unknown parameter (default: 2). Must be a number between 2 and 4 inclusively.
       *
       * \param userName
       * Username that will be displayed to the clients. If \c NULL, the Mii name will be used.
       */
      static nn::Result
      Initialize(uint8_t maxClientNum,
               uint32_t uniqueId,
               uint8_t childIndex,
               uint32_t blockBufferSize,
               uint32_t blockBufferNum,
               nn::cfg::CTR::UserName *userName) asm("Initialize__Q4_2nn3dlp4Cafe13ServerPrivateSFUcUiT1N22PQ4_2nn3cfg3CTR8UserName");

      /**
       * Initializes DLP.
       *
       * \param dupNoticeNeed
       * Unknown output bool, always false on the Wii U.
       *
       * \param maxClientNum
       * Maximum number of clients allowed for distribution. Must be between 1 and 8 inclusively.
       *
       * \param uniqueId
       * Unique ID of the DLP child to be distributed.
       *
       * \param childIndex
       * Index of the DLP child to be distributed.
       *
       * \param blockBufferSize
       * Unknown parameter (default: 0xC000). Must be bigger than 0x4000 and smaller than 0x80000 inclusively.
       *
       * \param blockBufferNum
       * Unknown parameter (default: 2). Must be a number between 2 and 4 inclusively.
       *
       * \param userName
       * Username that will be displayed to the clients. If \c NULL, the Mii name will be used.
       */
      static nn::Result
      Initialize(bool *dupNoticeNeed,
               uint8_t maxClientNum,
               uint32_t uniqueId,
               uint8_t childIndex,
               uint32_t blockBufferSize,
               uint32_t blockBufferNum,
               nn::cfg::CTR::UserName *userName) asm("Initialize__Q4_2nn3dlp4Cafe13ServerPrivateSFPbUcUiT2N23PQ4_2nn3cfg3CTR8UserName");
   };
} // namespace Cafe

} // namespace dlp

} // namespace nn

/** @} */

#endif
