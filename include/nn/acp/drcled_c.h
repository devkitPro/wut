#pragma once

#include <wut.h>
#include <nn/acp/result.h>
#include <nn/acp/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t ACPDrcLedStatus;
typedef uint32_t ACPDrcLedPattern;

void
ACPDrcLedStartTest();

void
ACPDrcLedStopTest();

void
ACPGetDrcLedStat(ACPDrcLedStatus *ledStatus);

void
ACPGetDrcLedStatusOfPattern(ACPDrcLedStatus *ledStatus,
                            ACPDrcLedPattern pattern);

void
ACPSetDrcLedDummyPowerStat(uint8_t unk1);

void
ACPSetDrcLedTimerLength(uint64_t unk1,
                        uint64_t unk2);

void
ACPSetDrcLedTimerSpeed(uint32_t speed);

void
ACPTurnOffDrcLed();

void
ACPTurnOffDrcLedTest(uint8_t unk1);

void
ACPTurnOnDrcLed(uint32_t unk1,
                ACPDrcLedPattern pattern);

void
ACPTurnOnDrcLedTest(uint8_t unk1,
                    uint32_t unk2,
                    ACPDrcLedPattern pattern);

#ifdef __cplusplus
}
#endif

/** @} */
