#include <nn/sl/KillerNotificationTransferRecordManager.h>

namespace nn::sl {
    namespace {
        extern "C" details::IKillerNotificationTransferRecordManagerInternal *GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv();
    }

    static KillerNotificationTransferRecordManagerFromPtr sDefaultKillerNotificationTransferRecordManager(GetDefaultKillerNotificationTransferRecordManager__Q2_2nn2slFv());

    IKillerNotificationTransferRecordManager &GetDefaultKillerNotificationTransferRecordManager() {
        return sDefaultKillerNotificationTransferRecordManager;
    }
} // namespace nn::sl