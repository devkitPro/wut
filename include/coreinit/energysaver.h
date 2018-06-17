#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_energysaver Energy saver
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

int32_t
IMEnableDim(void);

int32_t
IMDisableDim(void);

int32_t
IMIsDimEnabled(int32_t * result);

int32_t
IMEnableAPD(void);

int32_t
IMDisableAPD(void);

int32_t
IMIsAPDEnabled(int32_t * result);

int32_t
IMIsAPDEnabledBySysSettings(int32_t * result);

#ifdef __cplusplus
}
#endif

/** @} */
