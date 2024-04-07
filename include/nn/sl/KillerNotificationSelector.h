#pragma once

#include <nn/result.h>
#include <nn/sl/IAccountInfoAccessor.h>
#include <nn/sl/IKillerNotificationAccessor.h>
#include <nn/sl/ILaunchedTitleListAccessor.h>
#include <nn/sl/ISerializer.h>
#include <nn/sl/ISettingAccessor.h>
#include <nn/sl/ITimeAccessor.h>
#include <nn/sl/KillerNotification.h>
#include <nn/sl/KillerNotificationTransferRecordManager.h>
#include <nn/sl/TitleListCache.h>
#include <nn/sl/sl_cpp.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED KillerNotificationSelectorInternal {
            ILaunchedTitleListAccessorInternal *launchedTitleListAccessor;
            IKillerNotificationAccessorInternal *killerNotificationAccessor;
            ITitleListCacheInternal *titleListCache;
            ISerializerInternal *killerNotificationSerializer;
            ISettingAccessorInternal *settingsAccessor;
            IAccountInfoAccessorInternal *accountInfoAccessor;
            ITimeAccessorInternal *timeAccessor;
            IKillerNotificationTransferRecordManagerInternal *killerNotificationTransferRecordManager;
            void *vtable;
        } KillerNotificationSelectorInternal;
        WUT_CHECK_SIZE(KillerNotificationSelectorInternal, 0x24);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x00, launchedTitleListAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x04, killerNotificationAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x08, titleListCache);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x0C, killerNotificationSerializer);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x10, settingsAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x14, accountInfoAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x18, timeAccessor);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x1C, killerNotificationTransferRecordManager);
        WUT_CHECK_OFFSET(KillerNotificationSelectorInternal, 0x20, vtable);

        extern "C" KillerNotificationSelectorInternal *__ct__Q3_2nn2sl26KillerNotificationSelectorFv(KillerNotificationSelectorInternal *);
        extern "C" void __dt__Q3_2nn2sl26KillerNotificationSelectorFv(KillerNotificationSelectorInternal *, int);
        extern "C" nn::Result Select__Q3_2nn2sl26KillerNotificationSelectorFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfoPb(KillerNotificationSelectorInternal *, KillerNotification *, TitleInfo *, bool *);
        extern "C" void Initialize__Q3_2nn2sl26KillerNotificationSelectorFRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IKillerNotificationAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl49ISerializer__tm__30_Q3_2nn2sl18KillerNotificationRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl20IAccountInfoAccessorRQ3_2nn2sl13ITimeAccessorRQ3_2nn2sl40IKillerNotificationTransferRecordManager(
                KillerNotificationSelectorInternal *,
                ILaunchedTitleListAccessorInternal *,
                IKillerNotificationAccessorInternal *,
                ITitleListCacheInternal *,
                ISerializerInternal *,
                ISettingAccessorInternal *,
                IAccountInfoAccessorInternal *,
                ITimeAccessorInternal *,
                IKillerNotificationTransferRecordManagerInternal *);
    } // namespace details

    class KillerNotificationSelector {
    public:
        KillerNotificationSelector() : mLaunchedTitleListAccessor(nullptr),
                                       mKillerNotificationAccessor(nullptr),
                                       mTitleListCache(nullptr),
                                       mKillerNotificationSerializer(nullptr),
                                       mSettingAccessor(nullptr),
                                       mAccountInfoAccessor(nullptr),
                                       mTimeAccessor(nullptr),
                                       mKillerNotificationTransferRecordManager(nullptr) {
            if (__ct__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance) != nullptr) {
                mLaunchedTitleListAccessor               = details::LaunchedTitleListAccessorFromPtr(mInstance.launchedTitleListAccessor);
                mKillerNotificationAccessor              = details::KillerNotificationAccessorFromPtr(mInstance.killerNotificationAccessor);
                mTitleListCache                          = TitleListCacheFromPtr(mInstance.titleListCache);
                mKillerNotificationSerializer            = details::SerializerFromPtr<KillerNotification>(mInstance.killerNotificationSerializer);
                mSettingAccessor                         = details::SettingAccessorFromPtr(mInstance.settingsAccessor);
                mAccountInfoAccessor                     = details::AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
                mTimeAccessor                            = details::TimeAccessorFromPtr(mInstance.timeAccessor);
                mKillerNotificationTransferRecordManager = details::KillerNotificationTransferRecordManagerFromPtr(mInstance.killerNotificationTransferRecordManager);
            }
        }

        ~KillerNotificationSelector() {
            __dt__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance, 2);
        }

        details::ILaunchedTitleListAccessorBase &GetLaunchedTitleListAccessor() {
            return mLaunchedTitleListAccessor;
        }

        details::IKillerNotificationAccessorBase &GetKillerNotificationAccessor() {
            return mKillerNotificationAccessor;
        }

        details::ITitleListCacheBase &GetTitleListCache() {
            return mTitleListCache;
        }

        details::ISerializerBase<KillerNotification> &GetKillerNotificationSerializer() {
            return mKillerNotificationSerializer;
        }

        details::ISettingAccessorBase &GetSettingAccessor() {
            return mSettingAccessor;
        }

        details::IAccountInfoAccessorBase &GetAccountInfoAccessor() {
            return mAccountInfoAccessor;
        }

        details::ITimeAccessorBase &GetTimeAccessor() {
            return mTimeAccessor;
        }

        details::IKillerNotificationTransferRecordManagerBase &GetKillerNotificationTransferRecordManager() {
            return mKillerNotificationTransferRecordManager;
        }

        nn::Result Select(KillerNotification *outKillerNotification, TitleInfo *outKillerNotificationTitle, bool *u1) {
            return Select__Q3_2nn2sl26KillerNotificationSelectorFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfoPb(&mInstance, outKillerNotification, outKillerNotificationTitle, u1);
        }

        void Initialize(details::ILaunchedTitleListAccessorBase &launchedTitleListAccessor,
                        details::IKillerNotificationAccessorBase &killerNotificationAccessor,
                        details::ITitleListCacheBase &titleListCache,
                        details::ISerializerBase<KillerNotification> &killerNotificationSerializer,
                        details::ISettingAccessorBase &settingAccessor,
                        details::IAccountInfoAccessorBase &accountInfoAccessor,
                        details::ITimeAccessorBase &timeAccessor,
                        details::IKillerNotificationTransferRecordManagerBase &killerNotificationTransferRecordManager) {
            Initialize__Q3_2nn2sl26KillerNotificationSelectorFRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IKillerNotificationAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl49ISerializer__tm__30_Q3_2nn2sl18KillerNotificationRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl20IAccountInfoAccessorRQ3_2nn2sl13ITimeAccessorRQ3_2nn2sl40IKillerNotificationTransferRecordManager(
                    &mInstance,
                    launchedTitleListAccessor.GetInternal(),
                    killerNotificationAccessor.GetInternal(),
                    titleListCache.GetInternal(),
                    killerNotificationSerializer.GetInternal(),
                    settingAccessor.GetInternal(),
                    accountInfoAccessor.GetInternal(),
                    timeAccessor.GetInternal(),
                    killerNotificationTransferRecordManager.GetInternal());

            mLaunchedTitleListAccessor               = details::LaunchedTitleListAccessorFromPtr(launchedTitleListAccessor.GetInternal());
            mKillerNotificationAccessor              = details::KillerNotificationAccessorFromPtr(killerNotificationAccessor.GetInternal());
            mTitleListCache                          = TitleListCacheFromPtr(titleListCache.GetInternal());
            mKillerNotificationSerializer            = details::SerializerFromPtr<KillerNotification>(killerNotificationSerializer.GetInternal());
            mSettingAccessor                         = details::SettingAccessorFromPtr(settingAccessor.GetInternal());
            mAccountInfoAccessor                     = details::AccountInfoAccessorFromPtr(accountInfoAccessor.GetInternal());
            mTimeAccessor                            = details::TimeAccessorFromPtr(timeAccessor.GetInternal());
            mKillerNotificationTransferRecordManager = details::KillerNotificationTransferRecordManagerFromPtr(killerNotificationTransferRecordManager.GetInternal());
        }

    private:
        details::KillerNotificationSelectorInternal mInstance = {};

        details::LaunchedTitleListAccessorFromPtr mLaunchedTitleListAccessor;
        details::KillerNotificationAccessorFromPtr mKillerNotificationAccessor;
        TitleListCacheFromPtr mTitleListCache;
        details::SerializerFromPtr<KillerNotification> mKillerNotificationSerializer;
        details::SettingAccessorFromPtr mSettingAccessor;
        details::AccountInfoAccessorFromPtr mAccountInfoAccessor;
        details::TimeAccessorFromPtr mTimeAccessor;
        details::KillerNotificationTransferRecordManagerFromPtr mKillerNotificationTransferRecordManager;
    };
} // namespace nn::sl

#endif