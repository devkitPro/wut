#pragma once
#include <wut.h>
#include <padscore/wpad.h>

/**
 * \defgroup padscore_kpad KPAD
 * \ingroup padscore
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef WPADVec2D KPADVec2D;

typedef struct _KPADStatus
    {
    //! Indicates what KPADButtons are held down
    uint32_t hold;

    //! Indicates what KPADButtons have been pressed since last sample
    uint32_t trigger;

    //! Indicates what KPADButtons have been released since last sample
    uint32_t release;
    
    uint32_t unused_1[5];
    KPADVec2D pos;
    uint32_t unused_2[3];
    KPADVec2D angle;
    uint32_t unused_3[8];
    uint8_t device_type;
    uint8_t wpad_error;
    uint8_t pos_valid;
    uint8_t format;

    union
    {
        struct
        {
            KPADVec2D stick;
        } nunchuck;

        struct
        {
            uint32_t btns_h;
            uint32_t btns_d;
            uint32_t btns_r;
            KPADVec2D leftStick;
            KPADVec2D rightStick;
            float leftTrigger;
            float rightTrigger;
        } classic;

        struct
        {
            uint32_t hold;
            uint32_t trigger;
            uint32_t release;
            KPADVec2D leftStick;
            KPADVec2D rightStick;
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
