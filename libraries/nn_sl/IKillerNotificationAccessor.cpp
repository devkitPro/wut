#include <nn/sl/IKillerNotificationAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IKillerNotificationAccessorInternal *
GetDefaultKillerNotificationAccessor__Q2_2nn2slFv();
}

static details::KillerNotificationAccessorFromPtr sDefaultKillerNotificationAccessor(GetDefaultKillerNotificationAccessor__Q2_2nn2slFv());

details::IKillerNotificationAccessorBase &
GetDefaultKillerNotificationAccessor()
{
   return sDefaultKillerNotificationAccessor;
}
} // namespace nn::sl