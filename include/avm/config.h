#pragma once
#include <wut.h>
#include <tve/tve.h>
#include "tv.h"

/**
 * \defgroup avm_config AVM System Config
 * \ingroup avm
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Reads the TV aspect ratio.
 * 
 * \param outAspectRatio
 * Pointer to write the aspect ratio to.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMReadSystemAspectRatioConfig(AVMTvAspectRatio *outAspectRatio);

/**
 * Reads the TV port.
 * 
 * \param outPort
 * Pointer to write the port to.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMReadSystemPortConfig(TVEPort *outPort);

/**
 * Reads the TV under scan.
 * 
 * \param outUnderScan
 * Pointer to write the under scan to.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMReadSystemTVUnderScanConfig(uint32_t *outUnderScan);

/**
 * Reads the TV resolution.
 * 
 * \param outResolution
 * Pointer to write the resolution to.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMReadSystemVideoResConfig(AVMTvResolution *outResolution);

/**
 * Writes the TV aspect ratio.
 * 
 * \param aspectRatio
 * Must be one of #AVMTvAspectRatio.
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMWriteSystemAspectRatioConfig(AVMTvAspectRatio aspectRatio);

/**
 * Writes the TV under scan.
 * 
 * \param underScan
 * Must be less than \c 0x15 .
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMWriteSystemTVUnderScanConfig(uint32_t underScan);

/**
 * Writes the TV port and resolution.
 * 
 * \param port
 * Must be one of #TVEPort.
 * 
 * \param resolution
 * Must be one of:
 * - #AVM_TV_RESOLUTION_576I
 * - #AVM_TV_RESOLUTION_480I
 * - #AVM_TV_RESOLUTION_480P
 * - #AVM_TV_RESOLUTION_720P
 * - #AVM_TV_RESOLUTION_1080I
 * - #AVM_TV_RESOLUTION_1080P
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMWriteSystemVideoOutConfig(TVEPort port,
                             AVMTvResolution resolution);

/**
 * Writes the TV resolution.
 *
 * \param resolution
 * Must be one of:
 * - #AVM_TV_RESOLUTION_576I
 * - #AVM_TV_RESOLUTION_480I
 * - #AVM_TV_RESOLUTION_480P
 * - #AVM_TV_RESOLUTION_720P
 * - #AVM_TV_RESOLUTION_1080I
 * - #AVM_TV_RESOLUTION_1080P
 * 
 * \return
 * \c 0 on success or a negative value on error.
 */
int32_t
AVMWriteSystemVideoResConfig(AVMTvResolution resolution);

#ifdef __cplusplus
}
#endif

/** @} */
