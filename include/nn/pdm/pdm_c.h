#pragma once
#include <wut.h>

/**
 * \defgroup nn_pdm_c
 * \ingroup nn_pdm
 * C functions for PDM
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes PDM.
 * Needs to be called before using other functions.
 *
 * \return
 * 0 on success.
 */
uint32_t
PDMInitialize();

/**
 * Finalize PDM.
 */
void
PDMFinalize();

/**
 * Close all opened PDM Files.
 */
void
PDMCloseAllFiles();

void
PDMNotifySetTimeBeginEvent();

void
PDMNotifySetTimeEndEvent();

#ifdef __cplusplus
}
#endif

/** @} */
