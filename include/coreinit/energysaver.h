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

typedef int32_t IMError;

IMError
IMDisableAPD();

IMError
IMDisableDim();

IMError
IMEnableAPD();

IMError
IMEnableDim();

IMError
IMIsAPDEnabled(uint32_t *outValue);

IMError
IMIsAPDEnabledBySysSettings(uint32_t *outValue);

IMError
IMIsDimEnabled(uint32_t *outValue);

IMError
IMGetDimEnableDRC(uint32_t *outValue);

IMError
IMGetDimEnableTV(uint32_t *outValue);

IMError
IMGetDimPeriod(uint32_t *outValue);

IMError
IMGetTimeBeforeAPD(uint32_t *outSeconds);

IMError
IMGetTimeBeforeDimming(uint32_t *outSeconds);

IMError
IMSetDimEnableDRC(BOOL value);

IMError
IMSetDimEnableTV(BOOL value);

IMError
IMStartAPDVideoMode();

#ifdef __cplusplus
}
#endif

/** @} */
