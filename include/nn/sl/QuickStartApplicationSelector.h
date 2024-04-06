#pragma once

#include "BlackListAccessor.h"
#include "WhiteListAccessor.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED QuickStartApplicationSelectorInternal {
            IPreferentialTitleAccessorInternal *preferentialTitleAccessor;
            IDefaultTitleAccessorInternal *defaultTitleAccessor;
            IWhiteListAccessorInternal *whiteListAccessor;
            ITitleListCacheInternal *titleListCache;
            ISettingAccessorInternal *settingsAccessor;
            IBlackListAccessorInternal *blackListAccessor;
            void *vtable;
        } QuickStartApplicationSelectorInternal;
        WUT_CHECK_SIZE(QuickStartApplicationSelectorInternal, 0x1C);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x00, preferentialTitleAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x04, defaultTitleAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x08, whiteListAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x0C, titleListCache);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x10, settingsAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x14, blackListAccessor);
        WUT_CHECK_OFFSET(QuickStartApplicationSelectorInternal, 0x18, vtable);

        extern "C" QuickStartApplicationSelectorInternal *__ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(QuickStartApplicationSelectorInternal *);
        extern "C" nn::Result Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(QuickStartApplicationSelectorInternal *, TitleInfo *, int);
        extern "C" void Initialize__Q3_2nn2sl29QuickStartApplicationSelectorFRQ3_2nn2sl26IPreferentialTitleAccessorRQ3_2nn2sl21IDefaultTitleAccessorRQ3_2nn2sl18IWhiteListAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl18IBlackListAccessor(
                QuickStartApplicationSelectorInternal *,
                IPreferentialTitleAccessorInternal *,
                IDefaultTitleAccessorInternal *,
                IWhiteListAccessorInternal *,
                ITitleListCacheInternal *,
                ISettingAccessorInternal *,
                IBlackListAccessorInternal *);
    } // namespace details

    class QuickStartApplicationSelector {
    public:
        QuickStartApplicationSelector() : mPreferentialTitleAccessorFromPtr(nullptr),
                                          mDefaultTitleAccessorFromPtr(nullptr),
                                          mWhiteListAccessorFromPtr(nullptr),
                                          mTitleListCacheFromPtr(nullptr),
                                          mSettingAccessorFromPtr(nullptr),
                                          mBlackListAccessorFromPtr(nullptr) {
            if (__ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(&mInstance) != nullptr) {
                mPreferentialTitleAccessorFromPtr = PreferentialTitleAccessorFromPtr(mInstance.preferentialTitleAccessor);
                mDefaultTitleAccessorFromPtr      = DefaultTitleAccessorFromPtr(mInstance.defaultTitleAccessor);
                mWhiteListAccessorFromPtr         = WhiteListAccessorFromPtr(mInstance.whiteListAccessor);
                mTitleListCacheFromPtr            = TitleListCacheFromPtr(mInstance.titleListCache);
                mSettingAccessorFromPtr           = SettingAccessorFromPtr(mInstance.settingsAccessor);
                mBlackListAccessorFromPtr         = BlackListAccessorFromPtr(mInstance.blackListAccessor);
            }
        }

        ~QuickStartApplicationSelector() = default;

        nn::Result Select(TitleInfo *u1, int u2) {
            return Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(&mInstance, u1, u2);
        }

        void Initialize(IPreferentialTitleAccessor &preferentialTitleAccessor,
                        IDefaultTitleAccessor &defaultTitleAccessor,
                        IWhiteListAccessor &whiteListAccessor,
                        ITitleListCache &titleListCache,
                        ISettingAccessor &settingAccessor,
                        IBlackListAccessor &blackListAccessor) {
            Initialize__Q3_2nn2sl29QuickStartApplicationSelectorFRQ3_2nn2sl26IPreferentialTitleAccessorRQ3_2nn2sl21IDefaultTitleAccessorRQ3_2nn2sl18IWhiteListAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl18IBlackListAccessor(
                    &mInstance,
                    preferentialTitleAccessor.GetInternal(),
                    defaultTitleAccessor.GetInternal(),
                    whiteListAccessor.GetInternal(),
                    titleListCache.GetInternal(),
                    settingAccessor.GetInternal(),
                    blackListAccessor.GetInternal());
            mPreferentialTitleAccessorFromPtr = PreferentialTitleAccessorFromPtr(preferentialTitleAccessor.GetInternal());
            mDefaultTitleAccessorFromPtr      = DefaultTitleAccessorFromPtr(defaultTitleAccessor.GetInternal());
            mWhiteListAccessorFromPtr         = WhiteListAccessorFromPtr(whiteListAccessor.GetInternal());
            mTitleListCacheFromPtr            = TitleListCacheFromPtr(titleListCache.GetInternal());
            mSettingAccessorFromPtr           = SettingAccessorFromPtr(settingAccessor.GetInternal());
            mBlackListAccessorFromPtr         = BlackListAccessorFromPtr(blackListAccessor.GetInternal());
        }

    private:
        details::QuickStartApplicationSelectorInternal mInstance = {};
        PreferentialTitleAccessorFromPtr mPreferentialTitleAccessorFromPtr;
        DefaultTitleAccessorFromPtr mDefaultTitleAccessorFromPtr;
        WhiteListAccessorFromPtr mWhiteListAccessorFromPtr;
        TitleListCacheFromPtr mTitleListCacheFromPtr;
        SettingAccessorFromPtr mSettingAccessorFromPtr;
        BlackListAccessorFromPtr mBlackListAccessorFromPtr;
    };
} // namespace nn::sl

#endif