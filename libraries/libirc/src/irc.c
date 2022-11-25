#include "irc/irc.h"
#include "irc/cdc.h"

#include <vpad/input.h>

typedef enum {
   IRC_STATE_UNINITIALIZED,
   IRC_STATE_DISCONNECTED,
   IRC_STATE_WAITING,
   IRC_STATE_CONNECTED,
} IRCState;

static BOOL isInitialized = FALSE;
static IRCState state = IRC_STATE_UNINITIALIZED;
static CCRCDCIrdaConnectionType connectionType;
static uint8_t targetId;
static uint8_t sessionId;
static IRCReceiveCallback receiveCallback;
static IRCConnectCallback connectCallback;
static uint8_t receiveBuffer[CCR_CDC_IRDA_DATA_TRANSFER_SIZE] __attribute__((aligned(0x40)));

BOOL
IRCInit(VPADChan channel,
        uint8_t _targetId)
{
   if (!VPADBASEIsInit()) {
      return FALSE;
   }

   if (isInitialized) {
      return FALSE;
   }

   isInitialized = TRUE;
   state = IRC_STATE_DISCONNECTED;
   connectionType = CCR_IRDA_CONNECTION_WAIT;
   targetId = _targetId;
   receiveCallback = NULL;
   connectCallback = NULL;

   return TRUE;
}

IRCResult
IRCConnect(VPADChan channel,
           uint16_t timeout,
           CCRCDCIrdaConnectionType type,
           CCRCDCIrdaBitrate bitrate,
           uint32_t receiveSize,
           IRCConnectCallback callback)
{
   if (state == IRC_STATE_UNINITIALIZED) {
     return IRC_RESULT_UNINITIALIZED;
   }

   // Can't connected if we already have an established connection
   if (state == IRC_STATE_CONNECTED) {
      return IRC_RESULT_ALREADY_CONNECTED;
   }

   // IR is blocked if the TV menu is opened
   if (VPADGetTVMenuStatus(channel)) {
      return IRC_IR_UNAVAILABLE;
   }

   connectionType = type;

   uint8_t result;
   if (__CCRCDCIRCConnect(channel,
                          &result,
                          timeout,
                          bitrate,
                          receiveSize,
                          targetId,
                          type) != 0) {
      return IRC_RESULT_CONNECT_FAILED;
   }

   if (result != 0) {
      return result;
   }

   /* This causes a race between the connected bit changing in IRCStatus
      and IRCProc changing the state back to disconnected.
      Let's not do this. */
   //if (connectionType == CCR_IRDA_CONNECTION_ANY) {
   //   // If the type is any, we don't need to wait for a connection
   //   state = IRC_STATE_CONNECTED;
   //} else {
      state = IRC_STATE_WAITING;
      connectCallback = callback;
   //}

   return IRC_RESULT_SUCCESS;
}

IRCResult
IRCProc(VPADChan channel)
{
   if (!isInitialized) {
      return IRC_RESULT_UNINITIALIZED;
   }

   uint32_t status = VPADBASEGetIRCStatus(channel);
   if (status & VPAD_IRC_STATUS_FLAG_CONNECTED) {
      // If we were waiting on a connection, we're now connected
      if (state == IRC_STATE_WAITING) {
         if (connectCallback) {
            connectCallback();
         }

         state = IRC_STATE_CONNECTED;
         return IRC_RESULT_SUCCESS;
      }
   } else {
      // If we were connected, the connection is now broken
      if (state == IRC_STATE_CONNECTED) {
         state = IRC_STATE_DISCONNECTED;
      }
   }

   if (!(status & VPAD_IRC_STATUS_FLAG_HAS_DATA)) {
      // IR is blocked if the TV menu is opened
      if (VPADGetTVMenuStatus(channel)) {
         state = IRC_STATE_DISCONNECTED;
         return IRC_IR_UNAVAILABLE;
      }

      return IRC_RESULT_SUCCESS;
   }

   // If we're here, there is pending data which can be received
   uint8_t result;
   uint16_t receivedSize;
   if (__CCRCDCIRCReceive(channel,
                          &result,
                          &receivedSize,
                          receiveBuffer) != 0) {
      return IRC_RESULT_RECEIVE_FAILED;
   }

   if (state == IRC_STATE_UNINITIALIZED) {
      return IRC_RESULT_SUCCESS;
   }

   if (state == IRC_STATE_DISCONNECTED) {
      if (receiveCallback) {
         receiveCallback(NULL, 0, result);
      }

      return result;
   }

   // If we're not connected yet, but are already receiving data, terminate connection
   if (state == IRC_STATE_WAITING) {
      if (receiveCallback) {
         receiveCallback(NULL, 0, result);
      }

      state = IRC_STATE_DISCONNECTED;
      return result;
   }

   if (!receiveCallback) {
      return IRC_RESULT_SUCCESS;
   }

   if (result != 0) {
      receiveCallback(NULL, 0, result);
      return result;
   }

   CCRCDCIrdaSmallPacketHeader *smallHeader = (CCRCDCIrdaSmallPacketHeader *) (receiveBuffer + sizeof(CCRCDCIrdaReceiveReply));
   CCRCDCIrdaLargePacketHeader *largeHeader = (CCRCDCIrdaLargePacketHeader *) (receiveBuffer + sizeof(CCRCDCIrdaReceiveReply));

   sessionId = smallHeader->sessionId;

   void *packetData;
   uint16_t packetSize;
   if (smallHeader->isLarge) {
      packetData = largeHeader + 1;
      packetSize = largeHeader->dataSize;
   } else {
      packetData = smallHeader + 1;
      packetSize = smallHeader->dataSize;
   }

   // Don't count the request size
   packetSize -= 2;

   if (packetSize > 0x1fe) {
      receiveCallback(NULL, 0, IRC_RESULT_INVALID_PACKET);
      return IRC_RESULT_INVALID_PACKET;
   }

   receiveCallback(packetData, packetSize, IRC_RESULT_SUCCESS);
   return IRC_RESULT_SUCCESS;
}

IRCResult
IRCSend(VPADChan channel,
        void *data,
        uint32_t dataSize,
        uint32_t receiveSize)
{
   if (!isInitialized) {
      return IRC_RESULT_UNINITIALIZED;
   }

   // IR is blocked if the TV menu is opened
   if (VPADGetTVMenuStatus(channel)) {
      return IRC_IR_UNAVAILABLE;
   }

   if (state != IRC_STATE_CONNECTED) {
      return IRC_RESULT_NOT_CONNECTED;
   }

   uint8_t result;
   if (__CCRCDCIRCSend(channel,
                       &result,
                       dataSize,
                       receiveSize,
                       data) != 0) {
      return IRC_RESULT_SEND_FAILED;
   }

   return result;
}

BOOL
IRCIsConnect(VPADChan channel)
{
   return state == IRC_STATE_CONNECTED;
}

IRCResult
IRCDisconnect(VPADChan channel)
{
   if (!isInitialized) {
      return IRC_RESULT_UNINITIALIZED;
   }

   // IR is blocked if the TV menu is opened
   if (VPADGetTVMenuStatus(channel)) {
      return IRC_IR_UNAVAILABLE;
   }

   uint8_t result;
   if (__CCRCDCIRCDisconnect(channel,
                             &result) != 0) {
      return IRC_RESULT_DISCONNECT_FAILED;
   }

   state = IRC_STATE_DISCONNECTED;
   return result;
}

IRCReceiveCallback
IRCSetReceiveCallback(VPADChan channel,
                      IRCReceiveCallback _receiveCallback)
{
   IRCReceiveCallback prev = receiveCallback;
   receiveCallback = _receiveCallback;
   return prev;
}
