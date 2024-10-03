#include <nn/sl/KillerNotificationTransferRecordStream.h>

namespace nn::sl
{
namespace
{
extern "C" details::KillerNotificationTransferRecordStreamInternal *
GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv();
}

static KillerNotificationTransferRecordStream sDefaultKillerNotificationTransferRecordStream(GetDefaultKillerNotificationTransferRecordStream__Q2_2nn2slFv());

nn::sl::details::IStreamBase &
GetDefaultKillerNotificationTransferRecordStream()
{
   return sDefaultKillerNotificationTransferRecordStream;
}
} // namespace nn::sl