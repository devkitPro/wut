#include <nn/sl/IPreferentialTitleAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IPreferentialTitleAccessorInternal *
GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv();
}

static details::PreferentialTitleAccessorFromPtr sDefaultPreferentialTitleAccessor(GetDefaultPreferentialTitleAccessor__Q2_2nn2slFv());

details::IPreferentialTitleAccessorBase &
GetDefaultPreferentialTitleAccessor()
{
   return sDefaultPreferentialTitleAccessor;
}

} // namespace nn::sl
