#pragma once

#include "FileStream.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn {

   namespace sl {

      typedef struct WUT_PACKED LaunchInfoDatabaseInternal
      {
         WUT_UNKNOWN_BYTES(0x1C);
      } LaunchInfoDatabaseInternal;
      WUT_CHECK_SIZE(LaunchInfoDatabaseInternal, 0x1C);

      extern "C" LaunchInfoDatabaseInternal *
      __ct__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
      extern "C" nn::Result
      Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, nn::sl::FileStreamInternal *, nn::sl::Region);
      extern "C" void
      Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
      extern "C" nn::Result
      GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(LaunchInfoDatabaseInternal *, nn::sl::LaunchInfo *, uint64_t titleId);

      class LaunchInfoDatabase {
       public:
         LaunchInfoDatabase()
         {
            instance = __ct__Q3_2nn2sl18LaunchInfoDatabaseFv(nullptr);
         }

         ~LaunchInfoDatabase()
         {
            Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(instance);
         }

         nn::Result
         Load(nn::sl::FileStream *fileStream, nn::sl::Region region)
         {
            return Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(instance, fileStream->instance, region);
         }

         nn::Result
         GetLaunchInfoById(nn::sl::LaunchInfo *launchInfo, uint64_t titleId)
         {
            return GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(instance, launchInfo, titleId);
         }

       private:
         LaunchInfoDatabaseInternal *instance;
      };

   } //namespace sl

} //namespace nn

#endif