#include "irc/cdc.h"

#include <nsysccr/irda.h>
#include <vpadbase/base.h>

#include <string.h>

static uint8_t sendBuffer[CCR_CDC_IRDA_DATA_TRANSFER_SIZE] __attribute__((aligned(0x40)));
static uint8_t replyBuffer[CCR_CDC_IRDA_DATA_TRANSFER_SIZE] __attribute__((aligned(0x40)));

int32_t
__CCRCDCIRCConnect(int32_t drcIndex,
                   uint8_t *result,
                   uint16_t timeout,
                   CCRCDCIrdaBitrate bitrate,
                   uint32_t receiveSize,
                   uint8_t targetId,
                   CCRCDCIrdaConnectionType type)
{
    CCRCDCIrdaConnectRequest *request = (CCRCDCIrdaConnectRequest *) sendBuffer;
    CCRCDCIrdaConnectReply *reply = (CCRCDCIrdaConnectReply *) replyBuffer;

    if (receiveSize < 0x3e) {
        request->receiveSize = receiveSize + sizeof(CCRCDCIrdaSmallPacketHeader) + 1; // +1 for crc8
    } else {
        request->receiveSize = receiveSize + sizeof(CCRCDCIrdaLargePacketHeader) + 1; // +1 for crc8
    }

    reply->result = 0;
    request->command = CCR_IRDA_COMMAND_CONNECT;
    request->timeout = timeout;
    request->bitrate = bitrate;
    request->targetId = targetId;
    request->type = type;
    int32_t ret = CCRCDCPerIrdaControl(CCR_CDC_DESTINATION_DRC0 + drcIndex,
                                       request, sizeof(CCRCDCIrdaConnectRequest),
                                       reply, sizeof(CCRCDCIrdaConnectReply));
    if (ret == 0) {
        *result = reply->result;
    }

    return ret;
}

int32_t
__CCRCDCIRCSend(int32_t drcIndex,
                uint8_t *result,
                uint32_t size,
                uint32_t receiveSize,
                void *data)
{
    CCRCDCIrdaSendRequest *request = (CCRCDCIrdaSendRequest *) sendBuffer;
    CCRCDCIrdaSendReply *reply = (CCRCDCIrdaSendReply *) replyBuffer;

    uint16_t totalReceiveSize;
    if (receiveSize < 0x3e) {
        totalReceiveSize = receiveSize + sizeof(CCRCDCIrdaSmallPacketHeader) + 1; // +1 for crc8
    } else {
        totalReceiveSize = receiveSize + sizeof(CCRCDCIrdaLargePacketHeader) + 1; // +1 for crc8
    }

    void *packetData;
    uint32_t packetSize;
    if (size < 0x3e) {
        CCRCDCIrdaSmallPacketHeader *header = (CCRCDCIrdaSmallPacketHeader *) request->data;
        header->sessionId = 0;
        header->receiveSize = totalReceiveSize;
        header->magic = 0xa5;
        header->unk = 0;
        header->isLarge = 0;
        header->dataSize = size + 2; // +2 for requestSize

        packetData = header + 1;
        packetSize = size + sizeof(CCRCDCIrdaSmallPacketHeader) + 1; // +1 for crc8
    } else {
        CCRCDCIrdaLargePacketHeader *header = (CCRCDCIrdaLargePacketHeader *) request->data;
        header->sessionId = 0;
        header->receiveSize = totalReceiveSize;
        header->magic = 0xa5;
        header->unk = 0;
        header->isLarge = 1;
        header->dataSize = size + 2; // +2 for requestSize

        packetData = header + 1;
        packetSize = size + sizeof(CCRCDCIrdaLargePacketHeader) + 1; // +1 for crc8
    }

    // Copy the data into the packet
    memcpy(packetData, data, size);

    // Fill the rest of the buffer with 0
    uint32_t spaceLeft = CCR_CDC_IRDA_DATA_TRANSFER_SIZE - sizeof(CCRCDCIrdaSendRequest) - packetSize;
    if (spaceLeft > 0) {
        memset((uint8_t *) packetData + size, 0, spaceLeft);
    }

    request->command = CCR_IRDA_COMMAND_SEND;
    request->size = packetSize;
    reply->result = 0;
    int32_t ret = CCRCDCPerIrdaControl(CCR_CDC_DESTINATION_DRC0 + drcIndex,
                                       request, CCR_CDC_IRDA_DATA_TRANSFER_SIZE,
                                       reply, sizeof(CCRCDCIrdaSendReply));
    if (ret == 0) {
        *result = reply->result;
    }

    return ret;
}

int32_t
__CCRCDCIRCReceive(int32_t drcIndex,
                   uint8_t *result,
                   uint16_t *receivedSize,
                   void *data)
{
    CCRCDCIrdaReceiveRequest *request = (CCRCDCIrdaReceiveRequest *) sendBuffer;
    CCRCDCIrdaReceiveReply *reply = (CCRCDCIrdaReceiveReply *) data;

    request->command = CCR_IRDA_COMMAND_RECEIVE;
    memset(data, 0, CCR_CDC_IRDA_DATA_TRANSFER_SIZE);
    int32_t ret = CCRCDCPerIrdaControl(CCR_CDC_DESTINATION_DRC0 + drcIndex,
                                       request, sizeof(CCRCDCIrdaReceiveRequest),
                                       reply, CCR_CDC_IRDA_DATA_TRANSFER_SIZE);
    if (ret == 0) {
        *result = reply->result;
        *receivedSize = reply->size + 1; // +1 for crc8
    }

    VPADBASEClearIRCEvent((VPADChan) drcIndex);
    return ret;
}

int32_t
__CCRCDCIRCDisconnect(int32_t drcIndex,
                      uint8_t *result)
{
    CCRCDCIrdaDisconnectRequest *request = (CCRCDCIrdaDisconnectRequest *) sendBuffer;
    CCRCDCIrdaDisconnectReply *reply = (CCRCDCIrdaDisconnectReply *) replyBuffer;

    reply->result = 0;
    request->command = CCR_IRDA_COMMAND_DISCONNECT;
    int32_t ret = CCRCDCPerIrdaControl(CCR_CDC_DESTINATION_DRC0 + drcIndex,
                                       request, sizeof(CCRCDCIrdaDisconnectRequest),
                                       reply, sizeof(CCRCDCIrdaDisconnectReply));
    if (ret == 0) {
        *result = reply->result;
    }

    return ret;
}
