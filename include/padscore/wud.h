#pragma once
#include <wut.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_wud WUD
 * \ingroup padscore
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

uint16_t
WUDGetFirmwareVersion(void);

BOOL
WUDSerialFlashTestMode(void (*callback)(void));

BOOL
WUDSerialFlashTestRead(uint32_t unknown1,
                       uint8_t size,
                       void (*callback)(void *, void *));

BOOL
WUDSerialFlashTestWrite(uint32_t unknown1,
                        uint8_t size,
                        uint32_t unknown2,
                        void (*callback)(void));

BOOL
WUDSerialFlashUpdate(void (*callback)(char, char));

uint16_t
WUDSerialFlashVersion(void);

void
WUDSetSniffMode(WPADAddress *btaddr,
                void *unknown);

void
WUDSetVisibility(uint8_t unknown1,
                 uint8_t unknown2);

#ifdef __cplusplus
}
#endif

/** @} */
