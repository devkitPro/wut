#pragma once
#include <wut.h>
#include <coreinit/ios.h>

/**
 * \defgroup coreinit_im IM
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IMRequest IMRequest;
typedef struct IMHomeButtonParams IMHomeButtonParams;
typedef struct IMParameters IMParameters;
typedef struct IMDeviceStateEx IMDeviceStateEx;
typedef uint32_t IMEventMask;
typedef struct IMRequestArgDeviceState IMRequestArgDeviceState;
typedef struct IMRequestArgEventNotify IMRequestArgEventNotify;
typedef struct IMRequestArgParameter IMRequestArgParameter;
typedef struct IMRequestArgHomeButton IMRequestArgHomeButton;
typedef struct IMRequestArgTimer IMRequestArgTimer;

typedef enum IMPadType
{
   IM_PAD_TYPE_NONE                 = 0,
   IM_PAD_TYPE_WII_REMOTE           = 1,
   IM_PAD_TYPE_WIIU_PRO_CONTROLLER  = 2,
   IM_PAD_TYPE_WII_REMOTE_EXTENSION = 3,
   IM_PAD_TYPE_WIIU_GAMEPAD         = 4,
} IMPadType;

typedef enum IMDeviceState
{
   IM_DEVICE_STATE_CLEAR    = 0,
   IM_DEVICE_STATE_INACTIVE = 1,
   IM_DEVICE_STATE_ACTIVE   = 2,
   IM_DEVICE_STATE_HOME     = 3,
   IM_DEVICE_STATE_POWER    = 4,
   IM_DEVICE_STATE_SYNC     = 5,
} IMDeviceState;

typedef enum IMRequestID
{
   IM_REQUEST_ID_SET_SYSTEM_POLICY         = 0,
   IM_REQUEST_ID_SET_NV_PARAMETER          = 1,
   IM_REQUEST_ID_SET_PARAMETER             = 2,
   IM_REQUEST_ID_GET_PARAMETER             = 3,
   IM_REQUEST_ID_SET_DEVICE_STATE          = 4,
   IM_REQUEST_ID_GET_EVENT_NOTIFY          = 5,
   IM_REQUEST_ID_CANCEL_GET_EVENT_NOTIFY   = 6,
   IM_REQUEST_ID_GET_HOME_BUTTON_PARAMS    = 7,
   IM_REQUEST_ID_GET_TIMER_REMAINING       = 8,
   IM_REQUEST_ID_GET_NV_PARAMETER          = 9,
   IM_REQUEST_ID_SET_TIMER_ELAPSED_SECONDS = 10,
   IM_REQUEST_ID_SET_HOME_BUTTON_PARAMS    = 11,
} IMRequestID;

struct IMHomeButtonParams
{
   //! The controller type which pressed the home button
   IMPadType type;
   //! The controller index which pressed the home button
   int32_t index;
};
WUT_CHECK_OFFSET(IMHomeButtonParams, 0x0, type);
WUT_CHECK_OFFSET(IMHomeButtonParams, 0x4, index);
WUT_CHECK_SIZE(IMHomeButtonParams, 0x8);

struct IMParameters
{
   uint32_t resetEnabled;
   uint32_t dimEnabled;
   uint32_t dimPeriod;
   uint32_t apdEnabled;
   uint32_t apdPeriod;
};
WUT_CHECK_OFFSET(IMParameters, 0x00, resetEnabled);
WUT_CHECK_OFFSET(IMParameters, 0x04, dimEnabled);
WUT_CHECK_OFFSET(IMParameters, 0x08, dimPeriod);
WUT_CHECK_OFFSET(IMParameters, 0x0C, apdEnabled);
WUT_CHECK_OFFSET(IMParameters, 0x10, apdPeriod);
WUT_CHECK_SIZE(IMParameters, 0x14);

struct IMDeviceStateEx
{
   IMDeviceState state;
   IMHomeButtonParams params;
};
WUT_CHECK_OFFSET(IMDeviceStateEx, 0x0, state);
WUT_CHECK_OFFSET(IMDeviceStateEx, 0x4, params);
WUT_CHECK_SIZE(IMDeviceStateEx, 0xC);

typedef enum IMParameter
{
   IM_PARAMETER_INACTIVE_SECONDS = 0,
   IM_PARAMETER_DIM_ENABLED      = 1,
   IM_PARAMETER_DIM_PERIOD       = 2,
   IM_PARAMETER_APD_ENABLED      = 3,
   IM_PARAMETER_APD_PERIOD       = 4,
   IM_PARAMETER_RESET_ENABLE     = 5,
   IM_PARAMETER_RESET_SECONDS    = 6,
   IM_PARAMETER_POWER_OFF_ENABLE = 7,
   IM_PARAMETER_APD_OCCURED      = 8,
   IM_PARAMETER_DIM_ENABLE_TV    = 9,
   IM_PARAMETER_DIM_ENABLE_DRC   = 10,
   IM_PARAMETER_MAX              = 11,
} IMParameter;

typedef enum IMTimer
{
   IM_TIMER_DIM = 0,
   IM_TIMER_APD = 1,
} IMTimer;

typedef enum IMEvent
{
   IM_EVENT_ACTIVE    = 1u << 0u,
   IM_EVENT_INACTIVE  = 1u << 1u,
   IM_EVENT_DIM       = 1u << 2u,
   IM_EVENT_UNDIM     = 1u << 3u,
   //! Automatic power down
   IM_EVENT_APD       = 1u << 4u,
   //! Controller power button was pressed
   IM_EVENT_POWER     = 1u << 5u,
   //! Home button was pressed
   IM_EVENT_HOME      = 1u << 6u,
   //! Console sync button was pressed
   IM_EVENT_SYNC      = 1u << 7u,
   IM_EVENT_RESET     = 1u << 8u,
   //! Event notify was cancelled
   IM_EVENT_CANCELLED = 1u << 31u,
} IMEvent;

struct WUT_PACKED IMRequestArgDeviceState
{
   IMDeviceState state;
   uint32_t unknown1;
   uint32_t unknown2;
};
WUT_CHECK_OFFSET(IMRequestArgDeviceState, 0x00, state);
WUT_CHECK_OFFSET(IMRequestArgDeviceState, 0x04, unknown1);
WUT_CHECK_OFFSET(IMRequestArgDeviceState, 0x08, unknown2);
WUT_CHECK_SIZE(IMRequestArgDeviceState, 0x0C);

struct WUT_PACKED IMRequestArgEventNotify
{
   IMEventMask event;
};
WUT_CHECK_OFFSET(IMRequestArgEventNotify, 0x00, event);
WUT_CHECK_SIZE(IMRequestArgEventNotify, 0x04);

struct WUT_PACKED IMRequestArgParameter
{
   IMParameter parameter;
   uint32_t value;
};
WUT_CHECK_OFFSET(IMRequestArgParameter, 0x00, parameter);
WUT_CHECK_OFFSET(IMRequestArgParameter, 0x04, value);
WUT_CHECK_SIZE(IMRequestArgParameter, 0x08);

struct WUT_PACKED IMRequestArgHomeButton
{
   IMHomeButtonParams params;
};
WUT_CHECK_OFFSET(IMRequestArgHomeButton, 0x00, params);
WUT_CHECK_SIZE(IMRequestArgHomeButton, 0x08);

struct WUT_PACKED IMRequestArgTimer
{
   IMTimer timer;
   uint32_t value;
};
WUT_CHECK_OFFSET(IMRequestArgTimer, 0x00, timer);
WUT_CHECK_OFFSET(IMRequestArgTimer, 0x04, value);
WUT_CHECK_SIZE(IMRequestArgTimer, 0x08);

struct WUT_PACKED IMRequest
{
   union
   {
      IMRequestArgDeviceState deviceState;
      IMRequestArgEventNotify eventNotify;
      IMRequestArgParameter parameter;
      IMRequestArgHomeButton homeButton;
      IMRequestArgTimer timer;
      uint8_t padding[0x80];
   } arg;
   IOSVec ioctlVecs[2];
   IOSHandle handle;
   IMRequestID request;
   IOSAsyncCallbackFn asyncCallback;
   void *asyncCallbackContext;
   void *copySrc;
   void *copyDst;
   uint32_t copySize;
};
WUT_CHECK_OFFSET(IMRequest, 0x00, arg);
WUT_CHECK_OFFSET(IMRequest, 0x80, ioctlVecs);
WUT_CHECK_OFFSET(IMRequest, 0x98, handle);
WUT_CHECK_OFFSET(IMRequest, 0x9C, request);
WUT_CHECK_OFFSET(IMRequest, 0xA0, asyncCallback);
WUT_CHECK_OFFSET(IMRequest, 0xA4, asyncCallbackContext);
WUT_CHECK_OFFSET(IMRequest, 0xA8, copySrc);
WUT_CHECK_OFFSET(IMRequest, 0xAC, copyDst);
WUT_CHECK_OFFSET(IMRequest, 0xB0, copySize);
WUT_CHECK_SIZE(IMRequest, 0xB4);

IOSHandle
IM_Open(void);

IOSError
IM_Close(IOSHandle handle);

/* NOTE: for all functions, if asyncCallback == NULL, the call becomes synchronous */

IOSError
IM_GetHomeButtonParams(IOSHandle handle,
                       IMRequest *request,
                       IMHomeButtonParams *output,
                       IOSAsyncCallbackFn asyncCallback,
                       void *asyncCallbackContext);

IOSError
IM_GetParameter(IOSHandle handle,
                IMRequest *request,
                IMParameter parameter,
                uint32_t *output,
                IOSAsyncCallbackFn asyncCallback,
                void *asyncCallbackContext);

IOSError
IM_GetParameters(IMParameters *parameters);

IOSError
IM_GetNvParameter(IOSHandle handle,
                  IMRequest *request,
                  IMParameter parameter,
                  uint32_t *output,
                  IOSAsyncCallbackFn asyncCallback,
                  void *asyncCallbackContext);

IOSError
IM_GetNvParameterWithoutHandleAndItb(IMParameter parameter,
                                     uint32_t *outValue);

IOSError
IM_GetRuntimeParameter(IMParameter parameter,
                       uint32_t *outValue);

IOSError
IM_GetTimerRemaining(IOSHandle handle,
                     IMRequest *request,
                     IMTimer timer,
                     uint32_t *output,
                     IOSAsyncCallbackFn asyncCallback,
                     void *asyncCallbackContext);

IOSError
IM_GetTimerRemainingSeconds(IMTimer timer,
                            uint32_t *outSeconds);

IOSError
IM_SetParameter(IOSHandle handle,
                IMRequest *request,
                IMParameter parameter,
                uint32_t value,
                IOSAsyncCallbackFn asyncCallback,
                void *asyncCallbackContext);

IOSError
IM_SetRuntimeParameter(IMParameter parameter,
                       uint32_t value);

IOSError
IM_GetEventNotify(IOSHandle handle,
                  IMRequest *request,
                  IMEventMask *event,
                  IOSAsyncCallbackFn asyncCallback,
                  void *asyncCallbackContext);

IOSError
IM_CancelGetEventNotify(IOSHandle handle,
                        IMRequest *request,
                        IOSAsyncCallbackFn asyncCallback,
                        void *asyncCallbackContext);

IOSError
IM_SetDeviceState(IOSHandle handle,
                  IMRequest *request,
                  IMDeviceState state,
                  IOSAsyncCallbackFn asyncCallback,
                  void *asyncCallbackContext);

IOSError
IM_SetDeviceStateEx(IOSHandle handle,
                    IMRequest *request,
                    IMDeviceStateEx *state,
                    IOSAsyncCallbackFn asyncCallback,
                    void *asyncCallbackContext);

IOSError
IM_GetNvParameterWithoutHandleAndItb(IMParameter parameter,
                                     uint32_t *output);

IOSError
IM_SetNvParameterWithoutHandleAndItb(IMParameter parameter,
                                     uint32_t value);

IOSError
IM_SetHomeButtonParams(IOSHandle handle,
                       IMRequest *request,
                       IMHomeButtonParams *params,
                       IOSAsyncCallbackFn *asyncCallback,
                       void *asyncCallbackContext);

IOSError
IM_SetNvParameter(IOSHandle handle,
                  IMRequest *request,
                  IMParameter parameter,
                  uint32_t value,
                  IOSAsyncCallbackFn *asyncCallback,
                  void *asyncCallbackContext);

IOSError
IM_SetSystemPolicy(IOSHandle handle,
                   IMRequest *request,
                   IOSAsyncCallbackFn *asyncCallback,
                   void *asyncCallbackContext);

IOSError
IM_SetTimerElapsedSeconds(IOSHandle handle,
                          IMRequest *request,
                          IMTimer timer,
                          uint32_t value,
                          IOSAsyncCallbackFn *asyncCallback,
                          void *asyncCallbackContext) __asm__("IM_SetTimerElpasedSeconds");

#ifdef __cplusplus
}
#endif

/** @} */
