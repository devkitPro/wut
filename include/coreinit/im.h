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
   IM_DEVICE_STATE_CLEAR      = 0,
   IM_DEVICE_STATE_INACTIVE   = 1,
   IM_DEVICE_STATE_ACTIVE     = 2,
   IM_DEVICE_STATE_HOME       = 3,
   IM_DEVICE_STATE_POWER      = 4,
   IM_DEVICE_STATE_SYNC       = 5,
} IMDeviceState;

struct WUT_PACKED IMRequest
{
   uint8_t args[0x80];
   IOSVec ioctlVecs[2];
   IOSHandle handle;
   int32_t request;
   IOSAsyncCallbackFn asyncCallback;
   void *asyncCallbackContext;
   void *copySrc;
   void *copyDst;
   uint32_t copySize;
};
WUT_CHECK_OFFSET(IMRequest, 0x80, ioctlVecs);
WUT_CHECK_OFFSET(IMRequest, 0x98, handle);
WUT_CHECK_OFFSET(IMRequest, 0x9C, request);
WUT_CHECK_OFFSET(IMRequest, 0xA0, asyncCallback);
WUT_CHECK_OFFSET(IMRequest, 0xA4, asyncCallbackContext);
WUT_CHECK_OFFSET(IMRequest, 0xA8, copySrc);
WUT_CHECK_OFFSET(IMRequest, 0xAC, copyDst);
WUT_CHECK_OFFSET(IMRequest, 0xB0, copySize);
WUT_CHECK_SIZE(IMRequest, 0xB4);

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
   IM_PARAMETER_INACTIVE_SECONDS     = 0,
   IM_PARAMETER_DIM_ENABLED          = 1,
   IM_PARAMETER_DIM_PERIOD           = 2,
   IM_PARAMETER_APD_ENABLED          = 3,
   IM_PARAMETER_APD_PERIOD           = 4,
   IM_PARAMETER_RESET_ENABLE         = 5,
   IM_PARAMETER_RESET_SECONDS        = 6,
   IM_PARAMETER_POWER_OFF_ENABLE     = 7,
   IM_PARAMETER_APD_OCCURED          = 8,
   IM_PARAMETER_DIM_ENABLE_TV        = 9,
   IM_PARAMETER_DIM_ENABLE_DRC       = 10,
   IM_PARAMETER_MAX                  = 11,
} IMParameter;

typedef enum IMTimer
{
   IM_TIMER_DIM = 0,
   IM_TIMER_APD = 1,
} IMTimer;

typedef enum IMEvent
{
   IM_EVENT_ACTIVE    = 1 << 0,
   IM_EVENT_INACTIVE  = 1 << 1,
   IM_EVENT_DIM       = 1 << 2,
   IM_EVENT_UNDIM     = 1 << 3,
   //! Automatic power down
   IM_EVENT_APD       = 1 << 4,
   //! Controller power button was pressed
   IM_EVENT_POWER     = 1 << 5,
   //! Home button was pressed
   IM_EVENT_HOME      = 1 << 6,
   //! Console sync button was pressed
   IM_EVENT_SYNC      = 1 << 7,
   IM_EVENT_RESET     = 1 << 8,
   //! Event notify was cancelled
   IM_EVENT_CANCELLED = 1 << 31,
} IMEvent;

IOSHandle
IM_Open(void);

IOSError
IM_Close(IOSHandle handle);

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
IM_GetParameters(IMParameters* parameters);

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

#ifdef __cplusplus
}
#endif

/** @} */
