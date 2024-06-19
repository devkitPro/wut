#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/uds/NodeInformation.h>
#include <nn/cfg/CTR.h>

/**
 * \defgroup nn_uds nn_uds
 * \ingroup nn_uds
 * UDS Network functions (see \link nn::uds \endlink)
 * @{
 */

#ifdef __cplusplus

//! Theoretical supported maximum number of nodes connected to a network, including the host
#define UDS_MAX_NODES 0x10
//! Broadcast node ID, used for sending data to all nodes in the network
#define UDS_BROADCAST_NODE_ID 0xFFFF

namespace nn {

namespace uds {

namespace Cafe {
   //! Stores the connection status of the network
   struct ConnectionStatus {
      //! The network status
      uint32_t status;
      //! The reason why the status has changed
      uint32_t reason;
      //! The network node ID of this device
      uint16_t networkNodeId;
      //! Bitmask of nodes that have changed
      uint16_t changedNodes;
      //! Array of nodes connected to the network
      uint16_t nodes[UDS_MAX_NODES];
      //! Total amount of nodes connected to the network
      uint8_t totalNodes;
      //! Maximum number of nodes that can connect to the network, including the host
      uint8_t maxNodes;
      //! Bitmask of nodes connected to the network
      uint16_t nodeBitmask;
   };
   WUT_CHECK_SIZE(ConnectionStatus, 0x30);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x00, status);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x04, reason);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x08, networkNodeId);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x0A, changedNodes);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x0C, nodes);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x2C, totalNodes);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x2D, maxNodes);
   WUT_CHECK_OFFSET(ConnectionStatus, 0x2E, nodeBitmask);

   //! Recommended size to use for work memory buffer
   static constexpr uint32_t kWorkMemorySize = 0x14000;

   //! Describes a network endpoint
   using EndpointDescriptor = uint32_t;

   enum PollStateChangeFlags : uint8_t {
      //! Prevents \c PollStateChange from blocking if no new data is available
      UDS_POLL_NONBLOCK  = 1 << 0,
   };
   WUT_CHECK_SIZE(PollStateChangeFlags, 0x1);

   enum ReceiveFlags : uint8_t {
      //! Prevents \c Receive from blocking if no new data is available
      UDS_RECEIVE_NONBLOCK  = 1 << 0,
   };
   WUT_CHECK_SIZE(ReceiveFlags, 0x1);

   /**
    * Allows clients to connect to the network.
    */
   nn::Result
   AllowToConnect() asm("AllowToConnect__Q3_2nn3uds4CafeFv");

   /**
    * Allows clients to spectate the network.
    */
   nn::Result
   AllowToSpectate() asm("AllowToSpectate__Q3_2nn3uds4CafeFv");

   /**
    * Attaches an endpoint to a specified node.
    *
    * \param fd
    * The endpoint descriptor.
    *
    * \param networkNodeId
    * The network node ID. Use \link UDS_BROADCAST_NODE_ID \endlink to attach to all nodes.
    *
    * \param dataChannel
    * Data channel to attach to. Must not be 0.
    *
    * \param recvBufferSize
    * Size to be allocated for the internal buffer for receiving data.
    * Must be greater or equal than 1536 bytes.
    */
   nn::Result
   Attach(EndpointDescriptor *fd,
          uint16_t networkNodeId,
          uint8_t dataChannel,
          uint32_t recvBufferSize) asm("Attach__Q3_2nn3uds4CafeFPQ4_2nn3uds4Cafe18EndpointDescriptorUsUcUi");

   /**
    * Creates a local communication ID based on the given paramaters.
    *
    * \param uniqueId
    * A unique identifier of the current title.
    * This is truncated to 20 bits on the created ID.
    *
    * \param unknown
    * Enables or disables a flag on the created ID.
    *
    * \returns
    * The created local communication ID.
    */
   uint32_t
   CreateLocalCommunicationId(uint32_t uniqueId, bool unknown) asm("CreateLocalCommunicationId__Q3_2nn3uds4CafeFUib");

   /**
    * Creates a new endpoint.
    *
    * \param fd
    * A pointer where the endpoint descriptor is written.
    */
   nn::Result
   CreateEndpoint(EndpointDescriptor *fd) asm("CreateEndpoint__Q3_2nn3uds4CafeFPQ4_2nn3uds4Cafe18EndpointDescriptor");

   /**
    * Creates a new network with the given parameters.
    *
    * \param id8
    * ID8 to be used on the network. Must not be 0xFF.
    *
    * \param maxNodes
    * The maximum amount of nodes that will be able to connect to the network,
    * including the host. Must be a number between 2 and 9 inclusively.
    *
    * \param localCommunicationId
    * Local communication ID used for identifying the network.
    *
    * \param passphrase
    * Passphrase to be used for the network.
    *
    * \param passphraseSize
    * Size of the passphrase, including NULL termination. Must be greater than 8
    * characters and lower than 255 characters inclusively.
    *
    * \param channel
    * Channel to use for hosting the network. Use 0 to choose a channel automatically.
    * Must be either 0, 1, 6 or 11.
    */
   nn::Result
   CreateNetwork(uint8_t id8,
                 uint8_t maxNodes,
                 uint32_t localCommunicationId,
                 const char *passphrase,
                 uint32_t passphraseSize,
                 uint8_t channel) asm("CreateNetwork__Q3_2nn3uds4CafeFUcT1UiPCcT3T1");

   /**
    * Creates a new network with the given parameters.
    *
    * \param id8
    * ID8 to be used on the network. Must not be 0xFF.
    *
    * \param maxNodes
    * The maximum amount of nodes that will be able to connect to the network,
    * including the host. Must be a number between 2 and 9 inclusively.
    *
    * \param localCommunicationId
    * Local communication ID used for identifying the network.
    *
    * \param passphrase
    * Passphrase to be used for the network.
    *
    * \param passphraseSize
    * Size of the passphrase, including NULL termination. Must be greater than 8
    * characters and lower than 255 characters inclusively.
    *
    * \param channel
    * Channel to use for hosting the network. Use 0 to choose a channel automatically.
    * Must be either 0, 1, 6 or 11.
    *
    * \param appData
    * Pointer to application data.
    *
    * \param appDataSize
    * Size of application data. Must be lower than 200 bytes inclusively.
    */
   nn::Result
   CreateNetwork(uint8_t id8,
                 uint8_t maxNodes,
                 uint32_t localCommunicationId,
                 const char *passphrase,
                 uint32_t passphraseSize,
                 uint8_t channel,
                 const void *appData,
                 uint32_t appDataSize) asm("CreateNetwork__Q3_2nn3uds4CafeFUcT1UiPCcT3T1PCvT3");

   /**
    * Creates a new network with the given parameters.
    *
    * \param id8
    * ID8 to be used on the network. Must not be 0xFF.
    *
    * \param maxNodes
    * The maximum amount of nodes that will be able to connect to the network,
    * including the host. Must be a number between 2 and 9 inclusively.
    *
    * \param localCommunicationId
    * Local communication ID used for identifying the network.
    *
    * \param passphrase
    * Passphrase to be used for the network.
    *
    * \param passphraseSize
    * Size of the passphrase, including NULL termination. Must be greater than 8
    * characters and lower than 255 characters inclusively.
    *
    * \param unused
    * This parameter is unused.
    *
    * \param channel
    * Channel to use for hosting the network. Use 0 to choose a channel automatically.
    * Must be either 0, 1, 6 or 11.
    *
    * \param appData
    * Pointer to application data.
    *
    * \param appDataSize
    * Size of application data. Must be lower than 200 bytes inclusively.
    */
   nn::Result
   CreateNetwork(uint8_t id8,
                 uint8_t maxNodes,
                 uint32_t localCommunicationId,
                 const char *passphrase,
                 uint32_t passphraseSize,
                 bool unused,
                 uint8_t channel,
                 const void *appData,
                 uint32_t appDataSize) asm("CreateNetwork__Q3_2nn3uds4CafeFUcT1UiPCcT3bT1PCvT3");

   /**
    * Destroys the given endpoint.
    *
    * \param fd
    * The endpoint descriptor.
    */
   nn::Result
   DestroyEndpoint(EndpointDescriptor *fd) asm("DestroyEndpoint__Q3_2nn3uds4CafeFPQ4_2nn3uds4Cafe18EndpointDescriptor");

   /**
    * Destroys the previously created network.
    */
   nn::Result
   DestroyNetwork() asm("DestroyNetwork__Q3_2nn3uds4CafeFv");

   /**
    * Prevents clients from connecting to the network.
    *
    * \param unknown
    * Triggers an unknown flag.
    */
   nn::Result
   DisallowToConnect(bool unknown) asm("DisallowToConnect__Q3_2nn3uds4CafeFb");

   /**
    * Ejects the specified client from the network.
    *
    * \param networkNodeId
    * The network node ID of the client. Use \link UDS_BROADCAST_NODE_ID \endlink to eject all clients.
    */
   nn::Result
   EjectClient(uint16_t networkNodeId) asm("EjectClient__Q3_2nn3uds4CafeFUs");

   /**
    * Ejects all spectators from the network.
    */
   nn::Result
   EjectSpectator() asm("EjectSpectator__Q3_2nn3uds4CafeFv");

   /**
    * Finalizes UDS.
    */
   void
   Finalize() asm("Finalize__Q3_2nn3uds4CafeFv");

   /**
    * Gets the application data from the network.
    *
    * \param appData
    * Buffer where the application data is written.
    *
    * \param readSize
    * Pointer where the size of the application data is written.
    *
    * \param size
    * Size of the buffer.
    */
   nn::Result
   GetApplicationDataFromBeacon(void *appData,
                                uint32_t *readSize,
                                uint32_t size) asm("GetApplicationDataFromBeacon__Q3_2nn3uds4CafeFPvPUiUi");

   /**
    * Gets the network channel.
    *
    * \param channel
    * Pointer where the channel is written.
    */
   nn::Result
   GetChannel(uint8_t *channel) asm("GetChannel__Q3_2nn3uds4CafeFPUc");

   /**
    * Retrieves the connection status of the network.
    *
    * \param status
    * Pointer where the connection status is written.
    */
   nn::Result
   GetConnectionStatus(ConnectionStatus *status) asm("GetConnectionStatus__Q3_2nn3uds4CafeFPQ4_2nn3uds4Cafe16ConnectionStatus");

   /**
    * Gets information about a specified node.
    *
    * \param info
    * Output node information.
    *
    * \param networkNodeId
    * The network node ID.
    */
   nn::Result
   GetNodeInformation(NodeInformation *info, uint16_t networkNodeId) asm("GetNodeInformation__Q3_2nn3uds4CafeFPQ4_2nn3uds4Cafe15NodeInformationUs");

   /**
    * Initializes UDS. The username will be set to the Mii name.
    *
    * \param workMemory
    * Pointer to work memory to be used by UDS.
    *
    * \param workMemorySize
    * Size of work memory. See \link kWorkMemorySize \endlink for a recomended amount of memory.
    */
   nn::Result
   Initialize(void *workMemory, uint32_t workMemorySize) asm("Initialize__Q3_2nn3uds4CafeFPvUi");

   /**
    * Initializes UDS with the given username.
    *
    * \param workMemory
    * Pointer to work memory to be used by UDS.
    *
    * \param workMemorySize
    * Size of work memory. See \link kWorkMemorySize \endlink for a recomended amount of memory.
    *
    * \param username
    * The username to be used. If \c NULL, the username will be set to the Mii name.
    */
   nn::Result
   Initialize(void *workMemory,
              uint32_t workMemorySize,
              nn::cfg::CTR::UserName *username) asm("Initialize__Q3_2nn3uds4CafeFPvUiPQ4_2nn3cfg3CTR8UserName");

   /**
    * Checks if new data can be retrieved through \c GetConnectionStatus,
    * and waits until new data is available if specified.
    *
    * \param flags
    * Flags, see \link PollStateChangeFlags \endlink for all flags.
    */
   nn::Result
   PollStateChange(uint8_t flags) asm("PollStateChange__Q3_2nn3uds4CafeFUc");

   /**
    * Receives data from the specified endpoint.
    *
    * \param fd
    * The endpoint descriptor.
    *
    * \param buf
    * Output buffer where the data will be written.
    *
    * \param receivedSize
    * Pointer where the received size is written.
    *
    * \param networkNodeId
    * Pointer where the incoming node ID is written.
    *
    * \param size
    * Size of the buffer. Must be 4-byte aligned.
    *
    * \param flags
    * Flags, see \link ReceiveFlags \endlink for all flags.
    */
   nn::Result
   ReceiveFrom(const EndpointDescriptor &fd,
               void *buf,
               uint32_t *receivedSize,
               uint16_t *networkNodeId,
               uint32_t size,
               uint8_t flags) asm("ReceiveFrom__Q3_2nn3uds4CafeFRCQ4_2nn3uds4Cafe18EndpointDescriptorPvPUiPUsUiUc");

   /**
    * Receives data from the specified endpoint.
    *
    * \param fd
    * The endpoint descriptor.
    *
    * \param buf
    * Output buffer where the data will be written.
    *
    * \param receivedSize
    * Pointer where the received size is written.
    *
    * \param size
    * Size of the buffer. Must be 4-byte aligned.
    *
    * \param flags
    * Flags, see \link ReceiveFlags \endlink for all flags.
    */
   nn::Result
   Receive(const EndpointDescriptor &fd,
           void *buf,
           uint32_t *receivedSize,
           uint32_t size,
           uint8_t flags) asm("Receive__Q3_2nn3uds4CafeFRCQ4_2nn3uds4Cafe18EndpointDescriptorPvPUiUiUc");

   /**
    * Sends data to the specified node ID through the given data channel.
    *
    * \param fd
    * THe endpoint descriptor.
    *
    * \param buf
    * Buffer which holds the data to be sent.
    *
    * \param size
    * Size of the buffer. Must be lower or equal than 1478 bytes.
    *
    * \param destNodeId
    * The destination node ID.
    *
    * \param dataChannel
    * The destination data channel.
    *
    * \param flags
    * Unknown flags.
    */
   nn::Result
   SendTo(const EndpointDescriptor &fd,
          const void *buf,
          uint32_t size,
          uint16_t destNodeId,
          uint8_t dataChannel,
          uint8_t flags) asm("SendTo__Q3_2nn3uds4CafeFRCQ4_2nn3uds4Cafe18EndpointDescriptorPCvUiUsUcT5");

   /**
    * Sets the application data to the network.
    *
    * \param appData
    * Application data.
    *
    * \param size
    * Size of application data. Must be lower or equal to 200 bytes.
    */
   nn::Result
   SetApplicationDataToBeacon(const void *appData, uint32_t size) asm("SetApplicationDataToBeacon__Q3_2nn3uds4CafeFPCvUi");
} // namespace Cafe

} // namespace uds

} // namespace nn

#endif

/** @} */
