#include <nn/sl/ISerializer.h>
#include <nn/sl/sl_cpp.h>

namespace nn::sl
{
namespace
{
extern "C" details::ISerializerInternal *
GetDefaultIconInfoSerializer__Q2_2nn2slFv();
extern "C" details::ISerializerInternal *
GetDefaultQuickStartTitleInfoSerializer__Q2_2nn2slFv();
extern "C" details::ISerializerInternal *
GetDefaultKillerNotificationSerializer__Q2_2nn2slFv();
extern "C" details::ISerializerInternal *
GetDefaultJumpTitleInfoSerializer__Q2_2nn2slFv();
extern "C" details::ISerializerInternal *
GetDefaultPreviousSendingTimeSerializer__Q2_2nn2slFv();
} // namespace

static details::SerializerFromPtr<nn::sl::IconInfo> sDefaultIconInfoSerializer(GetDefaultIconInfoSerializer__Q2_2nn2slFv());
static details::SerializerFromPtr<nn::sl::TitleInfo> sDefaultQuickStartTitleInfoSerializer(GetDefaultQuickStartTitleInfoSerializer__Q2_2nn2slFv());
static details::SerializerFromPtr<nn::sl::KillerNotification> sDefaultKillerNotificationSerializer(GetDefaultKillerNotificationSerializer__Q2_2nn2slFv());
static details::SerializerFromPtr<nn::sl::TitleInfo> sDefaultJumpTitleInfoSerializer(GetDefaultJumpTitleInfoSerializer__Q2_2nn2slFv());
static details::SerializerFromPtr<OSTime> sDefaultPreviousSendingTimeSerializer(GetDefaultPreviousSendingTimeSerializer__Q2_2nn2slFv());

details::ISerializerBase<nn::sl::IconInfo> &
GetDefaultIconInfoSerializer()
{
   return sDefaultIconInfoSerializer;
}

details::ISerializerBase<nn::sl::TitleInfo> &
GetDefaultQuickStartTitleInfoSerializer()
{
   return sDefaultQuickStartTitleInfoSerializer;
}

details::ISerializerBase<nn::sl::KillerNotification> &
GetDefaultKillerNotificationSerializer()
{
   return sDefaultKillerNotificationSerializer;
}

details::ISerializerBase<nn::sl::TitleInfo> &
GetDefaultJumpTitleInfoSerializer()
{
   return sDefaultJumpTitleInfoSerializer;
}

details::ISerializerBase<OSTime> &
GetDefaultPreviousSendingTimeSerializer()
{
   return sDefaultPreviousSendingTimeSerializer;
}
} // namespace nn::sl