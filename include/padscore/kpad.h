#pragma once
#include <wut.h>

/**
 * \defgroup padscore_kpad KPAD
 * \ingroup padscore
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _KPADStatus
{
    uint32_t btns_h;
    uint32_t btns_d;
    uint32_t btns_r;
    uint32_t unused_1[5];
    float pos_x;
    float pos_y;
    uint32_t unused_2[3];
    float angle_x;
    float angle_y;
    uint32_t unused_3[8];
    uint8_t device_type;
    uint8_t wpad_error;
    uint8_t pos_valid;
    uint8_t format;

    union
    {
        struct
        {
            float stick_x;
            float stick_y;
        } nunchuck;

        struct
        {
            uint32_t btns_h;
            uint32_t btns_d;
            uint32_t btns_r;
            float lstick_x;
            float lstick_y;
            float rstick_x;
            float rstick_y;
            float ltrigger;
            float rtrigger;
        } classic;

        struct
        {
            uint32_t hold;
            uint32_t trigger;
            uint32_t release;
            float lstick_x;
            float lstick_y;
            float rstick_x;
            float rstick_y;
            int32_t charging;
            int32_t wired;
        } pro;

        uint32_t unused_6[20];
    };
    uint32_t unused_7[16];
} KPADStatus;


void
KPADInit (void);

int32_t
KPADRead(int32_t chan,
         void * data,
         uint32_t size);

int32_t
KPADReadEx(int32_t chan,
           KPADStatus * data,
           uint32_t size,
           int32_t *error);

#ifdef __cplusplus
}
#endif

/** @} */
