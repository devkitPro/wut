#include <nn/sl/ITitleListAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::ITitleListAccessorInternal *
GetDefaultTitleListAccessor__Q2_2nn2slFv();
}

static details::TitleListAccessorFromPtr sDefaultTitleListAccessor(GetDefaultTitleListAccessor__Q2_2nn2slFv());

details::ITitleListAccessorBase &
GetDefaultTitleListAccessor()
{
   return sDefaultTitleListAccessor;
}

} // namespace nn::sl