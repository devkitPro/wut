#pragma once
#include <wut.h>
#include <nn/result.h>

/**
 * \defgroup nn_ac_cpp Auto Connect C++ API
 * \ingroup nn_ac
 * C++ functions for the Auto Connect API (see nn::ac)
 * @{
 */

#ifdef __cplusplus

namespace nn
{
/**
 * Auto Connect API, used for managing and connecting to internet connection
 * profiles.
 */
namespace ac
{

/**
 * An ID number representing a network configuration. These are the same IDs as
 * shown in System Settings' Connection List.
 */
typedef uint32_t ConfigIdNum;

/**
 * C++ linkage for the autoconnect API, see \link nn::ac \endlink for use.
 * Cafe provides mangled symbols for C++ APIs, so nn::ac is actually static
 * inline calls to the mangled symbols under nn::ac::detail.
 */
namespace detail
{
extern "C"
{

nn::Result Initialize__Q2_2nn2acFv();
void Finalize__Q2_2nn2acFv();
nn::Result Connect__Q2_2nn2acFv();
nn::Result ConnectAsync__Q2_2nn2acFv();
nn::Result Close__Q2_2nn2acFv();
nn::Result GetCloseStatus__Q2_2nn2acFPQ3_2nn2ac6Status();
nn::Result GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(ConfigIdNum *id);
nn::Result Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);
nn::Result GetAssignedAddress__Q2_2nn2acFPUl(uint32_t *ip);

} // extern "C"
} // namespace detail

/**
 * Initialise the Auto Connect library. Call this function before any other nn::ac
 * functions.
 *
 * \return
 * A \link nn::Result Result\endlink - see \link nn::Result::IsSuccess \endlink
 * and \link nn::Result::IsFailure \endlink.
 *
 * \sa
 * - \link Finalize \endlink
 */
static inline nn::Result
Initialize()
{
   return detail::Initialize__Q2_2nn2acFv();
}

/**
 * Cleanup the Auto Connect library. Do not call any nn::ac functions (other
 * than \link Initialize \endlink) after calling this function.
 *
 * \sa
 * - \link Initialize \endlink
 */
static inline void
Finalize()
{
   return detail::Finalize__Q2_2nn2acFv();
}


/**
 * Gets the default connection configuration id. This is the default as marked
 * in System Settings.
 *
 * \param id
 * A pointer to an \link ConfigIdNum \endlink to write the config ID to. Must
 * not be a \c nullptr.
 *
 * \return
 * A \link nn::Result Result\endlink - see \link nn::Result::IsSuccess \endlink
 * and \link nn::Result::IsFailure \endlink.
 */
static inline nn::Result
GetStartupId(ConfigIdNum *id)
{
   return detail::GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
Connect()
{
   return detail::Connect__Q2_2nn2acFv();
}

static inline nn::Result
ConnectAsync()
{
   return detail::ConnectAsync__Q2_2nn2acFv();
}

static inline nn::Result
Close()
{
   return detail::Close__Q2_2nn2acFv();
}

static inline nn::Result
GetCloseStatus()
{
   return detail::GetCloseStatus__Q2_2nn2acFPQ3_2nn2ac6Status();
}

/**
 * Connects to a network, using the configuration represented by the given
 * \link ConfigIdNum \endlink.
 *
 * \param id
 * The \link ConfigIdNum \endlink representing the network to connect to.
 *
 * \return
 * A \link nn::Result Result\endlink - see \link nn::Result::IsSuccess \endlink
 * and \link nn::Result::IsFailure \endlink.
 */
static inline nn::Result
Connect(ConfigIdNum id)
{
   return detail::Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(id);
}

/**
 * Gets the IP address assosciated with the currently active connection.
 *
 * \param ip
 * A pointer to write the IP address to, in
 * <a href="https://en.wikipedia.org/wiki/IPv4#Address_representations"
 * target="_blank">numerical</a> form.
 *
 * \return
 * A \link nn::Result Result\endlink - see \link nn::Result::IsSuccess \endlink
 * and \link nn::Result::IsFailure \endlink.
 */
static inline nn::Result
GetAssignedAddress(uint32_t *ip)
{
   return detail::GetAssignedAddress__Q2_2nn2acFPUl(ip);
}

} // namespace ac
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
