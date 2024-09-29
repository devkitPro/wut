#pragma once
#include <wut.h>
#include <nn/result.h>
#include <nsysnet/netconfig.h>

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
 * The configuration for a given network profile.
 * \sa NetConfCfg
 */
using Config = NetConfCfg;

enum Status {
    STATUS_FAILED     = -1,
    STATUS_OK         = 0,
    STATUS_PROCESSING = 1,
};

/**
* C++ linkage for the autoconnect API, see \link nn::ac \endlink for use.
 * Cafe provides mangled symbols for C++ APIs, so nn::ac is actually static
 * inline calls to the mangled symbols under nn::ac::detail.
 */
namespace detail
{
extern "C"
{

nn::Result Close__Q2_2nn2acFv();
nn::Result CloseAll__Q2_2nn2acFv();
nn::Result Connect__Q2_2nn2acFPC16netconf_profile_(const Config *cfg);
nn::Result Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);
nn::Result Connect__Q2_2nn2acFv();
nn::Result ConnectAsync__Q2_2nn2acFPC16netconf_profile_(const Config *cfg);
nn::Result ConnectAsync__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);
nn::Result ConnectAsync__Q2_2nn2acFv();
void       Finalize__Q2_2nn2acFv();
nn::Result GetAssignedAddress__Q2_2nn2acFPUl(uint32_t *ip);
nn::Result GetCloseStatus__Q2_2nn2acFPQ3_2nn2ac6Status();
nn::Result GetCompatId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(ConfigIdNum *id);
nn::Result GetConnectResult__Q2_2nn2acFPQ2_2nn6Result(nn::Result *result);
nn::Result GetConnectStatus__Q2_2nn2acFPQ3_2nn2ac6Status(Status *status);
nn::Result GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(ConfigIdNum *id);
nn::Result Initialize__Q2_2nn2acFv();
nn::Result IsApplicationConnected__Q2_2nn2acFPb(bool *connected);
nn::Result IsConfigExisting__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumPb(ConfigIdNum id, bool *existing);
nn::Result ReadConfig__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumP16netconf_profile_(ConfigIdNum id, Config *cfg);
nn::Result SetCompatId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);
nn::Result SetStartupId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(ConfigIdNum id);

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
SetStartupId(ConfigIdNum id)
{
   return detail::SetStartupId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
GetCompatId(ConfigIdNum *id)
{
   return detail::GetCompatId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
SetCompatId(ConfigIdNum id)
{
   return detail::SetCompatId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
Connect()
{
   return detail::Connect__Q2_2nn2acFv();
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

static inline nn::Result
Connect(const Config *cfg)
{
   return detail::Connect__Q2_2nn2acFPC16netconf_profile_(cfg);
}

static inline nn::Result
ConnectAsync()
{
   return detail::ConnectAsync__Q2_2nn2acFv();
}

static inline nn::Result
ConnectAsync(ConfigIdNum id)
{
   return detail::ConnectAsync__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum(id);
}

static inline nn::Result
ConnectAsync(const Config *cfg)
{
   return detail::ConnectAsync__Q2_2nn2acFPC16netconf_profile_(cfg);
}

static inline nn::Result
GetConnectStatus(Status *status)
{
   return detail::GetConnectStatus__Q2_2nn2acFPQ3_2nn2ac6Status(&status_num);
}

static inline nn::Result
GetConnectResult(nn::Result *result)
{
   return detail::GetConnectResult__Q2_2nn2acFPQ2_2nn6Result(result);
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

static inline nn::Result
CloseAll()
{
   return detail::CloseAll__Q2_2nn2acFv();
}


static inline nn::Result
IsApplicationConnected(bool *connected)
{
   return detail::IsApplicationConnected__Q2_2nn2acFPb(connected);
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

static inline nn::Result
IsConfigExisting(ConfigIdNum id, bool *existing)
{
   return detail::IsConfigExisting__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumPb(id, existing);
}

static inline nn::Result
ReadConfig(ConfigIdNum id, Config *cfg)
{
   return detail::ReadConfig__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumP16netconf_profile_(id, cfg);
}

} // namespace ac
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
