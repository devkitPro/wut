#pragma once
#include <wut.h>
#include <vpadbase/base.h>
#include <nsysccr/irda.h>

/**
 * \defgroup irc_irc
 * \ingroup irc
 * High-Level InfraRed Connection
 * 
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
   //! No error
   IRC_RESULT_SUCCESS                   = 0,
   //! The amount of data received from the other device does not match the requested size
   IRC_RESULT_INVALID_RECEIVE_SIZE      = 3,
   //! The received packet is invalid
   IRC_RESULT_INVALID_PACKET            = 5,
   //! No data was available to receive
   IRC_RESULT_NO_DATA                   = 6,
   //! Tried to connect while a connection was already established
   IRC_RESULT_ALREADY_CONNECTED         = 11,
   //! IR is not available (Is the DRC TV menu open?)
   IRC_IR_UNAVAILABLE                   = 12,
   //! IRC is not initialized
   IRC_RESULT_UNINITIALIZED             = 13,
   //! No connection
   IRC_RESULT_NOT_CONNECTED             = 13,
   //! __CCRCDCIRCConnect failed
   IRC_RESULT_CONNECT_FAILED            = 15,
   //! __CCRCDCIRCReceive failed
   IRC_RESULT_RECEIVE_FAILED            = 16,
   //! __CCRCDCIRCSend failed
   IRC_RESULT_SEND_FAILED               = 17,
   //! __CCRCDCIRCDisconnect failed
   IRC_RESULT_DISCONNECT_FAILED         = 18,
} IRCResult;

typedef void (*IRCConnectCallback)();
typedef void (*IRCReceiveCallback)(void *data, uint16_t size, IRCResult result);

/**
 * Initializes the IRC library.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \param targetId
 * The targetId of the other device.
 * 
 * \return
 * \c TRUE on success.
 */
BOOL
IRCInit(VPADChan channel,
        uint8_t targetId);

/**
 * Starts an IR connection.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \param timeout
 * Timeout in ms for the connection.
 * 
 * \param type
 * The type of the connection.
 * 
 * \param bitrate
 * The bitrate of the connection.
 * See \link CCRCDCIrdaBitrateEnum \endlink.
 * 
 * \param receiveSize
 * Amount of data which should be received from the other device.
 * 
 * \param callback
 * Callback which will be called once the connection is established (can be \c NULL).
 * 
 * \return
 * \c IRC_RESULT_SUCCESS on success.
 */
IRCResult
IRCConnect(VPADChan channel,
           uint16_t timeout,
           CCRCDCIrdaConnectionType type,
           CCRCDCIrdaBitrate bitrate,
           uint32_t receiveSize,
           IRCConnectCallback callback);

/**
 * Process the internal state.
 * Should be called periodically.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \return
 * \c IRC_RESULT_SUCCESS on success.
 */
IRCResult
IRCProc(VPADChan channel);

/**
 * Sends data over an IR connection.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \param data
 * The data which should be sent.
 * 
 * \param dataSize
 * The size of the data which should be sent.
 * 
 * \param receiveSize
 * Amount of data which should be received from the other device.
 * 
 * \return
 * \c IRC_RESULT_SUCCESS on success.
 */
IRCResult
IRCSend(VPADChan channel,
        void *data,
        uint32_t dataSize,
        uint32_t receiveSize);

/**
 * Checks if a connection is established.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \return
 * \c TRUE if connected.
 */
BOOL
IRCIsConnect(VPADChan channel);

/**
 * Terminates the connection.
 * 
 * \param channel
 * The device to use for IR.
 * 
 * \return
 * \c IRC_RESULT_SUCCESS on success.
 */
IRCResult
IRCDisconnect(VPADChan channel);

/**
 * Sets a callback for receiving data.
 * 
 * \param channel
 * The device to use for IR.
 *
 * \param receiveCallback
 * The receive callback which should be set.
 * 
 * \return
 * The previously set callback.
 */
IRCReceiveCallback
IRCSetReceiveCallback(VPADChan channel,
                      IRCReceiveCallback receiveCallback);

#ifdef __cplusplus
}
#endif

/** @} */
