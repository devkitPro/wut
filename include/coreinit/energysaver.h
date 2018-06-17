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
IMGetDimEnableDrc(uint32_t *outValue);

IMError
IMGetDimEnableTv(uint32_t *outValue);

IMError
IMGetDimPeriod(uint32_t *outValue);

IMError
IMGetTimeBeforeAPD(uint32_t *outSeconds);

IMError
IMGetTimeBeforeDimming(uint32_t *outSeconds);

IMError
IMSetDimEnableDrc(BOOL value);

IMError
IMSetDimEnableTv(BOOL value);

IMError
IMStartAPDVideoMode();

#ifdef __cplusplus
}
#endif

/** @} */
