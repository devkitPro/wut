#include <stdio.h>
#include <string.h>
#include <sci/sci.h>


#define ValidateBool(boolValPtr) (*(int8_t*)boolValPtr >= 1) && !(*(int8_t*)boolValPtr < 0)

#define SCI_REPORT(FMT, ARGS...) SCI_REPORT_FUNC("SCI: " FMT "\n", ## ARGS);
#define SCI_REPORT_ERROR(FMT, ARGS...) SCI_REPORT_FUNC("SCI:ERROR:%s:%d: " FMT "\n", __FUNCTION__, __LINE__, ## ARGS)

#define makeParentalConfig(num) \
{ \
    { "p_acct" # num,                              0x777, UC_DATATYPE_COMPLEX,         UC_ERROR_OK, 0, NULL }, \
    { "p_acct" # num ".version",                   0x777, UC_DATATYPE_UNSIGNED_SHORT,  UC_ERROR_OK, 2, NULL }, \
    { "p_acct" # num ".game_rating",               0x777, UC_DATATYPE_UNSIGNED_INT,    UC_ERROR_OK, 4, NULL }, \
    { "p_acct" # num ".eshop_purchase",            0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".friend_reg",                0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".acct_modify",               0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".data_manage",               0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".int_setting",               0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".country_setting",           0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".sys_init",                  0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".int_browser",               0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".int_movie",                 0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".net_communication_on_game", 0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".network_launcher",          0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }, \
    { "p_acct" # num ".entertainment_launcher",    0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }  \
}
static constexpr const UCSysConfig s_SCIDefaultParentalConfigs[12][15] = {
    makeParentalConfig(1),
    makeParentalConfig(2),
    makeParentalConfig(3),
    makeParentalConfig(4),
    makeParentalConfig(5),
    makeParentalConfig(6),
    makeParentalConfig(7),
    makeParentalConfig(8),
    makeParentalConfig(9),
    makeParentalConfig(10),
    makeParentalConfig(11),
    makeParentalConfig(12),
};
#undef makeParentalConfig

static constexpr SCIParentalAccountSettings s_SCIDefaultParentalSettings {
    .version                   = 10,
    .game_rating               = 12,
    .eshop_purchase            = false,
    .friend_reg                = false,
    .acct_modify               = false,
    .data_manage               = false,
    .int_setting               = false,
    .country_setting           = false,
    .sys_init                  = false,
    .int_movie                 = false,
    .int_browser               = false,
    .net_communication_on_game = false,
    .network_launcher          = 0,
    .entertainment_launcher    = 0
};

static bool VerifyRestrictionLevel(int8_t *lvl)
{
    if (*lvl > 2)
    {
        *lvl = 2;
        return false;
    }
    if (*lvl < 0)
    {
        *lvl = 0;
        return false;
    }
    return true;
}


static bool VerifyValueRange(SCIParentalAccountSettings *parentalAccountSettings)
{
    bool result = true;
    if (static_cast<int8_t>(parentalAccountSettings->eshop_purchase) < 0) {
        result = false;
        parentalAccountSettings->eshop_purchase = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->friend_reg) < 0) {
        result = 0;
        parentalAccountSettings->friend_reg = false;
    }

    if (static_cast<int8_t>(parentalAccountSettings->acct_modify) < 0) {
        result = 0;
        parentalAccountSettings->acct_modify = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->data_manage) < 0) {
        result = 0;
        parentalAccountSettings->data_manage = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->int_setting) < 0) {
        result = 0;
        parentalAccountSettings->int_setting = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->country_setting) < 0) {
        result = 0;
        parentalAccountSettings->country_setting = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->sys_init) < 0) {
        result = 0;
        parentalAccountSettings->sys_init = false;
    }
    if (static_cast<int8_t>(parentalAccountSettings->int_movie) < 0) {
        result = 0;
        parentalAccountSettings->int_movie = false;
    }
    
    if (!VerifyRestrictionLevel(&parentalAccountSettings->int_browser)) result = false;
    if (static_cast<int8_t>(parentalAccountSettings->net_communication_on_game) < 0) {
        result = 0;
        parentalAccountSettings->net_communication_on_game = false;
    }
    if (!VerifyRestrictionLevel(&parentalAccountSettings->int_browser)) result = false;
    return result;
}

static nn::act::SlotNo SCIGetUCParentalAccountSlotNum(nn::act::SlotNo childSlotNo)
{
    nn::act::SlotNo parentalSlotNo;
    nn::Result res = nn::act::GetParentalControlsSlotNoEx(&parentalSlotNo, childSlotNo);
    if (res.IsFailure())
    {
        // nn::Result::ConstRangeBase<const nn::Result::Level::LEVEL_STATUS, const nn::Result::Module::RESULT_MODULE_NN_ACT, int const = 128128>::operator nn::Result(void) const
        if (res != nn::Result(nn::Result::Level::LEVEL_STATUS, nn::Result::Module::RESULT_MODULE_NN_ACT, 128128))
        {
            if (res == nn::Result(nn::Result::LEVEL_USAGE, nn::Result::Module::RESULT_MODULE_NN_ACT, 0xfa80))
            {
                SCI_REPORT("Account library is not initialized!");
            }

            else if (res == nn::Result(nn::Result::LEVEL_USAGE, nn::Result::Module::RESULT_MODULE_NN_ACT, 0x12c80))
            {
                SCI_REPORT("Invalid pointer detected!");
            }
        }
        return 0;
    }
    return parentalSlotNo;
}


SCIStatus SCIGetParentalAccountGameRating(int *outGameRating, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.game_rating", parentalSlotNo);
    return _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_INT, 4, outGameRating);
}

SCIStatus SCISetParentalAccountGameRating(int gameRating, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.game_rating", parentalSlotNo);
    int write_gameRating = gameRating;
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_INT, 4, &write_gameRating);
}

SCIStatus SCIGetParentalAccountEShopPurchase(bool *outEShopPurchase, nn::act::SlotNo accountSlotNo)
{   
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64,"p_acct%d.eshop_purchase", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outEShopPurchase);
    *outEShopPurchase = ValidateBool(outEShopPurchase);
    return err;
}

SCIStatus SCISetParentalAccountEShopPurchase(bool eshopPurchase, nn::act::SlotNo accountSlotNo)
{   
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    eshopPurchase = ValidateBool(&eshopPurchase);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64,"p_acct%d.eshop_purchase", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &eshopPurchase);
}

SCIStatus SCIGetParentalAccountNetCommunicationOnGame(bool *outNetCommunication, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64,"p_acct%d.net_communication_on_game", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outNetCommunication);
    *outNetCommunication = ValidateBool(outNetCommunication);
    return err;
}

SCIStatus SCISetParentalAccountNetCommunicationOnGame(bool netCommunication, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    
    netCommunication = ValidateBool(&netCommunication);

    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64,"p_acct%d.net_communication_on_game", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &netCommunication);
}

SCIStatus SCIGetParentalAccountFriendReg(bool *outFriendReg, nn::act::SlotNo accountSlotNo)
{
    char name_buffer[64] = { 0 };
    
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    snprintf(name_buffer, 64, "p_acct%d.friend_reg", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outFriendReg);
    *outFriendReg = ValidateBool(outFriendReg);
    return err;
}

SCIStatus SCISetParentalAccountFriendReg(bool friendReg, nn::act::SlotNo accountSlotNo)
{
    char name_buffer[64] = { 0 };

    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0)
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;

    friendReg = ValidateBool(&friendReg);
    snprintf(name_buffer, 64, "p_acct%d.friend_reg", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &friendReg);
}

SCIStatus SCIGetParentalAccountAcctModify(bool *outAcctModify, nn::act::SlotNo accountSlotNo)
{
    char name_buffer[64] = { 0 };
    
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    snprintf(name_buffer, 64, "p_acct%d.acct_modify", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outAcctModify);
    *outAcctModify = ValidateBool(outAcctModify);
    return err;
}

SCIStatus SCISetParentalAccountAcctModify(bool acctModify, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }

    acctModify = ValidateBool(&acctModify);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.acct_modify", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &acctModify);
}

SCIStatus SCIGetParentalAccountDataManage(bool *outDataManage, nn::act::SlotNo accountSlotNo)
{
    char name_buffer[64] = { 0 };
    
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    snprintf(name_buffer, 64, "p_acct%d.data_manage", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outDataManage);
    *outDataManage = ValidateBool(outDataManage);
    return err;
}

SCIStatus SCISetParentalAccountDataManage(bool dataManage, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    dataManage = ValidateBool(&dataManage);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.data_manage", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &dataManage);
}

SCIStatus SCIGetParentalAccountIntSetting(bool *outIntSetting, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.int_setting", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outIntSetting);
    *outIntSetting = ValidateBool(outIntSetting);
    return err;
}

SCIStatus SCISetParentalAccountIntSetting(bool intSetting, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    intSetting = ValidateBool(&intSetting);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.int_setting", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &intSetting);
}

SCIStatus SCIGetParentalAccountCountrySetting(bool *outCountrySetting, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.country_setting", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outCountrySetting);
    *outCountrySetting = ValidateBool(outCountrySetting);
    return err;
}

SCIStatus SCISetParentalAccountCountrySetting(bool countrySetting, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 64, "p_acct%d.country_setting", parentalSlotNo);
    countrySetting = ValidateBool(&countrySetting);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &countrySetting);
}

SCIStatus SCIGetParentalAccountSysInit(bool *outSysInit, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.sys_init", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outSysInit);
    *outSysInit = ValidateBool(outSysInit);
    return err;
}

SCIStatus SCISetParentalAccountSysInit(bool sysInit, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    sysInit = ValidateBool(&sysInit);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.sys_init", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &sysInit);
}

SCIStatus SCIGetParentalAccountIntMovie(bool *outIntMovie, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.int_movie", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outIntMovie);
    *outIntMovie = ValidateBool(outIntMovie);
    return err;
}

SCIStatus SCISetParentalAccountIntMovie(bool intMovie, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    intMovie = ValidateBool(&intMovie);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.int_movie", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &intMovie);
}

SCIStatus SCIGetParentalAccountIntBrowser(bool *outIntBrowser, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.int_browser", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outIntBrowser);
    *outIntBrowser = ValidateBool(outIntBrowser);
    return err;
}

SCIStatus SCISetParentalAccountIntBrowser(bool intBrowser, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    intBrowser = ValidateBool(&intBrowser);
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.int_browser", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &intBrowser);
}

SCIStatus SCIGetParentalAccountNetworkLauncher(int8_t *outNetLauncher, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.network_launcher", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outNetLauncher);
    VerifyRestrictionLevel(outNetLauncher);
    return err;
}

SCIStatus SCISetParentalAccountNetworkLauncher(int8_t netLauncher, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    VerifyRestrictionLevel(&netLauncher);
    snprintf(name_buffer, 0x40, "p_acct%d.network_launcher", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &netLauncher);
}

SCIStatus SCIGetParentalAccountEntertainmentLauncher(bool *outEntertainmentLauncher, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    snprintf(name_buffer, 0x40, "p_acct%d.entertainment_launcher", parentalSlotNo);
    SCIStatus err = _SCIReadSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, outEntertainmentLauncher);
    *outEntertainmentLauncher = ValidateBool(outEntertainmentLauncher);
    return err;
}

SCIStatus SCISetParentalAccountEntertainmentLauncher(bool entertainmentLauncher, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    if (parentalSlotNo == 0) {
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    char name_buffer[64] = { 0 };
    entertainmentLauncher = ValidateBool(&entertainmentLauncher);
    snprintf(name_buffer, 0x40, "p_acct%d.entertainment_launcher", parentalSlotNo);
    return _SCIWriteSysConfig(name_buffer, UC_DATATYPE_UNSIGNED_BYTE, 1, &entertainmentLauncher);
}

SCIStatus SCIGetParentalAccountSettings(SCIParentalAccountSettings *outParentalSettings, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0) {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)\n", uc_handle);
        return SCI_STATUS_ERROR;
    }
    if (parentalSlotNo == 0) {
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }

    UCSysConfig parentalConfigs[12][15];

    memcpy(parentalConfigs, s_SCIDefaultParentalConfigs, sizeof(parentalConfigs));

    //! TODO: check parentalSlotNo to be in range (less than 12 and greather than 0)

    parentalConfigs[parentalSlotNo-1][1].data = &outParentalSettings->version;
    parentalConfigs[parentalSlotNo-1][2].data = &outParentalSettings->game_rating;
    parentalConfigs[parentalSlotNo-1][3].data = &outParentalSettings->eshop_purchase;
    parentalConfigs[parentalSlotNo-1][4].data = &outParentalSettings->friend_reg;
    parentalConfigs[parentalSlotNo-1][5].data = &outParentalSettings->acct_modify;
    parentalConfigs[parentalSlotNo-1][6].data = &outParentalSettings->data_manage;
    parentalConfigs[parentalSlotNo-1][7].data = &outParentalSettings->int_setting;
    parentalConfigs[parentalSlotNo-1][8].data = &outParentalSettings->country_setting;
    parentalConfigs[parentalSlotNo-1][9].data = &outParentalSettings->sys_init;
    parentalConfigs[parentalSlotNo-1][10].data = &outParentalSettings->int_browser;
    parentalConfigs[parentalSlotNo-1][11].data = &outParentalSettings->int_movie;
    parentalConfigs[parentalSlotNo-1][12].data = &outParentalSettings->net_communication_on_game;
    parentalConfigs[parentalSlotNo-1][13].data = &outParentalSettings->network_launcher;
    parentalConfigs[parentalSlotNo-1][14].data = &outParentalSettings->entertainment_launcher;

    UCError uc_read_err = UCReadSysConfig(uc_handle, 15, parentalConfigs[parentalSlotNo-1]);
    if (uc_read_err != UC_ERROR_OK)
    {
        UCClose(uc_handle);
        return SCI_STATUS_ERROR;
    }
    VerifyValueRange(outParentalSettings);
    UCClose(uc_handle);
    return SCI_STATUS_OK;
}

SCIStatus SCISetParentalAccountSettings(SCIParentalAccountSettings *parentalSettings, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0) {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)\n", uc_handle);
        return SCI_STATUS_ERROR;
    }
    if (parentalSlotNo == 0) {
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }
    VerifyValueRange(parentalSettings);

    UCSysConfig parentalConfigs[12][15];

    memcpy(parentalConfigs, s_SCIDefaultParentalConfigs, sizeof(parentalConfigs));

    parentalConfigs[parentalSlotNo-1][1].data = &parentalSettings->version;
    parentalConfigs[parentalSlotNo-1][2].data = &parentalSettings->game_rating;
    parentalConfigs[parentalSlotNo-1][3].data = &parentalSettings->eshop_purchase;
    parentalConfigs[parentalSlotNo-1][4].data = &parentalSettings->friend_reg;
    parentalConfigs[parentalSlotNo-1][5].data = &parentalSettings->acct_modify;
    parentalConfigs[parentalSlotNo-1][6].data = &parentalSettings->data_manage;
    parentalConfigs[parentalSlotNo-1][7].data = &parentalSettings->int_setting;
    parentalConfigs[parentalSlotNo-1][8].data = &parentalSettings->country_setting;
    parentalConfigs[parentalSlotNo-1][9].data = &parentalSettings->sys_init;
    parentalConfigs[parentalSlotNo-1][10].data = &parentalSettings->int_browser;
    parentalConfigs[parentalSlotNo-1][11].data = &parentalSettings->int_movie;
    parentalConfigs[parentalSlotNo-1][12].data = &parentalSettings->net_communication_on_game;
    parentalConfigs[parentalSlotNo-1][13].data = &parentalSettings->network_launcher;
    parentalConfigs[parentalSlotNo-1][14].data = &parentalSettings->entertainment_launcher;

    UCError uc_write_err = UCWriteSysConfig(uc_handle, 15, parentalConfigs[parentalSlotNo-1]);
    UCClose(uc_handle);
    SCIStatus status = SCI_STATUS_OK;
    if (uc_write_err != UC_ERROR_OK) {
        status = SCI_STATUS_ERROR_WRITE;
    }
    return status;

}

SCIStatus SCIInitParentalAccountSettingsUC(SCIParentalAccountSettings *outParentalSettings, nn::act::SlotNo parentalSlotNo)
{
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0) {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)\n", uc_handle);
        return SCI_STATUS_ERROR;
    }
    if (parentalSlotNo == 0) {
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    }

    UCSysConfig parentalConfigs[12][15];

    memcpy(parentalConfigs, s_SCIDefaultParentalConfigs, sizeof(parentalConfigs));

    //! TODO: check parentalSlotNo to be in range (less than 12 and greather than 0)

    parentalConfigs[parentalSlotNo-1][1].data = &outParentalSettings->version;
    parentalConfigs[parentalSlotNo-1][2].data = &outParentalSettings->game_rating;
    parentalConfigs[parentalSlotNo-1][3].data = &outParentalSettings->eshop_purchase;
    parentalConfigs[parentalSlotNo-1][4].data = &outParentalSettings->friend_reg;
    parentalConfigs[parentalSlotNo-1][5].data = &outParentalSettings->acct_modify;
    parentalConfigs[parentalSlotNo-1][6].data = &outParentalSettings->data_manage;
    parentalConfigs[parentalSlotNo-1][7].data = &outParentalSettings->int_setting;
    parentalConfigs[parentalSlotNo-1][8].data = &outParentalSettings->country_setting;
    parentalConfigs[parentalSlotNo-1][9].data = &outParentalSettings->sys_init;
    parentalConfigs[parentalSlotNo-1][10].data = &outParentalSettings->int_browser;
    parentalConfigs[parentalSlotNo-1][11].data = &outParentalSettings->int_movie;
    parentalConfigs[parentalSlotNo-1][12].data = &outParentalSettings->net_communication_on_game;
    parentalConfigs[parentalSlotNo-1][13].data = &outParentalSettings->network_launcher;
    parentalConfigs[parentalSlotNo-1][14].data = &outParentalSettings->entertainment_launcher;

    UCError uc_read_err = UCReadSysConfig(uc_handle, 15, parentalConfigs[parentalSlotNo-1]);
    if (uc_read_err != UC_ERROR_OK)
    {
        if (uc_read_err == UC_ERROR_KEY_NOT_FOUND)
        {
            UCDeleteSysConfig(uc_handle, 1, parentalConfigs[parentalSlotNo-1]);
            memcpy(outParentalSettings, &s_SCIDefaultParentalSettings, 0x14);
        }
        outParentalSettings->version = 10;
        UCError uc_write_err = UCWriteSysConfig(uc_handle, 15, parentalConfigs[parentalSlotNo-1]);
        if (uc_write_err != UC_ERROR_OK) {
            SCI_REPORT_ERROR("writing p_acct%d.xml config file. (%d)", parentalSlotNo, uc_write_err);
            UCClose(uc_handle);
            return SCI_STATUS_ERROR_WRITE;
        }
    }
    bool iVar5 = VerifyValueRange(outParentalSettings);
    UCError uc_write_err = UCWriteSysConfig(uc_handle, 15, parentalConfigs[parentalSlotNo-1]);
    if (iVar5 == 0 && uc_write_err != UC_ERROR_OK) {
        SCI_REPORT_ERROR("writing p_acct%d.xml config file. (%d)", parentalSlotNo, uc_write_err);
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_WRITE;
    }
    UCClose(uc_handle);
    return SCI_STATUS_OK;
}

SCIStatus SCIInitParentalAccountSettings(SCIParentalAccountSettings *param_1, nn::act::SlotNo accountSlotNo)
{
    nn::act::SlotNo parentalSlotNo = SCIGetUCParentalAccountSlotNum(accountSlotNo);
    SCIStatus status = SCI_STATUS_ERROR_GET_PARENTAL_ACCOUNT_SLOT;
    if (parentalSlotNo != 0) {
        status = SCIInitParentalAccountSettingsUC(param_1, parentalSlotNo);
    }
    return status;
}