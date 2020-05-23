#pragma once
#include <wut.h>

/**
 * \defgroup nn_pdm
 * \ingroup nn_pdm
 * Log Activities for Titles (see nn::pdm)
 * @{
 */

#ifdef __cplusplus

namespace nn {

namespace pdm {

//! Flags for PlayDiary
typedef enum PlayDiaryFlags : uint16_t
{
   PLAYDIARY_FLAG_DEFAULT               = 0x0000,

   //! Set when the user played in Wii Mode
   //! Note: Title Id should be ffff ffff ffff ffff when set
   PLAYDIARY_FLAG_PLAYED_IN_WII_MODE    = 0x0100,
   PLAYDIARY_FLAG_UNKNOWN_0A00          = 0x0a00
} PlayDiaryFlags;
WUT_CHECK_SIZE(PlayDiaryFlags, 0x02);

//! Stores PlayData for each Day
struct WUT_PACKED PlayDiary
{
   //! Title ID of the title
   uint64_t title_id;
   //! Playtime in Minutes
   uint32_t playtime;
   //! Date in days since 01/01/2000
   uint16_t date;
   //! flags \link PlayDiaryFlags \endif
   PlayDiaryFlags flags;
};
WUT_CHECK_OFFSET(PlayDiary, 0x00, title_id);
WUT_CHECK_OFFSET(PlayDiary, 0x08, playtime);
WUT_CHECK_OFFSET(PlayDiary, 0x0c, date);
WUT_CHECK_OFFSET(PlayDiary, 0x0e, flags);

//! Stores total stats
struct WUT_PACKED PlayStats
{
   //! Title ID of the title
   uint64_t title_id;
   //! Total Playtime in minutes
   uint32_t playtime;
   //! Total amount of times played
   uint16_t times_played;
   //! Date when the title was first played in days since 01/01/2000
   uint16_t first_time_played;
    //! Date when the title was last played in days since 01/01/2000
   uint16_t last_time_played;

   //! Unknown seems to be always 0x0000
   WUT_UNKNOWN_BYTES(2); 
};
WUT_CHECK_OFFSET(PlayStats, 0x00, title_id);
WUT_CHECK_OFFSET(PlayStats, 0x08, playtime);
WUT_CHECK_OFFSET(PlayStats, 0x0c, times_played);
WUT_CHECK_OFFSET(PlayStats, 0x0e, first_time_played);
WUT_CHECK_OFFSET(PlayStats, 0x10, last_time_played);

//! Unknown
struct WUT_PACKED PlayEvent
{
   uint64_t title_id;
   WUT_UNKNOWN_BYTES(12);
};
WUT_CHECK_OFFSET(PlayEvent, 0x00, title_id);

//! Unknown
struct WUT_PACKED PlayLog
{
   uint64_t title_id;
   WUT_UNKNOWN_BYTES(16);
};
WUT_CHECK_OFFSET(PlayLog, 0x00, title_id);

/**
 * Initializes PDM.
 * Needs to be called before using other functions-
 *
 * \return
 * 0 on success.
 */
uint32_t 
Initialize()
   asm("Initialize__Q2_2nn3pdmFv");

/**
 * Finalize PDM.
 */
void 
Finalize()
   asm("Finalize__Q2_2nn3pdmFv");

/**
 * Close all opened PDM Files.
 */
void 
CloseAllFiles()
   asm("CloseAllFiles__Q2_2nn3pdmFv");

/**
 * Convert an users PDM Save to a newer save version.
 *
 * \return
 * 0 on success.
 */
uint32_t
Convert(uint32_t userId)
   asm("Convert__Q2_2nn3pdmFi");

/**
 * Wait until convert is done.
 *
 * \return
 * 0 on success.
 */
uint32_t 
WaitForConvertDone()
   asm("WaitForConvertDone__Q2_2nn3pdmFv");

/**
 * The max amount of \link PlayDiary \endlink that can
 * be written into the save.
 *
 * \param outMaxLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \return
 * 0 on success.
 */
uint32_t
GetPlayDiaryMaxLength(uint32_t* outMaxLength)
   asm("GetPlayDiaryMaxLength__Q2_2nn3pdmFPi");

/**
 * Gets the amount of an users \link PlayDiary \endlink entries.
 *
 * \param outLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayDiaryLength(uint32_t* outLength, uint32_t userId)
   asm("GetPlayDiaryLength__Q2_2nn3pdmFPii");

/**
 * 
 *
 * \param outStart
 * A pointer to write the start to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayDiaryStart(uint32_t* outStart, uint32_t userId)
   asm("GetPlayDiaryStart__Q2_2nn3pdmFPii");

/**
 * Gets an array of \link PlayDiary \endlink entries.
 *
 * \param outAmount
 * A pointer to write the amount of entries that have been
 * written to the array. Must not be \c NULL.
 * May be smaller than the amount passed to the function.
 * 
 * \param outPlayDiaries
 * A pointer to write an array of \link PlayDiary \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayDiary(uint32_t* outAmount, PlayDiary* outPlayDiaries, uint32_t userId, uint32_t amount)
   asm("GetPlayDiary__Q2_2nn3pdmFPiPQ3_2nn3pdm9PlayDiaryiT3");

/**
 * Gets an array of \link PlayDiary \endlink entries.
 * 
 * \param outPlayDiaries
 * A pointer to write an array of \link PlayDiary \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * Either the amount of entries that have been
 * written to the array or 0xFFFFFF on error.
 * May be smaller than the amount passed to the function.
 */
uint32_t
GetPlayDiary(PlayDiary* outPlayDiaries, uint32_t userId, uint32_t amount)
   asm("GetPlayDiary__Q2_2nn3pdmFPQ3_2nn3pdm9PlayDiaryiT2");

/**
 * The max amount of \link PlayEvent \endlink that can
 * be written into the save.
 *
 * \param outMaxLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \return
 * 0 on success.
 */
uint32_t
GetPlayEventMaxLength(uint32_t* outMaxLength)
   asm("GetPlayEventMaxLength__Q2_2nn3pdmFPi");

/**
 * Gets an array of \link PlayEvent \endlink entries.
 *
 * \param outAmount
 * A pointer to write the amount of entries that have been
 * written to the array. Must not be \c NULL.
 * May be smaller than the amount passed to the function.
 * 
 * \param outPlayEvents
 * A pointer to write an array of \link PlayEvent \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayEvent(uint32_t* outAmount, PlayEvent* outPlayEvents, uint32_t userId, uint32_t amount)
   asm("GetPlayEvent__Q2_2nn3pdmFPiPQ3_2nn3pdm9PlayEventiT3");

/**
 * The max amount of \link PlayLog \endlink that can
 * be written into the save.
 *
 * \param outMaxLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \return
 * 0 on success.
 */
uint32_t
GetPlayLogMaxLength(uint32_t* outMaxLength)
   asm("GetPlayLogMaxLength__Q2_2nn3pdmFPi");

/**
 * Gets the amount of an users \link PlayLog \endlink entries.
 *
 * \param outLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayLogLength(uint32_t* outLength, uint32_t userId)
   asm("GetPlayLogLength__Q2_2nn3pdmFPii");

/**
 * 
 *
 * \param outStart
 * A pointer to write the start to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayLogStart(uint32_t* outStart, uint32_t userId)
   asm("GetPlayLogStart__Q2_2nn3pdmFPii");

/**
 * Gets an array of \link PlayLog \endlink entries.
 *
 * \param outAmount
 * A pointer to write the amount of entries that have been
 * written to the array. Must not be \c NULL.
 * May be smaller than the amount passed to the function.
 * 
 * \param outPlayLogs
 * A pointer to write an array of \link PlayLog \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayLog(uint32_t* outAmount, PlayLog* outPlayLogs, uint32_t userId, uint32_t amount)
   asm("GetPlayLog__Q2_2nn3pdmFPiPQ3_2nn3pdm7PlayLogiT3");

/**
 * Gets an array of \link PlayLog \endlink entries.
 * 
 * \param outPlayLogs
 * A pointer to write an array of \link PlayLog \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * Either the amount of entries that have been
 * written to the array or 0xFFFFFF on error.
 * May be smaller than the amount passed to the function.
 */
uint32_t
GetPlayLog(PlayLog* outPlayLogs, uint32_t userId, uint32_t amount)
   asm("GetPlayLog__Q2_2nn3pdmFPQ3_2nn3pdm7PlayLogiT2");

/**
 * The max amount of \link PlayStats \endlink that can
 * be written into the save.
 *
 * \param outMaxLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \return
 * 0 on success.
 */
uint32_t
GetPlayStatsMaxLength(uint32_t* outMaxLength)
   asm("GetPlayStatsMaxLength__Q2_2nn3pdmFPi");

/**
 * Gets the amount of an users \link PlayStats \endlink entries.
 *
 * \param outLength
 * A pointer to write the size to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayStatsLength(uint32_t* outLength, uint32_t userId)
   asm("GetPlayStatsLength__Q2_2nn3pdmFPii");

/**
 * Gets \link PlayLog \endlink entry of a Title ID.
 * 
 * \param outPlayStats
 * A pointer to write a \link PlayLog \endlink to. 
 * Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param titleId
 * The titleId of the \link PlayLog \endlink
 * 
 * \return
 * 0 on success
 */
uint32_t
GetPlayStatsOfTitleId(PlayStats* outPlayStats, uint32_t userId, uint64_t titleId)
   asm("GetPlayStatsOfTitleId__Q2_2nn3pdmFPQ3_2nn3pdm9PlayStatsiUL");

/**
 * Gets an array of \link PlayStats \endlink entries.
 *
 * \param outAmount
 * A pointer to write the amount of entries that have been
 * written to the array. Must not be \c NULL.
 * May be smaller than the amount passed to the function.
 * 
 * \param outPlayStats
 * A pointer to write an array of \link PlayStats \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * 0 on success.
 */
uint32_t
GetPlayStats(uint32_t* outAmount, PlayStats* outPlayStats, uint32_t userId, uint32_t amount)
   asm("GetPlayStats__Q2_2nn3pdmFPiPQ3_2nn3pdm9PlayStatsiT3");

/**
 * Gets an array of \link PlayStats \endlink entries.
 * 
 * \param outPlayStats
 * A pointer to write an array of \link PlayStats \endlink
 * to. Must not be \c NULL.
 *
 * \param userId
 * A user ID from 1-12 to indicate the User
 * 
 * \param amount
 * The max amount of entries to be written to the array
 * 
 * \return
 * Either the amount of entries that have been
 * written to the array or 0xFFFFFF on error.
 * May be smaller than the amount passed to the function.
 */
uint32_t
GetPlayStats(PlayStats* outPlayStats, uint32_t userId, uint32_t amount)
   asm("GetPlayStats__Q2_2nn3pdmFPQ3_2nn3pdm9PlayStatsiT2");

void 
NotifySetTimeBeginEvent()
   asm("NotifySetTimeBeginEvent__Q2_2nn3pdmFv");

void 
NotifySetTimeEndEvent()
   asm("NotifySetTimeEndEvent__Q2_2nn3pdmFv");

} //namespace pdm

} //namespace nn

#endif

/** @} */
