#pragma once

#ifdef __cplusplus

#include <nn/sl/details/IIconInfoAccessorDetails.h>
#include <nn/sl/details/ISerializerDetails.h>
#include <nn/sl/details/ISettingAccessorDetails.h>
#include <nn/sl/details/ITitleIconCacheDetails.h>

namespace nn::sl
{

namespace details
{
typedef struct WUT_PACKED TitleIconCacheInternal
{
   void *vtable;
   uint32_t num;
   void *cachedIconsBuffer;
   IIconInfoAccessorInternal *iconInfoAccessor;
   ISerializerInternal *iconInfoSerializer;
   ISettingAccessorInternal *settingAccessor;
} TitleIconCacheInternal;
WUT_CHECK_SIZE(TitleIconCacheInternal, 0x18);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x00, vtable);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x04, num);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x08, cachedIconsBuffer);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x0C, iconInfoAccessor);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x10, iconInfoSerializer);
WUT_CHECK_OFFSET(TitleIconCacheInternal, 0x14, settingAccessor);

extern "C" ITitleIconCacheInternal *
__ct__Q3_2nn2sl14TitleIconCacheFv(TitleIconCacheInternal *);
extern "C" ITitleIconCacheInternal *
__dt__Q3_2nn2sl14TitleIconCacheFv(TitleIconCacheInternal *, int);
extern "C" void
Initialize__Q3_2nn2sl14TitleIconCacheFi(TitleIconCacheInternal *, int);
extern "C" void
Initialize__Q3_2nn2sl14TitleIconCacheFiRQ3_2nn2sl17IIconInfoAccessorRQ3_2nn2sl38ISerializer__tm__19_Q3_2nn2sl8IconInfoRQ3_2nn2sl16ISettingAccessor(
   TitleIconCacheInternal *,
   int,
   IIconInfoAccessorInternal *,
   ISerializerInternal *,
   ISettingAccessorInternal *);
extern "C" void
Finalize__Q3_2nn2sl14TitleIconCacheFv(TitleIconCacheInternal *);
extern "C" void
Get__Q3_2nn2sl14TitleIconCacheCFPQ3_2nn2sl8IconInfoi(TitleIconCacheInternal *, nn::sl::IconInfo *iconInfos, int num);
extern "C" nn::Result
Load__Q3_2nn2sl14TitleIconCacheFv(TitleIconCacheInternal *);
extern "C" nn::Result
Update__Q3_2nn2sl14TitleIconCacheFPCQ3_2nn2sl9TitleInfoi(TitleIconCacheInternal *, nn::sl ::TitleInfo *, int);
extern "C" nn::Result
Store__Q3_2nn2sl14TitleIconCacheCFv(TitleIconCacheInternal *);
} // namespace details

class TitleIconCache : public details::ITitleIconCacheBase
{
public:
   TitleIconCache()
   {
      details::__ct__Q3_2nn2sl14TitleIconCacheFv(&mInstance);
   }
   ~TitleIconCache() override
   {
      __dt__Q3_2nn2sl14TitleIconCacheFv(&mInstance, 2);
   }

   void
   Initialize(int cacheSize)
   {
      Initialize__Q3_2nn2sl14TitleIconCacheFi(&mInstance, cacheSize);
   }

   void
   Initialize(int cacheSize,
              details::IIconInfoAccessorBase &iconInfoAccessor,
              details::ISerializerBase<nn::sl::IconInfo> &iconInfoSerializer,
              details::ISettingAccessorBase &settingAccessor)
   {
      Initialize__Q3_2nn2sl14TitleIconCacheFiRQ3_2nn2sl17IIconInfoAccessorRQ3_2nn2sl38ISerializer__tm__19_Q3_2nn2sl8IconInfoRQ3_2nn2sl16ISettingAccessor(
         &mInstance,
         cacheSize,
         iconInfoAccessor.GetInternal(),
         iconInfoSerializer.GetInternal(),
         settingAccessor.GetInternal());
   }

   void
   Finalize(int cacheSize)
   {
      Finalize__Q3_2nn2sl14TitleIconCacheFv(&mInstance);
   }

   void
   Get(nn::sl::IconInfo *iconInfos, int num) const override
   {
      return Get__Q3_2nn2sl14TitleIconCacheCFPQ3_2nn2sl8IconInfoi((details::TitleIconCacheInternal *)&mInstance, iconInfos, num);
   }

   nn::Result
   Load() override
   {
      return Load__Q3_2nn2sl14TitleIconCacheFv(&mInstance);
   }

   nn::Result
   Update(nn::sl::TitleInfo *titleInfos, int num) override
   {
      return Update__Q3_2nn2sl14TitleIconCacheFPCQ3_2nn2sl9TitleInfoi(&mInstance, titleInfos, num);
   }

   nn::Result
   Store() override
   {
      return Store__Q3_2nn2sl14TitleIconCacheCFv(&mInstance);
   }

private:
   details::ITitleIconCacheInternal *
   GetInternal() override
   {
      return reinterpret_cast<details::ITitleIconCacheInternal *>(&mInstance);
   }

   details::TitleIconCacheInternal mInstance{};
};

} // namespace nn::sl

#endif