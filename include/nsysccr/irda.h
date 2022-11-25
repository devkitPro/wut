#pragma once
#include <nsysccr/cdc.h>

/**
 * \defgroup nsysccr_cdc_irda
 * \ingroup nsysccr
 * InfraRed Data
 * 
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t CCRCDCIrdaCommand;
typedef uint8_t CCRCDCIrdaBitrate;
typedef uint8_t CCRCDCIrdaConnectionType;
typedef struct CCRCDCIrdaConnectRequest CCRCDCIrdaConnectRequest;
typedef struct CCRCDCIrdaConnectReply CCRCDCIrdaConnectReply;
typedef struct CCRCDCIrdaSendRequest CCRCDCIrdaSendRequest;
typedef struct CCRCDCIrdaSendReply CCRCDCIrdaSendReply;
typedef struct CCRCDCIrdaReceiveRequest CCRCDCIrdaReceiveRequest;
typedef struct CCRCDCIrdaReceiveReply CCRCDCIrdaReceiveReply;
typedef struct CCRCDCIrdaDisconnectRequest CCRCDCIrdaDisconnectRequest;
typedef struct CCRCDCIrdaDisconnectReply CCRCDCIrdaDisconnectReply;
typedef struct CCRCDCIrdaSmallPacketHeader CCRCDCIrdaSmallPacketHeader;
typedef struct CCRCDCIrdaLargePacketHeader CCRCDCIrdaLargePacketHeader;

//! The buffer size for data tranfers (send / receive)
#define CCR_CDC_IRDA_DATA_TRANSFER_SIZE 0x208

typedef enum
{
   //! Initiate a new connection
   CCR_IRDA_COMMAND_CONNECT     = 0,
   //! Send data
   CCR_IRDA_COMMAND_SEND        = 1,
   //! Receive data
   CCR_IRDA_COMMAND_RECEIVE     = 2,
   //! Disconnect
   CCR_IRDA_COMMAND_DISCONNECT  = 3,
} CCRCDCIrdaCommandEnum;

typedef enum
{
   //! 115200 bits-per-second
   CCR_IRDA_BITRATE_115200  = 0,
   //! 96000 bits-per-second
   CCR_IRDA_BITRATE_96000   = 1,
   //! 72000 bits-per-second
   CCR_IRDA_BITRATE_72000   = 2,
   //! 57600 bits-per-second
   CCR_IRDA_BITRATE_57600   = 3,
   //! 48000 bits-per-second
   CCR_IRDA_BITRATE_48000   = 4,
   //! 38400 bits-per-second
   CCR_IRDA_BITRATE_38400   = 5,
   //! 36000 bits-per-second
   CCR_IRDA_BITRATE_36000   = 6,
   //! 24000 bits-per-second
   CCR_IRDA_BITRATE_24000   = 7,
   //! 19200 bits-per-second
   CCR_IRDA_BITRATE_19200   = 8,
   //! 18000 bits-per-second
   CCR_IRDA_BITRATE_18000   = 9,
   //! 12000 bits-per-second
   CCR_IRDA_BITRATE_12000   = 10,
   //! 9600 bits-per-second
   CCR_IRDA_BITRATE_9600    = 11,
   //! 7200 bits-per-second
   CCR_IRDA_BITRATE_7200    = 13,
   //! 6000 bits-per-second
   CCR_IRDA_BITRATE_6000    = 13,
   //! 4800 bits-per-second
   CCR_IRDA_BITRATE_4800    = 14,
   //! 3000 bits-per-second
   CCR_IRDA_BITRATE_3000    = 15,
} CCRCDCIrdaBitrateEnum;

typedef enum
{
   //! Wait for another device to start a connection
   CCR_IRDA_CONNECTION_WAIT     = 0,
   //! Initiate a new connection
   CCR_IRDA_CONNECTION_REQUIRE  = 1,
   //! Don't require a connection
   CCR_IRDA_CONNECTION_ANY      = 2,
} CCRCDCIrdaConnectionTypeEnum;

struct WUT_PACKED CCRCDCIrdaConnectRequest
{
   //! CCR_IRDA_COMMAND_CONNECT
   CCRCDCIrdaCommand command;
   //! Timeout of the connection in ms
   uint16_t timeout;
   //! Bitrate of the connection
   CCRCDCIrdaBitrate bitrate;
   //! Amount of data which should be received from the other device
   uint16_t receiveSize;
   //! The ID of the target device
   uint8_t targetId;
   //! The type of the connect request
   CCRCDCIrdaConnectionType type;
};
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x0, command);
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x1, timeout);
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x3, bitrate);
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x4, receiveSize);
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x6, targetId);
WUT_CHECK_OFFSET(CCRCDCIrdaConnectRequest, 0x7, type);
WUT_CHECK_SIZE(CCRCDCIrdaConnectRequest, 0x8);

struct WUT_PACKED CCRCDCIrdaConnectReply
{
   //! 0 on success
   uint8_t result;
};
WUT_CHECK_OFFSET(CCRCDCIrdaConnectReply, 0x0, result);
WUT_CHECK_SIZE(CCRCDCIrdaConnectReply, 0x1);

struct WUT_PACKED CCRCDCIrdaSendRequest
{
   //! CCR_IRDA_COMMAND_SEND
   CCRCDCIrdaCommand command;
   //! The size of this request
   uint16_t size;
   //! Packet data starts here
   uint8_t data[0];
};
WUT_CHECK_OFFSET(CCRCDCIrdaSendRequest, 0x0, command);
WUT_CHECK_OFFSET(CCRCDCIrdaSendRequest, 0x1, size);
WUT_CHECK_OFFSET(CCRCDCIrdaSendRequest, 0x3, data);
WUT_CHECK_SIZE(CCRCDCIrdaSendRequest, 0x3);

struct WUT_PACKED CCRCDCIrdaSendReply
{
   //! 0 on success
   uint8_t result;
};
WUT_CHECK_OFFSET(CCRCDCIrdaSendReply, 0x0, result);
WUT_CHECK_SIZE(CCRCDCIrdaSendReply, 0x1);

struct WUT_PACKED CCRCDCIrdaReceiveRequest
{
   //! CCR_IRDA_COMMAND_RECEIVE
   CCRCDCIrdaCommand command;
};
WUT_CHECK_OFFSET(CCRCDCIrdaReceiveRequest, 0x0, command);
WUT_CHECK_SIZE(CCRCDCIrdaReceiveRequest, 0x1);

struct WUT_PACKED CCRCDCIrdaReceiveReply
{
   //! 0 on success
   uint8_t result;
   //! The size of this reply
   uint16_t size;
   //! Packet data starts here
   uint8_t data[0];
};
WUT_CHECK_OFFSET(CCRCDCIrdaReceiveReply, 0x0, result);
WUT_CHECK_OFFSET(CCRCDCIrdaReceiveReply, 0x1, size);
WUT_CHECK_OFFSET(CCRCDCIrdaReceiveReply, 0x3, data);
WUT_CHECK_SIZE(CCRCDCIrdaReceiveReply, 0x3);

struct WUT_PACKED CCRCDCIrdaDisconnectRequest
{
   //! CCR_IRDA_COMMAND_DISCONNECT
   CCRCDCIrdaCommand command;
};
WUT_CHECK_OFFSET(CCRCDCIrdaDisconnectRequest, 0x0, command);
WUT_CHECK_SIZE(CCRCDCIrdaDisconnectRequest, 0x1);

struct WUT_PACKED CCRCDCIrdaDisconnectReply
{
   //! 0 on success
   uint8_t result;
};
WUT_CHECK_OFFSET(CCRCDCIrdaDisconnectReply, 0x0, result);
WUT_CHECK_SIZE(CCRCDCIrdaDisconnectReply, 0x1);

struct WUT_PACKED CCRCDCIrdaSmallPacketHeader
{
   //! Magic value (needs to be set to 0xa5)
   uint8_t magic;
   //! ID of the session (gets filled out by the DRC before transmitting the packet)
   uint8_t sessionId;
   uint8_t unk : 1;
   //! 0 for small packets
   uint8_t isLarge : 1;
   //! Size of the actual data
   uint8_t dataSize : 6;
   //! Amount of data which should be received from the other device
   uint16_t receiveSize;
};
WUT_CHECK_OFFSET(CCRCDCIrdaSmallPacketHeader, 0x0, magic);
WUT_CHECK_OFFSET(CCRCDCIrdaSmallPacketHeader, 0x1, sessionId);
WUT_CHECK_OFFSET(CCRCDCIrdaSmallPacketHeader, 0x3, receiveSize);
WUT_CHECK_SIZE(CCRCDCIrdaSmallPacketHeader, 0x5);

struct WUT_PACKED CCRCDCIrdaLargePacketHeader
{
   //! Magic value (needs to be set to 0xa5)
   uint8_t magic;
   //! ID of the session (gets filled out by the DRC before transmitting the packet)
   uint8_t sessionId;
   uint8_t unk : 1;
   //! 1 for large packets
   uint8_t isLarge : 1;
   //! Size of the actual data
   uint16_t dataSize : 14;
   //! Amount of data which should be received from the other device
   uint16_t receiveSize;
};
WUT_CHECK_OFFSET(CCRCDCIrdaLargePacketHeader, 0x0, magic);
WUT_CHECK_OFFSET(CCRCDCIrdaLargePacketHeader, 0x1, sessionId);
WUT_CHECK_OFFSET(CCRCDCIrdaLargePacketHeader, 0x4, receiveSize);
WUT_CHECK_SIZE(CCRCDCIrdaLargePacketHeader, 0x6);

/**
 * Controls IR of the GamePad.
 * Note that the GamePad expects data in a specific packet format.
 * 
 * \param dest
 * The device to get the mac address from.
 * See \link CCRCDCDestinationEnum \endlink.
 * 
 * \param request
 * The request payload sent to the GamePad.
 * 
 * \param requestSize
 * The size of the request payload.
 * 
 * \param response
 * The response payload received from the GamePad.
 * 
 * \param responseSize
 * The size of the response payload.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCDCPerIrdaControl(CCRCDCDestination dest,
                     void *request,
                     uint32_t requestSize,
                     void *response, 
                     uint32_t responseSize);

#ifdef __cplusplus
}
#endif

/** @} */
