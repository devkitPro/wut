#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_savedframe
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum OSSavedFrameType
{
    OS_SAVED_FRAME_A = 0,
    OS_SAVED_FRAME_B = 1,
} OSSavedFrameType;

typedef enum OSSavedFrameScreen
{
    OS_SAVED_FRAME_SCREEN_TV  = 2,
    OS_SAVED_FRAME_SCREEN_DRC = 4,
} OSSavedFrameScreen;

uint32_t
__OSClearSavedFrame(OSSavedFrameType type,
                    OSSavedFrameScreen screen);

/**
 * Gets the GX2Texture saved via \link __OSSetSavedFrame \endlink
 * @param ptr_size  must be <= 0x100
 */
void
__OSGetSavedFrame(OSSavedFrameScreen screen,
                  void *outPtr,
                  uint32_t ptr_size);

/**
 * Gets the GX2Texture saved via \link __OSSetSavedFrame \endlink
 * @param ptr_size  must be <= 0x100
 */
void
__OSGetSavedFrameA(OSSavedFrameScreen screen,
                   void *outPtr,
                   uint32_t ptr_size);

/**
 * Gets the GX2Texture saved via \link __OSSetSavedFrame \endlink
 * @param ptr_size  must be <= 0x100
 */
void
__OSGetSavedFrameB(OSSavedFrameScreen screen,
                   void *outPtr,
                   uint32_t ptr_size);

BOOL
__OSGetSavedFrameGammaA(OSSavedFrameScreen screen,
                        float *outGamma);

BOOL
__OSGetSavedFrameGammaB(OSSavedFrameScreen screen,
                        float *outGamma);

void *
__OSGetSavedFramePtr(OSSavedFrameType type,
                     OSSavedFrameScreen screen);

void *
__OSGetSavedFramePtrForRead(OSSavedFrameScreen screen);

void *
__OSGetSavedFramePtrForWrite(OSSavedFrameScreen screen);

uint32_t
__OSGetSavedFrames();

uint32_t
__OSGetSavedFramesA();

uint32_t
__OSGetSavedFramesB();

void
__OSResetSavedFrame(OSSavedFrameScreen screen);

/**
 *
 * @param data expected to be a GX2Texture
 * @param size must be <= 0x100
 * @return 0 on succes, -1 on error
 */
int
__OSSetSavedFrame(OSSavedFrameScreen screen,
                  void *data,
                  uint32_t size);

void
__OSSetSavedFrameGamma(float gamma,
                       OSSavedFrameScreen screen);

#ifdef __cplusplus
}
#endif

/** @} */
