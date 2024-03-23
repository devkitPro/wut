#pragma once
#include <wut.h>
#include <nn/hpad/hpad.h>

/**
 * \defgroup nn_hpad_beta
 * \ingroup nn_hpad
 * Beta functions for HPAD.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Prints internal state info to the COS shell.
 */
void
BETA_DEBUG_DUMP(void);

/**
 * Gets the command queue size of the specified adapter.
 *
 * \param chan
 * The channel to get the size of.
 * 
 * \return
 * The command queue size.
 */
int32_t
BETA_DEBUG_GET_QUEUE_SIZE(HPADGGGGChan chan);


/**
 * Sends a report to the specified adapter.
 *
 * \param chan
 * The channel to send the report to.
 * 
 * \param reptId
 * The ID of the report to send.
 */
void
BETA_DEBUG_SEND_REPT_ID(HPADGGGGChan chan,
                        uint32_t reptId);

/**
 * Returns immediately.
 */
void
BETA_DEBUG_GET_RAW_DATA(void);

/**
 * Returns immediately.
 */
void
BETA_DEBUG_SET_DUMP_MODE(void);

#ifdef __cplusplus
}
#endif

/** @} */
