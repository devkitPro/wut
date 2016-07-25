#pragma once
#include <wut.h>

/**
 * \defgroup vpad_input VPAD Input
 * \ingroup vpad
 * @{
 */

#define VPAD_BUTTON_A        0x8000
#define VPAD_BUTTON_B        0x4000
#define VPAD_BUTTON_X        0x2000
#define VPAD_BUTTON_Y        0x1000
#define VPAD_BUTTON_LEFT     0x0800
#define VPAD_BUTTON_RIGHT    0x0400
#define VPAD_BUTTON_UP       0x0200
#define VPAD_BUTTON_DOWN     0x0100
#define VPAD_BUTTON_ZL       0x0080
#define VPAD_BUTTON_ZR       0x0040
#define VPAD_BUTTON_L        0x0020
#define VPAD_BUTTON_R        0x0010
#define VPAD_BUTTON_PLUS     0x0008
#define VPAD_BUTTON_MINUS    0x0004
#define VPAD_BUTTON_HOME     0x0002
#define VPAD_BUTTON_SYNC     0x0001
#define VPAD_BUTTON_STICK_R  0x00020000
#define VPAD_BUTTON_STICK_L  0x00040000
#define VPAD_BUTTON_TV       0x00010000

#define VPAD_STICK_R_EMULATION_LEFT    0x04000000
#define VPAD_STICK_R_EMULATION_RIGHT   0x02000000
#define VPAD_STICK_R_EMULATION_UP      0x01000000
#define VPAD_STICK_R_EMULATION_DOWN    0x00800000

#define VPAD_STICK_L_EMULATION_LEFT    0x40000000
#define VPAD_STICK_L_EMULATION_RIGHT   0x20000000
#define VPAD_STICK_L_EMULATION_UP      0x10000000
#define VPAD_STICK_L_EMULATION_DOWN    0x08000000

#define VPAD_VALID       0x0
#define VPAD_INVALID_X   0x1
#define VPAD_INVALID_Y   0x2

#define VPAD_READ_SUCCESS   0x0
#define VPAD_READ_FAIL      -2

typedef uint32_t VPADReadError;

typedef struct
{
    float x,y;
} VPADVec2D;

typedef struct
{
    float x,y,z;
} VPADVec3D;

typedef struct
{
   uint16_t x;
   uint16_t y;
   uint16_t down;
   uint16_t unk1;
} VPADTouchData;

typedef struct
{
   uint16_t x;
   uint16_t y;
   uint16_t touched;
   uint16_t validity;
} VPADTouchPadStatus;

typedef struct
{
   float unk1;
   float unk2;
   float unk3;
   float unk4;
   float unk5;
   VPADVec2D vertical;
} VPADAccStatus;

typedef struct
{
   float unk1;
   float unk2;
   float unk3;
   float unk4;
   float unk5;
   float unk6;
} VPADGyroStatus;

typedef struct
{
   uint32_t btn_hold;
   uint32_t btn_trigger;
   uint32_t btn_release;
   VPADVec2D lstick;
   VPADVec2D rstick;
   VPADAccStatus accelorometer;
   VPADGyroStatus gyro;
   char unk1[0x2];
   VPADTouchPadStatus tpNormal;
   VPADTouchPadStatus tpFiltered1;
   VPADTouchPadStatus tpFiltered2;
   char unk2[0x28];
   VPADVec3D mag;
   uint8_t slideVolume;
   uint8_t battery;
   uint8_t micStatus;
   uint8_t slideVolumeEx;
   char unk3[0x7];
} VPADStatus;

#ifdef __cplusplus
"C" {
#endif

// Depreciated
void
VPADInit();

int32_t
VPADRead(uint32_t chan,
         VPADStatus *buffers,
         uint32_t count,
         VPADReadError *error);

void
VPADGetTPCalibratedPoint(uint32_t chan,
                         VPADTouchData *calibratedData,
                         VPADTouchData *uncalibratedData);

#ifdef __cplusplus
}
#endif

/** @} */
