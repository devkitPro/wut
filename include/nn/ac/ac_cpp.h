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
using ConfigIdNum = uint32_t;

/**
 * The configuration for a given network profile (from 1 to 6).
 * \sa NetConfCfg
 */
using Config = NetConfCfg;

using ErrorCode = uint32_t;

enum Status {
   STATUS_FAILED     = -1,
   STATUS_OK         =  0,
   STATUS_PROCESSING =  1,
};


nn::Result
BeginLocalConnection(bool unknown)
   asm("BeginLocalConnection__Q2_2nn2acFb");

void
ClearConfig(Config *cfg)
   asm("ClearConfig__Q2_2nn2acFP16netconf_profile_");

nn::Result
Close()
   asm("Close__Q2_2nn2acFv");

nn::Result
CloseAll()
   asm("CloseAll__Q2_2nn2acFv");

nn::Result
Connect(const Config *cfg)
   asm("Connect__Q2_2nn2acFPC16netconf_profile_");

nn::Result
Connect(ConfigIdNum id)
   asm("Connect__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum");

nn::Result
Connect()
   asm("Connect__Q2_2nn2acFv");

nn::Result
ConnectAsync(const Config *cfg)
   asm("ConnectAsync__Q2_2nn2acFPC16netconf_profile_");

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
nn::Result
ConnectAsync(ConfigIdNum id)
   asm("ConnectAsync__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum");

nn::Result
ConnectAsync()
   asm("ConnectAsync__Q2_2nn2acFv");

nn::Result
ConnectWithRetry()
   asm("ConnectWithRetry__Q2_2nn2acFv");

nn::Result
DeleteConfig(ConfigIdNum id)
   asm("DeleteConfig__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum");

nn::Result
EndLocalConnection()
   asm("EndLocalConnection__Q2_2nn2acFv");

/**
 * Cleans up the Auto Connect library. Do not call any nn::ac functions (other
 * than \link Initialize \endlink) after calling this function.
 *
 * \sa
 * - \link Initialize \endlink
 */
void
Finalize()
   asm("Finalize__Q2_2nn2acFv");

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
nn::Result
GetAssignedAddress(uint32_t *ip)
   asm("GetAssignedAddress__Q2_2nn2acFPUl");

nn::Result
GetAssignedAlternativeDns(uint32_t *ip)
   asm("GetAssignedAlternativeDns__Q2_2nn2acFPUl");

nn::Result
GetAssignedGateway(uint32_t *ip)
   asm("GetAssignedGateway__Q2_2nn2acFPUl");

nn::Result
GetAssignedPreferedDns(uint32_t *ip)
   asm("GetAssignedPreferedDns__Q2_2nn2acFPUl");

nn::Result
GetAssignedSubnet(uint32_t *ip)
   asm("GetAssignedSubnet__Q2_2nn2acFPUl");

nn::Result
GetCloseStatus(Status *status)
   asm("GetCloseStatus__Q2_2nn2acFPQ3_2nn2ac6Status");

nn::Result
GetCompatId(ConfigIdNum *id)
   asm("GetCompatId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum");

nn::Result
GetConnectResult(nn::Result *result)
   asm("GetConnectResult__Q2_2nn2acFPQ2_2nn6Result");

nn::Result
GetConnectStatus(Status *status)
   asm("GetConnectStatus__Q2_2nn2acFPQ3_2nn2ac6Status");

nn::Result
GetLastErrorCode(ErrorCode *error)
   asm("GetLastErrorCode__Q2_2nn2acFPUi");

nn::Result
GetRunningConfig(Config *cfg)
   asm("GetRunningConfig__Q2_2nn2acFP16netconf_profile_");

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
nn::Result
GetStartupId(ConfigIdNum *id)
   asm("GetStartupId__Q2_2nn2acFPQ3_2nn2ac11ConfigIdNum");

/**
 * Initializes the Auto Connect library. Call this function before any other nn::ac
 * functions.
 *
 * \return
 * A \link nn::Result Result\endlink - see \link nn::Result::IsSuccess \endlink
 * and \link nn::Result::IsFailure \endlink.
 *
 * \sa
 * - \link Finalize \endlink
 */
nn::Result
Initialize()
   asm("Initialize__Q2_2nn2acFv");

nn::Result
IsAnyKeepingConnect(bool keeping)
   asm("IsAnyKeepingConnect__Q2_2nn2acFPb");

nn::Result
IsApplicationConnected(bool *connected)
   asm("IsApplicationConnected__Q2_2nn2acFPb");

nn::Result
IsAutoConnectionFatallyFailed(nn::Result *failed)
   asm("IsAutoConnectionFatallyFailed__Q2_2nn2acFQ2_2nn6Result");

nn::Result
IsConfigExisting(ConfigIdNum id, bool *existing)
   asm("IsConfigExisting__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumPb");

nn::Result
IsKeepingConnect(bool *keeping)
   asm("IsKeepingConnect__Q2_2nn2acFPb");

nn::Result
IsReadyToConnect(bool *ready)
   asm("IsReadyToConnect__Q2_2nn2acFPb");

nn::Result
ReadConfig(ConfigIdNum id, Config *cfg)
   asm("ReadConfig__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumP16netconf_profile_");

nn::Result
SetCompatId(ConfigIdNum id)
   asm("SetCompatId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum");

nn::Result
SetStartupId(ConfigIdNum id)
   asm("SetStartupId__Q2_2nn2acFQ3_2nn2ac11ConfigIdNum");

nn::Result
WriteConfig(ConfigIdNum id, const Config *cfg)
   asm("WriteConfig__Q2_2nn2acFQ3_2nn2ac11ConfigIdNumPC16netconf_profile_");

} // namespace ac
} // namespace nn

#endif // ifdef __cplusplus

/** @} */
