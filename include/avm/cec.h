#pragma once
#include <wut.h>
#include <tve/cec.h>

/**
 * \defgroup avm_cec AVM HDMI CEC
 * \ingroup avm
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes CEC.
 * 
 * \return
 * \c TRUE on success.
 */
BOOL
AVMCECInit(void);

/**
 * Enable CEC.
 */
void
AVMEnableCEC(void);

/**
 * Disable CEC.
 */
void
AVMDisableCEC(void);

/**
 * Sends a CEC command.
 * 
 * \param destination
 * Logical address of the device where the command should be sent to.
 * 
 * \param opCode
 * The op code of the command to send.
 * 
 * \param parameters
 * Pointer to optional command parameters.
 * 
 * \param numParameters
 * The amount of additional parameters.
 * 
 * \return
 * \c TRUE on success.
 */
BOOL
AVMCECSendCommand(TVECECLogicalAddress destination,
                  TVECECOpCode opCode,
                  uint8_t *parameters,
                  uint8_t numParameters);

/**
 * Get the last receieved CEC command.
 * 
 * \param outInitiator
 * Pointer to store the logical address of the initiator of the command to.
 * 
 * \param outOpCode
 * Pointer to store the op code of the command to.
 * 
 * \param outParameters
 * Pointer to store additional parameters to.
 * 
 * \param numParameters
 * Pointer to store the amount of additional parameters to.
 * 
 * \return
 * \c TRUE on success.
 * 
 * \warning
 * This will return success even if no new command has been receieved.
 * The caller should check that the parameters were actually written to.
 */
BOOL
AVMCECReceiveCommand(TVECECLogicalAddress *outInitiator,
                     TVECECOpCode *outOpCode,
                     uint8_t *outParameters,
                     uint8_t *outNumParameters);

#ifdef __cplusplus
}
#endif

/** @} */
