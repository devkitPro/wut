#pragma once
#include <wut.h>
#include <coreinit/ios.h>

/**
 * \defgroup nsysccr_hid Raw HID data of the DRCs
 * \ingroup nsysccr
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CCRHIDReport CCRHIDReport;

struct WUT_PACKED CCRHIDReport
{
   WUT_UNKNOWN_BYTES(0x80);
};
WUT_CHECK_SIZE(CCRHIDReport, 0x80);

/**
 * Start transmission of HID reports from the specified DRC.
 * 
 * \param drcSlot
 * The DRC to read the HID reports from (0 or 1).
 * 
 * \param reportsBuffer
 * Aligned buffer to read reports to.
 * 
 * \param numReports
 * The amount of reports the buffer can store.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRHIDStart(uint32_t drcSlot,
            CCRHIDReport *reportsBuffer,
            uint32_t numReports,
            IOSAsyncCallbackFn callback,
            void *arg);

/**
 * Stop HID report transmission.
 * 
 * \param drcSlot
 * The DRC to read the HID reports from (0 or 1).
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRHIDStop(uint32_t drcSlot,
           IOSAsyncCallbackFn callback,
           void *arg);

int32_t
CCRHIDGetData(uint32_t drcSlot,
              CCRHIDReport *reportData);

int32_t
CCRHIDGetBufferedData(uint32_t drcSlot,
                      CCRHIDReport *reportData);

int32_t
CCRHIDGetFirmwareVersion(CCRHIDReport *report,
                         uint32_t *firmwareVersion);

int32_t
CCRHIDGetSequence(CCRHIDReport *report,
                  uint32_t *sequence);

#ifdef __cplusplus
}
#endif

/** @} */
