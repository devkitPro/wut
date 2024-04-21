#pragma once

#include <nn/result.h>
#include <nn/sl/FileStream.h>
#include <nn/sl/sl_cpp.h>
#include <optional>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED LaunchInfoDatabaseInternal {
            uint64_t *currentIdPtr;
            uint32_t *entryCountPtr;
            uint32_t *maxEntriesPtr;
            void *pDatabase;
            LaunchInfoDatabaseEntry *entriesPtr;
            LaunchInfoDatabaseEntry *systemTablePtr;
            uint32_t systemTableNum;
        } LaunchInfoDatabaseInternal;
        WUT_CHECK_SIZE(LaunchInfoDatabaseInternal, 0x1C);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x00, currentIdPtr);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x04, entryCountPtr);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x08, maxEntriesPtr);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x0C, pDatabase);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x10, entriesPtr);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x14, systemTablePtr);
        WUT_CHECK_OFFSET(LaunchInfoDatabaseInternal, 0x18, systemTableNum);

        extern "C" LaunchInfoDatabaseInternal *__ct__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
        extern "C" nn::Result Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(LaunchInfoDatabaseInternal *, nn::sl::details::IStreamInternal *);
        extern "C" nn::Result Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, nn::sl::details::IStreamInternal *, nn::sl::Region);
        extern "C" nn::Result LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(LaunchInfoDatabaseInternal *, int, nn::sl::Region);
        extern "C" nn::Result GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL(LaunchInfoDatabaseInternal *, nn::sl::LaunchInfo *, uint64_t titleId);
        extern "C" void Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
        extern "C" uint32_t GetEntryCount__Q3_2nn2sl18LaunchInfoDatabaseCFv(LaunchInfoDatabaseInternal *);
        extern "C" void Clear__Q3_2nn2sl18LaunchInfoDatabaseFv(LaunchInfoDatabaseInternal *);
        extern "C" uint64_t GetCurrentId__Q3_2nn2sl18LaunchInfoDatabaseCFv(LaunchInfoDatabaseInternal *);
        extern "C" uint64_t Register__Q3_2nn2sl18LaunchInfoDatabaseFRCQ3_2nn2sl10LaunchInfo(LaunchInfoDatabaseInternal *, const nn::sl::LaunchInfo &);
        extern "C" nn::Result Unregister__Q3_2nn2sl18LaunchInfoDatabaseFUL(LaunchInfoDatabaseInternal *, uint64_t);
        extern "C" nn::Result __CPR84__LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiPCQ4_2nn2slJ22J5EntryT1(LaunchInfoDatabaseInternal *, uint32_t max_entries, nn::sl::LaunchInfoDatabaseEntry *defaultEntries, uint32_t defaultEntryNum);
        extern "C" uint32_t __CPR86__ListLaunchInfos__Q3_2nn2sl18LaunchInfoDatabaseCFPQ4_2nn2slJ26J5EntryUi(LaunchInfoDatabaseInternal *, nn::sl::LaunchInfoDatabaseEntry *entriesOut, uint32_t num);
        extern "C" uint32_t __CPR93__Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamPCQ4_2nn2slJ15J5EntryUi(LaunchInfoDatabaseInternal *, details::IStreamInternal *stream, nn::sl::LaunchInfoDatabaseEntry *defaultEntries, uint32_t defaultEntryNum);
    } // namespace details

    class LaunchInfoDatabase {
    public:
        LaunchInfoDatabase() {
            __ct__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
        }

        ~LaunchInfoDatabase() {
            Finalize();
        }

        void Finalize() {
            // Only actually call finalize if the database is still loaded, otherwise we might trigger an assertion.
            if (mInstance.pDatabase != nullptr) {
                Finalize__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
            }
        }

        nn::Result Load(nn::sl::details::IStreamBase &fileStream, nn::sl::Region region) {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamQ3_2nn2sl6Region(&mInstance, fileStream.GetInternal(), region);
        }

        nn::Result Store(nn::sl::details::IStreamBase &fileStream) {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return Store__Q3_2nn2sl18LaunchInfoDatabaseCFRQ3_2nn2sl7IStream(&mInstance, fileStream.GetInternal());
        }

        nn::Result LoadInitial(int maxEntries, nn::sl::Region region) {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiQ3_2nn2sl6Region(&mInstance, maxEntries, region);
        }

        nn::Result GetLaunchInfoById(nn::sl::LaunchInfo *launchInfo, uint64_t titleId) const {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return GetLaunchInfoById__Q3_2nn2sl18LaunchInfoDatabaseCFPQ3_2nn2sl10LaunchInfoUL((details::LaunchInfoDatabaseInternal *) &mInstance, launchInfo, titleId);
        }

        [[nodiscard]] std::optional<uint32_t> GetEntryCount() const {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {};
            }
            return details::GetEntryCount__Q3_2nn2sl18LaunchInfoDatabaseCFv((details::LaunchInfoDatabaseInternal *) &mInstance);
        }

        [[nodiscard]] std::optional<uint64_t> GetCurrentId() const {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {};
            }
            return details::GetCurrentId__Q3_2nn2sl18LaunchInfoDatabaseCFv((details::LaunchInfoDatabaseInternal *) &mInstance);
        }

        [[nodiscard]] std::optional<uint64_t> Register(const nn::sl::LaunchInfo &launchInfo) {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {};
            }
            return details::Register__Q3_2nn2sl18LaunchInfoDatabaseFRCQ3_2nn2sl10LaunchInfo((details::LaunchInfoDatabaseInternal *) &mInstance, launchInfo);
        }

        [[nodiscard]] uint64_t Unregister(const nn::sl::LaunchInfo &launchInfo, uint64_t id) {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return details::Unregister__Q3_2nn2sl18LaunchInfoDatabaseFUL((details::LaunchInfoDatabaseInternal *) &mInstance, id);
        }

        void Clear() {
            if (mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return;
            }
            return details::Clear__Q3_2nn2sl18LaunchInfoDatabaseFv(&mInstance);
        }

        static nn::Result LoadInitial(LaunchInfoDatabase &launchDatabase, uint32_t maxEntries, nn::sl::LaunchInfoDatabaseEntry *defaultEntries, uint32_t defaultEntryNum) {
            if (launchDatabase.mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return details::__CPR84__LoadInitial__Q3_2nn2sl18LaunchInfoDatabaseFUiPCQ4_2nn2slJ22J5EntryT1(&launchDatabase.mInstance, maxEntries, defaultEntries, defaultEntryNum);
        }

        static uint32_t ListLaunchInfos(const LaunchInfoDatabase &launchDatabase, nn::sl::LaunchInfoDatabaseEntry *entriesOut, uint32_t num) {
            if (launchDatabase.mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return 0;
            }
            return details::__CPR86__ListLaunchInfos__Q3_2nn2sl18LaunchInfoDatabaseCFPQ4_2nn2slJ26J5EntryUi((details::LaunchInfoDatabaseInternal *) &launchDatabase.mInstance, entriesOut, num);
        }

        static uint32_t Load(LaunchInfoDatabase &launchDatabase, nn::sl::details::IStreamBase &fileStream, nn::sl::LaunchInfoDatabaseEntry *defaultEntries, uint32_t defaultEntryNum) {
            if (launchDatabase.mInstance.pDatabase == nullptr) { // Avoid triggering an assertion
                return {Result::LEVEL_FATAL, Result::RESULT_MODULE_NN_SL, 0};
            }
            return details::__CPR93__Load__Q3_2nn2sl18LaunchInfoDatabaseFRQ3_2nn2sl7IStreamPCQ4_2nn2slJ15J5EntryUi(&launchDatabase.mInstance, fileStream.GetInternal(), defaultEntries, defaultEntryNum);
        }

    private:
        details::LaunchInfoDatabaseInternal mInstance = {};
    };

} // namespace nn::sl

#endif