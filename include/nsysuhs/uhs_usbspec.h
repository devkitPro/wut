#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

/* USB class codes */
#define USBCLASS_DEVICE  0x00
#define USBCLASS_AUDIO   0x01
#define USBCLASS_HID     0x03
#define USBCLASS_STORAGE 0x08

typedef struct UhsDeviceDescriptor UhsDeviceDescriptor;
typedef struct UhsConfigDescriptor UhsConfigDescriptor;
typedef struct UhsInterfaceDescriptor UhsInterfaceDescriptor;
typedef struct UhsSetupPacket UhsSetupPacket;

/* USB device descriptor */
struct WUT_PACKED UhsDeviceDescriptor
{
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t bcdUsb;
   uint8_t bDeviceClass;
   uint8_t bDeviceSubclass;
   uint8_t bDeviceProtocol;
   uint8_t bMaxPacketSize;
   uint16_t idVendor;
   uint16_t idProduct;
   uint16_t bcdDevice;
   uint8_t iManufacturer;
   uint8_t iProduct;
   uint8_t iSerialNumber;
   uint8_t bNumConfigurations;
};
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x00, bLength);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x01, bDescriptorType);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x02, bcdUsb);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x04, bDeviceClass);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x05, bDeviceSubclass);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x06, bDeviceProtocol);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x07, bMaxPacketSize);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x08, idVendor);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x0A, idProduct);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x0C, bcdDevice);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x0E, iManufacturer);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x0F, iProduct);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x10, iSerialNumber);
WUT_CHECK_OFFSET(UhsDeviceDescriptor, 0x11, bNumConfigurations);
WUT_CHECK_SIZE(UhsDeviceDescriptor, 0x12);

/* USB configuration descriptor */
struct WUT_PACKED UhsConfigDescriptor
{
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t wTotalLength;
   uint8_t bNumInterfaces;
   uint8_t bConfigurationValue;
   uint8_t iConfiguration;
   uint8_t bmAttributes;
   uint8_t bMaxPower;
};
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x00, bLength);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x01, bDescriptorType);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x02, wTotalLength);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x04, bNumInterfaces);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x05, bConfigurationValue);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x06, iConfiguration);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x07, bmAttributes);
WUT_CHECK_OFFSET(UhsConfigDescriptor, 0x08, bMaxPower);
WUT_CHECK_SIZE(UhsConfigDescriptor, 0x09);

/* USB interface descriptor */
struct WUT_PACKED UhsInterfaceDescriptor
{
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint8_t bInterfaceNumber;
   uint8_t bAlternateSetting;
   uint8_t bNumEndpoints;
   uint8_t bInterfaceClass;
   uint8_t bInterfaceSubClass;
   uint8_t bInterfaceProtocol;
   uint8_t iInterface;
};
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x00, bLength);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x01, bDescriptorType);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x02, bInterfaceNumber);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x03, bAlternateSetting);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x04, bNumEndpoints);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x05, bInterfaceClass);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x06, bInterfaceSubClass);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x07, bInterfaceProtocol);
WUT_CHECK_OFFSET(UhsInterfaceDescriptor, 0x08, iInterface);
WUT_CHECK_SIZE(UhsInterfaceDescriptor, 0x09);

/* USB setup packet */
struct WUT_PACKED UhsSetupPacket
{
   uint8_t bmRequestType;
   uint8_t bRequest;
   uint16_t wValue;
   uint16_t wIndex;
   uint16_t wLength;
};
WUT_CHECK_OFFSET(UhsSetupPacket, 0x00, bmRequestType);
WUT_CHECK_OFFSET(UhsSetupPacket, 0x01, bRequest);
WUT_CHECK_OFFSET(UhsSetupPacket, 0x02, wValue);
WUT_CHECK_OFFSET(UhsSetupPacket, 0x04, wIndex);
WUT_CHECK_OFFSET(UhsSetupPacket, 0x06, wLength);
WUT_CHECK_SIZE(UhsSetupPacket, 0x08);

#ifdef __cplusplus
}
#endif