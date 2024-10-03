#pragma once

#include <wut.h>
#include <nn/result.h>
#include <nn/sl/IDiscCachedTitleAccessor.h>
#include <nn/sl/IInstalledTitleListAccessor.h>
#include <nn/sl/ILaunchedTitleListAccessor.h>
#include <nn/sl/IMetaInfoAccessor.h>
#include <nn/sl/ISerializer.h>
#include <nn/sl/ITimeAccessor.h>
#include <nn/sl/ITitleListAccessor.h>

#ifdef __cplusplus

namespace nn::sl
{
class QuickStartApplicationSelector;
class KillerNotificationSelector;
namespace details
{
typedef struct WUT_PACKED ITitleListCacheInternal
{
   ITitleListAccessorInternal *titleListAccessor;
   ILaunchedTitleListAccessorInternal *launchedTitleListAccessor;
   IInstalledTitleListAccessorInternal *installedTitleListAccessor;
   IDiscCachedTitleAccessorInternal *discCachedTitleAccessor;
   ISerializerInternal *titleInfoSerializer;
   ITimeAccessorInternal *timeAccessor;
   IMetaInfoAccessorInternal *metaInfoAccessor;
   WUT_UNKNOWN_BYTES(0x18);
   void *vtable;
} TitleListCacheInternal;
WUT_CHECK_SIZE(ITitleListCacheInternal, 0x38);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x00, titleListAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x04, launchedTitleListAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x08, installedTitleListAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x0C, discCachedTitleAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x10, titleInfoSerializer);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x14, timeAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x18, metaInfoAccessor);
WUT_CHECK_OFFSET(ITitleListCacheInternal, 0x34, vtable);

extern "C" ITitleListCacheInternal *
__ct__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" void
Finalize__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" nn::Result
Load__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" nn::Result
Update__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" nn::Result
UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" nn::Result
Store__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" nn::Result
Initialize__Q3_2nn2sl14TitleListCacheFiT1(ITitleListCacheInternal *, int, int);
extern "C" void
Finalize__Q3_2nn2sl14TitleListCacheFv(ITitleListCacheInternal *);
extern "C" void
Initialize__Q3_2nn2sl14TitleListCacheFiN21(
   ITitleListCacheInternal *,
   int,
   int,
   int);
extern "C" void
Initialize__Q3_2nn2sl14TitleListCacheFiT1RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfo(
   ITitleListCacheInternal *,
   int,
   int,
   ITitleListAccessorInternal *,
   ILaunchedTitleListAccessorInternal *,
   IInstalledTitleListAccessorInternal *,
   IDiscCachedTitleAccessorInternal *,
   ISerializerInternal *);
extern "C" void
Initialize__Q3_2nn2sl14TitleListCacheFiN21RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfo(
   ITitleListCacheInternal *,
   int,
   int,
   int,
   ITitleListAccessorInternal *,
   ILaunchedTitleListAccessorInternal *,
   IInstalledTitleListAccessorInternal *,
   IDiscCachedTitleAccessorInternal *,
   ISerializerInternal *);
extern "C" void
Initialize__Q3_2nn2sl14TitleListCacheFiN21RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfoRQ3_2nn2sl13ITimeAccessorRQ3_2nn2sl17IMetaInfoAccessor(
   ITitleListCacheInternal *,
   int,
   int,
   int,
   ITitleListAccessorInternal *,
   ILaunchedTitleListAccessorInternal *,
   IInstalledTitleListAccessorInternal *,
   IDiscCachedTitleAccessorInternal *,
   ISerializerInternal *,
   ITimeAccessorInternal *,
   IMetaInfoAccessorInternal *);

class ITitleListCacheBase
{
   friend class nn::sl::QuickStartApplicationSelector;
   friend class nn::sl::KillerNotificationSelector;

public:
   virtual ~ITitleListCacheBase() = default;
   virtual nn::Result
   Load() = 0;
   virtual nn::Result
   Update() = 0;
   virtual nn::Result
   UpdateIfNeeded() = 0;
   virtual nn::Result
   Store() = 0;

private:
   virtual details::ITitleListCacheInternal *
   GetInternal() = 0;
};

} // namespace details

class TitleListCache final : public details::ITitleListCacheBase
{
public:
   TitleListCache() :
      mTitleListAccessor(nullptr),
      mLaunchedTitleListAccessor(nullptr),
      mInstalledTitleListAccessor(nullptr),
      mDiscCachedTitleAccessor(nullptr),
      mTitleInfoSerializer(nullptr),
      mTimeAccessor(nullptr),
      mMetaInfoAccessor(nullptr)
   {
      if (__ct__Q3_2nn2sl14TitleListCacheFv(&mInstance) != nullptr) {
         mTitleListAccessor          = details::TitleListAccessorFromPtr(mInstance.titleListAccessor);
         mLaunchedTitleListAccessor  = details::LaunchedTitleListAccessorFromPtr(mInstance.launchedTitleListAccessor);
         mInstalledTitleListAccessor = details::InstalledTitleListAccessorFromPtr(mInstance.installedTitleListAccessor);
         mDiscCachedTitleAccessor    = details::DiscCachedTitleAccessorFromPtr(mInstance.discCachedTitleAccessor);
         mTitleInfoSerializer        = details::SerializerFromPtr<nn::sl::TitleInfo>(mInstance.titleInfoSerializer);
         mTimeAccessor               = details::TimeAccessorFromPtr(mInstance.timeAccessor);
         mMetaInfoAccessor           = details::MetaInfoAccessorFromPtr(mInstance.metaInfoAccessor);
      }
   }

   ~TitleListCache() override
   {
      Finalize__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

   details::ITitleListAccessorBase &
   GetTitleListAccessor()
   {
      return mTitleListAccessor;
   }

   details::ILaunchedTitleListAccessorBase &
   GetLaunchedTitleListAccessor()
   {
      return mLaunchedTitleListAccessor;
   }

   details::IInstalledTitleListAccessorBase &
   GetInstalledTitleListAccessor()
   {
      return mInstalledTitleListAccessor;
   }

   details::IDiscCachedTitleAccessorBase &
   GetDiscCachedTitleAccessor()
   {
      return mDiscCachedTitleAccessor;
   }

   details::ISerializerBase<nn::sl::TitleInfo> &
   GetTitleInfoSerializer()
   {
      return mTitleInfoSerializer;
   }

   details::ITimeAccessorBase &
   GetTimeAccessor()
   {
      return mTimeAccessor;
   }

   details::IMetaInfoAccessorBase &
   GetMetaInfoAccessor()
   {
      return mMetaInfoAccessor;
   }

   void
   Initialize(int u1, int num)
   {
      Initialize__Q3_2nn2sl14TitleListCacheFiT1(&mInstance, u1, num);
   }

   void
   Initialize(int u1, int num, int u3)
   {
      Initialize__Q3_2nn2sl14TitleListCacheFiN21(&mInstance, u1, num, u3);
   }

   void
   Initialize(int u1, int num, int u3, details::ITitleListAccessorBase &titleListAccessor, details::ILaunchedTitleListAccessorBase &launchedTitleListAccessor, details::IInstalledTitleListAccessorBase &installedTitleListAccessor, details::IDiscCachedTitleAccessorBase &discCachedTitleAccessor, details::ISerializerBase<nn::sl::TitleInfo> &titleInfoSerializer)
   {
      Initialize__Q3_2nn2sl14TitleListCacheFiN21RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfo(
         &mInstance, u1, num, u3,
         titleListAccessor.GetInternal(),
         launchedTitleListAccessor.GetInternal(),
         installedTitleListAccessor.GetInternal(),
         discCachedTitleAccessor.GetInternal(),
         titleInfoSerializer.GetInternal());
      mTitleListAccessor          = details::TitleListAccessorFromPtr(titleListAccessor.GetInternal());
      mLaunchedTitleListAccessor  = details::LaunchedTitleListAccessorFromPtr(launchedTitleListAccessor.GetInternal());
      mInstalledTitleListAccessor = details::InstalledTitleListAccessorFromPtr(installedTitleListAccessor.GetInternal());
      mDiscCachedTitleAccessor    = details::DiscCachedTitleAccessorFromPtr(discCachedTitleAccessor.GetInternal());
      mTitleInfoSerializer        = details::SerializerFromPtr<nn::sl::TitleInfo>(titleInfoSerializer.GetInternal());
      mTimeAccessor               = details::TimeAccessorFromPtr(mInstance.timeAccessor);
      mMetaInfoAccessor           = details::MetaInfoAccessorFromPtr(mInstance.metaInfoAccessor);
   }

   void
   Initialize(int u1, int num, details::ITitleListAccessorBase &titleListAccessor, details::ILaunchedTitleListAccessorBase &launchedTitleListAccessor, details::IInstalledTitleListAccessorBase &installedTitleListAccessor, details::IDiscCachedTitleAccessorBase &discCachedTitleAccessor, details::ISerializerBase<nn::sl::TitleInfo> &titleInfoSerializer)
   {
      Initialize__Q3_2nn2sl14TitleListCacheFiT1RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfo(
         &mInstance, u1, num,
         titleListAccessor.GetInternal(),
         launchedTitleListAccessor.GetInternal(),
         installedTitleListAccessor.GetInternal(),
         discCachedTitleAccessor.GetInternal(),
         titleInfoSerializer.GetInternal());
      mTitleListAccessor          = details::TitleListAccessorFromPtr(titleListAccessor.GetInternal());
      mLaunchedTitleListAccessor  = details::LaunchedTitleListAccessorFromPtr(launchedTitleListAccessor.GetInternal());
      mInstalledTitleListAccessor = details::InstalledTitleListAccessorFromPtr(installedTitleListAccessor.GetInternal());
      mDiscCachedTitleAccessor    = details::DiscCachedTitleAccessorFromPtr(discCachedTitleAccessor.GetInternal());
      mTitleInfoSerializer        = details::SerializerFromPtr<nn::sl::TitleInfo>(titleInfoSerializer.GetInternal());
      mTimeAccessor               = details::TimeAccessorFromPtr(mInstance.timeAccessor);
      mMetaInfoAccessor           = details::MetaInfoAccessorFromPtr(mInstance.metaInfoAccessor);
   }

   void
   Initialize(int u1, int u2, int u3, details::ITitleListAccessorBase &titleListAccessor, details::ILaunchedTitleListAccessorBase &launchedTitleListAccessor, details::IInstalledTitleListAccessorBase &installedTitleListAccessor, details::IDiscCachedTitleAccessorBase &discCachedTitleAccessor, details::ISerializerBase<nn::sl::TitleInfo> &titleInfoSerializer, details::ITimeAccessorBase &timeAccessor, details::IMetaInfoAccessorBase &metaInfoAccessor)
   {

      Initialize__Q3_2nn2sl14TitleListCacheFiN21RQ3_2nn2sl18ITitleListAccessorRQ3_2nn2sl26ILaunchedTitleListAccessorRQ3_2nn2sl27IInstalledTitleListAccessorRQ3_2nn2sl24IDiscCachedTitleAccessorRQ3_2nn2sl39ISerializer__tm__20_Q3_2nn2sl9TitleInfoRQ3_2nn2sl13ITimeAccessorRQ3_2nn2sl17IMetaInfoAccessor(
         &mInstance, u1, u2, u3,
         titleListAccessor.GetInternal(),
         launchedTitleListAccessor.GetInternal(),
         installedTitleListAccessor.GetInternal(),
         discCachedTitleAccessor.GetInternal(),
         titleInfoSerializer.GetInternal(),
         timeAccessor.GetInternal(),
         metaInfoAccessor.GetInternal());
      mTitleListAccessor          = details::TitleListAccessorFromPtr(titleListAccessor.GetInternal());
      mLaunchedTitleListAccessor  = details::LaunchedTitleListAccessorFromPtr(launchedTitleListAccessor.GetInternal());
      mInstalledTitleListAccessor = details::InstalledTitleListAccessorFromPtr(installedTitleListAccessor.GetInternal());
      mDiscCachedTitleAccessor    = details::DiscCachedTitleAccessorFromPtr(discCachedTitleAccessor.GetInternal());
      mTitleInfoSerializer        = details::SerializerFromPtr<nn::sl::TitleInfo>(titleInfoSerializer.GetInternal());
      mTimeAccessor               = details::TimeAccessorFromPtr(timeAccessor.GetInternal());
      mMetaInfoAccessor           = details::MetaInfoAccessorFromPtr(metaInfoAccessor.GetInternal());
   }

   void
   Finalize()
   {
      return Finalize__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

   nn::Result
   Load() override
   {
      return Load__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

   nn::Result
   Update() override
   {
      return Update__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

   nn::Result
   UpdateIfNeeded() override
   {
      return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

   nn::Result
   Store() override
   {
      return Store__Q3_2nn2sl14TitleListCacheFv(&mInstance);
   }

private:
   details::ITitleListCacheInternal *
   GetInternal() override
   {
      return &mInstance;
   }
   details::ITitleListCacheInternal mInstance = {};

   details::TitleListAccessorFromPtr mTitleListAccessor;
   details::LaunchedTitleListAccessorFromPtr mLaunchedTitleListAccessor;
   details::InstalledTitleListAccessorFromPtr mInstalledTitleListAccessor;
   details::DiscCachedTitleAccessorFromPtr mDiscCachedTitleAccessor;
   details::SerializerFromPtr<nn::sl::TitleInfo> mTitleInfoSerializer;
   details::TimeAccessorFromPtr mTimeAccessor;
   details::MetaInfoAccessorFromPtr mMetaInfoAccessor;
};

class TitleListCacheFromPtr final : public details::ITitleListCacheBase
{

public:
   explicit TitleListCacheFromPtr(details::ITitleListCacheInternal *ptr) :
      mPtrInstance(ptr)
   {
   }
   ~TitleListCacheFromPtr() override = default;

   nn::Result
   Load() override
   {
      return Load__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
   }

   nn::Result
   Update() override
   {
      return Update__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
   }

   nn::Result
   UpdateIfNeeded() override
   {
      return UpdateIfNeeded__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
   }

   nn::Result
   Store() override
   {
      return Store__Q3_2nn2sl14TitleListCacheFv(mPtrInstance);
   }

private:
   details::ITitleListCacheInternal *
   GetInternal() override
   {
      return mPtrInstance;
   }

   details::ITitleListCacheInternal *mPtrInstance = {};
};

details::ITitleListCacheBase &
GetDefaultTitleListCache();
} // namespace nn::sl

#endif