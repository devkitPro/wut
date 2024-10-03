#include <nn/sl/IDefaultTitleAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IDefaultTitleAccessorInternal *
GetDefaultDefaultTitleAccessor__Q2_2nn2slFv();
}

static details::DefaultTitleAccessorFromPtr sDefaultDefaultTitleAccessor(GetDefaultDefaultTitleAccessor__Q2_2nn2slFv());

details::IDefaultTitleAccessorBase &
GetDefaultDefaultTitleAccessor()
{
   return sDefaultDefaultTitleAccessor;
}

} // namespace nn::sl