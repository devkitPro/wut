#pragma once

#include <nn/result.h>
#include <nn/sl/KillerNotification.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {
    struct KillerNotification;
    namespace details {
        extern "C" nn::Result __CPR81__CheckEmptyValue__Q3_2nn2sl18KillerNotificationSFPbPCQ3_2nn2slJ26J(bool *u1, const KillerNotification *u2);
        extern "C" void __CPR76__GetEmptyValue__Q3_2nn2sl18KillerNotificationSFPQ3_2nn2slJ24J(KillerNotification *u1);
    } // namespace details
    struct WUT_PACKED KillerNotification {
        WUT_UNKNOWN_BYTES(0xae768);

        static nn::Result CheckEmptyValue(bool *u1, const KillerNotification *u2) {
            return details::__CPR81__CheckEmptyValue__Q3_2nn2sl18KillerNotificationSFPbPCQ3_2nn2slJ26J(u1, u2);
        }

        static void GetEmptyValue(KillerNotification *u1) {
            return details::__CPR76__GetEmptyValue__Q3_2nn2sl18KillerNotificationSFPQ3_2nn2slJ24J(u1);
        }
    };
    WUT_CHECK_SIZE(KillerNotification, 0xae768);

} // namespace nn::sl

#endif