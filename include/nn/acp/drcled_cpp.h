#pragma once

#include <wut.h>
#include <nn/acp/result.h>
#include <nn/acp/device.h>

#ifdef __cplusplus

namespace nn {

namespace acp {

typedef uint8_t DrcLedStatus;
typedef uint32_t DrcLedPattern;

void
GetDrcLedStatusOfPattern(DrcLedStatus *ledStatus,
                         DrcLedPattern pattern)
   asm("GetDrcLedStatusOfPattern__Q2_2nn3acpFPQ3_2nn3acp12DrcLedStatusQ3_2nn3acp13DrcLedPattern");

void
SetDrcLedDummyPowerStat(uint8_t unk1)
   asm("SetDrcLedDummyPowerStat__Q2_2nn3acpFUc");

void
SetDrcLedTimerLength(uint64_t unk1,
                        uint64_t unk2)
   asm("SetDrcLedTimerLength__Q2_2nn3acpFULT1");

void
SetDrcLedTimerSpeed(uint32_t speed)
   asm("SetDrcLedTimerSpeed__Q2_2nn3acpFUi");

void
TurnOffDrcLed()
   asm("TurnOffDrcLed__Q2_2nn3acpFv");

void
TurnOffDrcLedTest(uint8_t unk1)
   asm("TurnOffDrcLedTest__Q2_2nn3acpFUc");

void
TurnOnDrcLed(uint32_t unk1,
                DrcLedPattern pattern)
   asm("TurnOnDrcLed__Q2_2nn3acpFUiQ3_2nn3acp13DrcLedPattern");

void
TurnOnDrcLedTest(uint8_t unk1,
                uint32_t unk2,
                DrcLedPattern pattern)
   asm("TurnOnDrcLedTest__Q2_2nn3acpFUcUiQ3_2nn3acp13DrcLedPattern");

} //namespace acp

} //namespace nn

#endif

/** @} */
