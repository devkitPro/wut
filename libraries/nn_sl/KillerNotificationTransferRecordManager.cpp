#include <nn/sl/KillerNotificationTransferRecordManager.h>

namespace nn::sl {
    namespace {
        extern "C" details::IKillerNotificationTransferRecordManagerInternal *GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv();
    }

    static details::KillerNotificationTransferRecordManagerFromPtr sDefaultKillerNotificationTransferRecordManager(GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv());

    details::IKillerNotificationTransferRecordManagerBase &GetDefaultKillerNotificationTransferRecordManager() {
        return sDefaultKillerNotificationTransferRecordManager;
    }
} // namespace nn::sl