#pragma once

#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    namespace details {
        typedef struct WUT_PACKED ConditionInternal {
            void *settingAccessor;
            void *updatePackageAccessor;
            void *previousSendingTimeSerializer;
            void *timeAccessor;
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
    } // namespace details

    class Condition {
    public:
        Condition() {
            __ct__Q3_2nn2sl9ConditionFv(&mInstance);
        }

        ~Condition() = default;

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

    private:
        details::ConditionInternal mInstance = {};
    };

} // namespace nn::sl
#endif
