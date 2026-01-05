#pragma once

/**
 * \defgroup sndcore2_rmt Remote
 * \ingroup sndcore2
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Consume samples for all Wiimotes
 * \param count number of samples to consume
 * \return number of samples actually consumed
 *
 * \see AXRmtGetSamplesLeft
 * \see AXRmtGetSamples
 * Reduces number of available samples
 */
uint32_t
AXRmtAdvancePtr(uint32_t count);

/**
 * Gets 16-bit LPCM samples queued for a Wiimote
 * \param index WPAD channel of the device (0 - 3)
 * \param [out] samples 16-bit LPCM samples queued for specified device
 * \param sampleCount requested number of samples
 * \return actual number of 16-bit LPCM samples obtained
 *
 * \see WENCGetEncodeData
 * \see AXRmtGetSamplesLeft
 * \see AXRmtAdvancePtr
 * \see AXSetVoiceRmtOn
 *
 * Samples can be obtained while a voice with remote output enabled is playing
 */
uint32_t
AXRmtGetSamples(uint32_t index, int16_t *samples, uint32_t sampleCount);

/**
 * Get number of samples currently available to Wiimotes
 * \return number of available samples
 *
 * \see AXRmtGetSamples
 * \see AXRmtAdvancePtr
 */
uint32_t
AXRmtGetSamplesLeft();
#ifdef __cplusplus
}
#endif

/** @} */
