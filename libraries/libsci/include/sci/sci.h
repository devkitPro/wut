#pragma once

#include <wut.h>
#include <coreinit/userconfig.h>
#include <coreinit/debug.h>
#include <coreinit/mcp.h>
#include <nn/act/client_cpp.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

// typedef void(*SCIReportFunc_t)(const char*, ...)
#if defined(SCI_USE_CUSTOM_REPORT_FUNC) && defined(SCI_CUSTOM_REPORT_FUNC)
#define SCI_REPORT_FUNC       SCI_CUSTOM_REPORT_FUNC
#else
// Default report function
#define SCI_REPORT_FUNC       OSReport
#endif

typedef struct _SCICafeSettings SCICafeSettings;
typedef struct _SCIParentalSettings SCIParentalSettings;
typedef struct _SCIParentalAccountSettings SCIParentalAccountSettings;
typedef struct _SCIAreaInfo SCIAreaInfo;

typedef enum _SCIStatus {
    SCI_STATUS_OK                              =  1,
    SCI_STATUS_ERROR                           =  0,
    SCI_STATUS_ERROR_READ                      = -1,
    SCI_STATUS_ERROR_WRITE                     = -2,
    SCI_STATUS_ERROR_OPEN                      = -3,
    SCI_STATUS_ERROR_KEY_NOT_FOUND             = -4,
    SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT = -5,
    SCI_STATUS_ERROR_INVALID_BUFFER_SIZE       = -6,
    SCI_STATUS_ERROR_INVALID_ARGUMENT          = -7,
}SCIStatus;

// https://github.com/cemu-project/Cemu/blob/main/src/config/CemuConfig.h#L158
typedef enum _Language : int8_t {
	JA = 0,
	EN = 1,
	FR = 2,
	DE = 3,
	IT = 4,
	ES = 5,
	ZH = 6,
	KO = 7,
	NL = 8,
	PT = 9,
	RU = 10,
	TW = 11,
}Language;

struct _SCIParentalAccountSettings {
    short version;
    WUT_UNKNOWN_BYTES(2);
    int game_rating;
    bool eshop_purchase;
    bool friend_reg;
    bool acct_modify;
    bool data_manage;
    bool int_setting;
    bool country_setting;
    bool sys_init;
    bool int_movie;
    int8_t int_browser;
    bool net_communication_on_game;
    int8_t network_launcher;
    int8_t entertainment_launcher;
};
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x00, version);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x04, game_rating);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x08, eshop_purchase);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x09, friend_reg);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0A, acct_modify);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0B, data_manage);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0C, int_setting);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0D, country_setting);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0E, sys_init);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x0F, int_movie);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x10, int_browser);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x11, net_communication_on_game);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x12, network_launcher);
WUT_CHECK_OFFSET(SCIParentalAccountSettings, 0x13, entertainment_launcher);
WUT_CHECK_SIZE(SCIParentalAccountSettings, 0x14);

struct _SCICafeSettings {
    short version;
    int language;
    int country;
    bool eula_agree;
    int eula_version;
    bool initial_launch;
    bool eco;
    bool fast_boot;
};
WUT_CHECK_OFFSET(SCICafeSettings, 0x00, version);
WUT_CHECK_OFFSET(SCICafeSettings, 0x04, language);
WUT_CHECK_OFFSET(SCICafeSettings, 0x08, country);
WUT_CHECK_OFFSET(SCICafeSettings, 0x0C, eula_agree);
WUT_CHECK_OFFSET(SCICafeSettings, 0x10, eula_version);
WUT_CHECK_OFFSET(SCICafeSettings, 0x14, initial_launch);
WUT_CHECK_OFFSET(SCICafeSettings, 0x15, eco);
WUT_CHECK_OFFSET(SCICafeSettings, 0x16, fast_boot);
WUT_CHECK_SIZE(SCICafeSettings, 0x18);

struct _SCIParentalSettings {
    short version;
    bool enable;
    char pin_code[5];
    int8_t sec_question;
    char sec_answer[0x101];
    char email_address[0x401];
    bool permit_delete_all;
    uint32_t rating_organization;
};
WUT_CHECK_OFFSET(SCIParentalSettings, 0x00, version);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x02, enable);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x03, pin_code);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x08, sec_question);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x09, sec_answer);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x10A, email_address);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x50B, permit_delete_all);
WUT_CHECK_OFFSET(SCIParentalSettings, 0x50C, rating_organization);
WUT_CHECK_SIZE(SCIParentalSettings, 0x510);

struct _SCIAreaInfo
{
    char16_t areaName[64];
    short unk_0x80;
    short unk_0x82;
};
WUT_CHECK_OFFSET(_SCIAreaInfo, 0x00, areaName);
WUT_CHECK_OFFSET(_SCIAreaInfo, 0x80, unk_0x80);
WUT_CHECK_OFFSET(_SCIAreaInfo, 0x82, unk_0x82);
WUT_CHECK_SIZE(_SCIAreaInfo, 0x84);

SCIStatus
SCIGetCafeLanguage(int *outLanguage);

SCIStatus
SCIGetCafeCountry(int *outCountry);

SCIStatus
SCIGetCountryName(void *buffer, uint32_t bufferSize, uint32_t param_3, uint32_t language);

SCIStatus 
SCIGetCountryNameUtf16(char16_t *buffer, uint32_t bufferSize, uint32_t country, uint32_t language);

SCIStatus
SCIGetAreaInfoUtf16(SCIAreaInfo *areaInfoUtf16, uint32_t country, int language);

SCIStatus
SCIGetAreaInfo(char *buffer, uint32_t param_2, uint32_t param_3);

SCIStatus
SCIGetISOResource(char *buffer, uint32_t bufferSize, const char *filename);

char *
SCIGetCountryCodeA2(int country);

char *
SCIGetLanguageCodeA2(int language);

SCIStatus
SCIGetCafeXMLVersion(uint8_t *outVersion);

SCIStatus
SCISetCafeXMLVersion(uint8_t version);

SCIStatus
SCISetCafeLanguage(int language);

SCIStatus
SCISetCafeCountry(int country);

SCIStatus
SCIGetCafeEulaVersion(uint32_t *outEulaVersion);

SCIStatus
SCISetCafeEulaVersion(uint32_t eulaVersion);

SCIStatus
SCIGetCafeInitialLaunch(bool *outInitialLaunch);

SCIStatus
SCISetCafeInitialLaunch(uint8_t initialLaunch);

SCIStatus
SCIGetCafeECO(uint8_t *outECO);

SCIStatus
SCISetCafeECO(uint8_t outECO);

SCIStatus
SCIGetCafeFastBoot(bool *outFastBoot);

SCIStatus
SCISetCafeFastBoot(bool fastBoot);

SCIStatus
SCIGetCafeSettings(SCICafeSettings *);

SCIStatus
SCISetCafeSettings(SCICafeSettings settings);

SCIStatus
SCIInitCafeSettings(SCICafeSettings settings);

SCIStatus
SCIGetParentalXMLVersion(uint16_t *outVersion);

SCIStatus
SCISetParentalXMLVersion(uint16_t version);

SCIStatus
SCIGetParentalEnable(bool *outEnabled);

SCIStatus
SCISetParentalEnable(bool enable);

SCIStatus
SCIGetParentalPinCode(char *outPin, int pinLenght);

SCIStatus
SCISetParentalPinCode(char *pin, int pinLenght);

SCIStatus
SCICheckParentalPinCode(const char *pinCode);

SCIStatus
SCIGetParentalSecQuestion(int8_t *outQeuestionType);

/// @brief 
/// @param questionType 
/// 0 = "What did you call your first pet?"
/// 1 = "Where were you born?"
/// 2 = "What is your favourite sports team?"
/// 3 = "what was your favourite birthday present?"
/// 4 = "What is your favourite film?"
/// 5 = "If you could go anywhere, where would you go?"
/// ? = "(Create your own secret question)"
/// @return SCI_STATUS_OK on success
SCIStatus
SCISetParentalSecQuestion(int8_t questionType);

SCIStatus
SCIGetParentalSecAnswer(char *buffer, int bufferSize);

SCIStatus
SCISetParentalSecAnswer(char *buffer, int bufferSize);

SCIStatus
SCIGetParentalEmailAddress(char *outEmail, int emailBufferSize);

SCIStatus
SCISetParentalEmailAddress(char *email, int emailBufferSize);

SCIStatus
SCIGetParentalPermitDeleteAll(bool *permitDeleteAll);

SCIStatus
SCISetParentalPermitDeleteAll(bool permitDeleteAll);

SCIStatus
SCIGetParentalRatingOrganization(uint32_t *outRating);

SCIStatus
SCISetParentalRatingOrganization(uint32_t rating);

SCIStatus
SCIGetParentalSettings(SCIParentalSettings *settings);

SCIStatus
SCISetParentalSettings(SCIParentalSettings *settings);

SCIStatus
SCIInitParentalSettings(SCIParentalSettings *settings);

SCIStatus
SCIGetSystemSettings(MCPSysProdSettings *);

SCIStatus
SCIGetSystemProdArea(MCPRegion *systemProdArea);

SCIStatus
SCIGetPlatformRegion(MCPRegion *platformRegion);

SCIStatus
SCIGetSystemGameRegion(MCPRegion *gameRegion);

SCIStatus
_SCIReadSysConfig(const char *configName, UCDataType dataType, size_t dataSize, void *data);

SCIStatus
_SCIWriteSysConfig(const char *configName, UCDataType dataType, size_t dataSize, void *data);

SCIStatus
_SCIDeleteSysConfig(const char *configName, UCDataType dataType, size_t dataSize, void *data);

#ifdef __cplusplus

SCIStatus
SCIGetParentalAccountGameRating(int *outGameRating, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountGameRating(int gameRating, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountEShopPurchase(bool *outEShopPurchase, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountEShopPurchase(bool eshopPurchase, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountNetCommunicationOnGame(bool *outNetCommunication, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountNetCommunicationOnGame(bool netCommunication, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountFriendReg(bool *outFriendReg, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountFriendReg(bool friendReg, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountAcctModify(bool *outAcctModify, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountAcctModify(bool acctModify, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountDataManage(bool *outAccountDataMange, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountDataManage(bool accountDataManage, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountIntSetting(bool *outAccountIntSetting, nn::act::SlotNo accountSlotNo);

SCIStatus
SCISetParentalAccountIntSetting(bool accountIntSetting, nn::act::SlotNo accountSlotNo);

SCIStatus
SCIGetParentalAccountCountrySetting();

SCIStatus
SCISetParentalAccountCountrySetting();

SCIStatus
SCIGetParentalAccountSysInit();

SCIStatus
SCISetParentalAccountSysInit();

SCIStatus
SCIGetParentalAccountIntMovie();

SCIStatus
SCISetParentalAccountIntMovie();

SCIStatus
SCIGetParentalAccountIntBrowser();

SCIStatus
SCISetParentalAccountIntBrowser();

SCIStatus
SCIGetParentalAccountNetworkLauncher();

SCIStatus
SCISetParentalAccountNetworkLauncher();

SCIStatus
SCIGetParentalAccountEntertainmentLauncher();

SCIStatus
SCISetParentalAccountEntertainmentLauncher();

SCIStatus
SCIGetParentalAccountSettings();

SCIStatus
SCISetParentalAccountSettings();

SCIStatus
SCIInitParentalAccountSettingsUC();

SCIStatus
SCIInitParentalAccountSettings();

#endif

#ifdef __cplusplus
}
#endif