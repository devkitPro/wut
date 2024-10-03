#include <nn/sl/IAccountInfoAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IAccountInfoAccessorInternal *
GetDefaultAccountInfoAccessor__Q2_2nn2slFv();
}

static details::AccountInfoAccessorFromPtr gAccountInfoAccessor(GetDefaultAccountInfoAccessor__Q2_2nn2slFv());

details::IAccountInfoAccessorBase &
GetDefaultAccountInfoAccessor()
{
   return gAccountInfoAccessor;
}
} // namespace nn::sl