#pragma once

#include "KillerNotification.h"
#include "Transferrer.h"
#include "sl_cpp.h"
#include <nn/result.h>
#include <wut.h>

#ifdef __cplusplus

namespace nn::sl {

    namespace details {
        typedef struct WUT_PACKED DrcManagerInternal {
            ITransferrerInternal *drcTransferrer;
            ISettingAccessorInternal *settingsAccessor;
            ITimeAccessorInternal *timeAccessor;
            void *vtable;
        } DrcManagerInternal;
        WUT_CHECK_SIZE(DrcManagerInternal, 0x10);
        WUT_CHECK_OFFSET(DrcManagerInternal, 0x00, drcTransferrer);
        WUT_CHECK_OFFSET(DrcManagerInternal, 0x04, settingsAccessor);
        WUT_CHECK_OFFSET(DrcManagerInternal, 0x08, timeAccessor);
        WUT_CHECK_OFFSET(DrcManagerInternal, 0x0C, vtable);

        extern "C" DrcManagerInternal *__ct__Q3_2nn2sl10DrcManagerFv(DrcManagerInternal *);
        extern "C" nn::Result CancelTransfer__Q3_2nn2sl10DrcManagerFv(DrcManagerInternal *);
        extern "C" nn::Result PushNotification__Q3_2nn2sl10DrcManagerFPbPCQ3_2nn2sl18KillerNotificationbT3L(DrcManagerInternal *, bool *, const KillerNotification *, bool, bool, uint64_t);
        extern "C" nn::Result Transfer__Q3_2nn2sl10DrcManagerFRCQ3_2nn2sl16TransferableInfobQ4_2nn2sl12ITransferrer12TransferMode(DrcManagerInternal *, TransferableInfo *, bool, TransferMode);

        extern "C" nn::Result Initialize__Q3_2nn2sl10DrcManagerFRQ3_2nn2sl12ITransferrerRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl13ITimeAccessor(
                DrcManagerInternal *, ITransferrerInternal *, ISettingAccessorInternal *, ITimeAccessorInternal *);
    } // namespace details
    class DrcManager {
    public:
        DrcManager() : mTransferrer(nullptr),
                       mSettingAccessor(nullptr),
                       mTimeAccessor(nullptr) {
            if (__ct__Q3_2nn2sl10DrcManagerFv(&mInstance) != nullptr) {
                mTransferrer     = TransferrerFromPtr(mInstance.drcTransferrer);
                mSettingAccessor = SettingAccessorFromPtr(mInstance.settingsAccessor);
                mTimeAccessor    = TimeAccessorFromPtr(mInstance.timeAccessor);
            }
        }

        ~DrcManager() = default;

        ITransferrer &GetTransferrer() {
            return mTransferrer;
        }

        ISettingAccessor &GetSettingAccessor() {
            return mSettingAccessor;
        }

        ITimeAccessor &GetTimeAccessor() {
            return mTimeAccessor;
        }

        nn::Result CancelTransfer() {
            return CancelTransfer__Q3_2nn2sl10DrcManagerFv(&mInstance);
        }

        nn::Result PushNotification(bool *u1, const KillerNotification *u2, bool u3, bool u4, uint64_t u5) {
            return PushNotification__Q3_2nn2sl10DrcManagerFPbPCQ3_2nn2sl18KillerNotificationbT3L(&mInstance, u1, u2, u3, u4, u5);
        }

        nn::Result Transfer(TransferableInfo *u1, bool u2, TransferMode u3) {
            return Transfer__Q3_2nn2sl10DrcManagerFRCQ3_2nn2sl16TransferableInfobQ4_2nn2sl12ITransferrer12TransferMode(&mInstance, u1, u2, u3);
        }

        void Initialize(ITransferrer &transferrer, ISettingAccessor &settingAccessor, ITimeAccessor &timeAccessor) {
            Initialize__Q3_2nn2sl10DrcManagerFRQ3_2nn2sl12ITransferrerRQ3_2nn2sl16ISettingAccessorRQ3_2nn2sl13ITimeAccessor(
                    &mInstance,
                    transferrer.GetInternal(),
                    settingAccessor.GetInternal(),
                    timeAccessor.GetInternal());
        }

    private:
        details::DrcManagerInternal mInstance = {};

        TransferrerFromPtr mTransferrer;
        SettingAccessorFromPtr mSettingAccessor;
        TimeAccessorFromPtr mTimeAccessor;
    };
} // namespace nn::sl

#endif