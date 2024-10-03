#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/IBlackListAccessor.h>
#include <nn/sl/IDefaultTitleAccessor.h>
#include <nn/sl/IPreferentialTitleAccessor.h>
#include <nn/sl/ISettingAccessor.h>
#include <nn/sl/IWhiteListAccessor.h>
#include <nn/sl/TitleListCache.h>

#ifdef __cplusplus

namespace nn::sl
{
namespace details
{
typedef struct WUT_PACKED QuickStartApplicationSelectorInternal
{
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

extern "C" QuickStartApplicationSelectorInternal *
__ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(QuickStartApplicationSelectorInternal *);
extern "C" nn::Result
Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(QuickStartApplicationSelectorInternal *, nn::sl::TitleInfo *, int);
extern "C" void
Initialize__Q3_2nn2sl29QuickStartApplicationSelectorFRQ3_2nn2sl26IPreferentialTitleAccessorRQ3_2nn2sl21IDefaultTitleAccessorRQ3_2nn2sl18IWhiteListAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl18IBlackListAccessor(
   QuickStartApplicationSelectorInternal *,
   IPreferentialTitleAccessorInternal *,
   IDefaultTitleAccessorInternal *,
   IWhiteListAccessorInternal *,
   ITitleListCacheInternal *,
   ISettingAccessorInternal *,
   details::IBlackListAccessorInternal *);
} // namespace details

class QuickStartApplicationSelector
{
public:
   QuickStartApplicationSelector() :
      mPreferentialTitleAccessorFromPtr(nullptr),
      mDefaultTitleAccessorFromPtr(nullptr),
      mWhiteListAccessorFromPtr(nullptr),
      mTitleListCacheFromPtr(nullptr),
      mSettingAccessorFromPtr(nullptr),
      mBlackListAccessorFromPtr(nullptr)
   {
      if (__ct__Q3_2nn2sl29QuickStartApplicationSelectorFv(&mInstance) != nullptr) {
         mPreferentialTitleAccessorFromPtr = details::PreferentialTitleAccessorFromPtr(mInstance.preferentialTitleAccessor);
         mDefaultTitleAccessorFromPtr      = details::DefaultTitleAccessorFromPtr(mInstance.defaultTitleAccessor);
         mWhiteListAccessorFromPtr         = details::WhiteListAccessorFromPtr(mInstance.whiteListAccessor);
         mTitleListCacheFromPtr            = TitleListCacheFromPtr(mInstance.titleListCache);
         mSettingAccessorFromPtr           = details::SettingAccessorFromPtr(mInstance.settingsAccessor);
         mBlackListAccessorFromPtr         = details::BlackListAccessorFromPtr(mInstance.blackListAccessor);
      }
   }

   ~QuickStartApplicationSelector() = default;

   details::IPreferentialTitleAccessorBase &
   GetPreferentialTitleAccessor()
   {
      return mPreferentialTitleAccessorFromPtr;
   }

   details::IDefaultTitleAccessorBase &
   GetDefaultTitleAccessor()
   {
      return mDefaultTitleAccessorFromPtr;
   }

   details::IWhiteListAccessorBase &
   GetWhiteListAccessor()
   {
      return mWhiteListAccessorFromPtr;
   }

   details::ITitleListCacheBase &
   GetTitleListCache()
   {
      return mTitleListCacheFromPtr;
   }

   details::ISettingAccessorBase &
   GetSettingAccessor()
   {
      return mSettingAccessorFromPtr;
   }

   details::IBlackListAccessorBase &
   GetBlackListAccessor()
   {
      return mBlackListAccessorFromPtr;
   }

   nn::Result
   Select(nn::sl::TitleInfo *titleInfos, int num)
   {
      return Select__Q3_2nn2sl29QuickStartApplicationSelectorFPQ3_2nn2sl9TitleInfoi(&mInstance, titleInfos, num);
   }

   void
   Initialize(details::IPreferentialTitleAccessorBase &preferentialTitleAccessor,
              details::IDefaultTitleAccessorBase &defaultTitleAccessor,
              details::IWhiteListAccessorBase &whiteListAccessor,
              details::ITitleListCacheBase &titleListCache,
              details::ISettingAccessorBase &settingAccessor,
              details::IBlackListAccessorBase &blackListAccessor)
   {
      Initialize__Q3_2nn2sl29QuickStartApplicationSelectorFRQ3_2nn2sl26IPreferentialTitleAccessorRQ3_2nn2sl21IDefaultTitleAccessorRQ3_2nn2sl18IWhiteListAccessorRQ3_2nn2sl14TitleListCacheRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl18IBlackListAccessor(
         &mInstance,
         preferentialTitleAccessor.GetInternal(),
         defaultTitleAccessor.GetInternal(),
         whiteListAccessor.GetInternal(),
         titleListCache.GetInternal(),
         settingAccessor.GetInternal(),
         blackListAccessor.GetInternal());
      mPreferentialTitleAccessorFromPtr = details::PreferentialTitleAccessorFromPtr(preferentialTitleAccessor.GetInternal());
      mDefaultTitleAccessorFromPtr      = details::DefaultTitleAccessorFromPtr(defaultTitleAccessor.GetInternal());
      mWhiteListAccessorFromPtr         = details::WhiteListAccessorFromPtr(whiteListAccessor.GetInternal());
      mTitleListCacheFromPtr            = TitleListCacheFromPtr(titleListCache.GetInternal());
      mSettingAccessorFromPtr           = details::SettingAccessorFromPtr(settingAccessor.GetInternal());
      mBlackListAccessorFromPtr         = details::BlackListAccessorFromPtr(blackListAccessor.GetInternal());
   }

private:
   details::QuickStartApplicationSelectorInternal mInstance = {};
   details::PreferentialTitleAccessorFromPtr mPreferentialTitleAccessorFromPtr;
   details::DefaultTitleAccessorFromPtr mDefaultTitleAccessorFromPtr;
   details::WhiteListAccessorFromPtr mWhiteListAccessorFromPtr;
   TitleListCacheFromPtr mTitleListCacheFromPtr;
   details::SettingAccessorFromPtr mSettingAccessorFromPtr;
   details::BlackListAccessorFromPtr mBlackListAccessorFromPtr;
};
} // namespace nn::sl

#endif