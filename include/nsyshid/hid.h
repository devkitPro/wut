#pragma once
#include <wut.h>

/**
 * \defgroup nsyshid_hid HID API
 * \ingroup nsyshid
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct HIDClient HIDClient;
typedef struct HIDDevice HIDDevice;

typedef enum HIDAttachEvent
{
   HID_DEVICE_DETACH = 0,
   HID_DEVICE_ATTACH = 1,
} HIDAttachEvent;

typedef int32_t
(*HIDAttachCallback)(HIDClient *client,
                     HIDDevice *device,
                     HIDAttachEvent attach);

typedef void
(*HIDCallback)(uint32_t handle,
               int32_t error,
               uint8_t *buffer,
               uint32_t bytesTransferred,
               void *userContext);

struct HIDDevice
{
   uint32_t handle;
   uint32_t physicalDeviceInst;
   uint16_t vid;
   uint16_t pid;
   uint8_t interfaceIndex;
   uint8_t subClass;
   uint8_t protocol;
   WUT_PADDING_BYTES(1);
   uint16_t maxPacketSizeRx;
   uint16_t maxPacketSizeTx;
};
WUT_CHECK_OFFSET(HIDDevice, 0x00, handle);
WUT_CHECK_OFFSET(HIDDevice, 0x04, physicalDeviceInst);
WUT_CHECK_OFFSET(HIDDevice, 0x08, vid);
WUT_CHECK_OFFSET(HIDDevice, 0x0A, pid);
WUT_CHECK_OFFSET(HIDDevice, 0x0C, interfaceIndex);
WUT_CHECK_OFFSET(HIDDevice, 0x0D, subClass);
WUT_CHECK_OFFSET(HIDDevice, 0x0E, protocol);
WUT_CHECK_OFFSET(HIDDevice, 0x10, maxPacketSizeRx);
WUT_CHECK_OFFSET(HIDDevice, 0x12, maxPacketSizeTx);
WUT_CHECK_SIZE(HIDDevice, 0x14);

struct HIDClient
{
   HIDClient *next;
   HIDAttachCallback attachCallback;
};
WUT_CHECK_OFFSET(HIDClient, 0x00, next);
WUT_CHECK_OFFSET(HIDClient, 0x04, attachCallback);
WUT_CHECK_SIZE(HIDClient, 0x08);


int32_t
HIDSetup();

int32_t
HIDTeardown();

int32_t
HIDAddClient(HIDClient *client,
             HIDAttachCallback attachCallback);

int32_t
HIDDelClient(HIDClient *client);

int32_t
HIDGetDescriptor(uint32_t handle,
                 uint8_t descriptorType,
                 uint8_t descriptorIndex,
                 uint16_t languageId,
                 uint8_t *buffer,
                 uint32_t bufferLength,
                 HIDCallback callback,
                 void *userContext);

int32_t
HIDSetDescriptor(uint32_t handle,
                 uint8_t descriptorType,
                 uint8_t descriptorIndex,
                 uint16_t languageId,
                 uint8_t *buffer,
                 uint32_t bufferLength,
                 HIDCallback callback,
                 void *userContext);

int32_t
HIDGetReport(uint32_t handle,
             uint8_t reportType,
             uint8_t reportId,
             uint8_t *buffer,
             uint32_t bufferLength,
             HIDCallback callback,
             void *userContext);

int32_t
HIDSetReport(uint32_t handle,
             uint8_t reportType,
             uint8_t reportId,
             uint8_t *buffer,
             uint32_t bufferLength,
             HIDCallback callback,
             void *userContext);

int32_t
HIDSetIdle(uint32_t handle,
           uint8_t interfaceIndex,
           uint8_t duration,
           HIDCallback callback,
           void *userContext);

int32_t
HIDSetProtocol(uint32_t handle,
               uint8_t interfaceIndex,
               uint8_t protocol,
               HIDCallback callback,
               void *userContext);

int32_t
HIDGetProtocol(uint32_t handle,
               uint8_t interfaceIndex,
               uint8_t *protocol,
               HIDCallback callback,
               void *userContext);

int32_t
HIDRead(uint32_t handle,
        uint8_t *buffer,
        uint32_t bufferLength,
        HIDCallback callback,
        void *userContext);

int32_t
HIDWrite(uint32_t handle,
         uint8_t *buffer,
         uint32_t bufferLength,
         HIDCallback hc,
         void *userContext);

#ifdef __cplusplus
}
#endif

/** @} */
