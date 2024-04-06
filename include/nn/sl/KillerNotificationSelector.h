#pragma once

#include "KillerNotification.h"
#include "KillerNotificationAccessor.h"
#include "KillerNotificationTransferRecordManager.h"
#include "LaunchedTitleListAccessor.h"
#include "TitleListCache.h"
#include "sl_cpp.h"
#include <nn/result.h>
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
                                       mKillerNotificationTransferRecordManager(nullptr)

        {
            if (__ct__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance) != nullptr) {
                mLaunchedTitleListAccessor               = LaunchedTitleListAccessorFromPtr(mInstance.launchedTitleListAccessor);
                mKillerNotificationAccessor              = KillerNotificationAccessorFromPtr(mInstance.killerNotificationAccessor);
                mTitleListCache                          = TitleListCacheFromPtr(mInstance.titleListCache);
                mKillerNotificationSerializer            = SerializerFromPtr<KillerNotification>(mInstance.killerNotificationSerializer);
                mSettingAccessor                         = SettingAccessorFromPtr(mInstance.settingsAccessor);
                mAccountInfoAccessor                     = AccountInfoAccessorFromPtr(mInstance.accountInfoAccessor);
                mTimeAccessor                            = TimeAccessorFromPtr(mInstance.timeAccessor);
                mKillerNotificationTransferRecordManager = KillerNotificationTransferRecordManagerFromPtr(mInstance.killerNotificationTransferRecordManager);
            }
        }

        ~KillerNotificationSelector() {
            __dt__Q3_2nn2sl26KillerNotificationSelectorFv(&mInstance, 2);
        }

        ILaunchedTitleListAccessor &GetLaunchedTitleListAccessor() {
            return mLaunchedTitleListAccessor;
        }

        IKillerNotificationAccessor &GetKillerNotificationAccessor() {
            return mKillerNotificationAccessor;
        }

        ITitleListCache &GetTitleListCache() {
            return mTitleListCache;
        }

        ISerializer<KillerNotification> &GetKillerNotificationSerializer() {
            return mKillerNotificationSerializer;
        }

        ISettingAccessor &GetSettingAccessor() {
            return mSettingAccessor;
        }

        IAccountInfoAccessor &GetAccountInfoAccessor() {
            return mAccountInfoAccessor;
        }

        ITimeAccessor &GetTimeAccessor() {
            return mTimeAccessor;
        }

        IKillerNotificationTransferRecordManager &GetKillerNotificationTransferRecordManager() {
            return mKillerNotificationTransferRecordManager;
        }

        nn::Result
        Select(KillerNotification *u1, TitleInfo *u2, bool *u3) {
            return Select__Q3_2nn2sl26KillerNotificationSelectorFPQ3_2nn2sl18KillerNotificationPQ3_2nn2sl9TitleInfoPb(&mInstance, u1, u2, u3);
        }

        void Initialize(ILaunchedTitleListAccessor &launchedTitleListAccessor,
                        IKillerNotificationAccessor &killerNotificationAccessor,
                        ITitleListCache &titleListCache,
                        ISerializer<KillerNotification> &killerNotificationSerializer,
                        ISettingAccessor &settingAccessor,
                        IAccountInfoAccessor &accountInfoAccessor,
                        ITimeAccessor &timeAccessor,
                        IKillerNotificationTransferRecordManager &killerNotificationTransferRecordManager) {
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

            mLaunchedTitleListAccessor               = LaunchedTitleListAccessorFromPtr(launchedTitleListAccessor.GetInternal());
            mKillerNotificationAccessor              = KillerNotificationAccessorFromPtr(killerNotificationAccessor.GetInternal());
            mTitleListCache                          = TitleListCacheFromPtr(titleListCache.GetInternal());
            mKillerNotificationSerializer            = SerializerFromPtr<KillerNotification>(killerNotificationSerializer.GetInternal());
            mSettingAccessor                         = SettingAccessorFromPtr(settingAccessor.GetInternal());
            mAccountInfoAccessor                     = AccountInfoAccessorFromPtr(accountInfoAccessor.GetInternal());
            mTimeAccessor                            = TimeAccessorFromPtr(timeAccessor.GetInternal());
            mKillerNotificationTransferRecordManager = KillerNotificationTransferRecordManagerFromPtr(killerNotificationTransferRecordManager.GetInternal());
        }

    private:
        details::KillerNotificationSelectorInternal mInstance = {};

        LaunchedTitleListAccessorFromPtr mLaunchedTitleListAccessor;
        KillerNotificationAccessorFromPtr mKillerNotificationAccessor;
        TitleListCacheFromPtr mTitleListCache;
        SerializerFromPtr<KillerNotification> mKillerNotificationSerializer;
        SettingAccessorFromPtr mSettingAccessor;
        AccountInfoAccessorFromPtr mAccountInfoAccessor;
        TimeAccessorFromPtr mTimeAccessor;
        KillerNotificationTransferRecordManagerFromPtr mKillerNotificationTransferRecordManager;
    };
} // namespace nn::sl

#endif