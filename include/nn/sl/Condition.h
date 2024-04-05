#pragma once

#include "IUpdatePackageAccessor.h"
#include "SettingAccessor.h"
#include "TimeAccessor.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED ConditionInternal {
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

        extern "C" ConditionInternal *__ct__Q3_2nn2sl9ConditionFv(ConditionInternal *);
        extern "C" nn::Result GetEnability__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
        extern "C" nn::Result StoreCurrentTimeAsPreviousSendingTime__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
        extern "C" nn::Result NeedsUpdate__Q3_2nn2sl9ConditionCFv(ConditionInternal *);
        extern "C" nn::Result GetPreviousSendingTime__Q3_2nn2sl9ConditionCFPL(ConditionInternal *, uint32_t *outTime);
        extern "C" void Initialize__Q3_2nn2sl9ConditionFRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl22IUpdatePackageAccessorRQ3_2nn2sl20ISerializer__tm__2_LRQ3_2nn2sl13ITimeAccessor(ConditionInternal *,
                                                                                                                                                                                ISettingAccessorInternal *,
                                                                                                                                                                                IUpdatePackageAccessorInternal *,
                                                                                                                                                                                ISerializerInternal *,
                                                                                                                                                                                ITimeAccessorInternal *);
    } // namespace details

    class Condition {
    public:
        Condition() : mSettingAccesor(nullptr),
                      mUpdatePackageAccessor(nullptr),
                      mPreviousSendingTimeSerializer(nullptr),
                      mTimeAccessor(nullptr) {
            if (__ct__Q3_2nn2sl9ConditionFv(&mInstance) != nullptr) {
                mSettingAccesor                = SettingAccessorFromPtr(mInstance.settingAccessor);
                mUpdatePackageAccessor         = UpdatePackageAccessorFromPtr(mInstance.updatePackageAccessor);
                mPreviousSendingTimeSerializer = SerializerFromPtr<OSTime>(mInstance.previousSendingTimeSerializer);
                mTimeAccessor                  = TimeAccessorFromPtr(mInstance.timeAccessor);
            }
        }

        ~Condition() = default;

        [[nodiscard]] ISettingAccessor &GetSettingAccessor() {
            return mSettingAccesor;
        }

        [[nodiscard]] IUpdatePackageAccessor &GetUpdatePackageAccessor() {
            return mUpdatePackageAccessor;
        }

        [[nodiscard]] ISerializer<OSTime> &GetPreviousSendingTimeSerializer() {
            return mPreviousSendingTimeSerializer;
        }

        [[nodiscard]] ITimeAccessor &GetTimeAccessor() {
            return mTimeAccessor;
        }

        nn::Result GetEnability() {
            return GetEnability__Q3_2nn2sl9ConditionCFv(&mInstance);
        }

        nn::Result NeedsUpdate() {
            return NeedsUpdate__Q3_2nn2sl9ConditionCFv(&mInstance);
        }

        nn::Result StoreCurrentTimeAsPreviousSendingTime() {
            return StoreCurrentTimeAsPreviousSendingTime__Q3_2nn2sl9ConditionCFv(&mInstance);
        }

        nn::Result GetPreviousSendingTime(uint32_t *outTime) {
            return GetPreviousSendingTime__Q3_2nn2sl9ConditionCFPL(&mInstance, outTime);
        }

        void Initialize(ISettingAccessor &settingAccessor, IUpdatePackageAccessor &updatePackageAccessor, ISerializer<OSTime> &previousSendingTimeSerializer, ITimeAccessor &timeAccessor) {
            Initialize__Q3_2nn2sl9ConditionFRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl22IUpdatePackageAccessorRQ3_2nn2sl20ISerializer__tm__2_LRQ3_2nn2sl13ITimeAccessor(
                    &mInstance,
                    settingAccessor.GetInternal(),
                    updatePackageAccessor.GetInternal(),
                    previousSendingTimeSerializer.GetInternal(),
                    timeAccessor.GetInternal());
            mSettingAccesor                = SettingAccessorFromPtr(settingAccessor.GetInternal());
            mUpdatePackageAccessor         = UpdatePackageAccessorFromPtr(updatePackageAccessor.GetInternal());
            mPreviousSendingTimeSerializer = SerializerFromPtr<OSTime>(previousSendingTimeSerializer.GetInternal());
            mTimeAccessor                  = TimeAccessorFromPtr(timeAccessor.GetInternal());
        }

    private:
        details::ConditionInternal mInstance = {};
        SettingAccessorFromPtr mSettingAccesor;
        UpdatePackageAccessorFromPtr mUpdatePackageAccessor;
        SerializerFromPtr<OSTime> mPreviousSendingTimeSerializer;
        TimeAccessorFromPtr mTimeAccessor;
    };

} // namespace nn::sl

#endif
