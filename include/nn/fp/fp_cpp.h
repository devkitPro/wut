#pragma once
#include <wut.h>
#include <nn/act.h>
#include <nn/ffl/miidata.h>
#include <nn/result.h>

/**
 * \defgroup nn_fp_fp Friends Presence
 * \ingroup nn_fp
 * See \link nn::fp \endlink.
 *
 * @{
 */

#ifdef __cplusplus

namespace nn
{
namespace fp
{


enum NotificationType
{
   NOTIFICATION_ONLINE             = 1,
   NOTIFICATION_OFFLINE            = 2,
   NOTIFICATION_PREFERENCE         = 3,
   NOTIFICATION_FRIEND_ONLINE      = 4,
   NOTIFICATION_FRIEND_OFFLINE     = 5,
   NOTIFICATION_FRIEND_PRESENCE    = 6,
   NOTIFICATION_FRIEND_MII         = 7,
   NOTIFICATION_FRIEND_PROFILE     = 8,
   NOTIFICATION_FRIEND_ADDED       = 9,
   NOTIFICATION_FRIEND_REMOVED     = 10,
   NOTIFICATION_MY_REQUEST_ADDED   = 11,
   NOTIFICATION_MY_REQUEST_REMOVED = 12,
   NOTIFICATION_MY_REQUEST_UPDATED = 13,
   NOTIFICATION_BLACKLIST_ADDED    = 14,
   NOTIFICATION_BLACKLIST_REMOVED  = 15,
   NOTIFICATION_BLACKLIST_UPDATED  = 16,
   NOTIFICATION_REQUEST_ADDED      = 17,
   NOTIFICATION_REQUEST_REMOVED    = 18,

   //! TODO: find all notification types
};
struct DateTime
{
   uint16_t year;
   uint8_t month;
   uint8_t day;
   uint8_t hour; // hour-1
   uint8_t minutes;
   uint8_t seconds;      // unsure
   uint8_t milliseconds; // unsure
};
WUT_CHECK_OFFSET(DateTime, 0x00, year);
WUT_CHECK_OFFSET(DateTime, 0x02, month);
WUT_CHECK_OFFSET(DateTime, 0x03, day);
WUT_CHECK_OFFSET(DateTime, 0x04, hour);
WUT_CHECK_OFFSET(DateTime, 0x05, minutes);
WUT_CHECK_OFFSET(DateTime, 0x06, seconds);
WUT_CHECK_OFFSET(DateTime, 0x07, milliseconds);
WUT_CHECK_SIZE(DateTime, 0x08);

struct GameKey
{
   uint64_t titleId;
   uint16_t unk_0x8;
   uint32_t unk_0xC;
};
WUT_CHECK_OFFSET(GameKey, 0x00, titleId);
WUT_CHECK_SIZE(GameKey, 0x10);

struct RecentPlayRecord
{
   nn::act::PrincipalId principalId;
   uint16_t unk_0x04;
   char16_t inGameName[nn::act::AccountIdSize];
   char16_t myMiiName[nn::act::AccountIdSize];
};
WUT_CHECK_OFFSET(RecentPlayRecord, 0x00, principalId);
WUT_CHECK_OFFSET(RecentPlayRecord, 0x04, unk_0x04);
WUT_CHECK_OFFSET(RecentPlayRecord, 0x06, inGameName);
WUT_CHECK_OFFSET(RecentPlayRecord, 0x28, myMiiName);
WUT_CHECK_SIZE(RecentPlayRecord, 0x4C);

struct RecentPlayRecordEx
{
   RecentPlayRecord playRecord;
   GameKey game;
   DateTime date;
};
WUT_CHECK_OFFSET(RecentPlayRecordEx, 0x00, playRecord);
WUT_CHECK_OFFSET(RecentPlayRecordEx, 0x50, game);
WUT_CHECK_OFFSET(RecentPlayRecordEx, 0x60, date);
WUT_CHECK_SIZE(RecentPlayRecordEx, 0x68);

struct Preference
{
   bool unk_0x00;
   bool unk_0x01;
   bool unk_0x02;
   WUT_PADDING_BYTES(1);
};
WUT_CHECK_SIZE(Preference, 0x04);

struct GameMode
{
   BOOL joinAvailabilityFlag;
   uint32_t matchmakeSystemType; // 2 ??
   uint32_t joinGameId;
   uint32_t joinGameMode;
   //! only set when joinAvailabilityFlag is TRUE
   nn::act::PrincipalId ownerPrincipalId;
   uint32_t joinGroupId;
   uint8_t applicationArg[0x14];
};
WUT_CHECK_OFFSET(GameMode, 0x00, joinAvailabilityFlag);
WUT_CHECK_OFFSET(GameMode, 0x04, matchmakeSystemType);
WUT_CHECK_OFFSET(GameMode, 0x08, joinGameId);
WUT_CHECK_OFFSET(GameMode, 0x0C, joinGameMode);
WUT_CHECK_OFFSET(GameMode, 0x10, ownerPrincipalId);
WUT_CHECK_OFFSET(GameMode, 0x14, joinGroupId);
WUT_CHECK_OFFSET(GameMode, 0x18, applicationArg);
WUT_CHECK_SIZE(GameMode, 0x2C);

struct Presence
{
   GameMode gameMode;
   uint8_t region;
   uint8_t language;
   uint8_t platform;
};
WUT_CHECK_OFFSET(Presence, 0x00, gameMode);
WUT_CHECK_OFFSET(Presence, 0x2C, region);
WUT_CHECK_OFFSET(Presence, 0x2D, language);
WUT_CHECK_OFFSET(Presence, 0x2E, platform);
WUT_CHECK_SIZE(Presence, 0x30);

struct FriendPresence : Presence
{
   bool isOnline;
   bool isValid;
};
WUT_CHECK_OFFSET(FriendPresence, 0x30, isOnline);
WUT_CHECK_OFFSET(FriendPresence, 0x31, isValid);
WUT_CHECK_SIZE(FriendPresence, 0x34);

struct MyPresence : Presence
{
   char16_t presenceText[64];
};
WUT_CHECK_OFFSET(MyPresence, 0x30, presenceText);
WUT_CHECK_SIZE(MyPresence, 0xB0);

//! TODO: find member types and names
struct BasicInfo
{
   WUT_UNKNOWN_BYTES(0x68);
};
WUT_CHECK_SIZE(BasicInfo, 0x68);

//! TODO: find member types and names
struct BlackListedPrincipal
{
   WUT_UNKNOWN_BYTES(0xB0);
};
WUT_CHECK_SIZE(BlackListedPrincipal, 0xB0);

//! TODO: find member types and names
struct Profile
{
   WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_SIZE(Profile, 0x04);

struct Comment
{
   uint8_t unk_0x00; // probably bool isVisible
   uint8_t unk_0x01; // probably bool
   char16_t comment[17];
};
WUT_CHECK_OFFSET(Comment, 0x00, unk_0x00);
WUT_CHECK_OFFSET(Comment, 0x01, unk_0x01);
WUT_CHECK_OFFSET(Comment, 0x02, comment);
WUT_CHECK_SIZE(Comment, 0x24);

struct FriendData
{
   /*! TODO: find types and names */
   WUT_UNKNOWN_BYTES(0x228);
};
WUT_CHECK_SIZE(FriendData, 0x228);

struct GameModeDescription
{
   /*! TODO: find size and member types/names */
};

struct FriendRequest
{
   /* Notes:
     * MaxCharsOnKBD = char16_t[63]
     * Real Buffer prolly = char16_t[64]
    **/
   WUT_UNKNOWN_BYTES(0x164);
};
WUT_CHECK_SIZE(FriendRequest, 0x164);

typedef void (*FPAsyncCallback)(nn::Result, void *);
typedef void (*NotificationHandlerFn)(nn::fp::NotificationType, nn::act::PrincipalId, void *);

nn::Result
AcceptFriendRequestAsync(nn::act::LocalFriendCode /*unsure*/, FPAsyncCallback, void *)
   asm("AcceptFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
AddBlackListAsync(nn::act::PrincipalId, nn::fp::GameKey *, FPAsyncCallback, void *)
   asm("AddBlackListAsync__Q2_2nn2fpFUiPCQ3_2nn2fp7GameKeyPFQ2_2nn6ResultPv_vPv");


nn::Result
AddBlackListAsync(nn::act::PrincipalId, FPAsyncCallback, void *)
   asm("AddBlackListAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendAsync(char nnid[nn::act::AccountIdSize] /*unsure*/, FPAsyncCallback, void *)
   asm("AddFriendAsync__Q2_2nn2fpFPCcPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendAsync(nn::act::PrincipalId /*unsure*/, FPAsyncCallback, void *)
   asm("AddFriendAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestAsync(const nn::fp::RecentPlayRecordEx *, const char16_t *, FPAsyncCallback, void *)
   asm("AddFriendRequestAsync__Q2_2nn2fpFPCQ3_2nn2fp18RecentPlayRecordExPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestAsync(unsigned int, unsigned char, const char16_t *, unsigned char, const char16_t *, FPAsyncCallback, void *)
   asm("AddFriendRequestAsync__Q2_2nn2fpFUiUcPCwT2T3PFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestNoTitleAsync(unsigned int, unsigned char, const char16_t *, unsigned char, const char16_t *, FPAsyncCallback, void *)
   asm("AddFriendRequestNoTitleAsync__Q2_2nn2fpFUiUcPCwT2T3PFQ2_2nn6ResultPv_vPv");


nn::Result
AddRecentPlayRecordEx(const nn::fp::RecentPlayRecordEx *, unsigned int)
   asm("AddRecentPlayRecordEx__Q2_2nn2fpFPCQ3_2nn2fp18RecentPlayRecordExUi");


nn::Result
AddRecentPlayRecord(const nn::fp::RecentPlayRecord *, unsigned int)
   asm("AddRecentPlayRecord__Q2_2nn2fpFPCQ3_2nn2fp16RecentPlayRecordUi");


nn::Result
CancelFriendRequestAsync(nn::act::LocalFriendCode /*unsure*/, FPAsyncCallback, void *)
   asm("CancelFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
CheckSettingStatusAsync(unsigned char *, FPAsyncCallback, void *)
   asm("CheckSettingStatusAsync__Q2_2nn2fpFPUcPFQ2_2nn6ResultPv_vPv");


nn::Result
ClearLedEvent(void)
   asm("ClearLedEvent__Q2_2nn2fpFv");


nn::Result
DeleteFriendFlagsAsync(const unsigned int *, unsigned int, unsigned int, FPAsyncCallback, void *)
   asm("DeleteFriendFlagsAsync__Q2_2nn2fpFPCUiUiT2PFQ2_2nn6ResultPv_vPv");


nn::Result
DeleteFriendRequestAsync(nn::act::LocalFriendCode /*unsure*/, FPAsyncCallback, void *)
   asm("DeleteFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
DeleteRecentPlayRecordAll(void)
   asm("DeleteRecentPlayRecordAll__Q2_2nn2fpFv");


nn::Result
DeleteSaveDirectory(unsigned int)
   asm("DeleteSaveDirectory__Q2_2nn2fpFUi");


nn::Result
DenyFriendRequestAsync(nn::act::LocalFriendCode /*unsure*/, FPAsyncCallback, void *)
   asm("DenyFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
DetectNatPropertiesAsync(unsigned char *, unsigned char *, unsigned int *, FPAsyncCallback, void *)
   asm("DetectNatPropertiesAsync__Q2_2nn2fpFPUcT1PUiPFQ2_2nn6ResultPv_vPv");


nn::Result
FinalizeAdmin(void)
   asm("FinalizeAdmin__Q2_2nn2fpFv");


nn::Result
Finalize(void)
   asm("Finalize__Q2_2nn2fpFv");


nn::Result
GetBasicInfoAsync(nn::fp::BasicInfo *, unsigned int *, unsigned int, FPAsyncCallback, void *)
   asm("GetBasicInfoAsync__Q2_2nn2fpFPQ3_2nn2fp9BasicInfoPCUiUiPFQ2_2nn6ResultPv_vPv");


nn::Result
GetBlackListAccountId(char *outAccountIds, unsigned int *, unsigned int)
   asm("GetBlackListAccountId__Q2_2nn2fpFPA17_cPCUiUi");


nn::Result
GetBlackListAdditionalTime(nn::fp::DateTime *, unsigned int *, unsigned int)
   asm("GetBlackListAdditionalTime__Q2_2nn2fpFPQ3_2nn2fp8DateTimePCUiUi");


nn::Result
GetBlackListEx(nn::fp::BlackListedPrincipal *outBlackList, unsigned int *, unsigned int)
   asm("GetBlackListEx__Q2_2nn2fpFPQ3_2nn2fp20BlackListedPrincipalPCUiUi");


nn::Result
GetBlackList(nn::act::PrincipalId *outBlackListPrincipalBuffer, unsigned int *outBlackListPrincipalBufferSize, unsigned int /*unk*/, unsigned int maxReadCount)
   asm("GetBlackList__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendAccountId(char *outAccountIdBuffer, nn::act::PrincipalId *principalBuffer, unsigned int accountIdBufferSize)
   asm("GetFriendAccountId__Q2_2nn2fpFPA17_cPCUiUi");


nn::Result
GetFriendApprovalTime(nn::fp::DateTime *outDateTime, unsigned int *, unsigned int)
   asm("GetFriendApprovalTime__Q2_2nn2fpFPQ3_2nn2fp8DateTimePCUiUi");


nn::Result
GetFriendComment(nn::fp::Comment *outComment, unsigned int *, unsigned int)
   asm("GetFriendComment__Q2_2nn2fpFPQ3_2nn2fp7CommentPCUiUi");


nn::Result
GetFriendListAll(unsigned int *, unsigned int *, unsigned int, unsigned int)
   asm("GetFriendListAll__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendListEx(nn::fp::FriendData *outFriendData, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendListEx__Q2_2nn2fpFPQ3_2nn2fp10FriendDataPCUiUi");


nn::Result
GetFriendList(nn::act::PrincipalId *outPrincipalBuffer, unsigned int *outPrincipalBufferReadCount, unsigned int unkn /*slotId maybe*/, unsigned int principalBufferSize)
   asm("GetFriendList__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendMii(FFLStoreData *outMiiData, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendMii__Q2_2nn2fpFP12FFLStoreDataPCUiUi");


nn::Result
GetFriendPlayingGame(nn::fp::GameKey *outGameKey, nn::fp::GameModeDescription *outGameModeDescription, nn::act::PrincipalId *principalBuffer, unsigned int maxReadCount)
   asm("GetFriendPlayingGame__Q2_2nn2fpFPQ3_2nn2fp7GameKeyPQ3_2nn2fp19GameModeDescriptionPCUiUi");


nn::Result
GetFriendPresenceEx(nn::fp::FriendPresence *, nn::act::PrincipalId *principalBuffer, unsigned int maxReadCount)
   asm("GetFriendPresenceEx__Q2_2nn2fpFPQ3_2nn2fp14FriendPresencePCUiUi");


nn::Result
GetFriendPresence(nn::fp::FriendPresence *, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendPresence__Q2_2nn2fpFPQ3_2nn2fp14FriendPresencePCUiUi");


nn::Result
GetFriendProfile(nn::fp::Profile *, nn::act::PrincipalId *principalBuffer, unsigned int readCount)
   asm("GetFriendProfile__Q2_2nn2fpFPQ3_2nn2fp7ProfilePCUiUi");


nn::Result
GetFriendRelationship(uint8_t *outRelationshipNum, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendRelationship__Q2_2nn2fpFPUcPCUiUi");


nn::Result
GetFriendRequestAccountId(char *outAccountIds, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendRequestAccountId__Q2_2nn2fpFPA17_cPCUiUi");


nn::Result
GetFriendRequestListEx(nn::fp::FriendRequest *, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendRequestListEx__Q2_2nn2fpFPQ3_2nn2fp13FriendRequestPCUiUi");


nn::Result
GetFriendRequestList(nn::act::PrincipalId *outBuffer, unsigned int *outReadCount, unsigned int /*unk*/, unsigned int count)
   asm("GetFriendRequestList__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendRequestMessageId(unsigned long long *outMessageIds, unsigned int *, unsigned int)
   asm("GetFriendRequestMessageId__Q2_2nn2fpFPULPCUiUi");


nn::Result
GetFriendScreenName(char16_t outScreenName[nn::act::MiiNameSize], unsigned int *, unsigned int, bool, unsigned char *)
   asm("GetFriendScreenName__Q2_2nn2fpFPA11_wPCUiUibPUc");


nn::Result
GetFriendSortTime(nn::fp::DateTime *, nn::act::PrincipalId *principalBuffer, unsigned int count)
   asm("GetFriendSortTime__Q2_2nn2fpFPQ3_2nn2fp8DateTimePCUiUi");


nn::Result
GetLastLedEvent(unsigned int *, unsigned int *)
   asm("GetLastLedEvent__Q2_2nn2fpFPUiT1");


nn::Result
GetMyAccountId(char *outAccountId)
   asm("GetMyAccountId__Q2_2nn2fpFPc");


nn::Result
GetMyComment(nn::fp::Comment *outComment)
   asm("GetMyComment__Q2_2nn2fpFPQ3_2nn2fp7Comment");


nn::Result
GetMyMii(FFLStoreData *outMiiData)
   asm("GetMyMii__Q2_2nn2fpFP12FFLStoreData");


nn::Result
GetMyPlayingGame(nn::fp::GameKey *outPlayingGmae)
   asm("GetMyPlayingGame__Q2_2nn2fpFPQ3_2nn2fp7GameKey");


nn::Result
GetMyPreference(nn::fp::Preference *outPreference)
   asm("GetMyPreference__Q2_2nn2fpFPQ3_2nn2fp10Preference");


nn::Result
GetMyPresence(nn::fp::MyPresence *outMyPresence)
   asm("GetMyPresence__Q2_2nn2fpFPQ3_2nn2fp10MyPresence");


nn::act::PrincipalId
GetMyPrincipalId(void)
   asm("GetMyPrincipalId__Q2_2nn2fpFv");


nn::Result
GetMyProfile(nn::fp::Profile *outProfile)
   asm("GetMyProfile__Q2_2nn2fpFPQ3_2nn2fp7Profile");


nn::Result
GetMyScreenName(char16_t *outScreenName)
   asm("GetMyScreenName__Q2_2nn2fpFPw");


nn::Result
GetRecentPlayRecord(nn::fp::RecentPlayRecordEx *outPlayRecordBuffer, unsigned int *outPlayRecordBufferSize, unsigned int, unsigned int maxReadCount)
   asm("GetRecentPlayRecord__Q2_2nn2fpFPQ3_2nn2fp18RecentPlayRecordExPUiUiT3");


nn::Result
GetRequestBlockSettingAsync(unsigned char *, unsigned int *, unsigned int, FPAsyncCallback, void *)
   asm("GetRequestBlockSettingAsync__Q2_2nn2fpFPUcPCUiUiPFQ2_2nn6ResultPv_vPv");


bool
HasLoggedIn(void)
   asm("HasLoggedIn__Q2_2nn2fpFv");


nn::Result
InitializeAdmin(void)
   asm("InitializeAdmin__Q2_2nn2fpFv");


nn::Result
Initialize(void)
   asm("Initialize__Q2_2nn2fpFv");


bool
IsFriendRequestAllowed(void)
   asm("IsFriendRequestAllowed__Q2_2nn2fpFv");


bool
IsInitializedAdmin(void)
   asm("IsInitializedAdmin__Q2_2nn2fpFv");


bool
IsInitialized(void)
   asm("IsInitialized__Q2_2nn2fpFv");


bool
IsInvitation(nn::fp::GameMode *, nn::act::PrincipalId myPrincipalId, unsigned int /*unk*/)
   asm("IsInvitation__Q2_2nn2fpFPCQ3_2nn2fp8GameModeUiT2");


bool
IsJoinableForFriendListViewer(nn::fp::FriendPresence *, unsigned int, unsigned long long)
   asm("IsJoinableForFriendListViewer__Q2_2nn2fpFPCQ3_2nn2fp14FriendPresenceUiUL");


bool
IsJoinableForFriendListViewer(nn::fp::Presence *, unsigned int, unsigned long long)
   asm("IsJoinableForFriendListViewer__Q2_2nn2fpFPCQ3_2nn2fp8PresenceUiUL");


bool
IsJoinable(nn::fp::FriendPresence *, unsigned long long)
   asm("IsJoinable__Q2_2nn2fpFPCQ3_2nn2fp14FriendPresenceUL");


bool
IsOnline(void)
   asm("IsOnline__Q2_2nn2fpFv");


bool
IsPreferenceValid(void)
   asm("IsPreferenceValid__Q2_2nn2fpFv");


bool
IsRecentPlayRecordCorrupted(void)
   asm("IsRecentPlayRecordCorrupted__Q2_2nn2fpFv");


bool
IsRequestBlockForced(void)
   asm("IsRequestBlockForced__Q2_2nn2fpFv");


nn::Result
LoginAsync(FPAsyncCallback, void *)
   asm("LoginAsync__Q2_2nn2fpFPFQ2_2nn6ResultPv_vPv");


nn::Result
Logout(void)
   asm("Logout__Q2_2nn2fpFv");


nn::Result
MarkFriendRequestsAsReceivedAsync(unsigned long long *, unsigned int, FPAsyncCallback, void *)
   asm("MarkFriendRequestsAsReceivedAsync__Q2_2nn2fpFPCULUiPFQ2_2nn6ResultPv_vPv");


nn::Result
RegisterAccountAsync(FPAsyncCallback, void *)
   asm("RegisterAccountAsync__Q2_2nn2fpFPFQ2_2nn6ResultPv_vPv");


nn::Result
RemoveBlackListAsync(unsigned int, FPAsyncCallback, void *)
   asm("RemoveBlackListAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


nn::Result
RemoveFriendAsync(unsigned int, FPAsyncCallback, void *)
   asm("RemoveFriendAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


uint32_t
   ResultToErrorCode(nn::Result)
      asm("ResultToErrorCode__Q2_2nn2fpFQ2_2nn6Result");


nn::Result
SetInvitationParameter(nn::fp::GameMode *, unsigned int *, unsigned int, bool)
   asm("SetInvitationParameter__Q2_2nn2fpFPQ3_2nn2fp8GameModePCUiUib");


nn::Result
   SetLedEventMask(uint32_t)
      asm("SetLedEventMask__Q2_2nn2fpFUi");


nn::Result
SetNotificationHandler(uint32_t /*notificationFlags = 1 << NotificationType */, NotificationHandlerFn, void *)
   asm("SetNotificationHandler__Q2_2nn2fpFUiPFQ3_2nn2fp16NotificationTypeUiPv_vPv");


nn::Result
UnlockParentalControlTemporarily(const char pinCode[5])
   asm("UnlockParentalControlTemporarily__Q2_2nn2fpFPCc");


nn::Result
UpdateCommentAsync(const char16_t *, FPAsyncCallback, void *)
   asm("UpdateCommentAsync__Q2_2nn2fpFPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
UpdateGameModeDescription(const char16_t *description)
   asm("UpdateGameModeDescription__Q2_2nn2fpFPCw");


nn::Result
UpdateGameModeEx(nn::fp::GameMode *, const char16_t *)
   asm("UpdateGameModeEx__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameModeForOverlayApplication(nn::fp::GameMode *, const char16_t *)
   asm("UpdateGameModeForOverlayApplication__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameMode(nn::fp::GameMode *, const char16_t *)
   asm("UpdateGameMode__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameMode(nn::fp::GameMode *, const char16_t *, unsigned int)
   asm("UpdateGameMode__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCwUi");


nn::Result
UpdateMiiAsync(FFLStoreData *, char16_t *, FPAsyncCallback, void *)
   asm("UpdateMiiAsync__Q2_2nn2fpFPC12FFLStoreDataPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
UpdateMiiAsync(FFLStoreData *miiData, FPAsyncCallback, void *)
   asm("UpdateMiiAsync__Q2_2nn2fpFPC12FFLStoreDataPFQ2_2nn6ResultPv_vPv");


nn::Result
UpdatePlayingGame(nn::fp::GameKey *, unsigned int)
   asm("UpdatePlayingGame__Q2_2nn2fpFPCQ3_2nn2fp7GameKeyUi");


nn::Result
UpdatePlayingOverlayApplication(nn::fp::GameKey *, unsigned int)
   asm("UpdatePlayingOverlayApplication__Q2_2nn2fpFPCQ3_2nn2fp7GameKeyUi");


nn::Result
UpdatePreferenceAsync(nn::fp::Preference *, FPAsyncCallback, void *)
   asm("UpdatePreferenceAsync__Q2_2nn2fpFPCQ3_2nn2fp10PreferencePFQ2_2nn6ResultPv_vPv");

} // namespace fp
} // namespace nn

#endif // ifdef __cplusplus