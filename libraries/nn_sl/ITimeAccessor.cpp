#include <nn/sl/ITimeAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::ITimeAccessorInternal *
GetDefaultTimeAccessor__Q2_2nn2slFv();
}

static details::TimeAccessorFromPtr sDefaultTimeAccessor(GetDefaultTimeAccessor__Q2_2nn2slFv());

details::ITimeAccessorBase &
GetDefaultTimeAccessor()
{
   return sDefaultTimeAccessor;
}
} // namespace nn::sl