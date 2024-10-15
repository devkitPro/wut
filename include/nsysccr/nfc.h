#pragma once
#include <nsysccr/cdc.h>

/**
 * \defgroup nsysccr_cdc_nfc
 * \ingroup nsysccr
 * Near Field Communication, low level commands
 * 
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t CCRCDCNfcCommand;
typedef struct CCRCDCNfcStartupRequest CCRCDCNfcStartupRequest;
typedef struct CCRCDCNfcStartupExRequest CCRCDCNfcStartupExRequest;
typedef struct CCRCDCNfcStartupResponse CCRCDCNfcStartupResponse;
typedef struct CCRCDCNfcReadStartRequest CCRCDCNfcReadStartRequest;
typedef struct CCRCDCNfcReadStartResponse CCRCDCNfcReadStartResponse;
typedef struct CCRCDCNfcReadRequest CCRCDCNfcReadRequest;
typedef struct CCRCDCNfcReadResponse CCRCDCNfcReadResponse;
typedef struct CCRCDCNfcWriteStartRequest CCRCDCNfcWriteStartRequest;
typedef struct CCRCDCNfcWriteStartResponse CCRCDCNfcWriteStartResponse;
typedef struct CCRCDCNfcResultCheckRequest CCRCDCNfcResultCheckRequest;
typedef struct CCRCDCNfcResultCheckResponse CCRCDCNfcResultCheckResponse;
typedef struct CCRCDCNfcAbortRequest CCRCDCNfcAbortRequest;
typedef struct CCRCDCNfcAbortResponse CCRCDCNfcAbortResponse;
typedef struct CCRCDCNfcShutdownRequest CCRCDCNfcShutdownRequest;
typedef struct CCRCDCNfcShutdownResponse CCRCDCNfcShutdownResponse;
typedef struct CCRCDCNfcFormatRequest CCRCDCNfcFormatRequest;
typedef struct CCRCDCNfcFormatResponse CCRCDCNfcFormatResponse;
typedef struct CCRCDCNfcSetReadOnlyRequest CCRCDCNfcSetReadOnlyRequest;
typedef struct CCRCDCNfcSetReadOnlyResponse CCRCDCNfcSetReadOnlyResponse;
typedef struct CCRCDCNfcIsTagPresentRequest CCRCDCNfcIsTagPresentRequest;
typedef struct CCRCDCNfcIsTagPresentResponse CCRCDCNfcIsTagPresentResponse;
typedef struct CCRCDCNfcPassThroughSendRequest CCRCDCNfcPassThroughSendRequest;
typedef struct CCRCDCNfcPassThroughSendExRequest CCRCDCNfcPassThroughSendExRequest;
typedef struct CCRCDCNfcPassThroughEx2Request CCRCDCNfcPassThroughEx2Request;
typedef struct CCRCDCNfcPassThroughSendReponse CCRCDCNfcPassThroughSendReponse;
typedef struct CCRCDCNfcPassThroughReceiveRequest CCRCDCNfcPassThroughReceiveRequest;
typedef struct CCRCDCNfcPassThroughReceiveReponse CCRCDCNfcPassThroughReceiveReponse;
typedef struct CCRCDCNfcSetModeRequest CCRCDCNfcSetModeRequest;
typedef struct CCRCDCNfcSetModeResponse CCRCDCNfcSetModeResponse;
typedef struct CCRCDCNfcDetectStartRequest CCRCDCNfcDetectStartRequest;
typedef struct CCRCDCNfcDetectStartResponse CCRCDCNfcDetectStartResponse;
typedef struct CCRCDCNfcDetectRequest CCRCDCNfcDetectRequest;
typedef struct CCRCDCNfcDetectResponse CCRCDCNfcDetectResponse;
typedef struct CCRCDCNfcDetectStartMultiRequest CCRCDCNfcDetectStartMultiRequest;
typedef struct CCRCDCNfcDetectStartMultiResponse CCRCDCNfcDetectStartMultiResponse;
typedef struct CCRCDCNfcDetectMultiRequest CCRCDCNfcDetectMultiRequest;
typedef struct CCRCDCNfcDetectMultiTagInfo CCRCDCNfcDetectMultiTagInfo;
typedef struct CCRCDCNfcDetectMultiResponse CCRCDCNfcDetectMultiResponse;
typedef struct CCRCDCNfcPassThroughSend2RequestData CCRCDCNfcPassThroughSend2RequestData;
typedef struct CCRCDCNfcPassThroughSend2Request CCRCDCNfcPassThroughSend2Request;
typedef struct CCRCDCNfcPassThroughSend2Response CCRCDCNfcPassThroughSend2Response;
typedef struct CCRCDCNfcPassThroughReceive2Request CCRCDCNfcPassThroughReceive2Request;
typedef struct CCRCDCNfcPassThroughReceive2ResponseData CCRCDCNfcPassThroughReceive2ResponseData;
typedef struct CCRCDCNfcPassThroughReceive2Response CCRCDCNfcPassThroughReceive2Response;
typedef struct CCRCDCNfcAntennaCheckRequest CCRCDCNfcAntennaCheckRequest;
typedef struct CCRCDCNfcAntennaCheckResponse CCRCDCNfcAntennaCheckResponse;
typedef struct CCRCDCNfcReadT2TRange CCRCDCNfcReadT2TRange;
typedef struct CCRCDCNfcReadT2TStartRequest CCRCDCNfcReadT2TStartRequest;
typedef struct CCRCDCNfcReadT2TStartResponse CCRCDCNfcReadT2TStartResponse;
typedef struct CCRCDCNfcReadT2TRequest CCRCDCNfcReadT2TRequest;
typedef struct CCRCDCNfcReadT2TResponse CCRCDCNfcReadT2TResponse;
typedef struct CCRCDCNfcWriteT2TRange CCRCDCNfcWriteT2TRange;
typedef struct CCRCDCNfcWriteT2TRequest CCRCDCNfcWriteT2TRequest;
typedef struct CCRCDCNfcWriteT2TResponse CCRCDCNfcWriteT2TResponse;

typedef enum
{
   CCR_NFC_COMMAND_STARTUP               = 0x00,
   CCR_NFC_COMMAND_READ_START            = 0x01,
   CCR_NFC_COMMAND_READ                  = 0x02,
   CCR_NFC_COMMAND_WRITE_START           = 0x03,
   CCR_NFC_COMMAND_RESULT_CHECK          = 0x04,
   CCR_NFC_COMMAND_ABORT                 = 0x05,
   CCR_NFC_COMMAND_SHUTDOWN              = 0x06,
   CCR_NFC_COMMAND_FORMAT_START          = 0x07,
   CCR_NFC_COMMAND_SET_READ_ONLY         = 0x08,
   CCR_NFC_COMMAND_IS_TAG_PRESENT        = 0x09,
   CCR_NFC_COMMAND_PASS_THROUGH_SEND     = 0x0A,
   CCR_NFC_COMMAND_PASS_THROUGH_RECEIVE  = 0x0B,
   CCR_NFC_COMMAND_SET_MODE              = 0x0C,
   CCR_NFC_COMMAND_DETECT_START          = 0x0D,
   CCR_NFC_COMMAND_DETECT                = 0x0E,
   CCR_NFC_COMMAND_DETECT_START_MULTI    = 0x0F,
   CCR_NFC_COMMAND_DETECT_MULTI          = 0x10,
   CCR_NFC_COMMAND_PASS_THROUGH_SEND2    = 0x11,
   CCR_NFC_COMMAND_PASS_THROUGH_RECEIVE2 = 0x12,
   CCR_NFC_COMMAND_ANTENNA_CHECK         = 0x13,
   CCR_NFC_COMMAND_READ_T2T_START        = 0x14,
   CCR_NFC_COMMAND_READ_T2T              = 0x15,
   CCR_NFC_COMMAND_WRITE_T2T             = 0x16,
} CCRCDCNfcCommandEnum;

struct WUT_PACKED CCRCDCNfcStartupRequest
{
   //! CCR_NFC_COMMAND_STARTUP
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcStartupRequest, 0x01);

struct WUT_PACKED CCRCDCNfcStartupExRequest
{
   //! CCR_NFC_COMMAND_STARTUP
   CCRCDCNfcCommand command;
   uint8_t powerMode;
};
WUT_CHECK_SIZE(CCRCDCNfcStartupExRequest, 0x02);

struct WUT_PACKED CCRCDCNfcStartupResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcStartupResponse, 0x01);

struct WUT_PACKED CCRCDCNfcReadStartRequest
{
   //! CCR_NFC_COMMAND_READ_START
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t unknown;
};
WUT_CHECK_SIZE(CCRCDCNfcReadStartRequest, 0x12);

struct WUT_PACKED CCRCDCNfcReadStartResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcReadStartResponse, 0x01);

struct WUT_PACKED CCRCDCNfcReadRequest
{
   //! CCR_NFC_COMMAND_READ
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcReadRequest, 0x01);

struct WUT_PACKED CCRCDCNfcReadResponse
{
   uint8_t result;
   uint8_t uid[7];
   uint8_t readOnly;
   uint8_t unknown;
   uint8_t flags;
   uint16_t readSize;
   uint16_t lockedSize;
   uint8_t data[0x241];
};
WUT_CHECK_SIZE(CCRCDCNfcReadResponse, 0x250);

struct WUT_PACKED CCRCDCNfcWriteStartRequest
{
   //! CCR_NFC_COMMAND_WRITE_START
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t unknown0;
   uint8_t unknown1;
   WUT_PADDING_BYTES(2);
   uint8_t data[0x200];
};
WUT_CHECK_SIZE(CCRCDCNfcWriteStartRequest, 0x215);

struct WUT_PACKED CCRCDCNfcWriteStartResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcWriteStartResponse, 0x01);

struct WUT_PACKED CCRCDCNfcResultCheckRequest
{
   //! CCR_NFC_COMMAND_RESULT_CHECK
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcResultCheckRequest, 0x01);

struct WUT_PACKED CCRCDCNfcResultCheckResponse
{
   uint8_t result;
   uint8_t uid[7];
};
WUT_CHECK_SIZE(CCRCDCNfcResultCheckResponse, 0x08);

struct WUT_PACKED CCRCDCNfcAbortRequest
{
   //! CCR_NFC_COMMAND_ABORT
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcAbortRequest, 0x01);

struct WUT_PACKED CCRCDCNfcAbortResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcAbortResponse, 0x01);

struct WUT_PACKED CCRCDCNfcShutdownRequest
{
   //! CCR_NFC_COMMAND_SHUTDOWN
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcShutdownRequest, 0x01);

struct WUT_PACKED CCRCDCNfcShutdownResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcShutdownResponse, 0x01);

struct WUT_PACKED CCRCDCNfcFormatRequest
{
   //! CCR_NFC_COMMAND_FORMAT_START
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t unknown;
};
WUT_CHECK_SIZE(CCRCDCNfcFormatRequest, 0x12);

struct WUT_PACKED CCRCDCNfcFormatResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcFormatResponse, 0x01);

struct WUT_PACKED CCRCDCNfcSetReadOnlyRequest
{
   //! CCR_NFC_COMMAND_SET_READ_ONLY
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t unknown;
   uint8_t readOnly;
};
WUT_CHECK_SIZE(CCRCDCNfcSetReadOnlyRequest, 0x13);

struct WUT_PACKED CCRCDCNfcSetReadOnlyResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcSetReadOnlyResponse, 0x01);

struct WUT_PACKED CCRCDCNfcIsTagPresentRequest
{
   //! CCR_NFC_COMMAND_IS_TAG_PRESENT
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t unknown;
};
WUT_CHECK_SIZE(CCRCDCNfcIsTagPresentRequest, 0x12);

struct WUT_PACKED CCRCDCNfcIsTagPresentResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcIsTagPresentResponse, 0x01);

struct WUT_PACKED CCRCDCNfcPassThroughSendRequest
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_SEND
   CCRCDCNfcCommand command;
   uint8_t isActivationEvent;
   uint16_t discoveryTimeout;
   uint32_t commandTimeout;
   uint16_t commandSize;
   uint16_t responseSize;
   uint8_t commandData[0x200];
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSendRequest, 0x20C);

struct WUT_PACKED CCRCDCNfcPassThroughSendExRequest
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_SEND
   CCRCDCNfcCommand command;
   uint8_t isActivationEvent;
   uint16_t discoveryTimeout;
   uint32_t commandTimeout;
   uint16_t commandSize;
   uint16_t responseSize;
   uint8_t commandData[0x200];
   uint8_t disableCrc;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSendExRequest, 0x20D);

struct WUT_PACKED CCRCDCNfcPassThroughEx2Request
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_SEND
   CCRCDCNfcCommand command;
   uint8_t isActivationEvent;
   uint16_t discoveryTimeout;
   uint32_t commandTimeout;
   uint16_t commandSize;
   uint16_t responseSize;
   uint8_t commandData[0x200];
   uint8_t disableCrc;
   uint8_t technologyMask;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughEx2Request, 0x20E);

struct WUT_PACKED CCRCDCNfcPassThroughSendReponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSendReponse, 0x01);

struct WUT_PACKED CCRCDCNfcPassThroughReceiveRequest
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_RECEIVE
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughReceiveRequest, 0x01);

struct WUT_PACKED CCRCDCNfcPassThroughReceiveReponse
{
   uint8_t result;
   uint16_t responseSize;
   uint8_t data[0x200];
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughReceiveReponse, 0x203);

struct WUT_PACKED CCRCDCNfcSetModeRequest
{
   //! CCR_NFC_COMMAND_SET_MODE
   CCRCDCNfcCommand command;
   uint8_t mode;
};
WUT_CHECK_SIZE(CCRCDCNfcSetModeRequest, 0x02);

struct WUT_PACKED CCRCDCNfcSetModeResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcSetModeResponse, 0x01);

struct WUT_PACKED CCRCDCNfcDetectStartRequest
{
   //! CCR_NFC_COMMAND_DETECT_START
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectStartRequest, 0x03);

struct WUT_PACKED CCRCDCNfcDetectStartResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectStartResponse, 0x01);

struct WUT_PACKED CCRCDCNfcDetectRequest
{
   //! CCR_NFC_COMMAND_DETECT
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectRequest, 0x01);

struct WUT_PACKED CCRCDCNfcDetectResponse
{
   uint8_t result;
   uint8_t uid[7];
   uint8_t readOnly;
   uint8_t hasLockedData;
   uint8_t flags;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectResponse, 0x0B);

struct WUT_PACKED CCRCDCNfcDetectStartMultiRequest
{
   //! CCR_NFC_COMMAND_DETECT_START_MULTI
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectStartMultiRequest, 0x03);

struct WUT_PACKED CCRCDCNfcDetectStartMultiResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectStartMultiResponse, 0x01);

struct WUT_PACKED CCRCDCNfcDetectMultiRequest
{
   //! CCR_NFC_COMMAND_DETECT_MULTI
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcDetectMultiRequest, 0x01);

struct WUT_PACKED CCRCDCNfcDetectMultiTagInfo
{
   uint8_t rfDiscId;
   uint8_t protocol;
   uint8_t tagType;
   uint8_t uidSize;
   uint8_t uid[10];
};
WUT_CHECK_SIZE(CCRCDCNfcDetectMultiTagInfo, 0x0E);

struct WUT_PACKED CCRCDCNfcDetectMultiResponse
{
   uint8_t result;
   uint8_t numTags;
   CCRCDCNfcDetectMultiTagInfo tags[3];
   WUT_PADDING_BYTES(0x1C);
};
WUT_CHECK_SIZE(CCRCDCNfcDetectMultiResponse, 0x48);

struct WUT_PACKED CCRCDCNfcPassThroughSend2RequestData
{
   uint32_t timeout;
   uint16_t commandSize;
   uint16_t responseSize;
   uint8_t commandData[0x200];
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSend2RequestData, 0x208);

struct WUT_PACKED CCRCDCNfcPassThroughSend2Request
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_SEND2
   CCRCDCNfcCommand command;
   CCRCDCNfcPassThroughSend2RequestData command1;
   CCRCDCNfcPassThroughSend2RequestData command2;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSend2Request, 0x411);

struct WUT_PACKED CCRCDCNfcPassThroughSend2Response
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughSend2Response, 0x01);

struct WUT_PACKED CCRCDCNfcPassThroughReceive2Request
{
   //! CCR_NFC_COMMAND_PASS_THROUGH_RECEIVE2
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughReceive2Request, 0x01);

struct WUT_PACKED CCRCDCNfcPassThroughReceive2ResponseData
{
   uint8_t timedOut;
   uint16_t responseSize;
   uint8_t responseData[0x200];
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughReceive2ResponseData, 0x203);

struct WUT_PACKED CCRCDCNfcPassThroughReceive2Response
{
   uint8_t result;
   CCRCDCNfcPassThroughReceive2ResponseData response1;
   CCRCDCNfcPassThroughReceive2ResponseData response2;
};
WUT_CHECK_SIZE(CCRCDCNfcPassThroughReceive2Response, 0x407);

struct WUT_PACKED CCRCDCNfcAntennaCheckRequest
{
   //! CCR_NFC_COMMAND_ANTENNA_CHECK
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcAntennaCheckRequest, 0x01);

struct WUT_PACKED CCRCDCNfcAntennaCheckResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcAntennaCheckResponse, 0x01);

struct WUT_PACKED CCRCDCNfcReadT2TRange
{
   uint8_t start;
   uint8_t end;
};
WUT_CHECK_SIZE(CCRCDCNfcReadT2TRange, 0x02);

struct WUT_PACKED CCRCDCNfcReadT2TStartRequest
{
   //! CCR_NFC_COMMAND_READ_T2T_START
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t expectedVersion[8];
   uint32_t commandTimeout;
   uint8_t numRanges;
   CCRCDCNfcReadT2TRange ranges[4];
   uint8_t pwdAuth;
   WUT_PADDING_BYTES(0x19);
};
WUT_CHECK_SIZE(CCRCDCNfcReadT2TStartRequest, 0x40);

struct WUT_PACKED CCRCDCNfcReadT2TStartResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcReadT2TStartResponse, 0x01);

struct WUT_PACKED CCRCDCNfcReadT2TRequest
{
   //! CCR_NFC_COMMAND_READ_T2T
   CCRCDCNfcCommand command;
};
WUT_CHECK_SIZE(CCRCDCNfcReadT2TRequest, 0x01);

struct WUT_PACKED CCRCDCNfcReadT2TResponse
{
   uint8_t result;
   uint8_t rfDiscId;
   uint8_t protocol;
   uint8_t discoveryType;
   uint8_t uidSize;
   uint8_t uid[10];
   uint8_t version[8];
   WUT_PADDING_BYTES(0x10);
   uint8_t data[0x3A9];
   uint8_t signature[0x20];
};
WUT_CHECK_SIZE(CCRCDCNfcReadT2TResponse, 0x3F0);

struct WUT_PACKED CCRCDCNfcWriteT2TRange
{
   uint8_t start;
   uint8_t end;
   uint8_t data[0xF0];
};
WUT_CHECK_SIZE(CCRCDCNfcWriteT2TRange, 0xF2);

struct WUT_PACKED CCRCDCNfcWriteT2TRequest
{
   //! CCR_NFC_COMMAND_WRITE_T2T
   CCRCDCNfcCommand command;
   uint16_t discoveryTimeout;
   uint8_t uid[7];
   uint8_t uidMask[7];
   uint8_t version[8];
   uint32_t commandTimeout;
   uint8_t numRanges;
   CCRCDCNfcWriteT2TRange ranges[4];
   uint8_t activationOffset;
   uint8_t activationData0[4];
   uint8_t activationData1[4];
   uint8_t pwdAuth;
   uint8_t activationData;
   WUT_PADDING_BYTES(0xF);
};
WUT_CHECK_SIZE(CCRCDCNfcWriteT2TRequest, 0x400);

struct WUT_PACKED CCRCDCNfcWriteT2TResponse
{
   uint8_t result;
};
WUT_CHECK_SIZE(CCRCDCNfcWriteT2TResponse, 0x01);

int32_t
CCRCDCPerNfcControl(CCRCDCDestination dest,
                    void *request,
                    uint32_t requestSize,
                    void *response,
                    uint32_t responseSize);

#ifdef __cplusplus
}
#endif

/** @} */
