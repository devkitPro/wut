#pragma once
#include <wut.h>

/**
 * \defgroup cam Camera
 * \ingroup cam
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define CAMERA_WIDTH 640
#define CAMERA_PITCH 768
#define CAMERA_HEIGHT 480

#define CAMERA_Y_BUFFER_SIZE  (CAMERA_PITCH * CAMERA_HEIGHT)
#define CAMERA_UV_BUFFER_SIZE (CAMERA_PITCH * CAMERA_HEIGHT / 2)
#define CAMERA_YUV_BUFFER_SIZE (CAMERA_Y_BUFFER_SIZE + CAMERA_UV_BUFFER_SIZE)

#define CAMERA_YUV_BUFFER_ALIGNMENT 256

#define CAM_THREAD_AFFINITY_ANY 0x00000007u

typedef int CAMHandle;
typedef int CAMError;

typedef struct _Camera_Event_Handler_Input _Camera_Event_Handler_Input;
typedef struct CAMMode CAMMode;
typedef struct CAMWorkMem CAMWorkMem;
typedef struct CAMStreamInfo CAMStreamInfo;
typedef struct CAMSetupInfo CAMSetupInfo;
typedef struct CAMSurface CAMSurface;

typedef enum CamError
{
   CAMERA_ERROR_OK                     =  0,
   CAMERA_ERROR_INVALID_ARG            = -1,
   CAMERA_ERROR_INVALID_HANDLE         = -2,
   CAMERA_ERROR_INSUFFICIENT_MEMORY    = -5,
   CAMERA_ERROR_NOT_READY              = -6,
   CAMERA_ERROR_UNIINITIALIZED         = -8,
   CAMERA_ERROR_UNKNOWN                = -10,
   CAMERA_ERROR_DEVICE_IN_USE          = -12,
   CAMERA_ERROR_SEGMENT_VIOLATION      = -14
} CamError;

typedef enum CamFps
{
   CAMERA_FPS_15,
   CAMERA_FPS_30
} CamFps;

typedef enum CamStreamType
{
   CAMERA_STREAM_TYPE_1
} CamStreamType;

struct _Camera_Event_Handler_Input
{
   CAMError err;
   void *img;
   void *arg; // user provided value ??
};
WUT_CHECK_SIZE(_Camera_Event_Handler_Input, 0x0C);

typedef void(*CAMEventHandler)(_Camera_Event_Handler_Input*);

struct CAMMode
{
   int unk_0x00;
   CamFps fps;
};
WUT_CHECK_OFFSET(CAMMode, 0x00, unk_0x00);
WUT_CHECK_OFFSET(CAMMode, 0x04, fps);
WUT_CHECK_SIZE(CAMMode, 0x08);

struct CAMWorkMem
{
   int  size; // size of the work mem
   void *pMem; // pointer to the work mem
};
WUT_CHECK_OFFSET(CAMWorkMem, 0x00, size);
WUT_CHECK_OFFSET(CAMWorkMem, 0x04, pMem);
WUT_CHECK_SIZE(CAMWorkMem, 0x08);

struct CAMStreamInfo
{
   CamStreamType type;
   int height; // stream height              
   int width; // stream width
};
WUT_CHECK_OFFSET(CAMStreamInfo, 0x00, type);
WUT_CHECK_OFFSET(CAMStreamInfo, 0x04, height);
WUT_CHECK_OFFSET(CAMStreamInfo, 0x08, width);
WUT_CHECK_SIZE(CAMStreamInfo, 0x0C);

struct CAMSetupInfo
{
   CAMStreamInfo streamInfo;
   CAMWorkMem workMem;
   WUT_UNKNOWN_BYTES(8);
   CAMMode mode;
   int threadAffinity; // which cpu core to run on, only known value is CAM_THREAD_AFFINITY_ANY
   WUT_UNKNOWN_BYTES(0x10);
};
WUT_CHECK_OFFSET(CAMSetupInfo, 0x00, streamInfo);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x0C, workMem);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x1C, mode);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x24, threadAffinity);
WUT_CHECK_SIZE(CAMSetupInfo, 0x38);

struct CAMSurface
{
   int surfaceSize;
   void *surfaceBuffer;
   int height; // surface height
   int width; // surface width
   int unk_0x10; // pitch related?
   int alignment; // surface alignment
   int unk_0x18; // surface tile mode related?
   int unk_0x1C;
};
WUT_CHECK_OFFSET(CAMSurface, 0x00, surfaceSize);
WUT_CHECK_OFFSET(CAMSurface, 0x04, surfaceBuffer);
WUT_CHECK_OFFSET(CAMSurface, 0x08, height);
WUT_CHECK_OFFSET(CAMSurface, 0x0C, width);
WUT_CHECK_OFFSET(CAMSurface, 0x10, unk_0x10);
WUT_CHECK_OFFSET(CAMSurface, 0x14, alignment);
WUT_CHECK_OFFSET(CAMSurface, 0x18, unk_0x18);
WUT_CHECK_OFFSET(CAMSurface, 0x1C, unk_0x1C);
WUT_CHECK_SIZE(CAMSurface, 0x20);

CAMHandle 
CAMInit(int instance, CAMSetupInfo *setupInfo, CAMError *err);

void 
CAMExit(CAMHandle handle);

CAMError 
CAMOpen(CAMHandle handle);

CAMError 
CAMClose(CAMHandle handle);

CAMError 
CAMGetMemReq(CAMStreamInfo *streamInfo);

CAMError 
CAMSubmitTargetSurface(CAMHandle handle, CAMSurface *surface);

CAMError 
CAMCheckMemSegmentation(void *pMem, unsigned int size);

#ifdef __cplusplus
}
#endif
