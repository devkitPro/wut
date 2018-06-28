#pragma once
#include <wut.h>
#include "surface.h"

/**
 * \defgroup gx2_debug Debug
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2DebugCaptureInterface GX2DebugCaptureInterface;

typedef enum GX2DebugCaptureInterfaceVersion
{
   GX2_DEBUG_CAPTURE_INTERFACE_VERSION                = 1,
} GX2DebugCaptureInterfaceVersion;

typedef enum GX2DebugCaptureStartFlags
{
   GX2_DEBUG_CAPTURE_START_FLAGS_NONE                 = 0,

   //! When set GX2DebugCaptureEnd will NOT call GX2DrawDone.
   GX2_DEBUG_CAPTURE_START_FLAGS_DISABLE_GX2DRAWDONE  = 1,
} GX2DebugCaptureStartFlags;

typedef enum GX2DebugCaptureEndFlags
{
   GX2_DEBUG_CAPTURE_END_FLAGS_NONE                   = 0,

   //! When set GX2DebugCaptureEnd will NOT call GX2Flush.
   GX2_DEBUG_CAPTURE_END_FLAGS_DISABLE_GX2FLUSH       = 1,
} GX2DebugCaptureEndFlags;

struct GX2DebugCaptureInterface
{
   //! Must be set to GX2_DEBUG_CAPTURE_INTERFACE_VERSION
   uint32_t version;

   //! Called from GX2Shutdown.
   void (*onShutdown)();

   //! Called from GX2DebugSetCaptureInterface with the default gx2 allocators.
   void (*setAllocator)();

   //! Called from GX2DebugCaptureStart, the filename is first argument passed
   //! in to GX2DebugCaptureStart.
   void (*onCaptureStart)(const char *filename);

   //! Called from GX2DebugCaptureEnd.
   void (*onCaptureEnd)();

   //! Check if capture is enabled.
   BOOL (*isCaptureEnabled)();

   //! Called when GX2 memory is allocated.
   void (*onAlloc)(void *ptr, uint32_t size, uint32_t align);

   //! Called when GX2 memory is freed.
   void (*onFree)(void *ptr);

   //! UNKNOWN: Called when something happens with some memory.
   void (*onUnknownMemory)(void *ptr, uint32_t size);

   //! Called from GX2DebugCaptureStart with the TV scan buffer.
   void (*setOutputSurface)(GX2Surface *surface);

   //! Called from GX2SwapScanBuffers with the TV scan buffer.
   void (*onSwapScanBuffers)(GX2Surface *surface);

   //! Called when a command buffer is ready to be submitted to ring buffer.
   //! Note that it seems we must call TCLSubmitToRing from this callback
   //! because gx2 will not do it when capturing.
   void (*submitToRing)(void *unk1,
                        uint32_t unk2,
                        uint32_t *unk3,
                        uint64_t *outSubmitTimestamp);
};
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x00, version);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x04, onShutdown);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x08, setAllocator);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x0C, onCaptureStart);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x10, onCaptureEnd);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x14, isCaptureEnabled);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x18, onAlloc);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x1C, onFree);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x20, onUnknownMemory);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x24, setOutputSurface);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x28, onSwapScanBuffers);
WUT_CHECK_OFFSET(GX2DebugCaptureInterface, 0x2C, submitToRing);
WUT_CHECK_SIZE(GX2DebugCaptureInterface, 0x30);

BOOL
_GX2DebugSetCaptureInterface(GX2DebugCaptureInterface *interface);


/**
 * Starts a debug capture.
 *
 * User must have set interface first via _GX2DebugSetCaptureInterface.
 *
 * Note this doesn't write to filename, that is up to the implementor of the
 * GX2DebugCaptureInterface. This argument might not even be filename but I at
 * least know it is a string because GX2DebugCaptureFrame does a strncpy on it.
 *
 * \param filename
 * This is passed as first argument to GX2DebugCaptureInterface.onCaptureStart
 */
void
GX2DebugCaptureStart(const char *filename,
                     GX2DebugCaptureStartFlags flags);


/**
 * Ends a debug capture.
 */
void
GX2DebugCaptureEnd(GX2DebugCaptureEndFlags flags);


/**
 * Will capture the next frame.
 *
 * Capture begins during the next call to GX2SwapScanBuffers, and will end
 * at the next GX2SwapScanBuffers.
 *
 * Equivalent to calling GX2DebugCaptureFrames(filename, 1)
 */
void
GX2DebugCaptureFrame(const char* filename);


/**
 * Will capture count frames.
 *
 * Capture begins during the next call to GX2SwapScanBuffers, and will end
 * after count frames have been swapped in GX2SwapScanBuffers.
 *
 * Capture begins and ends during GX2SwapScanBuffers.
 */
void
GX2DebugCaptureFrames(const char* filename,
                      uint32_t count);

#ifdef __cplusplus
}
#endif

/** @} */
