#pragma once
#include <wut.h>

/**
 * \defgroup nsysccr_cfg
 * \ingroup nsysccr
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

int32_t
CCRCFGInit(void);

/**
 * Read from the cached Eeprom of the specified device.
 * 
 * \param drcSlot
 * The DRC to read the eeprom from (0 or 1).
 * 
 * \param offset
 * Offset of the Eeprom data.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCFGGetCachedEeprom(uint32_t drcSlot,
                      uint32_t offset,
                      void *buf,
                      uint32_t size);

/**
 * Write to the cached Eeprom of the specified device.
 * 
 * \param drcSlot
 * The DRC to read the eeprom from (0 or 1).
 * 
 * \param offset
 * Offset of the Eeprom data.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCFGSetCachedEeprom(uint32_t drcSlot,
                      uint32_t offset,
                      void *buf,
                      uint32_t size);

/**
 * Get the version check flag.
 * 
 * \param outFlag
 * Pointer to write the flag to.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCFGGetVersionCheckFlag(uint32_t *outFlag);

/**
 * Set the version check flag.
 * 
 * \param outFlag
 * The flag to set.
 * 
 * \return
 * 0 on success.
 */
int32_t
CCRCFGSetVersionCheckFlag(uint32_t flag);

#ifdef __cplusplus
}
#endif

/** @} */
