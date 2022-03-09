#pragma once
#include <wut.h>
#include <nn/result.h>
#include <nn/ffl/miidata.h>
#include <nn/act.h>

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

using DateTime = uint64_t;

//! Names taken from SONIC LOST WORLD (sonic2013.rpx).
enum NotificationType
{
    NOTIFICATION_ONLINE             =  1,
    NOTIFICATION_OFFLINE            =  2,
    NOTIFICATION_PREFERENCE         =  3,
    NOTIFICATION_FRIEND_ONLINE      =  4,
    NOTIFICATION_FRIEND_OFFLINE     =  5,
    NOTIFICATION_FRIEND_PRESENCE    =  6,
    NOTIFICATION_FRIEND_MII         =  7,
    NOTIFICATION_FRIEND_PROFILE     =  8,
    NOTIFICATION_FRIEND_ADDED       =  9,
    NOTIFICATION_FRIEND_REMOVED     = 10,
    NOTIFICATION_MY_REQUEST_ADDED   = 11,
    NOTIFICATION_MY_REQUEST_REMOVED = 12,
    NOTIFICATION_MY_REQUEST_UPDATED = 13,
    NOTIFICATION_BLACKLIST_ADDED    = 14,
    NOTIFICATION_BLACKLIST_REMOVED  = 15,
    NOTIFICATION_BLACKLIST_UPDATED  = 16,
    NOTIFICATION_REQUEST_ADDED      = 17,
    NOTIFICATION_REQUEST_REMOVED    = 18,
};

struct GameKey
{
    uint64_t titleId;
    uint16_t unk_0x8;
    uint32_t unk_0xC;
};
WUT_CHECK_OFFSET(GameKey, 0x00, titleId);
WUT_CHECK_SIZE(GameKey, 0x10);

struct RecentPlayRecordEx
{
    /*! TODO: */
};

struct RecentPlayRecord
{
    WUT_UNKNOWN_BYTES(0x4C);
};
WUT_CHECK_SIZE(RecentPlayRecord, 0x4C);

struct Preference
{
    WUT_UNKNOWN_BYTES(4);
};
WUT_CHECK_SIZE(Preference, 0x04);

struct GameMode
{
    uint32_t unk_0x0; // BOOL isOnlinePlaying | isInJoinableLobby
    uint32_t unk_0x4; // possibly a kind of mode enum
    void *unk_0x8; // pointer to some struct
    uint32_t unk_0xC;
    nn::act::PrincipalId principalId; // only set when playing "online"
    uint32_t unk_0x14;
    uint32_t unk_0x18;
    short unk_0x1c; // port ????
    WUT_UNKNOWN_BYTES(0xC);
};
WUT_CHECK_SIZE(GameMode, 0x2C);

struct Presence
{
    /*! TODO: */
};

struct FriendPresence
{
    WUT_UNKNOWN_BYTES(0x2c); // GameMode ??
    uint32_t unk_0x2c;
    bool unk_0x30;
    bool unk_0x31;
    bool unk_0x32;
    bool unk_0x33;
};
WUT_CHECK_SIZE(FriendPresence, 0x34);

struct MyPresence
{
    GameMode gameMode;
    uint32_t unk_0x2c; // possibly 3 uint8_t values
    char16_t presenceText[64];
};
WUT_CHECK_SIZE(MyPresence, 0xB0);

struct BasicInfo
{
    WUT_UNKNOWN_BYTES(0x68);
};
WUT_CHECK_SIZE(BasicInfo, 0x68);

struct BlackListedPrincipal
{
    /*! TODO: */
};

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
    /*! TODO: */
    WUT_UNKNOWN_BYTES(0xB8);
};
WUT_CHECK_SIZE(FriendData, 0xB8);

struct GameModeDescription
{
    /*! TODO: */
};

struct FriendRequest
{
    /*! Super Untested */
    uint32_t unk_0x00;
    uint8_t unk_0x04;
    uint8_t unk_0x05;
    uint8_t unk_0x06[34];
    uint8_t unk_0x28[40];
    uint32_t unk_0x54;
    uint32_t unk_0x58;
    uint16_t unk_0x5c;
    uint16_t unk_0x5e;
    uint8_t unk_0x5f;
    uint8_t unk_0x60;
    uint8_t unk_0x61;
    uint8_t unk_0x62;
    uint8_t unk_0x63;
};
WUT_CHECK_OFFSET(FriendRequest, 0x00, unk_0x00);
WUT_CHECK_OFFSET(FriendRequest, 0x04, unk_0x04);
WUT_CHECK_OFFSET(FriendRequest, 0x05, unk_0x05);
WUT_CHECK_OFFSET(FriendRequest, 0x06, unk_0x06);
WUT_CHECK_SIZE(FriendRequest, 0x64);

typedef void(*FPAsyncCallback)(nn::Result, void *);
typedef void(*NotificationHandlerFn)(nn::fp::NotificationType, nn::act::PrincipalId, void *);

nn::Result
AcceptFriendRequestAsync(unsigned long long, FPAsyncCallback, void *)
    asm("AcceptFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
AddBlackListAsync(unsigned int, nn::fp::GameKey *, FPAsyncCallback, void *)
    asm("AddBlackListAsync__Q2_2nn2fpFUiPCQ3_2nn2fp7GameKeyPFQ2_2nn6ResultPv_vPv");


nn::Result
AddBlackListAsync(unsigned int, FPAsyncCallback, void *)
    asm("AddBlackListAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendAsync(char *, FPAsyncCallback, void *)
    asm("AddFriendAsync__Q2_2nn2fpFPCcPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendAsync(nn::act::PrincipalId, FPAsyncCallback, void *)
    asm("AddFriendAsync__Q2_2nn2fpFUiPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestAsync(nn::fp::RecentPlayRecordEx *, wchar_t *, FPAsyncCallback, void *)
    asm("AddFriendRequestAsync__Q2_2nn2fpFPCQ3_2nn2fp18RecentPlayRecordExPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestAsync(unsigned int, unsigned char, wchar_t *, unsigned char, wchar_t *, FPAsyncCallback, void *)
    asm("AddFriendRequestAsync__Q2_2nn2fpFUiUcPCwT2T3PFQ2_2nn6ResultPv_vPv");


nn::Result
AddFriendRequestNoTitleAsync(unsigned int, unsigned char, wchar_t *, unsigned char, wchar_t *, FPAsyncCallback, void *)
    asm("AddFriendRequestNoTitleAsync__Q2_2nn2fpFUiUcPCwT2T3PFQ2_2nn6ResultPv_vPv");


nn::Result
AddRecentPlayRecordEx(nn::fp::RecentPlayRecordEx *, unsigned int)
    asm("AddRecentPlayRecordEx__Q2_2nn2fpFPCQ3_2nn2fp18RecentPlayRecordExUi");


nn::Result
AddRecentPlayRecord(nn::fp::RecentPlayRecord *, unsigned int)
    asm("AddRecentPlayRecord__Q2_2nn2fpFPCQ3_2nn2fp16RecentPlayRecordUi");


nn::Result
CancelFriendRequestAsync(unsigned long long, FPAsyncCallback, void *)
    asm("CancelFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
CheckSettingStatusAsync(unsigned char *, FPAsyncCallback, void *)
    asm("CheckSettingStatusAsync__Q2_2nn2fpFPUcPFQ2_2nn6ResultPv_vPv");


nn::Result
ClearLedEvent(void)
    asm("ClearLedEvent__Q2_2nn2fpFv");


nn::Result
DeleteFriendFlagsAsync(unsigned int *, unsigned int, unsigned int, FPAsyncCallback, void *)
    asm("DeleteFriendFlagsAsync__Q2_2nn2fpFPCUiUiT2PFQ2_2nn6ResultPv_vPv");


nn::Result
DeleteFriendRequestAsync(unsigned long long, FPAsyncCallback, void *)
    asm("DeleteFriendRequestAsync__Q2_2nn2fpFULPFQ2_2nn6ResultPv_vPv");


nn::Result
DeleteRecentPlayRecordAll(void)
    asm("DeleteRecentPlayRecordAll__Q2_2nn2fpFv");


nn::Result
DeleteSaveDirectory(unsigned int)
    asm("DeleteSaveDirectory__Q2_2nn2fpFUi");


nn::Result
DenyFriendRequestAsync(unsigned long long, FPAsyncCallback, void *)
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
GetBlackListAccountId(char outAccountId[nn::act::AccountIdSize], unsigned int *, unsigned int)
    asm("GetBlackListAccountId__Q2_2nn2fpFPA17_cPCUiUi");


nn::Result
GetBlackListAdditionalTime(nn::fp::DateTime *, unsigned int *, unsigned int)
    asm("GetBlackListAdditionalTime__Q2_2nn2fpFPQ3_2nn2fp8DateTimePCUiUi");


nn::Result
GetBlackListEx(nn::fp::BlackListedPrincipal *outBlackListed, unsigned int *, unsigned int)
    asm("GetBlackListEx__Q2_2nn2fpFPQ3_2nn2fp20BlackListedPrincipalPCUiUi");


nn::Result
GetBlackList(unsigned int *, unsigned int *, unsigned int, unsigned int)
    asm("GetBlackList__Q2_2nn2fpFPUiT1UiT3");


//! outAccountIds must be of size count * nn::act::AccountIdSize
nn::Result
GetFriendAccountId(char *outAccountIds, unsigned int *friendIdsBuf, unsigned int count)
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
GetFriendListEx(nn::fp::FriendData *outFriendData, unsigned int *principalBuf, unsigned int count)
    asm("GetFriendListEx__Q2_2nn2fpFPQ3_2nn2fp10FriendDataPCUiUi");


/*
 * Reads a given size into a uint32_t(nn::act::PricapalId) buffer.
**/
nn::Result
GetFriendList(nn::act::PrincipalId *outPrincipalBuffer, unsigned int *outPrincipalBufferReadCount, unsigned int unkn/*slotId maybe*/, unsigned int principalBufferSize)
    asm("GetFriendList__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendMii(FFLStoreData *, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendMii__Q2_2nn2fpFP12FFLStoreDataPCUiUi");


nn::Result
GetFriendPlayingGame(nn::fp::GameKey *outGameKey, nn::fp::GameModeDescription *outGameModeDescription, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendPlayingGame__Q2_2nn2fpFPQ3_2nn2fp7GameKeyPQ3_2nn2fp19GameModeDescriptionPCUiUi");


nn::Result
GetFriendPresenceEx(nn::fp::FriendPresence *, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendPresenceEx__Q2_2nn2fpFPQ3_2nn2fp14FriendPresencePCUiUi");


nn::Result
GetFriendPresence(nn::fp::FriendPresence *, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendPresence__Q2_2nn2fpFPQ3_2nn2fp14FriendPresencePCUiUi");


nn::Result
GetFriendProfile(nn::fp::Profile *, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendProfile__Q2_2nn2fpFPQ3_2nn2fp7ProfilePCUiUi");


nn::Result
GetFriendRelationship(uint8_t *outRelationshipNum, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendRelationship__Q2_2nn2fpFPUcPCUiUi");


nn::Result
GetFriendRequestAccountId(char outAccountId[17], nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendRequestAccountId__Q2_2nn2fpFPA17_cPCUiUi");


nn::Result
GetFriendRequestListEx(nn::fp::FriendRequest *, nn::act::PrincipalId *principalBuffer, unsigned int count)
    asm("GetFriendRequestListEx__Q2_2nn2fpFPQ3_2nn2fp13FriendRequestPCUiUi");


nn::Result
GetFriendRequestList(unsigned int *, unsigned int *, unsigned int, unsigned int)
    asm("GetFriendRequestList__Q2_2nn2fpFPUiT1UiT3");


nn::Result
GetFriendRequestMessageId(unsigned long long *, unsigned int *, unsigned int)
    asm("GetFriendRequestMessageId__Q2_2nn2fpFPULPCUiUi");


nn::Result
GetFriendScreenName(wchar_t outScreenName[nn::act::MiiNameSize], unsigned int *, unsigned int, bool, unsigned char *)
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
GetMyScreenName(wchar_t *outScreenName)
    asm("GetMyScreenName__Q2_2nn2fpFPw");


nn::Result
GetRecentPlayRecord(nn::fp::RecentPlayRecordEx *, unsigned int *, unsigned int, unsigned int)
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
IsInvitation(nn::fp::GameMode *, unsigned int myPrincipalId, unsigned int)
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
SetNotificationHandler(unsigned int /*accessFlags?? */, NotificationHandlerFn, void *)
    asm("SetNotificationHandler__Q2_2nn2fpFUiPFQ3_2nn2fp16NotificationTypeUiPv_vPv");


nn::Result
UnlockParentalControlTemporarily(char *)
    asm("UnlockParentalControlTemporarily__Q2_2nn2fpFPCc");


nn::Result
UpdateCommentAsync(wchar_t *, FPAsyncCallback, void *)
    asm("UpdateCommentAsync__Q2_2nn2fpFPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
UpdateGameModeDescription(wchar_t *)
    asm("UpdateGameModeDescription__Q2_2nn2fpFPCw");


nn::Result
UpdateGameModeEx(nn::fp::GameMode *, wchar_t *)
    asm("UpdateGameModeEx__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameModeForOverlayApplication(nn::fp::GameMode *, wchar_t *)
    asm("UpdateGameModeForOverlayApplication__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameMode(nn::fp::GameMode *, wchar_t *)
    asm("UpdateGameMode__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCw");


nn::Result
UpdateGameMode(nn::fp::GameMode *, wchar_t *, unsigned int)
    asm("UpdateGameMode__Q2_2nn2fpFPCQ3_2nn2fp8GameModePCwUi");


nn::Result
UpdateMiiAsync(FFLStoreData *, wchar_t *, FPAsyncCallback, void *)
    asm("UpdateMiiAsync__Q2_2nn2fpFPC12FFLStoreDataPCwPFQ2_2nn6ResultPv_vPv");


nn::Result
UpdateMiiAsync(FFLStoreData *, FPAsyncCallback, void *)
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