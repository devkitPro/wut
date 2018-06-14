#pragma once
#include <wut.h>
#include <nn/result.h>

/**
 * \defgroup nn_ac_cpp Auto Connect C++ API
 * \ingroup nn_ac
 * @{
 */

#ifdef __cplusplus

namespace nn
{
namespace ac
{

typedef uint32_t ConfigIdNum;

namespace detail
{
extern "C"
{

nn::Result Initialize__Q2_2nn2acFv();
void Finalize__Q2_2nn2acFv();
nn::Result GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(ConfigIdNum *id);
nn::Result Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);
nn::Result GetAssignedAddress__Q2_2nn2acFPUl(uint32_t *ip);

} // extern "C"
} // namespace detail

static inline nn::Result
Initialize()
{
   return detail::Initialize__Q2_2nn2acFv();
}

static inline void
Finalize()
{
   return detail::Finalize__Q2_2nn2acFv();
}

static inline nn::Result
GetStartupId(ConfigIdNum *id)
{
   return detail::GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
Connect(ConfigIdNum id)
{
   return detail::Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
GetAssignedAddress(uint32_t *ip)
{
   return detail::GetAssignedAddress__Q2_2nn2acFPUl(ip);
}

} // namespace ac
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
