#pragma once
#include <wut.h>
#include <coreinit/thread.h>

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

typedef int CAMHandle;
typedef int CAMError;

typedef struct CAMEventData CAMEventData;
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
   CAMERA_ERROR_TOO_MANY_SURFACES      = -4,
   CAMERA_ERROR_INSUFFICIENT_MEMORY    = -5,
   CAMERA_ERROR_NOT_READY              = -6,
   CAMERA_ERROR_UNINITIALIZED          = -8,
   CAMERA_ERROR_UVC                    = -9,
   CAMERA_ERROR_UVD_CONTEXT            = -10,
   CAMERA_ERROR_DEVICE_IN_USE          = -12,
   CAMERA_ERROR_UVD_SESSION            = -13,
   CAMERA_ERROR_SEGMENT_VIOLATION      = -15
} CamError;

typedef enum CamFps
{
   CAMERA_FPS_15   = 0,
   CAMERA_FPS_30   = 1
} CamFps;

typedef enum CamStreamType
{
   CAMERA_STREAM_TYPE_1   = 0
} CamStreamType;

typedef enum CamEventType
{
   CAMERA_DECODE_DONE   = 0,
   CAMERA_DRC_DETACH    = 1
} CamEventType;

struct CAMEventData
{
   //! Event type
   CamEventType eventType;
   union
   {
      struct
      {
         //! The surface that finished decoding
         CAMSurface* surface;
         //! Handle of instance
         CAMHandle handle;
         //! TRUE if decode failed
         BOOL failed;
      } decode;
      struct
      {
         //! Will be FALSE
         BOOL connected;
         //! Handle of instance
         CAMHandle handle;
      } detach;
      //! Event args
      uint32_t args[3];
   };
};
WUT_CHECK_OFFSET(CAMEventData, 0x00, eventType);
WUT_CHECK_OFFSET(CAMEventData, 0x04, decode.surface);
WUT_CHECK_OFFSET(CAMEventData, 0x08, decode.handle);
WUT_CHECK_OFFSET(CAMEventData, 0x0c, decode.failed);
WUT_CHECK_OFFSET(CAMEventData, 0x04, detach.connected);
WUT_CHECK_OFFSET(CAMEventData, 0x08, detach.handle);
WUT_CHECK_OFFSET(CAMEventData, 0x04, args);
WUT_CHECK_SIZE(CAMEventData, 0x10);

typedef void(*CAMEventHandler)(CAMEventData *camEventData);

struct CAMMode
{
   //! If TRUE, the GamePad will display the camera output regardless of what is being rendered
   BOOL forceDrc;
   //! Framerate setting
   CamFps fps;
};
WUT_CHECK_OFFSET(CAMMode, 0x00, forceDrc);
WUT_CHECK_OFFSET(CAMMode, 0x04, fps);
WUT_CHECK_SIZE(CAMMode, 0x08);

struct CAMWorkMem
{
   //! Size of the work memory
   uint32_t size;
   //! Pointer to the work memory
   void *pMem;
};
WUT_CHECK_OFFSET(CAMWorkMem, 0x00, size);
WUT_CHECK_OFFSET(CAMWorkMem, 0x04, pMem);
WUT_CHECK_SIZE(CAMWorkMem, 0x08);

struct CAMStreamInfo
{
   //! Stream type, only CAMERA_STREAM_TYPE_1 is valid
   CamStreamType type;
   //! Stream height
   uint32_t height;
   //! Stream width
   uint32_t width;
};
WUT_CHECK_OFFSET(CAMStreamInfo, 0x00, type);
WUT_CHECK_OFFSET(CAMStreamInfo, 0x04, height);
WUT_CHECK_OFFSET(CAMStreamInfo, 0x08, width);
WUT_CHECK_SIZE(CAMStreamInfo, 0x0C);

struct CAMSetupInfo
{
   //! Stream info
   CAMStreamInfo streamInfo;
   //! Memory used by library to record and decode frames
   CAMWorkMem workMem;
   //! Event handler
   CAMEventHandler eventHandler;
   //! Camera mode
   CAMMode mode;
   //! See \link OS_THREAD_ATTRIB \endlink
   uint32_t threadAffinity;
   WUT_PADDING_BYTES(0x10);
};
WUT_CHECK_OFFSET(CAMSetupInfo, 0x00, streamInfo);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x0C, workMem);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x14, eventHandler);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x18, mode);
WUT_CHECK_OFFSET(CAMSetupInfo, 0x20, threadAffinity);
WUT_CHECK_SIZE(CAMSetupInfo, 0x34);

struct CAMSurface
{
   //! Number of bytes allocated to surface buffer
   int32_t surfaceSize;
   //! Surface buffer data
   void *surfaceBuffer;
   //! Surface height
   int32_t height;
   //! Surface width
   int32_t width;
   //! Surface pitch
   int32_t pitch;
   //! Surface alignment
   int32_t alignment;
   //! Tile mode, should be zero
   int32_t tileMode;
   //! Pixel format, Should be zero
   int32_t pixelFormat;
};
WUT_CHECK_OFFSET(CAMSurface, 0x00, surfaceSize);
WUT_CHECK_OFFSET(CAMSurface, 0x04, surfaceBuffer);
WUT_CHECK_OFFSET(CAMSurface, 0x08, height);
WUT_CHECK_OFFSET(CAMSurface, 0x0C, width);
WUT_CHECK_OFFSET(CAMSurface, 0x10, pitch);
WUT_CHECK_OFFSET(CAMSurface, 0x14, alignment);
WUT_CHECK_OFFSET(CAMSurface, 0x18, tileMode);
WUT_CHECK_OFFSET(CAMSurface, 0x1C, pixelFormat);
WUT_CHECK_SIZE(CAMSurface, 0x20);

/**
* Initialize the camera
* \returns camera handle on success, and -1 on failure
*/
CAMHandle 
CAMInit(int instance, CAMSetupInfo *setupInfo, CAMError *err);

/**
* Deinitialize and clean up
*/
void 
CAMExit(CAMHandle handle);

/**
* Start recording and decoding frames
*/
CAMError 
CAMOpen(CAMHandle handle);

/**
* Stops recording and decoding.
* Automatically called when the process is moved to background
*/
CAMError 
CAMClose(CAMHandle handle);

/**
* Get the number of bytes requied by the work memory
* \returns number of bytes
* \returns CAM_ERROR_INVALID_ARG if streamInfo is NULL
*/
int32_t
CAMGetMemReq(CAMStreamInfo *streamInfo);

/**
* Submit 1 surface to the working queue.
* Once the frame is captured and decoded, the event handler set in CAMInit will fire, and the frame will be dequeued.
* Up to 20 surfaces may be queued.
* Surface data is returned in the NV12 format
*/
CAMError 
CAMSubmitTargetSurface(CAMHandle handle, CAMSurface *surface);

/**
* Checks whether memory is segmented correctly to be used with the camera library
*/
CAMError 
CAMCheckMemSegmentation(void *pMem, uint32_t size);

#ifdef __cplusplus
}
#endif
