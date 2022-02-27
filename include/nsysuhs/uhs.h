#pragma once
#include <wut.h>
#include <stdbool.h> 

#ifdef __cplusplus
extern "C" {
#endif

#include "uhs_usbspec.h"

typedef struct UhsInterfaceFilter UhsInterfaceFilter;
typedef struct UhsInterfaceProfile UhsInterfaceProfile;
typedef struct UhsEndpointDescriptor UhsEndpointDescriptor;
typedef struct UhsHandle UhsHandle;
typedef struct UhsConfig UhsConfig;

/* Determines which interface parameters to check */
#define MATCH_ANY               0x000
#define MATCH_DEV_VID           0x001
#define MATCH_DEV_PID           0x002
#define MATCH_DEV_CLASS         0x010
#define MATCH_DEV_SUBCLASS      0x020
#define MATCH_DEV_PROTOCOL      0x040
#define MATCH_IF_CLASS          0x080
#define MATCH_IF_SUBCLASS       0x100
#define MATCH_IF_PROTOCOL       0x200

typedef enum UHSStatus
{
   UHS_STATUS_OK                    = 0,   
   UHS_STATUS_HANDLE_INVALID_ARGS   = 0xffdefffd,   
   UHS_STATUS_HANDLE_INVALID_STATE  = 0xffdefffc,   
} UHSStatus;

typedef enum UHSHandleState
{
   UHS_HANDLE_STATE_INIT            =  0x00,
   UHS_HANDLE_STATE_OPENING         =  0x01,
   UHS_HANDLE_STATE_OPENED          =  0x02,
   UHS_HANDLE_STATE_CLOSING         =  0x03,
   UHS_HANDLE_STATE_CLOSED          =  0x04,
   UHS_HANDLE_STATE_ERROR           =  0x05,
} UHSHandleState;

#define UHS_CONFIG_BUFFER_SIZE 0x137f

struct WUT_PACKED UhsConfig
{
    uint32_t controller_num;
    /* buffer aligned by 0x40 with a size of UHS_CONFIG_BUFFER_SIZE */
    void* buffer;
    uint32_t buffer_size;
};
WUT_CHECK_OFFSET(UhsConfig, 0x00, controller_num);
WUT_CHECK_OFFSET(UhsConfig, 0x04, buffer);
WUT_CHECK_OFFSET(UhsConfig, 0x08, buffer_size);
WUT_CHECK_SIZE(UhsConfig, 0x0C);

struct WUT_PACKED UhsHandle
{
    UHSHandleState state;
    void* ipc_buffer;
    WUT_UNKNOWN_BYTES(4);       /* always 0xFFFFFFFF after init */
    uint32_t handle;
    UhsConfig * config;
    WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_OFFSET(UhsHandle, 0x00, state);
WUT_CHECK_OFFSET(UhsHandle, 0x04, ipc_buffer);
WUT_CHECK_OFFSET(UhsHandle, 0x0C, handle);
WUT_CHECK_OFFSET(UhsHandle, 0x10, config);
WUT_CHECK_SIZE(UhsHandle, 0x18);

/* Endpoint transfer directions */
#define ENDPOINT_TRANSFER_OUT       1
#define ENDPOINT_TRANSFER_IN        2

/* Special timeout values */
#define TIMEOUT_NONE                -1
 
/* Interface filter */
struct WUT_PACKED UhsInterfaceFilter
{
    uint16_t match_params;      /* Bitmask of above flags */
    uint16_t vid;               /* Vendor ID */
    uint16_t pid;               /* Product ID */
    WUT_UNKNOWN_BYTES(4);
    uint8_t dev_class;          /* Device class */
    uint8_t dev_subclass;       /* Device subclass */
    uint8_t dev_protocol;       /* Device protocol */
    uint8_t if_class;           /* Interface class */
    uint8_t if_subclass;        /* Interface subclass */
    uint8_t if_protocol;        /* Interface protocol */
};
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x00, match_params);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x02, vid);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x04, pid);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0A, dev_class);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0B, dev_subclass);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0C, dev_protocol);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0D, if_class);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0E, if_subclass);
WUT_CHECK_OFFSET(UhsInterfaceFilter, 0x0F, if_protocol);
WUT_CHECK_SIZE(UhsInterfaceFilter, 0x10);


/* Interface profile */
struct WUT_PACKED UhsEndpointDescriptor
{
    uint8_t 	bLength;
    uint8_t 	bDescriptorType;
    uint8_t 	bEndpointAddress;
    uint8_t 	bmAttributes;
    uint16_t 	wMaxPacketSize;
    uint8_t 	bInterval;
    WUT_UNKNOWN_BYTES(0x2);
};
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x00, bLength);
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x01, bDescriptorType);
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x02, bEndpointAddress);
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x03, bmAttributes);
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x04, wMaxPacketSize);
WUT_CHECK_OFFSET(UhsEndpointDescriptor, 0x06, bInterval);
WUT_CHECK_SIZE(UhsEndpointDescriptor, 0x09);

/* Interface profile */
struct WUT_PACKED UhsInterfaceProfile
{
    uint32_t if_handle;
    WUT_UNKNOWN_BYTES(0x24);
    UhsDeviceDescriptor dev_desc;
    UhsConfigDescriptor cfg_desc;
    UhsInterfaceDescriptor if_desc;
    UhsEndpointDescriptor in_endpoints[16];
    UhsEndpointDescriptor out_endpoints[16];
};
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0x00, if_handle);
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0x28, dev_desc);
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0x3A, cfg_desc);
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0x43, if_desc);
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0x4c, in_endpoints);
WUT_CHECK_OFFSET(UhsInterfaceProfile, 0xdc, out_endpoints);
WUT_CHECK_SIZE(UhsInterfaceProfile, 0x16C);

typedef enum UHSAdminDevType
{
   UHS_ADMIN_DEV_RESET        =  0x01,
   UHS_ADMIN_DEV_FREEZE       =  0x02,
   UHS_ADMIN_DEV_SUSPEND      =  0x03,
   UHS_ADMIN_DEV_RESUME       =  0x04,
   UHS_ADMIN_DEV_DESTROY      =  0x05,
} UHSAdminDevType;

typedef enum UHSAdminEpType
{
   UHS_ADMIN_EP_ENABLE        =  0x01,
   UHS_ADMIN_EP_DISABLE       =  0x02,
   UHS_ADMIN_EP_CANCEL        =  0x03,
   UHS_ADMIN_EP_CANCEL_RESET  =  0x04,
} UHSAdminEpType;

/* Open a specific controller under /dev/uhs */
UHSStatus
UhsClientOpen(UhsHandle* handle,
              UhsConfig* config);

UHSStatus
UhsClientClose(UhsHandle* handle);

typedef void(*UHSDrvRegCallback)(void * context, UhsInterfaceProfile * profile);

/* Register a USB class driver */
UHSStatus  
UhsClassDrvReg(UhsHandle* handle, 
               UhsInterfaceFilter *filter, 
               void *context, 
               UHSDrvRegCallback callback);

UHSStatus  
UhsClassDrvUnReg(UhsHandle* handle, 
                 uint32_t drv_handle);

UHSStatus
UhsGetFullConfigDescriptor(UhsHandle* handle,
                           uint32_t if_handle,
                           void* data,
                           uint32_t size);

UHSStatus
UhsGetDescriptorString(UhsHandle* handle,
                       uint32_t if_handle,
                       uint8_t string_index,
                       BOOL as_unicode,
                       void* data,
                       uint32_t size);

/* Determine which USB device interfaces are plugged in and available */
UHSStatus  
UhsQueryInterfaces(UhsHandle* handle, 
                   UhsInterfaceFilter *filter, 
                   UhsInterfaceProfile *profiles, 
                   int32_t max_profiles);


typedef void(*UhsAcquireInterfaceCallback)(void * context, int32_t arg1, int32_t arg2);

/* Acquire a USB device interface for use */
UHSStatus  
UhsAcquireInterface(UhsHandle* handle, 
                    uint32_t if_handle, 
                    void * context, 
                    UhsAcquireInterfaceCallback callback);

/* Release a currently-held USB device interface */
UHSStatus  
UhsReleaseInterface(UhsHandle* handle, 
                    uint32_t if_handle, 
                    bool no_reacquire);

/* Administer a USB device */
UHSStatus  
UhsAdministerDevice(UhsHandle* handle,
                    uint32_t if_handle,
                    UHSAdminDevType type,
                    int32_t arg3);

UHSStatus
UhsAdministerEndpoint(UhsHandle* handle,
                      uint32_t if_handle,
                      UHSAdminEpType type,
                      uint32_t endpointMask,
                      uint32_t max_pending_requests,
                      uint32_t max_request_size);

UHSStatus
UhsClearEndpointHalt(UhsHandle* handle,
                     uint32_t if_handle,
                     uint32_t endpoint,
                     int32_t direction);

/* Submit a control request to endpoint 0 */
UHSStatus  
UhsSubmitControlRequest(UhsHandle* handle, 
                        uint32_t if_handle, 
                        void *buffer, 
                        uint8_t bRequest, 
                        uint8_t bmRequestType, 
                        uint16_t wValue, 
                        uint16_t wIndex, 
                        uint16_t wLength, 
                        int32_t timeout);

/* Submit a bulk request to an endpoint */
UHSStatus  
UhsSubmitBulkRequest(UhsHandle* handle, 
                     uint32_t if_handle, 
                     uint8_t endpoint, 
                     int32_t direction, 
                     void *buffer, 
                     int32_t length, 
                     int32_t timeout);

/* Submit an interrupt request to an endpoint */
UHSStatus  
UhsSubmitInterruptRequest(UhsHandle* handle, 
                          uint32_t if_handle, 
                          uint8_t endpoint, 
                          int32_t direction, 
                          void *buffer, 
                          int32_t length, 
                          int32_t timeout);

static inline uint32_t UHSEndpointDirIsIn(UhsEndpointDescriptor * endpoint_descriptor){
    return ((endpoint_descriptor->bEndpointAddress & 0x80) == 0x80);
}

static inline uint32_t UHSEndpointGetNum(UhsEndpointDescriptor * endpoint_descriptor){
    return (endpoint_descriptor->bEndpointAddress & 0x0F);
}

static inline uint32_t UHSEndpointGetMask(UhsEndpointDescriptor * endpoint_descriptor){
    uint32_t endpoint_mask;

    if (UHSEndpointDirIsIn(endpoint_descriptor)) {
        endpoint_mask = (1 << (UHSEndpointGetNum(endpoint_descriptor) + 16));
    } else {
        endpoint_mask = (1 << UHSEndpointGetNum(endpoint_descriptor));
    }
    return endpoint_mask;
}

#ifdef __cplusplus
}
#endif

/** @} */