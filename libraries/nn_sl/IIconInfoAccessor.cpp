#include <nn/sl/IIconInfoAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IIconInfoAccessorInternal *
GetDefaultIconInfoAccessor__Q2_2nn2slFv();
}

static details::IconInfoAccessorFromPtr sDefaultIconInfoAccessor(GetDefaultIconInfoAccessor__Q2_2nn2slFv());

details::IIconInfoAccessorBase &
GetDefaultIconInfoAccessor()
{
   return sDefaultIconInfoAccessor;
}

} // namespace nn::sl