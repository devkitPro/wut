#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_cosreport COS Report
 * \ingroup coreinit
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum COSReportLevel{
   COS_REPORT_LEVEL_ERROR       = 0,
   COS_REPORT_LEVEL_WARN        = 1,
   COS_REPORT_LEVEL_INFO        = 2,
   COS_REPORT_LEVEL_VERBOSE     = 3,
} COSReportLevel;

typedef enum COSReportModule{
   COS_REPORT_MODULE_UNKNOWN_0  = 0,
   COS_REPORT_MODULE_UNKNOWN_1  = 1,
   COS_REPORT_MODULE_UNKNOWN_2  = 2,
   COS_REPORT_MODULE_UNKNOWN_5  = 5,
} COSReportModule;

void
COSVReport(COSReportModule module,
           COSReportLevel level,
           const char* fmt,
           ...);

void
COSError(COSReportModule module,
         const char* fmt,
         ...);

void
COSInfo(COSReportModule module,
        const char* fmt,
        ...);

void
COSVerbose(COSReportModule module,
           const char* fmt,
           ...);

void
COSWarn(COSReportModule module,
        const char* fmt,
        ...);

#ifdef __cplusplus
}
#endif

/** @} */
