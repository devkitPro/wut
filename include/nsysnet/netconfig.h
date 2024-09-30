#pragma once

#include <wut.h>
#include <wut_rplwrap.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * \defgroup nsysnet_netconfig
 * \ingroup nsysnet
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef uint16_t NetConfEthCfgSpeed;
typedef uint16_t NetConfEthCfgDuplex;
typedef uint16_t NetConfEthCfgNegotiation;
typedef uint16_t NetConfWifiPrivacyMode;
typedef uint16_t NetConfProxyAuthType;
typedef uint16_t NetConfProxyStatus;
typedef uint16_t NetConfInterfaceType;
typedef uint16_t NetConfLinkState;
typedef uint16_t NetConfOperState;
typedef uint16_t NetConfAdminState;

typedef struct NetConfAllProfileState NetConfAllProfileState;
typedef struct NetConfEthCfg NetConfEthCfg;
typedef struct NetConfProxyConfig NetConfProxyConfig;
typedef struct NetConfValidFlags NetConfValidFlags;
typedef struct NetConfWifiConfig NetConfWifiConfig;
typedef struct NetConfOpt NetConfOpt;
typedef struct NetConfIPv4Info NetConfIPv4Info;
typedef struct NetConfMACAddr NetConfMACAddr;
typedef struct NetConfCfg NetConfCfg;
typedef struct NetConfAOSSConfig NetConfAOSSConfig;
typedef struct NetConfWifiConfigData NetConfWifiConfigData;
typedef struct NetConfWifiConfigDataPrivacy NetConfWifiConfigDataPrivacy;
typedef struct NetConfInterface NetConfInterface;
typedef struct NetConfIfState NetConfIfState;

typedef enum NetConfInterfaceTypeEnum {
    NET_CONF_INTERFACE_TYPE_WIFI = 0,
    NET_CONF_INTERFACE_TYPE_ETHERNET = 1,
} NetConfInterfaceTypeEnum;

typedef enum NetConfEthCfgSpeedEnum {
    NET_CONF_ETH_CFG_SPEED_10M = 10,
    NET_CONF_ETH_CFG_SPEED_100M = 100,
} NetConfEthCfgSpeedEnum;

typedef enum NetConfEthCfgDuplexEnum {
    NET_CONF_ETH_CFG_DUPLEX_HALF = 1,
    NET_CONF_ETH_CFG_DUPLEX_FULL = 2,
} NetConfEthCfgDuplexEnum;

typedef enum NetConfEthCfgNegotiationEnum {
    NET_CONF_ETH_CFG_NEGOTIATION_MANUAL = 1,
    NET_CONF_ETH_CFG_NEGOTIATION_AUTO = 2,
} NetConfEthCfgNegotiationEnum;

typedef enum NetConfIPv4Mode {
    NET_CONF_IPV4_MODE_DHCP = 0,
    NET_CONF_IPV4_MODE_MANUAL = 2,
} NetConfIPv4Mode;

typedef enum NetConfWifiPrivacyModeEnum {
    NET_CONF_WIFI_PRIVACY_MODE_NONE = 0,
    NET_CONF_WIFI_PRIVACY_MODE_WEP = 1,
    NET_CONF_WIFI_PRIVACY_MODE_WPA2_PSK_TKIP = 3,
    NET_CONF_WIFI_PRIVACY_MODE_WPA_PSK_TKIP = 4,
    NET_CONF_WIFI_PRIVACY_MODE_WPA2_PSK_AES = 5,
    NET_CONF_WIFI_PRIVACY_MODE_WPA_PSK_AES = 6,
} NetConfWifiPrivacyModeEnum;

typedef enum NetConfProxyAuthTypeEnum {
    NET_CONF_PROXY_AUTH_TYPE_NONE = 0,
    NET_CONF_PROXY_AUTH_TYPE_BASIC_AUTHENTICATION = 1,
} NetConfProxyAuthTypeEnum;

typedef enum NetConfProxyStatusEnum {
    NET_CONF_PROXY_DISABLED = 0,
    NET_CONF_PROXY_ENABLED = 1,
} NetConfProxyStatusEnum;

typedef enum NetConfLinkStateEnum {
    NET_CONF_LINK_STATE_UP = 1,
    NET_CONF_LINK_STATE_DOWN = 2,
    NET_CONF_LINK_STATE_NEGOTIATE = 3,
} NetConfLinkStateEnum;

typedef enum NetConfOperStateEnum {
    NET_CONF_OPER_STATE_UP = 1,
    NET_CONF_OPER_STATE_DOWN = 2,
} NetConfOperStateEnum;

typedef enum NetConfAdminStateEnum {
    NET_CONF_ADMIN_STATE_UP = 1,
    NET_CONF_ADMIN_STATE_DOWN = 2,
} NetConfAdminStateEnum;

typedef enum NetConfProfile {
    NET_CONF_PROFILE_0 = 0,
    NET_CONF_PROFILE_1 = 1,
    NET_CONF_PROFILE_2 = 2,
    NET_CONF_PROFILE_3 = 3,
    NET_CONF_PROFILE_4 = 4,
    NET_CONF_PROFILE_5 = 5,
} NetConfProfile;

struct NetConfAllProfileState {
    WUT_UNKNOWN_BYTES(0x18);
};
WUT_CHECK_SIZE(NetConfAllProfileState, 0x18);

struct WUT_PACKED NetConfEthCfg {
    NetConfEthCfgSpeed speed;
    NetConfEthCfgDuplex duplex;
    NetConfEthCfgNegotiation negotiation;
    WUT_PADDING_BYTES(2);
};
WUT_CHECK_OFFSET(NetConfEthCfg, 0x00, speed);
WUT_CHECK_OFFSET(NetConfEthCfg, 0x02, duplex);
WUT_CHECK_OFFSET(NetConfEthCfg, 0x04, negotiation);
WUT_CHECK_SIZE(NetConfEthCfg, 0x8);

struct NetConfIPv4Info {
    NetConfIPv4Mode mode;
    uint32_t addr;
    uint32_t netmask;
    uint32_t nexthop; // gateway
    uint32_t ns1; // dns 1
    uint32_t ns2; // dns 2
};
WUT_CHECK_SIZE(NetConfIPv4Info, 0x18);

struct NetConfMACAddr {
    uint8_t MACAddr[0x6];
};
WUT_CHECK_SIZE(NetConfMACAddr, 0x6);

struct NetConfProxyConfig {
    NetConfProxyStatus use_proxy; // true/false
    uint16_t port;
    WUT_UNKNOWN_BYTES(0x02);
    NetConfProxyAuthType auth_type;
    char host[0x80];
    char username[0x80]; // only 0x20 bytes usable
    char password[0x40]; // only 0x20 bytes usable
    char noproxy_hosts[0x80]; // not used
};
WUT_CHECK_SIZE(NetConfProxyConfig, 0x1c8);

struct NetConfValidFlags {
    WUT_UNKNOWN_BYTES(0x18);
};
WUT_CHECK_SIZE(NetConfValidFlags, 0x18);

struct WUT_PACKED NetConfWifiConfigDataPrivacy {
    NetConfWifiPrivacyMode mode;
    WUT_PADDING_BYTES(2);
    uint16_t aes_key_len;
    uint8_t aes_key[0x40];
    WUT_PADDING_BYTES(2);
};
WUT_CHECK_OFFSET(NetConfWifiConfigDataPrivacy, 0x00, mode);
WUT_CHECK_OFFSET(NetConfWifiConfigDataPrivacy, 0x04, aes_key_len);
WUT_CHECK_OFFSET(NetConfWifiConfigDataPrivacy, 0x06, aes_key);
WUT_CHECK_SIZE(NetConfWifiConfigDataPrivacy, 0x48);

struct WUT_PACKED NetConfWifiConfigData {
    char ssid[0x20];
    uint16_t ssidlength;
    WUT_PADDING_BYTES(2);
    NetConfWifiConfigDataPrivacy privacy;
};
WUT_CHECK_OFFSET(NetConfWifiConfigData, 0x00, ssid);
WUT_CHECK_OFFSET(NetConfWifiConfigData, 0x20, ssidlength);
WUT_CHECK_OFFSET(NetConfWifiConfigData, 0x24, privacy);
WUT_CHECK_SIZE(NetConfWifiConfigData, 0x6C);

struct NetConfWifiConfig {
    uint16_t config_method;
    WUT_PADDING_BYTES(2);
    NetConfWifiConfigData config;
};
WUT_CHECK_SIZE(NetConfWifiConfig, 0x70);

struct NetConfOpt {
    WUT_UNKNOWN_BYTES(0x2c1);
};
WUT_CHECK_SIZE(NetConfOpt, 0x2c1);

struct WUT_PACKED NetConfInterface {
    uint16_t if_index;
    uint16_t if_state;
    uint32_t if_mtu;
    NetConfIPv4Info ipv4Info;
};
WUT_CHECK_OFFSET(NetConfInterface, 0x00, if_index);
WUT_CHECK_OFFSET(NetConfInterface, 0x02, if_state);
WUT_CHECK_OFFSET(NetConfInterface, 0x04, if_mtu);
WUT_CHECK_OFFSET(NetConfInterface, 0x08, ipv4Info);
WUT_CHECK_SIZE(NetConfInterface, 0x20);

struct NetConfCfg {
    NetConfInterface wl0;
    NetConfWifiConfig wifi;
    NetConfInterface eth0;
    NetConfEthCfg ethCfg;
    NetConfProxyConfig proxy;
};
WUT_CHECK_OFFSET(NetConfCfg, 0x0, wl0);
WUT_CHECK_OFFSET(NetConfCfg, 0x20, wifi);
WUT_CHECK_OFFSET(NetConfCfg, 0x90, eth0);
WUT_CHECK_OFFSET(NetConfCfg, 0xB0, ethCfg);
WUT_CHECK_OFFSET(NetConfCfg, 0xB8, proxy);
WUT_CHECK_SIZE(NetConfCfg, 0x280);

struct WUT_PACKED NetConfAOSSConfig {
    NetConfWifiConfigData config[4];
};
WUT_CHECK_SIZE(NetConfAOSSConfig, 0x1b0);

struct NetConfIfState {
    uint16_t if_state;
    NetConfLinkState linkstate;
    NetConfOperState operstate;
    WUT_PADDING_BYTES(2);
};
WUT_CHECK_SIZE(NetConfIfState, 0x8);

int
netconf_init();

int
netconf_close();

int
netconf_delete_profile(NetConfProfile id);

int
netconf_get_all_profile_state(NetConfAllProfileState *state);

/**
 * Returns the currently used IP address of the console if the given interface matches
 * the used interface.
 */
int
netconf_get_assigned_address(NetConfInterfaceType interface,
                             uint32_t *assignedAddress);

/**
 * Returns the currently used DNS of the console if the given interface matches
 * the used interface.
 */
int
netconf_get_assigned_dns(NetConfInterfaceType interface,
                         uint32_t *dns1,
                         uint32_t *dns2);

/**
 * Returns the currently used gateway of the console if the given interface matches
 * the used interface.
 */
int
netconf_get_assigned_gateway(NetConfInterfaceType unk1,
                             uint32_t *gateway);

/**
 * Returns the currently used subnet of the console if the given interface matches
 * the used interface.
 */
int
netconf_get_assigned_subnet(NetConfInterfaceType unk1,
                            uint32_t *subnet);

/**
 * Returns the manually set DNS servers of the loaded config if the given
 * interface matches the used interface.
 */
int
netconf_get_dns(NetConfInterfaceType unk1,
                uint32_t *dns1,
                uint32_t *dns2);

int
netconf_get_eth_cfg(NetConfEthCfg *outCfg);

NetConfAdminState
netconf_get_if_adminstate(NetConfInterfaceType interface);

/**
 * Returns the WIFI IPv4 Info of the loaded config
 */
int
netconf_get_if_ipv4_info(NetConfIPv4Info *info);

/**
 * Returns the IPv4 Info of the loaded config for the given interface
 */
int
netconf_get_if_ipv4_info_ex(NetConfInterfaceType interface, NetConfIPv4Info *info);

NetConfLinkState
netconf_get_if_linkstate(NetConfInterfaceType interface);

int
netconf_get_if_macaddr(NetConfInterfaceType interface,
                       NetConfMACAddr *info);

NetConfOperState
netconf_get_if_operstate(NetConfInterfaceType interface);

int
netconf_get_ifstate(NetConfInterfaceType interface, NetConfIfState *ifState);

int
netconf_get_interface_mtu(NetConfInterfaceType NetConfInterfaceType, uint32_t *mtu);

int
netconf_get_last_wifi_link_error(uint32_t *lastError);

int
netconf_get_profile_state(NetConfInterfaceType interface,
                          uint32_t *profileState);

int
netconf_get_proxy_config(NetConfProxyConfig *proxyConfig);

int
SOGetProxyConfig(NetConfProxyConfig *config);

/**
 * Return the current NetConfCfg
 */
int
netconf_get_running(NetConfCfg *running);

/**
 * Gets the default profileId
 */
int
netconf_get_startup_profile_id();

int
netconf_get_valid_flags(NetConfValidFlags *validFlags);

int
netconf_get_wifi_cfg(NetConfWifiConfig *wifiConfig);

/**
 * Not implemented on IOSU side
 */
int
netconf_getopt(uint16_t unk1,
               NetConfOpt *buffer,
               uint32_t *bufferSize);

/**
 * Read a profile into memory without using it.
 */
int
netconf_nv_read(NetConfProfile profileId,
                NetConfCfg *data);

/**
 * Write a profile from buffer.
 */
int
netconf_nv_write(NetConfProfile profileId,
                 NetConfCfg *data);

/**
 * Load a profile into memory and use it.
 */
int
netconf_nv_load(NetConfProfile profileId);

/**
 * Save the loaded profile from memory into a profile
 */
int
netconf_nv_store(NetConfProfile profileId);

int
netconf_read_aoss_config(NetConfProfile profileId,
                         NetConfAOSSConfig *data);

int
netconf_write_aoss_config(NetConfProfile profileId,
                          NetConfAOSSConfig *data);

int
netconf_read_compat_profile_id(uint32_t *outProfileId);


int
netconf_set_dns(NetConfInterfaceType interface,
                uint32_t *dns1,
                uint32_t *dns2);

int
netconf_set_eth_cfg(NetConfEthCfg *config);

int
netconf_set_if_admin_state(NetConfInterfaceType interface,
                           NetConfAdminStateEnum unk2);

int
netconf_set_if_ipv4_info(NetConfIPv4Info *info);

int
netconf_set_if_ipv4_info_ex(NetConfInterfaceType interface,
                            NetConfIPv4Info *info);

int
netconf_set_interface_mtu(NetConfInterfaceType interface,
                          uint32_t mtu);

int
netconf_set_proxy_config(NetConfProxyConfig *config);

int
netconf_set_running(NetConfCfg *config);

/**
 * Sets the default profileId
 */
int
netconf_set_startup_profile_id(uint32_t profileId);

int
netconf_set_valid_flag(uint32_t unk1,
                       uint32_t unk2);

int
netconf_set_wifi_cfg(NetConfWifiConfig *config);

/**
 * DEBUG mode only
 */
int
netconf_setopt(uint16_t unk1,
               NetConfOpt *buffer,
               uint32_t *bufferSize);

int
netconf_write_compat_profile_id(uint32_t unk1);

#ifdef __cplusplus
}
#endif

/** @} */
