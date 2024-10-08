#include <nn/sl/ISettingAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::ISettingAccessorInternal *
GetDefaultSettingAccessor__Q2_2nn2slFv();
}

static details::SettingAccessorFromPtr sDefaultSettingAccessor(GetDefaultSettingAccessor__Q2_2nn2slFv());

details::ISettingAccessorBase &
GetDefaultSettingAccessor()
{
   return sDefaultSettingAccessor;
}
} // namespace nn::sl