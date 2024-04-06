#pragma once

#include "IconInfoAccessor.h"
#include "KillerNotification.h"
#include "LaunchInfoDatabase.h"
#include "SettingAccessor.h"
#include "TitleIconCache.h"
#include "sl_cpp.h"
#include <nn/result.h>
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
                mIconInfoAccessor    = IconInfoAccessorFromPtr(mInstance.iconInfoAccessor);
                mAccountInfoAccessor = AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
                mSettingAccessor     = SettingAccessorFromPtr(mInstance.settingInfoAccessor);
                mTitleIconCache      = TitleIconCacheFromPtr(mInstance.titleIconCache);
            }
        }

        [[nodiscard]] IIconInfoAccessor &getIconInfoAccessor() {
            return mIconInfoAccessor;
        }

        [[nodiscard]] IAccountInfoAccessor &getAccountInfoAccessor() {
            return mAccountInfoAccessor;
        }

        [[nodiscard]] ISettingAccessor &getSettingAccessor() {
            return mSettingAccessor;
        }

        [[nodiscard]] ITitleIconCache &getTitleIconCache() {
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

        void Initialize(IIconInfoAccessor &iconInfoAccessor, IAccountInfoAccessor &accountInfoAccessor, ISettingAccessor &settingAccessor, ITitleIconCache &titleIconCache) {
            details::Initialize__Q3_2nn2sl11DataCreatorFRQ3_2nn2sl17IIconInfoAccessorRQ3_2nn2sl20IAccountInfoAccessorRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl15ITitleIconCache(
                    &mInstance, iconInfoAccessor.GetInternal(), accountInfoAccessor.GetInternal(), settingAccessor.GetInternal(), titleIconCache.GetInternal());
            mIconInfoAccessor    = IconInfoAccessorFromPtr(mInstance.iconInfoAccessor);
            mAccountInfoAccessor = AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
            mSettingAccessor     = SettingAccessorFromPtr(mInstance.settingInfoAccessor);
            mTitleIconCache      = TitleIconCacheFromPtr(mInstance.titleIconCache);
        }

        ~DataCreator() = default;

    private:
        details::DataCreatorInternal mInstance = {};
        IconInfoAccessorFromPtr mIconInfoAccessor;
        AccountInfoAccessorFromPtr mAccountInfoAccessor;
        SettingAccessorFromPtr mSettingAccessor;
        TitleIconCacheFromPtr mTitleIconCache;
    };
}; // namespace nn::sl

#endif