#pragma once

#include <nn/result.h>
#include <nn/sl/IIconInfoAccessor.h>
#include <nn/sl/ISettingAccessor.h>
#include <nn/sl/ITitleIconCache.h>
#include <nn/sl/KillerNotification.h>
#include <nn/sl/LaunchInfoDatabase.h>
#include <nn/sl/details/IAccountInfoAccessorDetails.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn ::sl {
    namespace details {
        typedef struct WUT_PACKED DataCreatorInternal {
            IIconInfoAccessorInternal *iconInfoAccessor;
            IAccountInfoAccessorInternal *accountInfoAccessor;
            ISettingAccessorInternal *settingInfoAccessor;
            ITitleIconCacheInternal *titleIconCache;
            void *vtable;
        } DataCreatorInternal;
        WUT_CHECK_SIZE(DataCreatorInternal, 0x14);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x00, iconInfoAccessor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x04, accountInfoAccessor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x08, settingInfoAccessor);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x0c, titleIconCache);
        WUT_CHECK_OFFSET(DataCreatorInternal, 0x10, vtable);

        extern "C" DataCreatorInternal *__ct__Q3_2nn2sl11DataCreatorFv(DataCreatorInternal *);
        extern "C" nn::Result Create__Q3_2nn2sl11DataCreatorFPQ3_2nn2sl16TransferableInfoPCQ3_2nn2sl9TitleInfoiRCQ3_2nn2sl18KillerNotificationRCQ3_2nn2sl9TitleInfoRQ3_2nn2sl18LaunchInfoDatabase(
                DataCreatorInternal *, TransferableInfo *, const TitleInfo *, int, const KillerNotification &, const TitleInfo &, LaunchInfoDatabase &);
        extern "C" nn::Result Initialize__Q3_2nn2sl11DataCreatorFRQ3_2nn2sl17IIconInfoAccessorRQ3_2nn2sl20IAccountInfoAccessorRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl15ITitleIconCache(
                DataCreatorInternal *, IIconInfoAccessorInternal *, IAccountInfoAccessorInternal *, ISettingAccessorInternal *, ITitleIconCacheInternal *);
    } // namespace details


    class DataCreator {
    public:
        DataCreator() : mIconInfoAccessor(nullptr),
                        mAccountInfoAccessor(nullptr),
                        mSettingAccessor(nullptr),
                        mTitleIconCache(nullptr) {
            if (__ct__Q3_2nn2sl11DataCreatorFv(&mInstance) != nullptr) {
                mIconInfoAccessor    = details::IconInfoAccessorFromPtr(mInstance.iconInfoAccessor);
                mAccountInfoAccessor = details::AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
                mSettingAccessor     = details::SettingAccessorFromPtr(mInstance.settingInfoAccessor);
                mTitleIconCache      = details::TitleIconCacheFromPtr(mInstance.titleIconCache);
            }
        }

        [[nodiscard]] details::IIconInfoAccessorBase &getIconInfoAccessor() {
            return mIconInfoAccessor;
        }

        [[nodiscard]] details::IAccountInfoAccessorBase &getAccountInfoAccessor() {
            return mAccountInfoAccessor;
        }

        [[nodiscard]] details::ISettingAccessorBase &getSettingAccessor() {
            return mSettingAccessor;
        }

        [[nodiscard]] details::ITitleIconCacheBase &getTitleIconCache() {
            return mTitleIconCache;
        }

        nn::Result Create(TransferableInfo *outTransferableInfo,
                          const TitleInfo *quickstartTitleInfos,
                          int numQuickstartTitleInfos,
                          const KillerNotification &killerNotification,
                          const TitleInfo &killerNotificationTitleInfo,
                          LaunchInfoDatabase &launchInfoDatabase) {
            return details::Create__Q3_2nn2sl11DataCreatorFPQ3_2nn2sl16TransferableInfoPCQ3_2nn2sl9TitleInfoiRCQ3_2nn2sl18KillerNotificationRCQ3_2nn2sl9TitleInfoRQ3_2nn2sl18LaunchInfoDatabase(
                    &mInstance, outTransferableInfo, quickstartTitleInfos, numQuickstartTitleInfos, killerNotification, killerNotificationTitleInfo, launchInfoDatabase);
        }

        void Initialize(details::IIconInfoAccessorBase &iconInfoAccessor, details::IAccountInfoAccessorBase &accountInfoAccessor, details::ISettingAccessorBase &settingAccessor, details::ITitleIconCacheBase &titleIconCache) {
            details::Initialize__Q3_2nn2sl11DataCreatorFRQ3_2nn2sl17IIconInfoAccessorRQ3_2nn2sl20IAccountInfoAccessorRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl15ITitleIconCache(
                    &mInstance, iconInfoAccessor.GetInternal(), accountInfoAccessor.GetInternal(), settingAccessor.GetInternal(), titleIconCache.GetInternal());
            mIconInfoAccessor    = details::IconInfoAccessorFromPtr(mInstance.iconInfoAccessor);
            mAccountInfoAccessor = details::AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
            mSettingAccessor     = details::SettingAccessorFromPtr(mInstance.settingInfoAccessor);
            mTitleIconCache      = details::TitleIconCacheFromPtr(mInstance.titleIconCache);
        }

        ~DataCreator() = default;

    private:
        details::DataCreatorInternal mInstance = {};
        details::IconInfoAccessorFromPtr mIconInfoAccessor;
        details::AccountInfoAccessorFromPtr mAccountInfoAccessor;
        details::SettingAccessorFromPtr mSettingAccessor;
        details::TitleIconCacheFromPtr mTitleIconCache;
    };
}; // namespace nn::sl

#endif