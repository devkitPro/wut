#include <nn/sl/IMetaInfoAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IMetaInfoAccessorInternal *
GetDefaultMetaInfoAccessor__Q2_2nn2slFv();
}

static details::MetaInfoAccessorFromPtr sDefaultMetaInfoAccessor(GetDefaultMetaInfoAccessor__Q2_2nn2slFv());

details::IMetaInfoAccessorBase &
GetDefaultMetaInfoAccessor()
{
   return sDefaultMetaInfoAccessor;
}

} // namespace nn::sl