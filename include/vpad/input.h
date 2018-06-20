#pragma once
#include <wut.h>

/**
 * \defgroup vpad_input VPAD Input
 * \ingroup vpad
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VPADAccStatus VPADAccStatus;
typedef struct VPADDirection VPADDirection;
typedef struct VPADGyroStatus VPADGyroStatus;
typedef struct VPADStatus VPADStatus;
typedef struct VPADTouchData VPADTouchData;
typedef struct VPADVec2D VPADVec2D;
typedef struct VPADVec3D VPADVec3D;

typedef enum VPADButtons
{
   VPAD_BUTTON_A                 = 0x8000,
   VPAD_BUTTON_B                 = 0x4000,
   VPAD_BUTTON_X                 = 0x2000,
   VPAD_BUTTON_Y                 = 0x1000,
   VPAD_BUTTON_LEFT              = 0x0800,
   VPAD_BUTTON_RIGHT             = 0x0400,
   VPAD_BUTTON_UP                = 0x0200,
   VPAD_BUTTON_DOWN              = 0x0100,
   VPAD_BUTTON_ZL                = 0x0080,
   VPAD_BUTTON_ZR                = 0x0040,
   VPAD_BUTTON_L                 = 0x0020,
   VPAD_BUTTON_R                 = 0x0010,
   VPAD_BUTTON_PLUS              = 0x0008,
   VPAD_BUTTON_MINUS             = 0x0004,
   VPAD_BUTTON_HOME              = 0x0002,
   VPAD_BUTTON_SYNC              = 0x0001,
   VPAD_BUTTON_STICK_R           = 0x00020000,
   VPAD_BUTTON_STICK_L           = 0x00040000,
   VPAD_BUTTON_TV                = 0x00010000,
   VPAD_STICK_R_EMULATION_LEFT   = 0x04000000,
   VPAD_STICK_R_EMULATION_RIGHT  = 0x02000000,
   VPAD_STICK_R_EMULATION_UP     = 0x01000000,
   VPAD_STICK_R_EMULATION_DOWN   = 0x00800000,
   VPAD_STICK_L_EMULATION_LEFT   = 0x40000000,
   VPAD_STICK_L_EMULATION_RIGHT  = 0x20000000,
   VPAD_STICK_L_EMULATION_UP     = 0x10000000,
   VPAD_STICK_L_EMULATION_DOWN   = 0x08000000,
} VPADButtons;

typedef enum VPADChan
{
   VPAD_CHAN_0                   = 0,
} VPADChan;

typedef enum VPADTouchPadValidity
{
   //! Both X and Y touchpad positions are accurate
   VPAD_VALID                    = 0x0,

   //! X position is inaccurate
   VPAD_INVALID_X                = 0x1,

   //! Y position is inaccurate
   VPAD_INVALID_Y                = 0x2,
} VPADTouchPadValidity;

typedef enum VPADReadError
{
   VPAD_READ_SUCCESS             = 0,
   VPAD_READ_NO_SAMPLES          = -1,
   VPAD_READ_INVALID_CONTROLLER  = -2,
} VPADReadError;

struct VPADVec2D
{
   float x;
   float y;
};
WUT_CHECK_OFFSET(VPADVec2D, 0x00, x);
WUT_CHECK_OFFSET(VPADVec2D, 0x04, y);
WUT_CHECK_SIZE(VPADVec2D, 0x08);

struct VPADVec3D
{
   float x;
   float y;
   float z;
};
WUT_CHECK_OFFSET(VPADVec3D, 0x00, x);
WUT_CHECK_OFFSET(VPADVec3D, 0x04, y);
WUT_CHECK_OFFSET(VPADVec3D, 0x08, z);
WUT_CHECK_SIZE(VPADVec3D, 0x0C);


struct VPADDirection
{
   VPADVec3D x;
   VPADVec3D y;
   VPADVec3D z;
};
WUT_CHECK_OFFSET(VPADDirection, 0x00, x);
WUT_CHECK_OFFSET(VPADDirection, 0x0C, y);
WUT_CHECK_OFFSET(VPADDirection, 0x18, z);
WUT_CHECK_SIZE(VPADDirection, 0x24);

struct VPADTouchData
{
   uint16_t x;
   uint16_t y;

   //! 0 if screen is not currently being touched
   uint16_t touched;

   //! Bitfield of VPADTouchPadValidity to indicate how touch sample accuracy
   uint16_t validity;
};
WUT_CHECK_OFFSET(VPADTouchData, 0x00, x);
WUT_CHECK_OFFSET(VPADTouchData, 0x02, y);
WUT_CHECK_OFFSET(VPADTouchData, 0x04, touched);
WUT_CHECK_OFFSET(VPADTouchData, 0x06, validity);
WUT_CHECK_SIZE(VPADTouchData, 0x08);

struct VPADAccStatus
{
   VPADVec3D acc;
   float magnitude;
   float variation;
   VPADVec2D vertical;
};
WUT_CHECK_OFFSET(VPADAccStatus, 0x00, acc);
WUT_CHECK_OFFSET(VPADAccStatus, 0x0C, magnitude);
WUT_CHECK_OFFSET(VPADAccStatus, 0x10, variation);
WUT_CHECK_OFFSET(VPADAccStatus, 0x14, vertical);
WUT_CHECK_SIZE(VPADAccStatus, 0x1c);

struct WUT_PACKED VPADStatus
{
   //! Indicates what VPADButtons are held down
   uint32_t hold;

   //! Indicates what VPADButtons have been pressed since last sample
   uint32_t trigger;

   //! Indicates what VPADButtons have been released since last sample
   uint32_t release;

   //! Position of left analog stick
   VPADVec2D leftStick;

   //! Position of right analog stick
   VPADVec2D rightStick;

   //! Status of DRC accelorometer
   VPADAccStatus accelorometer;

   //! Status of DRC gyro
   VPADVec3D gyro;

   //! Status of DRC angle
   VPADVec3D angle;

   uint8_t error;

   WUT_UNKNOWN_BYTES(0x01);

   //! Current touch position on DRC
   VPADTouchData tpNormal;

   //! Filtered touch position, first level of smoothing
   VPADTouchData tpFiltered1;

   //! Filtered touch position, second level of smoothing
   VPADTouchData tpFiltered2;

   WUT_UNKNOWN_BYTES(0x02);

   VPADDirection direction;

   //! Set to 1 if headphones are plugged in, 0 otherwise
   BOOL usingHeadphones;

   //! Status of DRC magnetometer
   VPADVec3D mag;

   //! Current volume set by the slide control
   uint8_t slideVolume;

   //! Battery level of controller
   uint8_t battery;

   //! Status of DRC microphone
   uint8_t micStatus;

   //! Unknown volume related value
   uint8_t slideVolumeEx;

   WUT_UNKNOWN_BYTES(0x8);
};
WUT_CHECK_OFFSET(VPADStatus, 0x00, hold);
WUT_CHECK_OFFSET(VPADStatus, 0x04, trigger);
WUT_CHECK_OFFSET(VPADStatus, 0x08, release);
WUT_CHECK_OFFSET(VPADStatus, 0x0C, leftStick);
WUT_CHECK_OFFSET(VPADStatus, 0x14, rightStick);
WUT_CHECK_OFFSET(VPADStatus, 0x1C, accelorometer);
WUT_CHECK_OFFSET(VPADStatus, 0x38, gyro);
WUT_CHECK_OFFSET(VPADStatus, 0x44, angle);
WUT_CHECK_OFFSET(VPADStatus, 0x50, error);
WUT_CHECK_OFFSET(VPADStatus, 0x52, tpNormal);
WUT_CHECK_OFFSET(VPADStatus, 0x5A, tpFiltered1);
WUT_CHECK_OFFSET(VPADStatus, 0x62, tpFiltered2);
WUT_CHECK_OFFSET(VPADStatus, 0x6C, direction);
WUT_CHECK_OFFSET(VPADStatus, 0x94, mag);
WUT_CHECK_OFFSET(VPADStatus, 0xA0, slideVolume);
WUT_CHECK_OFFSET(VPADStatus, 0xA1, battery);
WUT_CHECK_OFFSET(VPADStatus, 0xA2, micStatus);
WUT_CHECK_OFFSET(VPADStatus, 0xA3, slideVolumeEx);
WUT_CHECK_SIZE(VPADStatus, 0xAC);

//! Deprecated
void
VPADInit();

void
VPADShutdown();

int32_t
VPADRead(VPADChan chan,
         VPADStatus *buffers,
         uint32_t count,
         VPADReadError *outError);

void
VPADGetTPCalibratedPoint(VPADChan chan,
                         VPADTouchData *calibratedData,
                         VPADTouchData *uncalibratedData);

int32_t
VPADBASEGetMotorOnRemainingCount(VPADChan chan);

int32_t
VPADBASESetMotorOnRemainingCount(VPADChan chan,
                                 int32_t counter);

void
VPADSetAccParam(VPADChan chan,
                float playRadius,
                float sensitivity);

void
VPADGetAccParam(VPADChan chan,
                float *outPlayRadius,
                float *outSensitivity);

void
VPADSetBtnRepeat(VPADChan chan,
                 float delaySec,
                 float pulseSec);

void
VPADEnableStickCrossClamp(VPADChan chan);

void
VPADDisableStickCrossClamp(VPADChan chan);

void
VPADSetLStickClampThreshold(VPADChan chan,
                            int32_t max,
                            int32_t min);

void
VPADSetRStickClampThreshold(VPADChan chan,
                            int32_t max,
                            int32_t min);

void
VPADGetLStickClampThreshold(VPADChan chan,
                            int32_t *max,
                            int32_t *min);

void
VPADGetRStickClampThreshold(VPADChan chan,
                            int32_t *max,
                            int32_t *min);

void
VPADSetStickOrigin(VPADChan chan);

void
VPADDisableLStickZeroClamp(VPADChan chan);

void
VPADDisableRStickZeroClamp(VPADChan chan);

void
VPADEnableLStickZeroClamp(VPADChan chan);

void
VPADEnableRStickZeroClamp(VPADChan chan);

void
VPADSetCrossStickEmulationParamsL(VPADChan chan,
                                  float rotationDegree,
                                  float range,
                                  float radius);

void
VPADSetCrossStickEmulationParamsR(VPADChan chan,
                                  float rotationDegree,
                                  float range,
                                  float radius);

void
VPADGetCrossStickEmulationParamsL(VPADChan chan,
                                  float *outRotationDegree,
                                  float *outRange,
                                  float *outRadius);

void
VPADGetCrossStickEmulationParamsR(VPADChan chan,
                                  float *outRotationDegree,
                                  float *outRange,
                                  float *outRadius);

void
VPADSetGyroAngle(VPADChan chan,
                 float ax,
                 float ay,
                 float az);

void
VPADSetGyroDirection(VPADChan chan,
                     VPADDirection *dir);

void
VPADSetGyroDirectionMag(VPADChan chan,
                        float mag);

void
VPADSetGyroMagnification(VPADChan chan,
                         float pitch,
                         float yaw,
                         float roll);

void
VPADEnableGyroZeroPlay(VPADChan chan);

void
VPADEnableGyroDirRevise(VPADChan chan);

void
VPADEnableGyroAccRevise(VPADChan chan);

void
VPADDisableGyroZeroPlay(VPADChan chan);

void
VPADDisableGyroDirRevise(VPADChan chan);

void
VPADDisableGyroAccRevise(VPADChan chan);


float
VPADIsEnableGyroZeroPlay(VPADChan chan);

float
VPADIsEnableGyroZeroDrift(VPADChan chan);

float
VPADIsEnableGyroDirRevise(VPADChan chan);

float
VPADIsEnableGyroAccRevise(VPADChan chan);

void
VPADSetGyroZeroPlayParam(VPADChan chan,
                         float radius);

void
VPADInitGyroZeroPlayParam(VPADChan chan);

void
VPADInitGyroDirReviseParam(VPADChan chan);

void
VPADInitGyroAccReviseParam(VPADChan chan);

void
VPADInitGyroZeroDriftMode(VPADChan chan);

int32_t
VPADControlMotor(VPADChan chan,
                 uint8_t *pattern,
                 uint8_t length);

void
VPADStopMotor(VPADChan chan);

int32_t
VPADSetLcdMode(VPADChan chan,
               int32_t lcdMode);

int32_t
VPADGetLcdMode(VPADChan chan,
               int32_t *outLcdMode);

void
VPADBASESetSensorBarSetting(VPADChan chan,
                            int8_t setting);

void
VPADBASEGetSensorBarSetting(VPADChan chan,
                            int8_t *outSetting);

int32_t
VPADSetSensorBar(VPADChan chan,
                 BOOL on);

#ifdef __cplusplus
}
#endif

/** @} */
