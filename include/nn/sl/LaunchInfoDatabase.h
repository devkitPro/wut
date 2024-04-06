#pragma once

#include <nn/result.h>
#include <nn/sl/FileStream.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED LaunchInfoDatabaseInternal {
            WUT_UNKNOWN_BYTES(0x1C);
        } LaunchInfoDatabaseInternal;
        WUT_CHECK_SIZE(LaunchInfoDatabaseInternal, 0x1C);

        extern "C" LaunchInfoDatabaseInternal *__ct__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
        extern "C" nn::Result Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(LaunchInfoDatabaseInternal *, nn::sl::details::IStreamInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, nn::sl::details::IStreamInternal *, nn::sl::Region);
        extern "C" nn::Result LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, int, nn::sl::Region);
        extern "C" nn::Result GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(LaunchInfoDatabaseInternal *, nn::sl::LaunchInfo *, uint64_t titleId);
        extern "C" void Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
    } // namespace details

    class LaunchInfoDatabase {
    public:
        LaunchInfoDatabase() {
            __ct__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
        }

        ~LaunchInfoDatabase() {
            Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
        }

        nn::Result Load(nn::sl::details::IStreamBase &fileStream, nn::sl::Region region) {
            return Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(&mInstance, fileStream.GetInternal(), region);
        }

        nn::Result Store(nn::sl::details::IStreamBase &fileStream) {
            return Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(&mInstance, fileStream.GetInternal());
        }

        nn::Result LoadInitial(int unkn, nn::sl::Region region) {
            return LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(&mInstance, unkn, region);
        }

        nn::Result GetLaunchInfoById(nn::sl::LaunchInfo *launchInfo, uint64_t titleId) {
            return GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(&mInstance, launchInfo, titleId);
        }

    private:
        details::LaunchInfoDatabaseInternal mInstance = {};
    };

} // namespace nn::sl

#endif