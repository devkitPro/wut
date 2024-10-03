#include <nn/sl/IInstalledTitleListAccessor.h>

namespace nn::sl
{
namespace
{
extern "C" details::IInstalledTitleListAccessorInternal *
GetDefaultInstalledTitleListAccessor__Q2_2nn2slFv();
}

static details::InstalledTitleListAccessorFromPtr sDefaultInstalledTitleListAccessor(GetDefaultInstalledTitleListAccessor__Q2_2nn2slFv());

details::IInstalledTitleListAccessorBase &
GetDefaultInstalledTitleListAccessor()
{
   return sDefaultInstalledTitleListAccessor;
}

} // namespace nn::sl