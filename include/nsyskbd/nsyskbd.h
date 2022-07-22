#pragma once

#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WUT_PACKED KBDAttachEvent {
    uint8_t channel;
    WUT_PADDING_BYTES(3);
} KBDAttachEvent;
WUT_CHECK_OFFSET(KBDAttachEvent, 0x00, channel);
WUT_CHECK_SIZE(KBDAttachEvent, 0x04);

typedef struct WUT_PACKED KBDKeyEvent {
    uint8_t channel;
    uint8_t hidCode;
    WUT_PADDING_BYTES(2);
    BOOL isPressedDown;
    WUT_UNKNOWN_BYTES(4);
    uint16_t asUTF16Character;
    WUT_PADDING_BYTES(2);
} KBDKeyEvent;
WUT_CHECK_OFFSET(KBDKeyEvent, 0x00, channel);
WUT_CHECK_OFFSET(KBDKeyEvent, 0x01, hidCode);
WUT_CHECK_OFFSET(KBDKeyEvent, 0x04, isPressedDown);
WUT_CHECK_OFFSET(KBDKeyEvent, 0x0C, asUTF16Character);
WUT_CHECK_SIZE(KBDKeyEvent, 0x10);

typedef void (*KDBAttachCallback)(KBDAttachEvent *channel);

typedef void (*KDBKeyCallback)(KBDKeyEvent *event);

typedef enum KDBCountry {
    KDB_COUNTRY_UNKNOWN_0 = 0,
    KDB_COUNTRY_UNKNOWN_1 = 1,
    KDB_COUNTRY_UNKNOWN_2 = 2,
    KDB_COUNTRY_UNKNOWN_3 = 3,
    KDB_COUNTRY_UNKNOWN_4 = 4,
    KDB_COUNTRY_UNKNOWN_5 = 5,
    KDB_COUNTRY_UNKNOWN_6 = 6,
    KDB_COUNTRY_UNKNOWN_7 = 7,
    KDB_COUNTRY_UNKNOWN_8 = 8,
    KDB_COUNTRY_UNKNOWN_9 = 9,
    KDB_COUNTRY_UNKNOWN_10 = 10,
    KDB_COUNTRY_UNKNOWN_11 = 11,
    KDB_COUNTRY_UNKNOWN_12 = 12,
    KDB_COUNTRY_UNKNOWN_13 = 13,
    KDB_COUNTRY_UNKNOWN_14 = 14,
    KDB_COUNTRY_UNKNOWN_15 = 15,
    KDB_COUNTRY_UNKNOWN_16 = 16,
    KDB_COUNTRY_UNKNOWN_17 = 17,
    KDB_COUNTRY_UNKNOWN_18 = 18,
} KDBCountry;

typedef enum KDBError {
    KDB_ERROR_NONE = 0,
    KDB_ERROR_NOT_INITIALIZED = 2,
    KDB_ERROR_ALREADY_INITIALIZED = 3,
    KDB_ERROR_INVALID_COUNTRY = 4,
} KDBError;

KDBError
KBDInit(uint32_t unused,
        KDBAttachCallback attachCallback,
        KDBAttachCallback detachCallback,
        KDBKeyCallback keyCallback);

KDBError
KBDSetup(KDBAttachCallback attachCallback,
         KDBAttachCallback detachCallback,
         KDBKeyCallback keyCallback);

KDBError
KBDTeardown();

KDBError
KBDSetCountry(uint8_t channel,
              KDBCountry country);

#ifdef __cplusplus
}
#endif

/** @} */
