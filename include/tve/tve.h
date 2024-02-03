#pragma once
#include <wut.h>

/**
 * \defgroup tve_tve TVE
 * \ingroup tve
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TVEPort
{
   TVE_PORT_HDMI,
   TVE_PORT_COMPONENT,
   TVE_PORT_COMPOSITE,
   TVE_PORT_SCART,
} TVEPort;

typedef enum TVEHdmiState
{
   TVE_HDMI_STATE_NONE,
   TVE_HDMI_STATE_HTPG_OFF,
   TVE_HDMI_STATE_RXWAIT,
   TVE_HDMI_STATE_EDID_COMP,
   TVE_HDMI_STATE_DUMMY_TMDS,
   TVE_HDMI_STATE_W4WK,
   TVE_HDMI_STATE_1STA,
   TVE_HDMI_STATE_2NDA,
   TVE_HDMI_STATE_3RDA,
   TVE_HDMI_STATE_STAV_OFF,
   TVE_HDMI_STATE_DONE,
   TVE_HDMI_STATE_OTHER,
   TVE_HDMI_STATE_TMDSDOWN,
   TVE_HDMI_STATE_SHUTDOWN,
   TVE_HDMI_STATE_WII,
   TVE_HDMI_STATE_ERR_NRESET,
   TVE_HDMI_STATE_ERR_INT_LINE,
   TVE_HDMI_STATE_ERR_KEY_LOAD,
   TVE_HDMI_STATE_ERR_EDID_READ,
   TVE_HDMI_STATE_ERR_HOTPLUG,
   TVE_HDMI_STATE_ERR_VSYNC,
   TVE_HDMI_STATE_ERR_HDCP,
   TVE_HDMI_STATE_ERR_SYS,
   TVE_HDMI_STATE_ERR_CEC,
   TVE_HDMI_STATE_ERR_W41A,
   TVE_HDMI_STATE_ERR_W4ED,
   TVE_HDMI_STATE_UNKNOWN_1A,
} TVEHdmiState;

/**
 * Gets the analog state.
 * 
 * \param outState
 * Pointer to write the state to.
 */
void
TVEGetAnalogStat(uint32_t *outState);

/**
 * Gets the TV port.
 * 
 * \return
 * One of #TVEPort.
 */
TVEPort
TVEGetCurrentPort(void);

/**
 * Gets the HDMI state.
 * 
 * \param outState
 * Pointer to write the state to.
 */
void
TVEGetHDMIErrorStat(TVEHdmiState *outState);

#ifdef __cplusplus
}
#endif

/** @} */
