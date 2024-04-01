#pragma once

#include "FileStream.h"
#include "sl_cpp.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace {
        typedef struct WUT_PACKED LaunchInfoDatabaseInternal {
            WUT_UNKNOWN_BYTES(0x1C);
        } LaunchInfoDatabaseInternal;
        WUT_CHECK_SIZE(LaunchInfoDatabaseInternal, 0x1C);

        extern "C" LaunchInfoDatabaseInternal *__ct__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
        extern "C" nn::Result Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(LaunchInfoDatabaseInternal *, nn::sl::FileStreamInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, nn::sl::FileStreamInternal *, nn::sl::Region);
        extern "C" nn::Result LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, int, nn::sl::Region);
        extern "C" nn::Result GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(LaunchInfoDatabaseInternal *, nn::sl::LaunchInfo *, uint64_t titleId);
    } // namespace

    class LaunchInfoDatabase {
    public:
        LaunchInfoDatabase() {
            __ct__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
        }

        ~LaunchInfoDatabase() = default;

        nn::Result Load(nn::sl::FileStream *fileStream, nn::sl::Region region) {
            return Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(&mInstance, &fileStream->mInstance, region);
        }

        nn::Result Store(nn::sl::FileStream *fileStream) {
            return Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(&mInstance, &fileStream->mInstance);
        }

        nn::Result LoadInitial(int unkn, nn::sl::Region region) {
            return LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(&mInstance, unkn, region);
        }

        nn::Result GetLaunchInfoById(nn::sl::LaunchInfo *launchInfo, uint64_t titleId) {
            return GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(&mInstance, launchInfo, titleId);
        }

    private:
        LaunchInfoDatabaseInternal mInstance = {};
    };

} // namespace nn::sl

#endif