#include <sci/sci.h>
#include <coreinit/filesystem.h>

// Macro so i dont have to repeat myself a million times
// 'returns' bool
// clips any values >1 as true, otherwise flase
#define ValidateBool(boolValPtr) (*(int8_t*)boolValPtr >= 1) && !(*(int8_t*)boolValPtr < 0)

#define SCI_REPORT(FMT, ARGS...) SCI_REPORT_FUNC("SCI: " FMT "\n", ## ARGS);
#define SCI_REPORT_ERROR(FMT, ARGS...) SCI_REPORT_FUNC("SCI:ERROR:%s:%d: " FMT "\n", __FUNCTION__, __LINE__, ## ARGS)

static char s_SCILanguageA2Buffer[0x30];
static char s_SCICountryA2Buffer[0x300];
static FSClient s_SCIFsClient;
static FSCmdBlock s_SCIFsCmdBlock;
static uint8_t s_SCIISOBuffer[0x800];

typedef struct SCICountryData SCICountryData;

struct SCICountryData
{
    int unk1, languageCount, unk3;
    char16_t languages[16][64];
    WUT_UNKNOWN_BYTES(0x30);
};
WUT_CHECK_SIZE(SCICountryData, 0x83c);

static SCICountryData s_SCICountryDataBuffer[64];


typedef struct SCIAreaData
{
    uint8_t unk_0x00 [4];
    uint8_t unk_0x04 [0x810];
    short unk_0x814;
    short unk_0x816;
};
WUT_CHECK_OFFSET(SCIAreaData, 0x00,  unk_0x00);
WUT_CHECK_OFFSET(SCIAreaData, 0x04,  unk_0x04);
WUT_CHECK_OFFSET(SCIAreaData, 0x814, unk_0x814);
WUT_CHECK_OFFSET(SCIAreaData, 0x816, unk_0x816);
WUT_CHECK_SIZE(SCIAreaData, 0x818);

typedef int CountryArea;
typedef enum _CountryArea{
    Invalid = -1,
    Japan   =  0,
    USA     =  1,
    Europe  =  2,
    China   =  3,
    Korea   =  4,
    Taiwan  =  5,
    Other   =  6,
};

static constexpr const char *s_region_names[] = {
    "JP",
    "US",
    "EU",
    "CN",
    "KR",
    "TW",
    "OTHER"
};

static constexpr const SCICafeSettings s_SCIDefaultCafeSettings = {
    .version        = 5,
    .language       = 0,
    .country        = 0,
    .eula_agree     = false,
    .eula_version   = 0,
    .initial_launch = false,
    .eco            = false,
    .fast_boot      = false
};

static constexpr const UCSysConfig s_SCIDefaultCafeConfigs[9] = {
    { "cafe",                   0x777, UC_DATATYPE_COMPLEX,         UC_ERROR_OK, 0, NULL },
    { "cafe.version",           0x777, UC_DATATYPE_UNSIGNED_SHORT,  UC_ERROR_OK, 2, NULL },
    { "cafe.language",          0x777, UC_DATATYPE_UNSIGNED_INT,    UC_ERROR_OK, 4, NULL },
    { "cafe.cntry_reg",         0x777, UC_DATATYPE_UNSIGNED_INT,    UC_ERROR_OK, 4, NULL },
    { "cafe.eula_agree",        0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL },
    { "cafe.eula_version",      0x777, UC_DATATYPE_UNSIGNED_INT,    UC_ERROR_OK, 4, NULL },
    { "cafe.initial_launch",    0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL },
    { "cafe.eco",               0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL },
    { "cafe.fast_boot",         0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1, NULL }
};

static constexpr const SCIParentalSettings s_SCIDefaultParentalSettings = {
    .version             = 9,
    .enable              = 0,
    .pin_code            = { 0 },
    .sec_question        = 0,
    .sec_answer          = { 0 },
    .email_address       = { 0 },
    .permit_delete_all   = 0,
    .rating_organization = 0
};

static constexpr const UCSysConfig s_SCIDefaultParentalConfigs[9] = {
    { "parent",                     0x777, UC_DATATYPE_COMPLEX,         UC_ERROR_OK, 0,     NULL },
    { "parent.version",             0x777, UC_DATATYPE_UNSIGNED_SHORT,  UC_ERROR_OK, 2,     NULL },
    { "parent.enable",              0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1,     NULL },
    { "parent.pin_code",            0x777, UC_DATATYPE_STRING,          UC_ERROR_OK, 5,     NULL },
    { "parent.sec_question",        0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1,     NULL },
    { "parent.sec_answer",          0x777, UC_DATATYPE_STRING,          UC_ERROR_OK, 0x101, NULL },
    { "parent.email_address",       0x777, UC_DATATYPE_STRING,          UC_ERROR_OK, 0x401, NULL },
    { "parent.permit_delete_all",   0x777, UC_DATATYPE_UNSIGNED_BYTE,   UC_ERROR_OK, 1,     NULL },
    { "parent.rating_organization", 0x777, UC_DATATYPE_UNSIGNED_INT,    UC_ERROR_OK, 4,     NULL },
};

static bool VerifyLanguageRange(int *language)
{
    if (*language < 0xc && (*(int8_t*)language) > -1)
        return true;
    *language = 0xff;
    return false;
}

static bool VerifyCountryRange(int *country)
{
    if (*country > 0xff) {
        *country = 0xff;
        return false;
    }
    if (*country < 0) {
        *country = 0;
        return false;
    }
    return true;
}

static bool VerifyValueRange(SCICafeSettings settings)
{
    bool result = true;
    result = VerifyLanguageRange(&settings.language);
    result = VerifyCountryRange(&settings.country);
    // should we validate it ?
    // in the REd code it does check for it
    settings.eula_agree = ValidateBool(&settings.eula_agree);
    settings.eco = ValidateBool(&settings.eco);
    settings.fast_boot = ValidateBool(&settings.fast_boot);
    return result;
}

static bool VerifyQuestionType(int8_t *questionType)
{
    if (5 < *questionType) {
        *questionType = 5;
        return false;
    }
    if (*questionType < 0) {
        *questionType = 0;
        return false;
    }
    return true;
}

static bool VerifyRatingOrganization(uint32_t *rating)
{
    if (*rating >= 0x10) {
        *rating = 0xff;
        return false;
    }
    return *rating < 0x10;
}

// ugly port from the decompiler from ghidra
static bool VerifyValueRange(SCIParentalSettings setting)
{
    BOOL res = TRUE;
    setting.enable = ValidateBool(&setting.enable);

    if (!VerifyQuestionType(&setting.sec_question)) {
        res = false;
    }

    // if (setting.permit_delete_all < 2) {
    //     if ((char)setting.permit_delete_all < 0) {
    //         res = 0;
    //         setting.permit_delete_all = 0;
    //     }
    // }
    // else {
    //     res = 0;
    //     setting.permit_delete_all = 1;
    // }
    setting.permit_delete_all = ValidateBool(&setting.permit_delete_all);

    if (!VerifyRatingOrganization(&setting.rating_organization)) res = false;
    return res;
}

SCIStatus SCIGetCafeLanguage(int *outLanguage)
{
    SCIStatus status = _SCIReadSysConfig("cafe.language", UC_DATATYPE_UNSIGNED_INT, 4, outLanguage);
    VerifyLanguageRange(outLanguage);
    return status;
}

SCIStatus SCIGetCafeCountry(int *outCountry)
{
    SCIStatus status = _SCIReadSysConfig("cafe.cntry_reg", UC_DATATYPE_UNSIGNED_INT, 4, outCountry);
    VerifyCountryRange(outCountry);
    return status;
}

// ugly port from the decompiler from ghidra
static char *SCIUTF32to8(uint32_t utf32_value, char *outUtf8_value)
{
	if (utf32_value - 0xd800 < 0x800)
		return nullptr;
	
    bool bVar1;
	int iVar2;
	
	int iVar3 = 0;
	if (utf32_value < 0x80) {
		*outUtf8_value++ = utf32_value;
	}
	else {
		if (utf32_value < 0x800) {
			*outUtf8_value++ = (utf32_value >> 6) | 0xc0;
		}
		else if (utf32_value < 0x10000) {
			iVar3 = 1;
			*outUtf8_value++ = (utf32_value >> 0xc) | 0xe0;
		}
		else {
			if (0x10ffff < utf32_value) {
				return nullptr;
			}
			iVar3 = 2;
			*outUtf8_value++ = (utf32_value >> 0x12) | 0xf0;
		}
		do {
			iVar2 = iVar3 * 6;
			bVar1 = 0 < iVar3;
			iVar3 -= 1;
			*outUtf8_value++ = ((utf32_value >> iVar2) & 0x3f) | 0x80;
		} while (bVar1);
  	}
	return outUtf8_value;
}

// ugly port from the decompiler from ghidra
static void SCIConvertWCharToChar(char *outChar, char16_t *source)
{
    uint32_t uVar2 = *source;
    while (uVar2 != 0)
    {
        SCIUTF32to8(uVar2, outChar);
        source = source + 1;
        if (uVar2 < 0x1001) {
            if (uVar2 < 0x7f) {
                uVar2 = *source;
                outChar = outChar + 1;
            }
            else {
                uVar2 = *source;
                outChar = outChar + 2;
            }
        }
        else {
            uVar2 = *source;
            outChar = outChar + 3;
        }
    }
    *outChar = (char)uVar2;
    return;
}

// I dont like the design decision to use `sprintf`
// caller always passes a `FS_MAX_PATH` sized buffer
static SCIStatus SCIGetContentPath(char *outPath, const char *mlc)
{
    FSDirectoryHandle dirHandle;
    sprintf(outPath, "%s/%s", "/vol/storage_mlc01", mlc);
    FSStatus mlc_status = FSOpenDir(&s_SCIFsClient, &s_SCIFsCmdBlock, outPath, &dirHandle, FS_ERROR_FLAG_ALL);
    if (mlc_status != FS_STATUS_OK)
    {
        sprintf(outPath, "%s/%s", "/vol/storage_hfiomlc01", mlc);
        FSStatus hfio_status = FSOpenDir(&s_SCIFsClient, &s_SCIFsCmdBlock, outPath, &dirHandle, FS_ERROR_FLAG_ALL);
        if (hfio_status != FS_STATUS_OK)
        {
            SCI_REPORT_ERROR("FSOpenDir %s : (mlc:%d) (hfio:%d)", outPath, mlc_status, hfio_status);
            return SCI_STATUS_ERROR_OPEN;
        }
    }
    FSCloseDir(&s_SCIFsClient, &s_SCIFsCmdBlock, dirHandle, FS_ERROR_FLAG_NONE);
    return SCI_STATUS_OK;
}

static CountryArea SCIGetCountryArea(int country, const char *directoryPath)
{
    FSDirectoryHandle fsDirHandle;
    FSDirectoryEntry fsDirEntry;
    FSStatus fsStatus;
    char absolutePath[FS_MAX_PATH];

    for (int region_index = 0; region_index < 7; region_index++)
    {
        sprintf(absolutePath, "%s/%s", directoryPath, s_region_names[region_index]);
        fsStatus = FSOpenDir(&s_SCIFsClient, &s_SCIFsCmdBlock, absolutePath, &fsDirHandle, FS_ERROR_FLAG_ALL);
        if (fsStatus == FS_STATUS_OK)
        {
            fsStatus = FSReadDir(&s_SCIFsClient, &s_SCIFsCmdBlock, fsDirHandle, &fsDirEntry, FS_ERROR_FLAG_NONE);
            while (fsStatus == FS_STATUS_OK)
            {
                char *pdot = strchr(fsDirEntry.name, '.');
                if (pdot)
                {
                    // replace '.' with '\0'
                    *pdot = '\0';
                    if (strcmp("country", fsDirEntry.name) != 0 && atoi(fsDirEntry.name) == country)
                    {
                        FSCloseDir(&s_SCIFsClient, &s_SCIFsCmdBlock, fsDirHandle, FS_ERROR_FLAG_NONE);
                        return region_index;
                    }
                }
                fsStatus = FSReadDir(&s_SCIFsClient, &s_SCIFsCmdBlock, fsDirHandle, &fsDirEntry, FS_ERROR_FLAG_NONE);
            }
            FSCloseDir(&s_SCIFsClient, &s_SCIFsCmdBlock, fsDirHandle, FS_ERROR_FLAG_NONE);
        }
        else
        {
            SCI_REPORT_ERROR("FSOpenDir %s : (%d)", absolutePath, fsStatus);
        }
    }
    return _CountryArea::Invalid;
}

//! TODO: 
static SCIStatus SCIGetCountryData(char *buffer, size_t bufferSize, int country, int language, const char *directoryPath , const char *filePath)
{
    FSStatus fsStatus;
    int uVar2;
    FSFileHandle fileHandle;
    uint32_t maxEntryCount;
    char absoluteFilePath[FS_MAX_PATH];

    uint32_t currentEntryIndex = 0;
    
    if (language > 11)
    {
        SCI_REPORT_ERROR("Invalid language (type=%d)", language);
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    
    sprintf(absoluteFilePath, "%s/%s", directoryPath, filePath);

    fsStatus = FSOpenFile(&s_SCIFsClient, &s_SCIFsCmdBlock, absoluteFilePath, "r", &fileHandle, FS_ERROR_FLAG_ALL);

    if (fsStatus > -1)
    {
        fsStatus = FSReadFile(&s_SCIFsClient, &s_SCIFsCmdBlock, (uint8_t*)&maxEntryCount, 4, 1, fileHandle, 0, FS_ERROR_FLAG_NONE);
        if (fsStatus < 0)
        {
            SCI_REPORT_ERROR("FSReadFile %s : (%d)", absoluteFilePath, fsStatus);
            FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
            return SCI_STATUS_ERROR_READ;
        }
        
        while( true )
        {
            if (currentEntryIndex == maxEntryCount)
            {
                FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle , FS_ERROR_FLAG_NONE);
                return SCI_STATUS_ERROR_KEY_NOT_FOUND;
            }

            memset(s_SCICountryDataBuffer, 0, sizeof(s_SCICountryDataBuffer));

            uVar2 = FSReadFileWithPos(&s_SCIFsClient, &s_SCIFsCmdBlock,
                            (uint8_t*)s_SCICountryDataBuffer, 0x83c, 0x40, currentEntryIndex * 0x83c + 4,
                            fileHandle, 0, FS_ERROR_FLAG_ALL);
            currentEntryIndex += uVar2;
            if ((uVar2 < 0) || maxEntryCount < currentEntryIndex)
                break;
            
            int uVar4 = 0;
            if (uVar2 != 0)
            {
                do
                {
                    if ((int)(&s_SCICountryDataBuffer)[uVar4 * 0x20f] >> 0x18 == country) {
                        SCIConvertWCharToChar(buffer, (char16_t*)&s_SCICountryDataBuffer + 0xC + language * 0x80 + uVar4 * 0x83c);
                        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
                        return SCI_STATUS_OK;
                    }
                    uVar4++;
                } while (uVar4 < uVar2);
            }
        }
        SCI_REPORT_ERROR("FSReadFile %s : (%d), entries = %u/%u", absoluteFilePath, uVar2, currentEntryIndex, maxEntryCount);
        FSCloseFile(&s_SCIFsClient,&s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_ERROR_READ;
    }
    SCI_REPORT_ERROR("FSReadFile %s : (%d)", absoluteFilePath, fsStatus);
    return SCI_STATUS_ERROR_OPEN;
}

static SCIStatus SCIGetCountryDataUtf16(char16_t *buffer, size_t bufferSize, int country, int language, const char *directoryPath, const char *filePath)
{
    FSStatus fsStatus;
    int uVar2;
    FSFileHandle fileHandle;
    uint32_t maxEntryCount;
    char absoluteFilePath[FS_MAX_PATH];

    uint32_t currentEntryIndex = 0;
    
    if (language > 11)
    {
        SCI_REPORT_ERROR("Invalid language (type=%d)", language);
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    
    sprintf(absoluteFilePath, "%s/%s", directoryPath, filePath);

    fsStatus = FSOpenFile(&s_SCIFsClient, &s_SCIFsCmdBlock, absoluteFilePath, "r", &fileHandle, FS_ERROR_FLAG_ALL);

    if (fsStatus > -1)
    {
        fsStatus = FSReadFile(&s_SCIFsClient, &s_SCIFsCmdBlock, (uint8_t*)&maxEntryCount, 4, 1, fileHandle, 0, FS_ERROR_FLAG_NONE);
        if (fsStatus < 0)
        {
            SCI_REPORT_ERROR("FSReadFile %s : (%d)", absoluteFilePath, fsStatus);
            FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
            return SCI_STATUS_ERROR_READ;
        }
        
        while( true )
        {
            if (currentEntryIndex == maxEntryCount)
            {
                FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle , FS_ERROR_FLAG_NONE);
                return SCI_STATUS_ERROR_KEY_NOT_FOUND;
            }

            memset(s_SCICountryDataBuffer, 0, sizeof(s_SCICountryDataBuffer));

            uVar2 = FSReadFileWithPos(&s_SCIFsClient, &s_SCIFsCmdBlock,
                            (uint8_t*)s_SCICountryDataBuffer, 0x83c, 0x40, currentEntryIndex * 0x83c + 4,
                            fileHandle, 0, FS_ERROR_FLAG_ALL);
            currentEntryIndex += uVar2;
            if ((uVar2 < 0) || maxEntryCount < currentEntryIndex)
                break;
            
            int uVar4 = 0;
            if (uVar2 != 0)
            {
                do
                {
                    if ((int)(&s_SCICountryDataBuffer)[uVar4 * 0x20f] >> 0x18 == country) {
                        memcpy(buffer, (char16_t*)&s_SCICountryDataBuffer + 0xC + language * 0x80 + uVar4 * 0x83c, bufferSize);
                        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
                        return SCI_STATUS_OK;
                    }
                    uVar4++;
                } while (uVar4 < uVar2);
            }
        }
        SCI_REPORT_ERROR("FSReadFile %s : (%d), entries = %u/%u", absoluteFilePath, uVar2, currentEntryIndex, maxEntryCount);
        FSCloseFile(&s_SCIFsClient,&s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_ERROR_READ;
    }
    SCI_REPORT_ERROR("FSReadFile %s : (%d)", absoluteFilePath, fsStatus);
    return SCI_STATUS_ERROR_OPEN;
}

//! TODO: clean up
static SCIStatus SCIGetAreaDataUtf16(SCIAreaData *areaData, int country, const char *directoryPath, const char *filePath)
{
    int fsStatus;
    // int iVar3;
    FSFileHandle fileHandle;
    int maxEntryCount;
    char absolutePath[FS_MAX_PATH];

    int currentEntryIndex = 0;
    sprintf(absolutePath, "%s/%s", directoryPath, filePath);
    fsStatus = FSOpenFile(&s_SCIFsClient, &s_SCIFsCmdBlock, absolutePath, "r", &fileHandle, FS_ERROR_FLAG_ALL);
    if (fsStatus < 0)
    {
        SCI_REPORT_ERROR("FSReadFile %s : (%d)", absolutePath, fsStatus);
        return SCI_STATUS_ERROR_OPEN;
    }
    fsStatus = FSReadFile(&s_SCIFsClient, &s_SCIFsCmdBlock, (uint8_t*)&maxEntryCount, 4, 1, fileHandle, 0, FS_ERROR_FLAG_NONE);
    if (fsStatus < 0)
    {
        SCI_REPORT_ERROR("FSReadFile %s : (%d)", absolutePath, fsStatus);
        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_ERROR_READ;
    }
    maxEntryCount++;
    if (fsStatus != 0)
    {
        do
        {
            memset(s_SCICountryDataBuffer, 0, 0x8180);
            fsStatus = FSReadFile(&s_SCIFsClient, &s_SCIFsCmdBlock, (uint8_t*)&s_SCICountryDataBuffer, 0x818, 0x40, fileHandle, 0, FS_ERROR_FLAG_NONE);
            currentEntryIndex += fsStatus;
            if ((fsStatus < 0) || (maxEntryCount < currentEntryIndex))
            {
                SCI_REPORT_ERROR("FSReadFile %s : (%d), entries = %u/%u", absolutePath, fsStatus, currentEntryIndex, maxEntryCount);
                FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
                return SCI_STATUS_ERROR_READ;
            }
            int uVar2 = 0;
            if (currentEntryIndex != -1)
            {
                do
                {
                    if (((int*)&s_SCICountryDataBuffer)[uVar2 * 0x206] == country)
                    {
                        memcpy(areaData, &s_SCICountryDataBuffer + uVar2 * 0x206, sizeof(SCIAreaData));
                        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
                        return SCI_STATUS_OK;
                    }
                    uVar2++;
                } while (uVar2 < currentEntryIndex + 1);
            }
        } while (currentEntryIndex != maxEntryCount);
    }
    FSCloseFile(&s_SCIFsClient,&s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
    return SCI_STATUS_ERROR_KEY_NOT_FOUND;
}

static void _SCIFsStateChangeCallback(FSClient *client, FSVolumeState state, void *param)
{
    // this was propably meant to be SCI_REPORT lol
    SCI_REPORT_ERROR("Volume state of client 0x%08x changed to %d", client, state);
    SCI_REPORT_ERROR("Last fs error: %d", FSGetLastError(client));
}

SCIStatus SCIGetCountryName(char *buffer, size_t bufferSize, int country, int language)
{
    char directoryPath[FS_MAX_PATH];
    SCIStatus status;

    if (bufferSize < 0xc0) {
        SCI_REPORT_ERROR("Invalid Size of buffer (size=%d)", bufferSize);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    if (language > 11) {
        SCI_REPORT_ERROR("Invalid language (type=%d)", language);
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    memset(buffer, 0, bufferSize);
    if ((country == 0) || (country > 0xff))
    {
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    FSAddClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    FSInitCmdBlock(&s_SCIFsCmdBlock);
    FSStateChangeParams stateChangeParams = {
        .callback = _SCIFsStateChangeCallback,
        .param = NULL,
        .unk_0x08 = 0
    };
    FSSetStateChangeNotification(&s_SCIFsClient, &stateChangeParams);

    status = SCIGetContentPath(directoryPath, "sys/title/0005001b/10052000/content/00");
    if (status == SCI_STATUS_OK)
    {
        if (country == 1) {
            status = SCIGetCountryData(buffer, bufferSize, 1, language, directoryPath, "JP/country.bin");
checkStatus:
            if (status != SCI_STATUS_ERROR_KEY_NOT_FOUND) goto exit;
        }
        else {
            if ((country - 8 < 0x2d) || (country - 0x98 < 5)) {
                status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "US/country.bin");
                goto checkStatus;
            }
            if (country - 0x40 < 0x40) {
                status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "EU/country.bin");
                goto checkStatus;
            }
            if (((country == 0x80) || (country == 0x90)) || (country == 0x91)) {
                status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "TW/country.bin");
                goto checkStatus;
            }
            if (country == 0x88) {
                status = SCIGetCountryData(buffer, bufferSize, 0x88, language, directoryPath, "KR/country.bin");
                goto checkStatus;
            }
            if (country == 0xa0) {
                status = SCIGetCountryData(buffer, bufferSize, 0xa0, language, directoryPath, "CN/country.bin");
                goto checkStatus;
            }
        }
        int countryArea = SCIGetCountryArea(country, directoryPath);
        switch(countryArea) {
        case 0:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "JP/country.bin");
            break;
        case 1:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "US/country.bin");
            break;
        case 2:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "EU/country.bin");
            break;
        case 3:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "CN/country.bin");
            break;
        case 4:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "KR/country.bin");
            break;
        case 5:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "TW/country.bin");
            break;
        case 6:
            status = SCIGetCountryData(buffer, bufferSize, country, language, directoryPath, "OTHER/country.bin");
            break;
        default:
            status = SCI_STATUS_ERROR_KEY_NOT_FOUND;
            break;
        }
    }
    exit:
    FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    return status;
}

//! TODO: clean up
SCIStatus SCIGetCountryNameUtf16(char16_t *buffer, uint32_t bufferSize, uint32_t country, uint32_t language)
{
    SCIStatus status;
    char directoryPath[FS_MAX_PATH];
    
    if (bufferSize < 0xc0)
    {
        SCI_REPORT_ERROR("Invalid Size of buffer (size=%d)", bufferSize);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    if (0xb < (int)language) {
        OSReport("SCI:ERROR:%s:%d: Invalid language (type=%d)\n","SCIGetCountryNameUtf16",0x321,
                 language);
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    
    memset(buffer, 0, bufferSize);
    
    if ((country == 0) || (0xff < country))
    {
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    FSAddClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    FSInitCmdBlock(&s_SCIFsCmdBlock);
    FSStateChangeInfo param
    {
        .callback = _SCIFsStateChangeCallback,
        .param = NULL,
        .unk_0x08 = 0,
    };
    FSSetStateChangeNotification(&s_SCIFsClient, &param);
    status = SCIGetContentPath(directoryPath, "sys/title/0005001b/10052000/content/00");
    if (status == SCI_STATUS_OK) {
        if (country == 1) {
            status = SCIGetCountryDataUtf16(buffer, bufferSize, 1, language, directoryPath, "JP/country.bin");
joined_r0x02c75ba0:
            if (status != SCI_STATUS_ERROR_KEY_NOT_FOUND) goto exit;
        }
        else {
            if ((country - 8 < 0x2d) || (country - 0x98 < 5)) {
                status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "US/country.bin");
                goto joined_r0x02c75ba0;
            }
            if (country - 0x40 < 0x40)
            {
                status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "EU/country.bin");
                goto joined_r0x02c75ba0;
            }
            if (((country == 0x80) || (country == 0x90)) || (country == 0x91))
            {
                status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "TW/country.bin");
                goto joined_r0x02c75ba0;
            }
            if (country == 0x88)
            {
                status = SCIGetCountryDataUtf16(buffer, bufferSize, 0x88, language, directoryPath, "KR/country.bin");
                goto joined_r0x02c75ba0;
            }
            if (country == 0xa0)
            {
                status = SCIGetCountryDataUtf16(buffer, bufferSize, 0xa0, language, directoryPath, "CN/country.bin");
                goto joined_r0x02c75ba0;
            }
        }
        CountryArea countryArea = SCIGetCountryArea(country,directoryPath);
        switch(countryArea)
        {
        case Japan:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "JP/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case USA:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "US/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case Europe:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "EU/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case China:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "CN/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case Korea:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "KR/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case Taiwan:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "TW/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        case Other:
            status = SCIGetCountryDataUtf16(buffer, bufferSize, country, language, directoryPath, "OTHER/country.bin");
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            break;
        default:
            status = SCI_STATUS_ERROR_KEY_NOT_FOUND;
            goto exit;
        }
    }
exit:
    FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    return status;
}

//! TODO: clean up
SCIStatus SCIGetAreaInfoUtf16(SCIAreaInfo *areaInfoUtf16, uint32_t param_2, int language)
{
    uint country;
    SCIStatus status;
    int regionIndex;
    uint uVar3;
    uint uVar4;
    char filePath [32];
    char directoryPath [FS_MAX_PATH];

    SCIAreaData areaData;
    
    memset(areaInfoUtf16, 0, sizeof(SCIAreaInfo));

    country = param_2 >> 0x18;
    uVar4 = param_2 >> 0x10 & 0xff;
    if ((country == 0) || (0xff < country))
    {
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    if (language > 11) {
        SCI_REPORT_ERROR("Invalid language (type=%d)", language);
        return SCI_STATUS_ERROR_INVALID_ARGUMENT;
    }
    
    FSAddClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    FSInitCmdBlock(&s_SCIFsCmdBlock);

    FSStateChangeParams params {
        .callback = _SCIFsStateChangeCallback,
        .param = NULL,
        .unk_0x08 = 0,
    };
    FSSetStateChangeNotification(&s_SCIFsClient, &params);
    
    status = SCIGetContentPath(directoryPath,"sys/title/0005001b/10052000/content/00");
    
    if (status != SCI_STATUS_OK) goto exit;
    if (country == 1)
    {
        uVar3 = 0x01000000;
        regionIndex = 0;
    }
    else if ((country - 8 < 0x2d) || (country - 0x98 < 5))
    {
        regionIndex = 1;
        set_invalid_country:
        uVar3 = param_2 & 0xff000000;
    }
    else if (country - 0x40 < 0x40)
    {
        uVar3 = param_2 & 0xff000000;
        regionIndex = 2;
    }
    else if (((country == 0x80) || (country == 0x90)) || (country == 0x91))
    {
        uVar3 = param_2 & 0xff000000;
        regionIndex = 5;
    }
    else
    {
        if (country != 0x88)
        {
            regionIndex = 0xff;
            if (country == 0xa0)
            {
                regionIndex = 3;
            }
            goto set_invalid_country;
        }
      uVar3 = 0x88000000;
      regionIndex = 4;
    }
    if (uVar4 != 1)
    {
        uVar3 = uVar4 << 0x10 | (param_2 & 0xff000000);
    }
    if (regionIndex == 0xff)
    {
    LAB_02c76080:
        int countryArea = SCIGetCountryArea(country, directoryPath);
        if (6 < countryArea)
        {
            FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
            return SCI_STATUS_ERROR_KEY_NOT_FOUND;
        }
        snprintf(filePath, 0x20, "%s/%u.bin", s_region_names[regionIndex], country);
        status = SCIGetAreaDataUtf16(&areaData, uVar3, directoryPath, filePath);
    }
    else
    {
        snprintf(filePath, 0x20, "%s/%u.bin", s_region_names[regionIndex], country);
        status = SCIGetAreaDataUtf16(&areaData, uVar3, directoryPath, filePath);
        if (status == SCI_STATUS_ERROR_KEY_NOT_FOUND) goto LAB_02c76080;
    }
    if (status == SCI_STATUS_OK)
    {
        if (uVar4 == 1)
        {
            if (regionIndex < 7)
            {
                snprintf(filePath, 0x20, "%s/country.bin", s_region_names[regionIndex]);
                status = SCIGetCountryDataUtf16(areaInfoUtf16->areaName, sizeof(areaInfoUtf16->areaName), country, language, directoryPath, filePath);
                areaInfoUtf16->unk_0x80 = areaData.unk_0x814;
                areaInfoUtf16->unk_0x82 = areaData.unk_0x816;
            }
            else
            {
                status = SCI_STATUS_ERROR_KEY_NOT_FOUND;
                areaInfoUtf16->unk_0x80 = areaData.unk_0x814;
                areaInfoUtf16->unk_0x82 = areaData.unk_0x816;
            }
        }
        else
        {
            memcpy(areaInfoUtf16->areaName, areaData.unk_0x04 + language * 0x80, sizeof(areaInfoUtf16->areaName));
            areaInfoUtf16->unk_0x80 = areaData.unk_0x814;
            areaInfoUtf16->unk_0x82 = areaData.unk_0x816;
        }
    }
exit:
    FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    return status;
}

//! TODO: clean up
SCIStatus SCIGetAreaInfo(char *buffer, uint32_t param_2, uint32_t param_3)
{
    SCIAreaInfo areaInfo;
    // why is this struct bigger ??
    memset(buffer, 0, 0xc4);
    SCIStatus status = SCIGetAreaInfoUtf16(&areaInfo, param_2, param_3);
    if (status == SCI_STATUS_OK)
    {
        areaInfo.areaName[63] = 0;
        SCIConvertWCharToChar(buffer, areaInfo.areaName);
        *(short*)(buffer + 0xc0) = areaInfo.unk_0x80;
        *(short*)(buffer + 0xc2) = areaInfo.unk_0x82;
    }
    return status;
}

SCIStatus SCIGetISOResource(char *buffer, size_t bufferSize, const char *filename)
{
    if (strlen(buffer+2) != 3)
        return SCI_STATUS_OK;

    FSAddClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    FSInitCmdBlock(&s_SCIFsCmdBlock);
    FSStateChangeParams stateChangeParams = {
        .callback = _SCIFsStateChangeCallback,
        .param = NULL,
        .unk_0x08 = 0
    };
    FSSetStateChangeNotification(&s_SCIFsClient, &stateChangeParams);

    char absolutePath[FS_MAX_PATH];
    SCIStatus conetent_err = SCIGetContentPath(absolutePath, "sys/title/0005001b/1005c000/content");
    if (conetent_err != SCI_STATUS_OK)
    {
        FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
        return conetent_err;
    }

    FSFileHandle fileHandle;
    FSStatus fsStatus;
    // sprintf(absolutePath, "%s/%s", absolutePath, filename); // original
    snprintf(absolutePath, sizeof(absolutePath), "%s/%s", absolutePath, filename);

    fsStatus = FSOpenFile(&s_SCIFsClient, &s_SCIFsCmdBlock, absolutePath, "r", &fileHandle, FS_ERROR_FLAG_ALL);
    if (fsStatus < 0)
    {
        SCI_REPORT_ERROR("FSReadFile %s : (%d)", absolutePath, fsStatus);
        FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_ERROR_OPEN;
    }
    
    fsStatus = FSReadFile(&s_SCIFsClient, &s_SCIFsCmdBlock, s_SCIISOBuffer, 1, 0x800, fileHandle, 0, FS_ERROR_FLAG_NONE);
    if (fsStatus < 0)
    {
        SCI_REPORT_ERROR("FSReadFile %s : (%d)", absolutePath, fsStatus);
        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
        FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_ERROR_READ;
    }

    if (fsStatus == FS_STATUS_OK)
    {
        FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
        FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
        return SCI_STATUS_OK;
    }

    for (size_t i = 0; i < bufferSize; i++)
    {
        char cVar1 = s_SCIISOBuffer[i];
        if ((cVar1 == '\r') || (cVar1 == '\n')) {
            
        }
    }

    FSCloseFile(&s_SCIFsClient, &s_SCIFsCmdBlock, fileHandle, FS_ERROR_FLAG_NONE);
    FSDelClient(&s_SCIFsClient, FS_ERROR_FLAG_NONE);
    return SCI_STATUS_OK;
}

char *SCIGetCountryCodeA2(int country)
{
    SCIStatus status = SCIGetISOResource(s_SCICountryA2Buffer, sizeof(s_SCICountryA2Buffer), "country.txt");
    if (country < 0x100 && status == SCI_STATUS_OK)
    {
        char *pcVar2 = s_SCICountryA2Buffer + country * 3;
        // do { pcVar2++; } while (*pcVar2 != 0);
        // if (pcVar2 != s_SCICountryA2Buffer + country * 3)
        //     return s_SCICountryA2Buffer + country * 3;

        if (strlen(pcVar2) != 0) {
            return s_SCILanguageA2Buffer + country * 3;
        }
    }
    return nullptr;
}

char *SCIGetLanguageCodeA2(int language)
{
    //! TODO:
    SCIStatus status = SCIGetISOResource(s_SCILanguageA2Buffer, sizeof(s_SCILanguageA2Buffer), "language.txt");
    if (language < 0x10 && status == SCI_STATUS_OK)
    {
        char *pcVar2 = (char *)(language * 3 + &s_SCILanguageA2Buffer);
        // do pcVar2++; while (*pcVar2 != '\0');
        // if (pcVar2 != s_SCILanguageA2Buffer + language * 3) {
        //     return s_SCILanguageA2Buffer + language * 3;
        // }

        if (strlen(pcVar2) != 0) {
            return s_SCILanguageA2Buffer + language * 3;
        }
    }
    return nullptr;
}

SCIStatus SCIGetCafeXMLVersion(uint8_t *outXmlVersion)
{
    return _SCIReadSysConfig("cafe.version", UC_DATATYPE_UNSIGNED_BYTE, 1, outXmlVersion);
}

SCIStatus SCISetCafeXMLVersion(uint8_t xmlVersion)
{
    return _SCIWriteSysConfig("cafe.version", UC_DATATYPE_UNSIGNED_BYTE, 1, &xmlVersion);
}

SCIStatus SCISetCafeLanguage(int language)
{
    VerifyLanguageRange(&language);
    return _SCIWriteSysConfig("cafe.language", UC_DATATYPE_UNSIGNED_INT, 4, &language);
}

SCIStatus SCISetCafeCountry(int country)
{
    VerifyCountryRange(&country);
    return _SCIWriteSysConfig("cafe.cntry_reg", UC_DATATYPE_UNSIGNED_INT, 4, &country);
}

SCIStatus SCIGetCafeEulaVersion(uint32_t *outEulaVersion)
{
    return _SCIReadSysConfig("cafe.eula_version", UC_DATATYPE_UNSIGNED_INT, 4, outEulaVersion);
}

SCIStatus SCISetCafeEulaVersion(uint32_t eulaVersion)
{
    return _SCIWriteSysConfig("cafe.eula_version", UC_DATATYPE_UNSIGNED_INT, 4, &eulaVersion);
}

SCIStatus SCIGetCafeInitialLaunch(bool *outInitialLaunch)
{
    SCIStatus status = _SCIReadSysConfig("cafe.initial_launch", UC_DATATYPE_UNSIGNED_BYTE, 1, outInitialLaunch);
    *outInitialLaunch = (*(uint8_t*)outInitialLaunch >= 1) &&  !(*(char*)outInitialLaunch < 0);
    return status;
}

SCIStatus SCISetCafeInitialLaunch(uint8_t initialLaunch)
{
    return _SCIWriteSysConfig("cafe.initial_launch", UC_DATATYPE_UNSIGNED_BYTE, 1, &initialLaunch);
}

SCIStatus SCIGetCafeECO(uint8_t *outECO)
{
    SCIStatus status = _SCIReadSysConfig("cafe.eco", UC_DATATYPE_UNSIGNED_BYTE, 1, outECO);
    *outECO = ((uint8_t)*outECO >= 1) &&  !((char)*outECO < 0);
    return status;
}

SCIStatus SCISetCafeECO(uint8_t eco)
{
    // if (eco < 2) {
    //     if ((char)eco < 0)
    //         eco = 0;
    // }
    // else {
    //     eco = 1;
    // }
    eco = ValidateBool(&eco);
    return _SCIWriteSysConfig("cafe.eco", UC_DATATYPE_UNSIGNED_BYTE, 1, &eco);
}

SCIStatus SCIGetCafeFastBoot(bool *outFastBoot)
{
    SCIStatus status = _SCIReadSysConfig("cafe.fast_boot", UC_DATATYPE_UNSIGNED_BYTE, 1, outFastBoot);
    *outFastBoot = ValidateBool(outFastBoot);
    return status;
}

SCIStatus SCISetCafeFastBoot(bool fastBoot)
{
    // if (fastBoot < 2) {
    //     if ((char)fastBoot < 0)
    //         fastBoot = 0;
    // }
    // else {
    //     fastBoot = 1;
    // }
    fastBoot = ValidateBool(&fastBoot);
    return _SCIWriteSysConfig("cafe.fast_boot", UC_DATATYPE_UNSIGNED_BYTE, 1, &fastBoot);
}

SCIStatus SCIGetCafeSettings(SCICafeSettings *out)
{
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", uc_handle);
        UCClose(uc_handle);
        return SCI_STATUS_ERROR;
    }
    UCSysConfig cafeSettings[9];
    memcpy(cafeSettings, s_SCIDefaultCafeConfigs, sizeof(cafeSettings));

    cafeSettings[1].data = &out->version;
    cafeSettings[2].data = &out->language;
    cafeSettings[3].data = &out->country;
    cafeSettings[4].data = &out->eula_agree;
    cafeSettings[5].data = &out->eula_version;
    cafeSettings[6].data = &out->initial_launch;
    cafeSettings[7].data = &out->eco;
    cafeSettings[8].data = &out->fast_boot;

    UCError uc_read_err = UCReadSysConfig(uc_handle, 9, cafeSettings);
    if (uc_read_err != UC_ERROR_OK)
    {
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_READ;
    }
    VerifyValueRange(*out);
    UCClose(uc_handle);
    return SCI_STATUS_OK;
}

SCIStatus SCISetCafeSettings(SCICafeSettings settings)
{
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", uc_handle);
        UCClose(uc_handle);
        return SCI_STATUS_ERROR;
    }

    VerifyValueRange(settings);

    UCSysConfig cafeSettings[9];
    memcpy(cafeSettings, s_SCIDefaultCafeConfigs, sizeof(cafeSettings));

    cafeSettings[1].data = &settings.version;
    cafeSettings[2].data = &settings.language;
    cafeSettings[3].data = &settings.country;
    cafeSettings[4].data = &settings.eula_agree;
    cafeSettings[5].data = &settings.eula_version;
    cafeSettings[6].data = &settings.initial_launch;
    cafeSettings[7].data = &settings.eco;
    cafeSettings[8].data = &settings.fast_boot;

    UCError write_err = UCWriteSysConfig(uc_handle, 9, cafeSettings);
    UCClose(uc_handle);
    if (write_err != 0)
        return SCI_STATUS_ERROR_WRITE;
    return SCI_STATUS_OK;
}

SCIStatus SCIInitCafeSettings(SCICafeSettings settings)
{
    UCHandle uc_handle = UCOpen();
    if (uc_handle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", uc_handle);
        UCClose(uc_handle);
        return SCI_STATUS_ERROR;
    }

    UCSysConfig cafeSettings[9];
    memcpy(cafeSettings, s_SCIDefaultCafeConfigs, sizeof(cafeSettings));

    cafeSettings[1].data = &settings.version;
    cafeSettings[2].data = &settings.language;
    cafeSettings[3].data = &settings.country;
    cafeSettings[4].data = &settings.eula_agree;
    cafeSettings[5].data = &settings.eula_version;
    cafeSettings[6].data = &settings.initial_launch;
    cafeSettings[7].data = &settings.eco;
    cafeSettings[8].data = &settings.fast_boot;

    UCError read_err = UCReadSysConfig(uc_handle, 9, cafeSettings);
    if (read_err != UC_ERROR_OK)
    {
        if (read_err != UC_ERROR_KEY_NOT_FOUND)
        {
            UCDeleteSysConfig(uc_handle, 1, cafeSettings);
            memcpy(&settings, &s_SCIDefaultCafeSettings, 0x18);
        }

        settings.version = 5;
        UCError write_err = UCWriteSysConfig(uc_handle, 9, cafeSettings);
        if (write_err < 0)
        {
            SCI_REPORT_ERROR("writing cafe.xml config file. (%d)", write_err);
            UCClose(uc_handle);
            return SCI_STATUS_ERROR_WRITE;
        }
    }
    BOOL verified = VerifyValueRange(settings);
    UCError write_err = UCWriteSysConfig(uc_handle, 9, cafeSettings);
    if (verified == 0 && write_err != UC_ERROR_OK)
    {
        SCI_REPORT_ERROR("writing cafe.xml config file. (%d)", write_err);
        UCClose(uc_handle);
        return SCI_STATUS_ERROR_WRITE;
    }
    UCClose(uc_handle);
    return SCI_STATUS_OK;
}

SCIStatus SCIGetParentalXMLVersion(uint16_t *outVersion)
{
    return _SCIReadSysConfig("parent.version", UC_DATATYPE_UNSIGNED_SHORT, 2, outVersion);
}

SCIStatus SCISetParentalXMLVersion(short version)
{
    return _SCIWriteSysConfig("parent.version", UC_DATATYPE_UNSIGNED_SHORT, 2, &version);
}

SCIStatus SCIGetParentalEnable(bool *outEnabled)
{
    SCIStatus status = _SCIReadSysConfig("parent.enable", UC_DATATYPE_UNSIGNED_BYTE, 1, outEnabled);
    *outEnabled = ValidateBool(outEnabled);
    return status;
}

SCIStatus SCISetParentalEnable(bool enabled)
{
    enabled = ValidateBool(&enabled);
    return _SCIWriteSysConfig("parent.enable", UC_DATATYPE_UNSIGNED_BYTE, 1, &enabled);
}

SCIStatus SCIGetParentalPinCode(char *outPin, int pinLenght)
{
    if (pinLenght < 5)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be over %d bytes.", 5);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIReadSysConfig("parent.pin_code", UC_DATATYPE_STRING, pinLenght, outPin);
}

SCIStatus SCISetParentalPinCode(char *pin, int pinLenght)
{
    if (pinLenght > 5)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be over %d bytes.", 5);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIWriteSysConfig("parent.pin_code", UC_DATATYPE_STRING, pinLenght, pin);
}

SCIStatus SCICheckParentalPinCode(const char *pinCode)
{
    char outPinCode[5];
    SCIStatus read_err = _SCIReadSysConfig("parent.pin_code", UC_DATATYPE_STRING, 5, outPinCode);
    if (read_err != SCI_STATUS_OK)
    {
        SCI_REPORT_ERROR("failed to get pin code from system config.");
        return read_err;
    }
    return strncmp(outPinCode, pinCode, 5) == 0 ? SCI_STATUS_OK : SCI_STATUS_ERROR;
}

SCIStatus SCIGetParentalSecQuestion(int8_t *outQuestionType)
{
    SCIStatus status = _SCIReadSysConfig("parent.sec_question", UC_DATATYPE_UNSIGNED_BYTE, 1, outQuestionType);
    VerifyQuestionType(outQuestionType);
    return status;
}

SCIStatus SCISetParentalSecQuestion(int8_t questionType)
{
    VerifyQuestionType(&questionType);
    return _SCIWriteSysConfig("parent.sec_question", UC_DATATYPE_UNSIGNED_BYTE, 1, &questionType);
}

SCIStatus SCIGetParentalSecAnswer(char *buffer, int bufferSize)
{
    if (bufferSize < 0x101)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be over %d bytes.", 0x101);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIReadSysConfig("parent.sec_answer", UC_DATATYPE_STRING, bufferSize, buffer);
}

SCIStatus SCISetParentalSecAnswer(char *buffer, int bufferSize)
{
    if (bufferSize > 0x101)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be under %d bytes.", 0x101);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIWriteSysConfig("parent.sec_answer", UC_DATATYPE_STRING, bufferSize, buffer);
}

SCIStatus SCIGetParentalEmailAddress(char *outEmail, int emailBufferSize)
{
    if(emailBufferSize < 0x401)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be over %d bytes.", 0x401);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIReadSysConfig("parent.email_address", UC_DATATYPE_STRING, emailBufferSize, outEmail);
}

SCIStatus SCISetParentalEmailAddress(char *email, int emailBufferSize)
{
    if(emailBufferSize > 0x401)
    {
        SCI_REPORT_ERROR("invalid size of buffer. It should be under %d bytes.", 0x401);
        return SCI_STATUS_ERROR_INVALID_BUFFER_SIZE;
    }
    return _SCIWriteSysConfig("parent.email_address", UC_DATATYPE_STRING, emailBufferSize, email);
}

SCIStatus SCIGetParentalPermitDeleteAll(bool *outPermit)
{
    SCIStatus status = _SCIReadSysConfig("parent.permit_delete_all", UC_DATATYPE_UNSIGNED_BYTE, 1, outPermit);
    *outPermit = ((uint8_t)*outPermit >= 1) &&  !((char)*outPermit < 0);
    return status;
}

SCIStatus SCISetParentalPermitDeleteAll(bool permit)
{
    // if (permit < 2) {
    //     if ((char)permit < 0)
    //         permit = 0;
    // }
    // else {
    //     permit = 1;
    // }
    permit = ValidateBool(&permit);
    return _SCIWriteSysConfig("parent.permit_delete_all", UC_DATATYPE_UNSIGNED_BYTE, 1, &permit);
}

SCIStatus SCIGetParentalRatingOrganization(uint32_t *outRating)
{
    SCIStatus status = _SCIReadSysConfig("parent.rating_organization", UC_DATATYPE_UNSIGNED_INT, 4, outRating);
    VerifyRatingOrganization(outRating);
    return status;
}

SCIStatus SCISetParentalRatingOrganization(uint32_t rating)
{
    VerifyRatingOrganization(&rating);
    return _SCIWriteSysConfig("parent.rating_organization", UC_DATATYPE_UNSIGNED_INT, 4, &rating);
}

SCIStatus SCIGetParentalSettings(SCIParentalSettings *outSettings)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        return SCI_STATUS_ERROR;
    }
    UCSysConfig parentalSettings[9];
    memcpy(parentalSettings, s_SCIDefaultParentalConfigs, sizeof(parentalSettings));
    parentalSettings[1].data = &outSettings->version;
    parentalSettings[2].data = &outSettings->enable;
    parentalSettings[3].data = &outSettings->pin_code;
    parentalSettings[4].data = &outSettings->sec_question;
    parentalSettings[5].data = &outSettings->sec_answer;
    parentalSettings[6].data = &outSettings->email_address;
    parentalSettings[7].data = &outSettings->permit_delete_all;
    parentalSettings[8].data = &outSettings->rating_organization;

    UCError ucError = UCReadSysConfig(ucHandle, 9, parentalSettings);
    if (ucError != UC_ERROR_OK)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_READ;
    }
    VerifyValueRange(*outSettings);
    UCClose(ucHandle);
    return SCI_STATUS_OK;
}

SCIStatus SCISetParentalSettings(SCIParentalSettings *settings)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        return SCI_STATUS_ERROR;
    }
    VerifyValueRange(*settings);
    UCSysConfig parentalSettings[9];
    memcpy(parentalSettings, s_SCIDefaultParentalConfigs, sizeof(parentalSettings));
    parentalSettings[1].data = &settings->version;
    parentalSettings[2].data = &settings->enable;
    parentalSettings[3].data = &settings->pin_code;
    parentalSettings[4].data = &settings->sec_question;
    parentalSettings[5].data = &settings->sec_answer;
    parentalSettings[6].data = &settings->email_address;
    parentalSettings[7].data = &settings->permit_delete_all;
    parentalSettings[8].data = &settings->rating_organization;

    UCError ucError = UCWriteSysConfig(ucHandle, 9, parentalSettings);
    UCClose(ucHandle);
    SCIStatus res = SCI_STATUS_OK;
    if (ucError < 0)
        res = SCI_STATUS_ERROR_WRITE;
    return res;
}

SCIStatus SCIInitParentalSettings(SCIParentalSettings *settings)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        return SCI_STATUS_ERROR;
    }

    UCSysConfig parentalSettings[9];
    memcpy(parentalSettings, s_SCIDefaultParentalConfigs, sizeof(parentalSettings));
    parentalSettings[1].data = &settings->version;
    parentalSettings[2].data = &settings->enable;
    parentalSettings[3].data = &settings->pin_code;
    parentalSettings[4].data = &settings->sec_question;
    parentalSettings[5].data = &settings->sec_answer;
    parentalSettings[6].data = &settings->email_address;
    parentalSettings[7].data = &settings->permit_delete_all;
    parentalSettings[8].data = &settings->rating_organization;

    UCError ucError = UCReadSysConfig(ucHandle, 9, parentalSettings);
    if (ucError < 0)
    {
        if (ucError != UC_ERROR_KEY_NOT_FOUND)
        {
            UCDeleteSysConfig(ucHandle, 9, parentalSettings);
            memcpy(settings, &s_SCIDefaultParentalSettings, sizeof(s_SCIDefaultParentalSettings));
        }
        settings->version = 9;
        ucError = UCWriteSysConfig(ucHandle, 9, parentalSettings);
        if (ucError != UC_ERROR_OK)
        {
            SCI_REPORT_ERROR("writing parent.xml config file. (%d)", ucError);
            UCClose(ucHandle);
            return SCI_STATUS_ERROR_WRITE;
        }
    }
    BOOL verifiy_success = VerifyValueRange(*settings);
    ucError = UCWriteSysConfig(ucHandle, 9, parentalSettings);
    if (verifiy_success == 0 && ucError != UC_ERROR_OK)
    {
        SCI_REPORT_ERROR("writing parent.xml config file. (%d)", ucError);
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_WRITE;
    }
    UCClose(ucHandle);
    return SCI_STATUS_OK;
}

SCIStatus SCIGetSystemSettings(MCPSysProdSettings *outSysSettings)
{
    int mcpHandle = MCP_Open();
    if (mcpHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get mcp handle(%d)", mcpHandle);
        MCP_Close(mcpHandle);
        return SCI_STATUS_ERROR;
    }
    MCPSysProdSettings sysSettings;
    MCPError mcpError = MCP_GetSysProdSettings(mcpHandle, &sysSettings);
    if (mcpError != 0)
    {
        SCI_REPORT_ERROR("MCP Error loading product information(%d)", mcpError);
        MCP_Close(mcpHandle);
        return SCI_STATUS_ERROR_READ;
    }
    MCP_Close(mcpHandle);
    memcpy(outSysSettings, &sysSettings, sizeof(sysSettings));
    return SCI_STATUS_OK;
}

SCIStatus SCIGetSystemProdArea(MCPRegion *outProdArea)
{
    MCPSysProdSettings sysSettings;
    SCIStatus status = SCIGetSystemSettings(&sysSettings);
    *outProdArea = sysSettings.product_area;
    return status;
}

SCIStatus SCIGetPlatformRegion(MCPRegion *outPlatformRegion)
{
    return SCIGetSystemProdArea(outPlatformRegion);
}

SCIStatus SCIGetSystemGameRegion(MCPRegion *outGameRegion)
{
    MCPSysProdSettings sysSettings;
    SCIStatus status = SCIGetSystemSettings(&sysSettings);
    *outGameRegion = sysSettings.game_region;
    return status;
}

SCIStatus _SCIReadSysConfig(const char *name, UCDataType dataType, size_t dataSize, void *data)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        UCClose(ucHandle);
        return SCI_STATUS_ERROR;
    }
    UCSysConfig conf = {
        { 0 },
        0x777,
        dataType,
        UC_ERROR_OK,
        dataSize,
        data
    };
    memcpy(conf.name, name, 64);

    UCError ucError = UCReadSysConfig(ucHandle, 1, &conf);
    if (ucError == UC_ERROR_OK)
    {
        UCClose(ucHandle);
        return SCI_STATUS_OK;
    }
    if (ucError == UC_ERROR_KEY_NOT_FOUND)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_KEY_NOT_FOUND;
    }
    if (ucError == UC_ERROR_FILE_OPEN)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_OPEN;
    }
    SCI_REPORT_ERROR("Couldn\'t read from system config file (UC status=%d)", ucError);
    UCClose(ucHandle);
    return SCI_STATUS_ERROR_READ;
}

SCIStatus _SCIWriteSysConfig(const char *name, UCDataType dataType, size_t dataSize, void *data)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        UCClose(ucHandle);
        return SCI_STATUS_ERROR;
    }
    UCSysConfig conf = {
        { 0 },
        0x777,
        dataType,
        UC_ERROR_OK,
        dataSize,
        data
    };
    memcpy(conf.name, name, 64);

    UCError ucError = UCWriteSysConfig(ucHandle, 1, &conf);
    if (ucError == UC_ERROR_OK)
    {
        UCClose(ucHandle);
        return SCI_STATUS_OK;
    }
    if (ucError == UC_ERROR_KEY_NOT_FOUND)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_KEY_NOT_FOUND;
    }
    if (ucError == UC_ERROR_FILE_OPEN)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_OPEN;
    }
    SCI_REPORT_ERROR("Couldn\'t write to system config file (UC status=%d)", ucError);
    UCClose(ucHandle);
    return SCI_STATUS_ERROR_WRITE;
}

SCIStatus _SCIDeleteSysConfig(const char *name, UCDataType dataType, size_t dataSize, void *data)
{
    UCHandle ucHandle = UCOpen();
    if (ucHandle < 0)
    {
        SCI_REPORT_ERROR("Couldn\'t get UC handle(%d)", ucHandle);
        UCClose(ucHandle);
        return SCI_STATUS_ERROR;
    }
    UCSysConfig conf = {
        { 0 },
        0x777,
        dataType,
        UC_ERROR_OK,
        dataSize,
        data
    };
    memcpy(conf.name, name, 64);

    UCError ucError = UCDeleteSysConfig(ucHandle, 1, &conf);
    if (ucError == UC_ERROR_KEY_NOT_FOUND)
    {
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_KEY_NOT_FOUND;
    }
    if (ucError < 0)
    {
        SCI_REPORT_ERROR("Removing %s config file. (UC status=%d)", name, ucError);
        UCClose(ucHandle);
        return SCI_STATUS_ERROR_WRITE;
    }
    UCClose(ucHandle);
    return SCI_STATUS_OK;
}