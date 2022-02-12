#pragma once

#include <coreinit/memdefaultheap.h>
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn {

   namespace sl {

      typedef struct WUT_PACKED LaunchInfo
      {
         uint64_t titleId;
         WUT_UNKNOWN_BYTES(0x810 - 0x08);
      } LaunchInfo;

      WUT_CHECK_OFFSET(LaunchInfo, 0x00, titleId);
      WUT_CHECK_SIZE(LaunchInfo, 0x810);

      typedef enum Region
      {
         REGION_JPN = 0,
         REGION_USA = 1,
         REGION_EUR = 2
      } Region;

      void
      GetDefaultDatabasePath(char *, int size, uint64_t titleId) asm("GetDefaultDatabasePath__Q2_2nn2slFPcUiUL");

      nn::Result
              Initialize(MEMAllocFromDefaultHeapExFn, MEMFreeToDefaultHeapFn) asm("Initialize__Q2_2nn2slFPFUiT1_PvPFPv_v");

      nn::Result
      Finalize() asm("Finalize__Q2_2nn2slFv");

   }; //namespace sl

}; //namespace nn

#endif