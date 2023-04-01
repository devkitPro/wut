#pragma once

#include <wut.h>

/**
 * \defgroup coreinit_bsp BSP
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t BSPError;
typedef uint32_t BSPHardwareVersion;
typedef uint32_t BSPConsoleTypeRaw;

typedef enum BSPErrors
{
    BSP_ERROR_OK                    =   0,
    BSP_ERROR_IOS_ERROR             =   0x40,
    BSP_ERROR_RESPONSE_TOO_LARGE    =   0x80,
} BSPErrors;
WUT_CHECK_SIZE(BSPErrors, 4);

typedef enum BSPHardwareVersions
{
    BSP_HARDWARE_VERSION_UNKNOWN                        =   0x00000000,

    // vWii Hardware Versions
    BSP_HARDWARE_VERSION_HOLLYWOOD_ENG_SAMPLE_1         =   0x00000001,
    BSP_HARDWARE_VERSION_HOLLYWOOD_ENG_SAMPLE_2         =   0x10000001,
    BSP_HARDWARE_VERSION_HOLLYWOOD_PROD_FOR_WII         =   0x10100001,
    BSP_HARDWARE_VERSION_HOLLYWOOD_CORTADO              =   0x10100008,
    BSP_HARDWARE_VERSION_HOLLYWOOD_CORTADO_ESPRESSO     =   0x1010000C,
    BSP_HARDWARE_VERSION_BOLLYWOOD                      =   0x20000001,
    BSP_HARDWARE_VERSION_BOLLYWOOD_PROD_FOR_WII         =   0x20100001,

    // WiiU Hardware Versions
    BSP_HARDWARE_VERSION_LATTE_A11_EV            =   0x21100010,
    BSP_HARDWARE_VERSION_LATTE_A11_CAT           =   0x21100020,
    BSP_HARDWARE_VERSION_LATTE_A12_EV            =   0x21200010,
    BSP_HARDWARE_VERSION_LATTE_A12_CAT           =   0x21200020,
    BSP_HARDWARE_VERSION_LATTE_A2X_EV            =   0x22100010,
    BSP_HARDWARE_VERSION_LATTE_A2X_CAT           =   0x22100020,
    BSP_HARDWARE_VERSION_LATTE_A3X_EV            =   0x23100010,
    BSP_HARDWARE_VERSION_LATTE_A3X_CAT           =   0x23100020,
    BSP_HARDWARE_VERSION_LATTE_A3X_CAFE          =   0x23100028,
    BSP_HARDWARE_VERSION_LATTE_A4X_EV            =   0x24100010,
    BSP_HARDWARE_VERSION_LATTE_A4X_CAT           =   0x24100020,
    BSP_HARDWARE_VERSION_LATTE_A4X_CAFE          =   0x24100028,
    BSP_HARDWARE_VERSION_LATTE_A5X_EV            =   0x25100010,
    BSP_HARDWARE_VERSION_LATTE_A5X_EV_Y          =   0x25100011,
    BSP_HARDWARE_VERSION_LATTE_A5X_CAT           =   0x25100020,
    BSP_HARDWARE_VERSION_LATTE_A5X_CAFE          =   0x25100028,
    BSP_HARDWARE_VERSION_LATTE_B1X_EV            =   0x26100010,
    BSP_HARDWARE_VERSION_LATTE_B1X_EV_Y          =   0x26100011,
    BSP_HARDWARE_VERSION_LATTE_B1X_CAT           =   0x26100020,
    BSP_HARDWARE_VERSION_LATTE_B1X_CAFE          =   0x26100028
} BSPHardwareVersions;
WUT_CHECK_SIZE(BSPHardwareVersions, 4);

BSPError
bspInitializeShimInterface();

BSPError
bspShutdownShimInterface();

BSPError
bspGetHardwareVersion(BSPHardwareVersion *version);

BSPError
bspGetConsoleTypeRaw(BSPConsoleTypeRaw *consoleTypeRaw);


BSPError
bspInitialize(const char *entityName,
              uint32_t instance,
              const char *attributeName,
              uint32_t optionSize,
              void *pOptions);

BSPError
bspShutdown(const char *entity,
            uint8_t instance,
            const char *attribute);

BSPError
bspGetEntityVersion(const char *entityName,
                    uint32_t *entityVersion);

BSPError
bspRead(const char *entity,
        uint8_t instance,
        const char *attribute,
        size_t size,
        void *ptr);

BSPError
bspWrite(const char *entity,
         uint8_t instance,
         const char *attribute,
         size_t size,
         void *ptr);

BSPError
bspQuery(const char *entity,
         uint8_t instance,
         const char *attribute,
         size_t size,
         void *ptr);

#ifdef __cplusplus
}
#endif

/** @} */
