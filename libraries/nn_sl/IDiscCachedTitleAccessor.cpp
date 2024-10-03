#include <nn/sl/IDiscCachedTitleAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IDiscCachedTitleAccessorInternal *
GetDefaultDiscCachedTitleAccessor__Q2_2nn2slFv();
}

static details::DiscCachedTitleAccessorFromPtr sDefaultDiscCachedTitleListAccessor(GetDefaultDiscCachedTitleAccessor__Q2_2nn2slFv());

details::IDiscCachedTitleAccessorBase &
GetDefaultDiscCachedTitleAccessor()
{
   return sDefaultDiscCachedTitleListAccessor;
}

} // namespace nn::sl