#pragma once

#include <wut.h>
#include <coreinit/time.h>
#include <nn/result.h>
#include <nn/sl/ISettingAccessor.h>
#include <nn/sl/ITimeAccessor.h>
#include <nn/sl/IUpdatePackageAccessor.h>
#include <nn/sl/details/ISerializerDetails.h>

#ifdef __cplusplus

namespace nn::sl
{
namespace details
{
typedef struct WUT_PACKED ConditionInternal
{
   ISettingAccessorInternal *settingAccessor;
   IUpdatePackageAccessorInternal *updatePackageAccessor;
   ISerializerInternal *previousSendingTimeSerializer;
   ITimeAccessorInternal *timeAccessor;
   void *vtable;
} ConditionInternal;
WUT_CHECK_SIZE(ConditionInternal, 0x14);
WUT_CHECK_OFFSET(ConditionInternal, 0x00, settingAccessor);
WUT_CHECK_OFFSET(ConditionInternal, 0x04, updatePackageAccessor);
WUT_CHECK_OFFSET(ConditionInternal, 0x08, previousSendingTimeSerializer);
WUT_CHECK_OFFSET(ConditionInternal, 0x0C, timeAccessor);
WUT_CHECK_OFFSET(ConditionInternal, 0x10, vtable);

extern "C" ConditionInternal *
__ct__Q3_2nn2sl9ConditionFv(ConditionInternal *);
extern "C" nn::Result
GetEnability__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
extern "C" nn::Result
StoreCurrentTimeAsPreviousSendingTime__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
extern "C" nn::Result
NeedsUpdate__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
extern "C" nn::Result
GetPreviousSendingTime__Q3_2nn2sl9ConditionCFPL(ConditionInternal *, int64_t *outTime);
extern "C" void
Initialize__Q3_2nn2sl9ConditionFRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl22IUpdatePackageAccessorRQ3_2nn2sl20ISerializer__tm__2_LRQ3_2nn2sl13ITimeAccessor(ConditionInternal *,
                                                                                                                                                        ISettingAccessorInternal *,
                                                                                                                                                        IUpdatePackageAccessorInternal *,
                                                                                                                                                        ISerializerInternal *,
                                                                                                                                                        ITimeAccessorInternal *);
} // namespace details

class Condition
{
public:
   Condition() :
      mSettingAccessor(nullptr),
      mUpdatePackageAccessor(nullptr),
      mPreviousSendingTimeSerializer(nullptr),
      mTimeAccessor(nullptr)
   {
      if (__ct__Q3_2nn2sl9ConditionFv(&mInstance) != nullptr) {
         mSettingAccessor               = details::SettingAccessorFromPtr(mInstance.settingAccessor);
         mUpdatePackageAccessor         = details::UpdatePackageAccessorFromPtr(mInstance.updatePackageAccessor);
         mPreviousSendingTimeSerializer = details::SerializerFromPtr<OSTime>(mInstance.previousSendingTimeSerializer);
         mTimeAccessor                  = details::TimeAccessorFromPtr(mInstance.timeAccessor);
      }
   }

   ~Condition() = default;

   [[nodiscard]] details::ISettingAccessorBase &
   GetSettingAccessor()
   {
      return mSettingAccessor;
   }

   [[nodiscard]] details::IUpdatePackageAccessorBase &
   GetUpdatePackageAccessor()
   {
      return mUpdatePackageAccessor;
   }

   [[nodiscard]] details::ISerializerBase<OSTime> &
   GetPreviousSendingTimeSerializer()
   {
      return mPreviousSendingTimeSerializer;
   }

   [[nodiscard]] details::ITimeAccessorBase &
   GetTimeAccessor()
   {
      return mTimeAccessor;
   }

   nn::Result
   GetEnability()
   {
      return GetEnability__Q3_2nn2sl9ConditionCFv(&mInstance);
   }

   nn::Result
   NeedsUpdate()
   {
      return NeedsUpdate__Q3_2nn2sl9ConditionCFv(&mInstance);
   }

   nn::Result
   StoreCurrentTimeAsPreviousSendingTime()
   {
      return StoreCurrentTimeAsPreviousSendingTime__Q3_2nn2sl9ConditionCFv(&mInstance);
   }

   nn::Result
   GetPreviousSendingTime(int64_t *outTime)
   {
      return GetPreviousSendingTime__Q3_2nn2sl9ConditionCFPL(&mInstance, outTime);
   }

   void
   Initialize(details::ISettingAccessorBase &settingAccessor,
              details::IUpdatePackageAccessorBase &updatePackageAccessor,
              details::ISerializerBase<OSTime> &previousSendingTimeSerializer,
              details::ITimeAccessorBase &timeAccessor)
   {
      Initialize__Q3_2nn2sl9ConditionFRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl22IUpdatePackageAccessorRQ3_2nn2sl20ISerializer__tm__2_LRQ3_2nn2sl13ITimeAccessor(
         &mInstance,
         settingAccessor.GetInternal(),
         updatePackageAccessor.GetInternal(),
         previousSendingTimeSerializer.GetInternal(),
         timeAccessor.GetInternal());
      mSettingAccessor               = details::SettingAccessorFromPtr(settingAccessor.GetInternal());
      mUpdatePackageAccessor         = details::UpdatePackageAccessorFromPtr(updatePackageAccessor.GetInternal());
      mPreviousSendingTimeSerializer = details::SerializerFromPtr<OSTime>(previousSendingTimeSerializer.GetInternal());
      mTimeAccessor                  = details::TimeAccessorFromPtr(timeAccessor.GetInternal());
   }

private:
   details::ConditionInternal mInstance = {};
   details::SettingAccessorFromPtr mSettingAccessor;
   details::UpdatePackageAccessorFromPtr mUpdatePackageAccessor;
   details::SerializerFromPtr<OSTime> mPreviousSendingTimeSerializer;
   details::TimeAccessorFromPtr mTimeAccessor;
};

} // namespace nn::sl

#endif
