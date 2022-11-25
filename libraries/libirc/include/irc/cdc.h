#pragma once
#include <nsysccr/irda.h>

/**
 * \defgroup irc_cdc
 * \ingroup irc
 * Low-Level InfraRed Connection
 * 
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

int32_t
__CCRCDCIRCConnect(int32_t drcIndex,
                   uint8_t *result,
                   uint16_t timeout,
                   CCRCDCIrdaBitrate bitrate,
                   uint32_t receiveSize,
                   uint8_t targetId,
                   CCRCDCIrdaConnectionType type);

int32_t
__CCRCDCIRCSend(int32_t drcIndex,
                uint8_t *result,
                uint32_t size,
                uint32_t receiveSize,
                void *data);

int32_t
__CCRCDCIRCReceive(int32_t drcIndex,
                   uint8_t *result,
                   uint16_t *receivedSize,
                   void *data);

int32_t
__CCRCDCIRCDisconnect(int32_t drcIndex,
                      uint8_t *result);

#ifdef __cplusplus
}
#endif

/** @} */
