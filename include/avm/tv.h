#pragma once
#include <wut.h>
#include <tve/tve.h>

/**
 * \defgroup avm_tv TV
 * \ingroup avm
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AVMTvAspectRatio
{
   //! 4:3
   AVM_TV_ASPECT_RATIO_4_3,
   //! 16:9
   AVM_TV_ASPECT_RATIO_16_9,
} AVMTvAspectRatio;

typedef enum AVMTvResolution
{
   AVM_TV_RESOLUTION_576I           = 1,
   AVM_TV_RESOLUTION_480I           = 2,
   AVM_TV_RESOLUTION_480P           = 3,
   AVM_TV_RESOLUTION_720P           = 4,
   AVM_TV_RESOLUTION_720P_3D        = 5,
   AVM_TV_RESOLUTION_1080I          = 6,
   AVM_TV_RESOLUTION_1080P          = 7,
   AVM_TV_RESOLUTION_480I_PAL60     = 10,
   AVM_TV_RESOLUTION_576P           = 11,
   AVM_TV_RESOLUTION_720P_50HZ      = 12,
   AVM_TV_RESOLUTION_1080I_50HZ     = 13,
   AVM_TV_RESOLUTION_1080P_50HZ     = 14,
} AVMTvResolution;

typedef enum AVMTvVideoRegion
{
   AVM_TV_VIDEO_REGION_NTSC = 1,
   AVM_TV_VIDEO_REGION_PAL,
} AVMTvVideoRegion;

/**
 * Gets the TV video region.
 *
 * \return
 * \c TRUE if the region is set to \link AVM_TV_VIDEO_REGION_NTSC NTSC \endlink.
 * \c FALSE if the region is set to \link AVM_TV_VIDEO_REGION_PAL PAL \endlink.
 */
BOOL
AVMDebugIsNTSC(void);

/**
 * Gets the TV port.
 * 
 * \param outPort
 * Pointer to write the port to.
 * 
 * \return
 * Always returns \c TRUE .
 * 
 * \sa
 * - TVEGetCurrentPort()
 */
BOOL
AVMGetCurrentPort(TVEPort *outPort);

/**
 * Gets the HDMI state.
 * 
 * \param outState
 * Pointer to write the state to.
 * 
 * \sa
 * - TVEGetHDMIErrorStat()
 */
void
AVMGetHDMIState(TVEHdmiState *outState);

/**
 * Gets the TV aspect ratio.
 * 
 * \param outAspectRatio
 * Pointer to write the aspect ratio to.
 * 
 * \return
 * Always returns \c TRUE .
 */
BOOL
AVMGetTVAspectRatio(AVMTvAspectRatio *outAspectRatio);

/**
 * Gets the TV resolution.
 * 
 * \warning
 * If the resolution is set to #AVM_TV_RESOLUTION_480I_PAL60, this function
 * will instead output #AVM_TV_RESOLUTION_480I.
 * If the resolution is set to either #AVM_TV_RESOLUTION_720P_50HZ,
 * #AVM_TV_RESOLUTION_1080I_50HZ, or #AVM_TV_RESOLUTION_1080P_50HZ, then
 * \e nothing will be stored to \a outResolution .
 * 
 * \param outResolution
 * Pointer to write the resolution to.
 * 
 * \return
 * Always returns \c TRUE .
 */
BOOL
AVMGetTVScanMode(AVMTvResolution *outResolution);

/**
 * Gets the TV under scan.
 * 
 * \param outUnderScan
 * Pointer to write the under scan to.
 * 
 * \return
 * \c 0 on success or \c -1 on failure.
 */
int32_t
AVMGetTVUnderScan(uint32_t *outUnderScan);

/**
 * Determines whether a TV is currently connected and displaying the Wii U source.
 * 
 * Internally checks that either the #TVEHdmiState is #TVE_HDMI_STATE_DONE or
 * the analog state is \c 1 , depending on whether the \link TVEPort port \endlink is
 * set to \link TVE_PORT_HDMI HDMI \endlink or not.
 * 
 * \return
 * \c TRUE if a TV is connected, \c FALSE otherwise.
 * 
 * \sa
 * - AVMGetHDMIState()
 * - TVEGetHDMIErrorStat()
 * - TVEGetAnalogStat()
 */
BOOL
AVMIsAVOutReady(void);

/**
 * Sets the TV aspect ratio.
 * 
 * \param aspectRatio
 * Must be one of #AVMTvAspectRatio.
 * 
 * \return
 * \c TRUE on success or \c FALSE on failure.
 */
BOOL
AVMSetTVAspectRatio(AVMTvAspectRatio aspectRatio);

/**
 * Sets whether to show or hide the TV video out.
 * 
 * \param enable
 * If \c FALSE then a black image is output (i.e. blanks the screen).
 * The TV still receives a signal as normal and still plays audio.
 * 
 * \return
 * \c TRUE on success or \c FALSE on failure.
 */
BOOL
AVMSetTVEnable(BOOL enable);

/**
 * Sets the TV port.
 * 
 * \param port
 * Must be one of #TVEPort.
 * 
 * \param resolution
 * Must be one of #AVMTvResolution.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMSetTVOutPort(TVEPort port,
                AVMTvResolution resolution);

/**
 * Sets the TV resolution and port.
 * 
 * \param resolution
 * Must be one of #AVMTvResolution.
 * 
 * \param port
 * Must be one of #TVEPort.
 * 
 * \return
 * \c 1 on success.
 */
int32_t
AVMSetTVScanMode(AVMTvResolution resolution,
                 uint32_t unknown,
                 TVEPort port);

/**
 * Sets the TV resolution.
 *
 * \param resolution
 * Must be one of #AVMTvResolution.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMSetTVScanResolution(AVMTvResolution resolution);

/**
 * Sets the TV under scan.
 * 
 * \param underScan
 * Must be less than \c 0x15 .
 * 
 * \return
 * \c 0 on success or a negative value on error.
 * 
 * \sa
 * - AVMSetTVUnderScanParam()
 */
int32_t
AVMSetTVUnderScan(uint32_t underScan);

/**
 * \param underScan
 * Must be less than \c 0x15 .
 * 
 * \return
 * \c 0 on success or \c -1 on failure.
 * 
 * \sa
 * - AVMSetTVUnderScan()
 */
int32_t
AVMSetTVUnderScanParam(uint32_t underScan);

/**
 * Sets the TV video region.
 * 
 * \param videoRegion
 * Must be one of #AVMTvVideoRegion.
 * 
 * \param port
 * Must be one of #TVEPort.
 * 
 * \param resolution
 * Must be one of #AVMTvResolution.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMSetTVVideoRegion(AVMTvVideoRegion videoRegion,
                    TVEPort port,
                    AVMTvResolution resolution);

#ifdef __cplusplus
}
#endif

/** @} */
