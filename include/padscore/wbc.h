#pragma once
#include <wut.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_wbc WBC
 * \ingroup padscore
 *
 * WBC is a library for accessing the Balance Board.
 *
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif


typedef enum WBCError
{
   WBC_ERROR_NONE            =  0,
   WBC_ERROR_NO_CONTROLLER   = -1,
   WBC_ERROR_NOT_READY       = -2,
   WBC_ERROR_BAD_TEMPERATURE = -3,
   WBC_ERROR_INVALID         = -4,
} WBCError;


// TODO: Check result, it seems to return total raw pressure data, not weight.
uint32_t
WBCGetABSWeight(void);

/**
 * Converts raw battery value to a level.
 *
 * \param battery The `battery` field from `WPADStatusBalanceBoard`.
 * \return A level from 0 to 4.
 */
uint32_t
WBCGetBatteryLevel(uint8_t battery);

/**
 * Checks if the Balance Board calibration is completed.
 *
 * \return TRUE if calibration is completed, FALSE if in progress, or an error occurred.
 * \sa `WBCSetupCalibration()`
 */
BOOL
WBCGetCalibrationStatus(void);

/**
 * Returns gravity-corrected weight.
 *
 * Used internally by `WBCGetTGCWeight()`.
 */
double
WBCGetGCWeight(double weight);

/**
 * Returns the gravity coefficient.
 */
double
WBCGetGravCoff(void);

/**
 * Always returns 0.
 */
uint32_t
WBCGetProductArea(void);

/**
 * Returns temperature-corrected weight.
 *
 * Used internally by `WBCGetTGCWeight()`.
 */
WBCError
WBCGetTCWeight(double weight,
               double *correctedWeight,
               const WPADStatusBalanceBoard *status);

/**
 * Applies temperature and gravity correction to weight value.
 *
 * \param inputWeight The input weight value.
 * \param correctedWeidht Where to store the corrected weight.
 * \param status The status data used in `WPADRead()` and `WBCRead()`.
 * \return Zero on success, or an error code.
 */
WBCError
WBCGetTGCWeight(double inputWeight,
                double *correctedWeight,
                const WPADStatusBalanceBoard *status);

/**
 * Return the current zeros for each sensor.
 */
WBCError
WBCGetZEROPoint(double zeros[],
                uint32_t count);

/**
 * Converts the raw pressure data into weight values.
 *
 * \param status The status argument filled in by `WPADRead()`.
 * \param weights Pointer to an array of 4 elements to store the weights in Kg.
 * \param count How many elements in `weight` (should be 4).
 * \return
 *   - `1`: at least 7 Kg were detected.
 *   - `0`: measuring less than 7 Kg.
 *   - Negative: one of the `WBCError` values.
 * \sa `WBCSetupCalibration()`
 */
int32_t
WBCRead(WPADStatusBalanceBoard *status,
        double weights[],
        uint32_t count);

/**
 * Resets the zero weight value.
 *
 * \param zeros Array raw pressure values that correspond to zero weight, one for each sensor.
 * \param count The size of the `zeros` array, should be 4.
 * \sa
 * - `WBCSetupCalibration()`
 * - `WPADControlBLC()`
 */
WBCError
WBCSetZEROPoint(const double zeros[],
                uint32_t count);

/**
 * Starts the calibration of Balance Board.
 *
 * Note: this function is asynchronous.
 * \return TRUE if calibration started successfully, FALSE if it failed to start.
 * \sa `WBCGetCalibrationStatus()`
 */
BOOL
WBCSetupCalibration(void);

#ifdef __cplusplus
}
#endif

/** @} */
